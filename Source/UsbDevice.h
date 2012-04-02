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

class UsbBulkReadListener;

class UsbDevice
{
public:
    //==============================================================================
    UsbDevice (uint16 vendorID_, uint16 productID_, int usbInterface_, const String& deviceName_)
        : vendorID (vendorID_), productID (productID_), usbInterface (usbInterface_), 
          deviceIndex (0), osHandle (nullptr), deviceName (deviceName_) {}

    ~UsbDevice() {}
    
    //==============================================================================
    int getCount();
    
    Result openDevice (int index);
    inline bool isOpen() { return (osHandle != nullptr); } const
    inline int getIndex() { return deviceIndex; } const
    void closeDevice() { osHandle = nullptr; }
    
    const String getDeviceName() const 
    { 
        return String (deviceName + "-" + String (deviceIndex)); 
    } 
    
    //==============================================================================
    Result setInterfaceAlternateSetting (int alternateSetting);
    
    //==============================================================================
    enum RequestType
    {
        StandardOut = (0 << 5),
        StandardIn  = (0 << 5) + 1,
        ClassOut    = (1 << 5),
        ClassIn     = (1 << 5) + 1,
        VendorOut   = (2 << 5),
        VendorIn    = (2 << 5) + 1,
    };
    
    Result controlTransfer (RequestType requestType, uint8 request, 
                            uint16 value, uint16 index, uint8* data, 
                            uint16 length) const;
    
    enum EndPoint
    {
        EndOut0     = 0x00,
        EndIn0      = 0x80,
        EndOut1     = 0x01,
        EndIn1      = 0x81,
        EndOut2     = 0x02,
        EndIn2      = 0x82,
        EndOut3     = 0x03,
        EndIn3      = 0x83,
        EndOut4     = 0x04,
        EndIn4      = 0x84,
        EndOut5     = 0x05,
        EndIn5      = 0x85,
        EndOut6     = 0x06,
        EndIn6      = 0x86,
        EndOut7     = 0x07,
        EndIn7      = 0x87,
        EndOut8     = 0x08,
        EndIn8      = 0x88,
        EndOut9     = 0x09,
        EndIn9      = 0x89,
        EndOut10    = 0x0a,
        EndIn10     = 0x8a,
        EndOut11    = 0x0b,
        EndIn11     = 0x8b,
        EndOut12    = 0x0c,
        EndIn12     = 0x8c,
        EndOut13    = 0x0d,
        EndIn13     = 0x8d,
        EndOut14    = 0x0e,
        EndIn14     = 0x8e,
        EndOut15    = 0x0f,
        EndIn15     = 0x8f,        
    };
    
    Result bulkTransfer (EndPoint endPoint, uint8* data, int length,
                         int& transferred) const;
    
    //==============================================================================
    Result addBulkReadListener (UsbBulkReadListener* listener, EndPoint endPoint, int size);
    Result removeBulkReadListener (EndPoint endPoint);
    
private:
    //==============================================================================
    uint16 vendorID;
    uint16 productID;
    int usbInterface;
    int deviceIndex;

    ScopedPointer<UsbOSHandle> osHandle;
    const String deviceName;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UsbDevice)
};

//==============================================================================
//==============================================================================
class UsbBulkReadListener
{
public:
    //==============================================================================
    UsbBulkReadListener() {}
    virtual ~UsbBulkReadListener() {}
    
    //==============================================================================
    virtual void bulkDataRead (UsbDevice::EndPoint endPoint, const uint8* data, int size) = 0;
    
    //==============================================================================
private:
    JUCE_LEAK_DETECTOR (UsbBulkReadListener);
};


#endif  // __USBDEVICE_H_424472D6__
