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
    
    enum PacketType 
    {
        DataType = 1,
        TimeType = 2,
        ConfigType = 3
    };
    
    enum TimeCommand
    {
        IdleCmd = 0,
        WriteCmd = 1,
        ReadCmd = 2
    };
    
    enum TimeControl
    {
        FreezeControl = 1,
        NoPhysControl = 2,
        BlinkControl = 4
    };
    
    enum SmpteFlags
    {
        SmpteSync = 0x20,
        SmpteReading = 0x40
    };
    
    enum SmpteType
    {
        Smpte30fps = 1,
        SmpteDropFrame = 2,
        Smpte25fps = 3,
        Smpte24fps = 4
    };

#pragma pack(push)
#pragma pack(1)
    
    struct DataPacket
    {
        uint8	type;		// = DataPacketType
        uint8	rsvd[63];
    };
    
    struct TimePacket
    {
        uint8	type;		// = TimePacketType
        uint8	command;	// 0=idle, 1=write, 2=read
        uint8	control;	// 1= freeze (no inc), 2= no physical output, 4= blink
        uint8	htens;      // Time
        uint8	hunits;     // We split time this way so we can encode user bits
        uint8	mtens;
        uint8	munits;
        uint8	stens;
        uint8	sunits;
        uint8	ftens;
        uint8	funits;
        uint8	stype;      // Time Type, 1=30, 2=df, 3=25, 4=24
        uint8	rsvd[52];
    };

    struct ConfigPacket
    {
        uint8 type;         // = ConfigPacketType
        uint8 dmx1;         // DMX Max Page counts
        uint8 dmx2;
        uint8 dmx3;
        uint8 dmx4;
        uint8 inBaseH;      // Input base
        uint8 inBaseL;
        uint8 rsvd[57];
    };

#pragma pack(pop)
    
}


//==============================================================================
//==============================================================================
Result BlueLiteX1Mini::open (int index)
{
    // In range
    if (index < 0 || index > 15)
        return Result::fail ("Only devices in the range of 0 to 15 can be opened.");
    
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
                // Send the DMX configuration
                r = sendConfig();
                if (r.wasOk())
                {
                    // Initialize Time
                    BlueLiteHelpers::TimePacket time;
                    zerostruct<BlueLiteHelpers::TimePacket> (time);
                    time.type       = BlueLiteHelpers::TimeType;
                    time.stype      = BlueLiteHelpers::Smpte30fps;
                    time.command    = BlueLiteHelpers::WriteCmd;
                    time.control    = BlueLiteHelpers::BlinkControl;
                    
                    int transferred;
                    r = usbDevice.bulkTransfer (UsbDevice::EndOut2, 
                                                (uint8*)&time, 
                                                sizeof(time), transferred);
                    // Initialize Time
                    zerostruct<BlueLiteHelpers::TimePacket> (time);
                    time.type       = BlueLiteHelpers::TimeType;
                    time.stype      = BlueLiteHelpers::Smpte30fps;
                    time.command    = BlueLiteHelpers::WriteCmd;
                    time.control    = BlueLiteHelpers::FreezeControl;
                    
                    r = usbDevice.bulkTransfer (UsbDevice::EndOut2, 
                                                (uint8*)&time, 
                                                sizeof(time), transferred);
                    if (r.wasOk())
                        return r;
                }
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
    Result r = usbDevice.controlTransfer(UsbDevice::VendorOut, 0xa0, 0xe600, 0, &b, 1);
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
    r = usbDevice.controlTransfer(UsbDevice::VendorOut, 0xa0, 0xe600, 0, &b, 1);
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
    conf.type = BlueLiteHelpers::ConfigType;
    conf.dmx1 = BlueLiteHelpers::DmxAllPages;
    conf.dmx2 = BlueLiteHelpers::DmxAllPages;
    conf.dmx3 = BlueLiteHelpers::DmxAllPages;
    conf.dmx4 = BlueLiteHelpers::DmxAllPages;
    conf.inBaseH = 0;
    conf.inBaseL = 1;

    int transferred;
    Result r = usbDevice.bulkTransfer (UsbDevice::EndOut2, 
                                       (uint8*)(&conf), sizeof (conf), 
                                       transferred);
    if (! r.wasOk())
        return r;
    
    return Result::ok();
}

