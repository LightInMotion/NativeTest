/*
    UsbDevice.h

    (Semi) Generic USB Device Access 
*/

#ifndef __USBDEVICE_H_424472D6__
#define __USBDEVICE_H_424472D6__

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
// Generic OS handle, should be inherited by platform implementation
// Destructor should know how to clean up!
class UsbOSHandle
{
public:
    UsbOSHandle() {}
    virtual ~UsbOSHandle() {}
};


//==============================================================================
//==============================================================================
// USB Device
class UsbDevice
{
public:
    //==============================================================================
    UsbDevice (uint16 vendorID_, uint16 productID_, int interface_)
        : vendorID (vendorID_), productID (productID_),
          interface (interface_), osHandle (nullptr) {}

    ~UsbDevice() {}
    
    //==============================================================================
    int getCount();
    
    Result openDevice (int index);
    void closeDevice() { osHandle = nullptr; }
    
    //==============================================================================
    Result setInterfaceAlternateSetting (int alternateSetting);
    Result resetDevice();
    
    //==============================================================================
    Result controlTransfer (uint8 requestType, uint8 request, uint16 value, uint16 index, uint8* data, uint16 length, uint32 timeout);
    
private:
    //==============================================================================
    uint16 vendorID;
    uint16 productID;
    int interface;

    ScopedPointer<UsbOSHandle> osHandle;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UsbDevice)
};


#endif  // __USBDEVICE_H_424472D6__
