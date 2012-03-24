/*
    UsbDevice_Unix.cpp

    Mac/Linux implementation of UsbDevice 
*/

#include "libusb.h"

//==============================================================================
//==============================================================================
// Helper classes for libusb
class LibUsbContext : public ReferenceCountedObject
{
public:
    //==============================================================================
    LibUsbContext()
    {
        if (libusb_init (&context) < 0)
            context = nullptr;
    }
    
    ~LibUsbContext() 
    { 
        if (context != nullptr)
            libusb_exit (context); 
    }
    
    //==============================================================================
    libusb_context* get() { return context; }
    operator libusb_context* () { return context; }
    
    //==============================================================================    
    typedef ReferenceCountedObjectPtr<LibUsbContext> Ptr;

private:
    //==============================================================================
    libusb_context* context;

    //==============================================================================
    JUCE_LEAK_DETECTOR(LibUsbContext)    
};

//==============================================================================
class LibUsbDeviceList : public ReferenceCountedObject
{
public:
    //==============================================================================
    LibUsbDeviceList(LibUsbContext::Ptr context_)
        : context (context_)
    {
        if (libusb_get_device_list (*context, &devices) < 0)
            devices = nullptr;
    }
    
    ~LibUsbDeviceList()
    {
        if (devices != nullptr)
            libusb_free_device_list (devices, 1);            
    }
    
    //==============================================================================
    libusb_device ** get() { return devices; }

    libusb_device* operator[] (const int index)
    {
        if (devices == nullptr)
            return nullptr;
        
        return devices[index]; 
    }

    //==============================================================================    
    typedef ReferenceCountedObjectPtr<LibUsbDeviceList> Ptr;
    
private:
    //==============================================================================
    LibUsbContext::Ptr context;
	libusb_device **devices;

    //==============================================================================
    JUCE_LEAK_DETECTOR(LibUsbDeviceList)
};

class LibUsbDeviceHandle : public ReferenceCountedObject
{
public:
    //==============================================================================
    LibUsbDeviceHandle (LibUsbContext::Ptr context_, libusb_device *device)
        : context (context_)
    {
        if (libusb_open (device, &deviceHandle) < 0)
            deviceHandle = nullptr;
    }
    
    ~LibUsbDeviceHandle() 
    { 
        if (deviceHandle != nullptr)
            libusb_close (deviceHandle);
    }
    
    //==============================================================================
    libusb_device_handle* get() { return deviceHandle; }
    operator libusb_device_handle* () { return deviceHandle; }
    
    //==============================================================================    
    typedef ReferenceCountedObjectPtr<LibUsbDeviceHandle> Ptr;
    
private:
    //==============================================================================
    LibUsbContext::Ptr context;
    libusb_device_handle* deviceHandle;
    
    //==============================================================================
    JUCE_LEAK_DETECTOR(LibUsbDeviceHandle)    
};


//==============================================================================
//==============================================================================
// We keep our OS handles in a helper class
class UnixOSHandle : public UsbOSHandle
{
public:
    //==============================================================================
    UnixOSHandle (int interface_, LibUsbContext::Ptr context_, LibUsbDeviceHandle::Ptr device_)
        : interface (interface_),
          context (context_),
          device (device_)
    {
    }
    
    ~UnixOSHandle() 
    {
        // If there are handles when we are deleted, clean up 
        if (device != nullptr)
        {
            if (interface >= 0)
                libusb_release_interface (*device, interface);            
        }        
    }
    
    //==============================================================================
    static LibUsbDeviceHandle::Ptr getDevice (const ScopedPointer<UsbOSHandle>& handle)
    {
        if (handle == nullptr)
            return nullptr;
        
        UsbOSHandle *os = handle.get();
        return ((UnixOSHandle*)os)->device;
    }
    
    //==============================================================================
    int interface;
    LibUsbContext::Ptr context;
    LibUsbDeviceHandle::Ptr device;

    //==============================================================================
    JUCE_LEAK_DETECTOR(UnixOSHandle)
};


//==============================================================================
//==============================================================================
// Our implementation for UsbDevice methods
int UsbDevice::getCount()
{
    LibUsbContext::Ptr c = new LibUsbContext();
	if (c->get() == nullptr)
        return 0;
    
    LibUsbDeviceList::Ptr devs = new LibUsbDeviceList (c);
    if (devs->get() == nullptr)
        return 0;

    int count = 0;
    int idx = 0;
	libusb_device *dev;
    
	while ((dev = (*devs)[idx++]) != NULL) 
    {
		struct libusb_device_descriptor desc;
		if (libusb_get_device_descriptor (dev, &desc) < 0)
            break;
        
        if (desc.idVendor == vendorID && desc.idProduct == productID)
            count++;
	}

	return count;    
}

//==============================================================================
Result UsbDevice::openDevice (int index)
{
    LibUsbContext::Ptr c = new LibUsbContext();
    if (c->get() == nullptr)
        return Result::fail ("Could not initialize USB services.");

    LibUsbDeviceList::Ptr devs = new LibUsbDeviceList (c);
    if (devs->get() == nullptr)
        return Result::fail ("Could not obtain device information.");
    
    int count = 0;
    int idx = 0;
	libusb_device *dev;
    
	while ((dev = (*devs)[idx++]) != NULL) 
    {
		struct libusb_device_descriptor desc;
		if (libusb_get_device_descriptor (dev, &desc) < 0)
            break;
        
        if (desc.idVendor == vendorID && desc.idProduct == productID)
        {        
            if (count == index)
            {
                LibUsbDeviceHandle::Ptr devH = new LibUsbDeviceHandle (c, dev);
                if (devH->get() == nullptr)
                    return Result::fail ("Could not open device.");
                
                if (libusb_claim_interface (*devH, interface) < 0)
                    return Result::fail ("Device is already inuse.");
                
                osHandle = new UnixOSHandle (interface, c, devH);
                return Result::ok();
            }
            
            ++count;
        }
	}
    
    return Result::fail ("Could not open device.");
}

//==============================================================================
Result UsbDevice::setInterfaceAlternateSetting (int alternateSetting)
{
    LibUsbDeviceHandle::Ptr device = UnixOSHandle::getDevice (osHandle);
    if (device == nullptr)
        return Result::fail ("Device is not open.");
    
    if (libusb_set_interface_alt_setting (*device, 
                                          interface, 
                                          alternateSetting) < 0)
        return Result::fail ("Could not set alternate.");
    
    
    return Result::ok();
}

//==============================================================================
Result UsbDevice::resetDevice()
{
    LibUsbDeviceHandle::Ptr device = UnixOSHandle::getDevice (osHandle);
    if (device == nullptr)
        return Result::fail ("Device is not open.");

    if (libusb_reset_device (*device) < 0)
        return Result::fail ("Could not reset device.");
    
    return Result::ok();
}

//==============================================================================
Result UsbDevice::controlTransfer (uint8 requestType, 
                                   uint8 request, 
                                   uint16 value, uint16 index, 
                                   uint8 *data, uint16 length, 
                                   uint32 timeout)
{
    LibUsbDeviceHandle::Ptr device = UnixOSHandle::getDevice (osHandle);
    if (device == nullptr)
        return Result::fail ("Device is not open.");

    if (libusb_control_transfer (*device, requestType, request, 
                                 value, index, data, length, timeout) < 0)
        return Result::fail ("Transfer error.");
    
    return Result::ok();
}



