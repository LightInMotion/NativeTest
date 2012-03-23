/*
    UsbDevice.cpp

    (Semi) Generic USB Device
*/

#include "UsbDevice.h"

#if JUCE_MAC || JUCE_LINUX
  #include "Native/UsbDevice_Unix.cpp"
#elif JUCE_WINDOWS
  #include "Native/UsbDevice_Win.cpp"
#endif

//==============================================================================
UsbDevice::UsbDevice (uint16 vendorID_, uint16 productID_, int interface_)
    : vendorID (vendorID_),
      productID (productID_),
      interface (interface_),
      osHandle (nullptr)
{
    
}