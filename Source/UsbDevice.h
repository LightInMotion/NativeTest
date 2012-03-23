/*
  ==============================================================================

    UsbDevice.h
    Created: 23 Mar 2012 8:47:43am
    Author:  Joe Fitzpatrick

  ==============================================================================
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
// USB Device
class UsbDevice
{
public:
    //==============================================================================
    UsbDevice (uint16 vendorID, uint16 productID, int interface = 0);
    ~UsbDevice() {}
    
    //==============================================================================
    int getCount();

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
