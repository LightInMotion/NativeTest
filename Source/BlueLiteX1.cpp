/*
    BlueLiteX1.cpp

    Low Level Access to BlueLite X1
*/

#include "BlueLiteUsb.h"
#include "IntelHexReader.h"
#include "BlueLiteX1.h"

//==============================================================================
BlueLiteX1::BlueLiteX1()
    : maxDevice (BlueLite::MaxDevice),
      dmxDataSize (BlueLite::X1DmxDataSize),
      dmxInputSize (BlueLite::DmxInputSize),
      usbDevice (0x4a9, 0x2109, 0, "BlueLite X1"),
      dmxPacket (BlueLite::X1DmxDataSize + sizeof(BlueLite::DataPacket)),
      dmxInput (BlueLite::DmxInputSize),
      timeInput (10)
{
    // Assume inputs are 0
    dmxInput.fillWith (0);
    
    // We'll send this same packet again and again.
    dmxPacket.fillWith (0);
    dmxPacket[0] = BlueLite::DataType;
}

BlueLiteX1::~BlueLiteX1()
{
    if (usbDevice.isOpen())
        usbDevice.closeDevice();
}

//==============================================================================
Result BlueLiteX1::open (int index)
{
    // In range
    if (index < 0 || index >= maxDevice)
        return Result::fail ("Only devices in the range of 0 to " +
                             String(maxDevice) + " can be opened.");
    
    // Try to open the physical device
    Result r = usbDevice.openDevice (index);
    if (r.wasOk())
    {   
        // Put the chip into an alternate interface
        r = usbDevice.setInterfaceAlternateSetting (1);
        if (r.wasOk())
        {
            // Load the firmware
            r = loadFirmware ("X1FIRM_HEX");
            if (r.wasOk())
            {
                // Send the DMX configuration
                r = sendConfig();
                if (r.wasOk())
                {
                    // Initialize Time
                    r = sendTime();
                    if (r.wasOk())
                    {
                        usbDevice.addBulkReadListener (this, UsbDevice::EndIn1, 64);
                        usbDevice.addBulkReadListener (this, UsbDevice::EndIn2, 64);
                        return r;
                    }
                }
            }
        }
        
        close();
    }
    
    return r;
}

//==============================================================================
void BlueLiteX1::close()
{
    if (usbDevice.isOpen())
    {
        loadFirmware ("X1IDLE_HEX");
        usbDevice.closeDevice();
    }
}

//==============================================================================
Result BlueLiteX1::updateDmxData (uint16 offset, const MemoryBlock& newData)
{
    if ((offset + newData.getSize()) > dmxDataSize)
        return Result::fail ("Data is larger than universe.");
    
    dmxPacket.copyFrom (newData.getData(), offset + sizeof(BlueLite::DataPacket), newData.getSize());
    
    int transferred;
    Result r = usbDevice.bulkTransfer (UsbDevice::EndOut2, (uint8*) dmxPacket.getData(),
                                       dmxPacket.getSize(), transferred);
    
    if (transferred != dmxPacket.getSize())
        Logger::outputDebugString ("Undersized bulk transfer of dmx data");
    
    return r;
}

//==============================================================================
MemoryBlock BlueLiteX1::readDmxData()
{
    return MemoryBlock ((uint8*) dmxPacket.getData() + sizeof(BlueLite::DataPacket), 
                        dmxDataSize);
}

//==============================================================================
void BlueLiteX1::addInputEvent (BlueLiteEvent* event)
{
    inputEventList.addIfNotAlreadyThere (event);
}

void BlueLiteX1::removeInputEvent (BlueLiteEvent* event)
{
    inputEventList.removeObject (event);
}

//==============================================================================
MemoryBlock BlueLiteX1::readDmxInput()
{
    const ScopedLock lock (inputEventList.getLock());
    return (MemoryBlock (dmxInput));
}

//==============================================================================
void BlueLiteX1::addTimeEvent (BlueLiteEvent* event)
{
    timeEventList.addIfNotAlreadyThere (event);
}

void BlueLiteX1::removeTimeEvent (BlueLiteEvent* event)
{
    timeEventList.removeObject (event);
}

//==============================================================================
MemoryBlock BlueLiteX1::readTimeInput()
{
    const ScopedLock lock (timeEventList.getLock());
    return (MemoryBlock (timeInput));
}

//==============================================================================
Result BlueLiteX1::loadFirmware (const String& firmware)
{
    uint8 b = 1;            
    Result r = usbDevice.controlTransfer(UsbDevice::VendorOut, 0xa0, 0x7f92, 0, &b, 1);
    if (! r.wasOk())
        return r;
    
    IntelHexReader hexReader (firmware);
    if (hexReader.getTotalLength() == 0)
        return Result::fail ("Could not find firmware to download to device.");
    
    MemoryBlock block;
    uint16 address;
    while (hexReader.readLineAsBinary (block, address))
    {
        r = usbDevice.controlTransfer (UsbDevice::VendorOut, 0xa0, address, 0,
                                       (uint8*)block.getData(), block.getSize());
        
        if (! r.wasOk())
            return r;
    }
    
    b = 0;
    r = usbDevice.controlTransfer(UsbDevice::VendorOut, 0xa0, 0x7f92, 0, &b, 1);
    if (! r.wasOk())
        return r;
    
    return Result::ok();
}

//==============================================================================
Result BlueLiteX1::sendConfig()
{
    // Set the configuration
    BlueLite::ConfigPacket conf;
    zerostruct<BlueLite::ConfigPacket> (conf);
    conf.type = BlueLite::ConfigType;
    conf.dmx1 = BlueLite::DmxAllPages;
    conf.dmx2 = BlueLite::DmxAllPages;
    conf.dmx3 = BlueLite::DmxAllPages;
    conf.dmx4 = BlueLite::DmxAllPages;
    conf.inBaseH = 0;
    conf.inBaseL = 1;
    
    int transferred;
    Result r = usbDevice.bulkTransfer (UsbDevice::EndOut2, 
                                       (uint8*)(&conf), sizeof (conf), transferred);
    
    if (! r.wasOk())
        return r;
    
    return Result::ok();
}

//==============================================================================
Result BlueLiteX1::sendTime()
{
    BlueLite::TimePacket time;
    zerostruct<BlueLite::TimePacket> (time);
    time.type       = BlueLite::TimeType;
    time.stype      = BlueLite::Smpte30fps;
    time.command    = BlueLite::WriteCmd;
    time.control    = BlueLite::BlinkControl; //  BlueLite::FreezeControl | BlueLite::NoPhysControl;
    
    int transferred;
    return usbDevice.bulkTransfer (UsbDevice::EndOut2, (uint8*)&time, 
                                   sizeof(time), transferred);
}

//==============================================================================
void BlueLiteX1::bulkDataRead (UsbDevice::EndPoint endPoint, 
                                   const uint8* data, int size)
{
    {
        if (endPoint == UsbDevice::EndIn1)
        {
            if (size >= 10)
            {
                const ScopedLock lock (timeEventList.getLock());
                
                timeInput.copyFrom (data, 0, 10);
                
                int listSize = timeEventList.size();
                for (int n = 0; n < listSize; ++n)
                    timeEventList[n]->signal();
            }
        }
        else if (endPoint == UsbDevice::EndIn2)
        {
            if (size >= dmxInputSize)
            {
                const ScopedLock lock (inputEventList.getLock());
                
                dmxInput.copyFrom (data, 0, dmxInputSize);
                
                int listSize = inputEventList.size();
                for (int n = 0; n < listSize; ++n)
                    inputEventList[n]->signal();
            }
        }
    }
}
