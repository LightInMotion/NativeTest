/*
    BlueLiteX1Mini.cpp

    Low Level Access to X1 Mini 
*/

#include "IntelHexReader.h"
#include "BlueLiteX1Mini.h"


//==============================================================================
namespace BlueLiteHelpers
{
    bool loadFirmware (UsbDevice& usbDevice, const String& firmware)
    {
        uint8 b = 1;            
        if (! usbDevice.controlTransfer(UsbDevice::VendorOut, 0xa0, 0xe600, 0, &b, 1, 500).wasOk())
            return false;
        
        IntelHexReader hexReader (firmware);
        if (hexReader.getTotalLength() == 0)
            return false;
        
        MemoryBlock block;
        uint16 address;
        while (hexReader.readLineAsBinary (block, address))
        {
            if (! usbDevice.controlTransfer (UsbDevice::VendorOut, 0xa0, address, 0,
                                             (uint8*)block.getData(), block.getSize(), 500))
                return false;
        }
        
        b = 0;
        if (! usbDevice.controlTransfer(UsbDevice::VendorOut, 0xa0, 0xe600, 0, &b, 1, 500).wasOk())
            return false;
        
        return true;
    }
}

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
            if (BlueLiteHelpers::loadFirmware (usbDevice, "minifirm_hex"))
                return Result::ok();
        }
    }
        
    return r;
}

void BlueLiteX1Mini::close()
{
    if (usbDevice.isOpen())
    {
        BlueLiteHelpers::loadFirmware (usbDevice, "X1IDLE_HEX");
        usbDevice.closeDevice();
    }
}

