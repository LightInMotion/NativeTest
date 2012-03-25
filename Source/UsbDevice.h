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
    UsbDevice (uint16 vendorID_, uint16 productID_, int interface_, const String& deviceName_)
        : vendorID (vendorID_), productID (productID_),
          interface (interface_), osHandle (nullptr), deviceName (deviceName_) {}

    ~UsbDevice() {}
    
    //==============================================================================
    int getCount();
    
    bool isOpen() { return (osHandle != nullptr); }
    Result openDevice (int index);
    void closeDevice() { osHandle = nullptr; }
    
    //==============================================================================
    Result setInterfaceAlternateSetting (int alternateSetting);
    Result resetDevice();
    
    //==============================================================================
    typedef enum {
        StandardOut = (0 << 5),
        StandardIn  = (0 << 5) + 1,
        ClassOut    = (1 << 5),
        ClassIn     = (1 << 5) + 1,
        VendorOut   = (2 << 5),
        VendorIn    = (2 << 5) + 1,
    } RequestType;
    
    Result controlTransfer (RequestType requestType, uint8 request, uint16 value, uint16 index, uint8* data, uint16 length, uint32 timeout);
    
private:
    //==============================================================================
    uint16 vendorID;
    uint16 productID;
    int interface;

    ScopedPointer<UsbOSHandle> osHandle;
    const String deviceName;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UsbDevice)
};


#endif  // __USBDEVICE_H_424472D6__
