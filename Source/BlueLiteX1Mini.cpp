/*
    BlueLiteX1Mini.cpp

    Low Level Access to X1 Mini 
*/

#include "IntelHexReader.h"
#include "BlueLiteX1Mini.h"


//==============================================================================
namespace BlueLiteHelpers
{
    const int DmxPageSize = 32;
    const int DmxAllPages = (512 / DmxPageSize);
    
    typedef enum {
        DataPacketType = 1,
        TimePacketType = 2,
        ConfigPacketType = 3
    } PacketType;

#pragma pack(push)
#pragma pack(1)
    
    typedef struct {
        uint8 type;     // Packet type
        uint8 dmx1;     // DMX Max Page counts
        uint8 dmx2;
        uint8 dmx3;
        uint8 dmx4;
        uint8 inBaseH;  // Input base
        uint8 inBaseL;
        uint8 rsvd[57];
    } ConfigPacket;

#pragma pack(pop)
    
}


//==============================================================================
//==============================================================================
Result BlueLiteX1Mini::open (int index)
{
    // Try to open the physical device
    Result r = usbDevice.openDevice (index);
    if (r.wasOk())
    {    
        // Put the chip into an alternate interface
        r = usbDevice.setInterfaceAlternateSetting (1);
        if (r.wasOk())
        {
            // Load the firmware
            r = loadFirmware ("minifirm_hex");
            if (r.wasOk())
            {                
                r = sendConfig();
                if (r.wasOk())
                    return r;
            }
        }
        
        close();
    }
        
    return r;
}

//==============================================================================
void BlueLiteX1Mini::close()
{
    if (usbDevice.isOpen())
    {
        loadFirmware ("X1IDLE_HEX");
        usbDevice.closeDevice();
    }
}

//==============================================================================
Result BlueLiteX1Mini::loadFirmware (const String& firmware)
{
    uint8 b = 1;            
    Result r = usbDevice.controlTransfer(UsbDevice::VendorOut, 0xa0, 0xe600, 0, &b, 1, 500);
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
                                       (uint8*)block.getData(), block.getSize(), 500);
        
        if (! r.wasOk())
            return r;
    }
    
    b = 0;
    r = usbDevice.controlTransfer(UsbDevice::VendorOut, 0xa0, 0xe600, 0, &b, 1, 500);
    if (! r.wasOk())
        return r;
    
    return Result::ok();
}

//==============================================================================
Result BlueLiteX1Mini::sendConfig()
{
    // Set the configuration
    BlueLiteHelpers::ConfigPacket conf;
    zerostruct<BlueLiteHelpers::ConfigPacket> (conf);
    conf.type = BlueLiteHelpers::ConfigPacketType;
    conf.dmx1 = BlueLiteHelpers::DmxAllPages;
    conf.dmx2 = BlueLiteHelpers::DmxAllPages;
    conf.dmx3 = BlueLiteHelpers::DmxAllPages;
    conf.dmx4 = BlueLiteHelpers::DmxAllPages;
    conf.inBaseH = 0;
    conf.inBaseL = 1;

    int transferred;
    Result r = usbDevice.bulkTransfer (UsbDevice::EndOut2, 
                                       (uint8*)(&conf), sizeof (conf), 
                                       transferred, 500);
    if (! r.wasOk())
        return r;
    
    return Result::ok();
}

