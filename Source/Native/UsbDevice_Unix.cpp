/*
    UsbDevice_Unix.cpp

    Mac/Linux implementation of UsbDevice 
*/

#include "libusb.h"

//==============================================================================
// We keep our OS handles in a helper class
class UnixOSHandle : UsbOSHandle
{
public:
    //==============================================================================
    UnixOSHandle()
        : interface (-1),
          context (nullptr),
          device (nullptr)
    {
        
    }
    
    ~UnixOSHandle() 
    {
        // If there are handles when we are deleted, clean up 
        if (device != nullptr)
        {
            if (interface >= 0)
                libusb_release_interface (device, interface);
            
            libusb_close (device);
        }
        
        if (context != nullptr)
            libusb_exit (context);
    }
    
    //==============================================================================
    int interface;
    libusb_context* context;    
    libusb_device_handle* device;

    //==============================================================================
    JUCE_LEAK_DETECTOR(UnixOSHandle)
};


//==============================================================================
//==============================================================================
int UsbDevice::getCount()
{
    libusb_context* c;
    if (libusb_init (&c) < 0)
        return 0;
    
	libusb_device **devs;
	if (libusb_get_device_list(c, &devs) < 0)
    {
        libusb_exit (c);
        return 0;
    }

    int count = 0;
    int idx = 0;
	libusb_device *dev;
    
	while ((dev = devs[idx++]) != NULL) 
    {
		struct libusb_device_descriptor desc;
		if (libusb_get_device_descriptor (dev, &desc) < 0)
            break;
        
        if (desc.idVendor == vendorID && desc.idProduct == productID)
            count++;
	}

    
	libusb_free_device_list (devs, 1);
	libusb_exit (c);

	return count;    
}

