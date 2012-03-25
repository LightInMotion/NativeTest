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
        
        libusb_set_debug (context, 3);
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
        // If there are handles when we are deleted, release the interface
        if (device != nullptr)
        {
            if (interface >= 0)
                libusb_release_interface (*device, interface);            
        }        
    }
    
    //==============================================================================
    static const LibUsbDeviceHandle::Ptr getDevice (const ScopedPointer<UsbOSHandle>& handle)
    {
        if (handle == nullptr)
            return nullptr;
        
        UsbOSHandle *os = handle.get();
        return ((UnixOSHandle*)os)->device;
    }
    
    static UnixOSHandle* getSelf (const ScopedPointer<UsbOSHandle>& handle)
    {
        if (handle == nullptr)
            return nullptr;
        
        UsbOSHandle *os = handle.get();
        return (UnixOSHandle*)os;
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
    // Close open session (if any)
    osHandle = nullptr;

    // Save the index
    deviceIndex = index;
    
    // Get a new context
    LibUsbContext::Ptr c = new LibUsbContext();
    if (c->get() == nullptr)
        return Result::fail ("Could not initialize USB services.");

    // Search the device list for a matching device
    LibUsbDeviceList::Ptr devs = new LibUsbDeviceList (c);
    if (devs->get() == nullptr)
        return Result::fail ("Could not obtain USB device information.");
    
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
                    return Result::fail ("Could not open " + deviceName + String(index) + ".");
 
                if (libusb_set_configuration (*devH, 1) < 0)
                    return Result::fail (deviceName + String(index) + " could not be set to config 1.");
                
                if (libusb_claim_interface (*devH, interface) < 0)
                    return Result::fail (deviceName + String(index) + " is already inuse.");
                
                osHandle = new UnixOSHandle (interface, c, devH);
                return Result::ok();
            }
            
            ++count;
        }
	}
    
    return Result::fail ("Could not find " + deviceName + String(index) + ".");
}

//==============================================================================
Result UsbDevice::setInterfaceAlternateSetting (int alternateSetting)
{
    const LibUsbDeviceHandle::Ptr device = UnixOSHandle::getDevice (osHandle);
    if (device == nullptr)
        return Result::fail (deviceName + " is not open.");
    
    if (libusb_set_interface_alt_setting (*device, 
                                          interface, 
                                          alternateSetting) < 0)
        return Result::fail ("Could not set alternate interface on " + 
                             deviceName + String(deviceIndex) + ".");

/*    
    if (libusb_release_interface (*device, interface) < 0)
        return Result::fail ("Could not release claim on " +
                             deviceName + String(deviceIndex) + ".");
    
    if (libusb_claim_interface (*device, interface) < 0)
        return Result::fail ("Could not claim interface on " +
                             deviceName + String(deviceIndex) + ".");
*/
    return Result::ok();
}

//==============================================================================
Result UsbDevice::resetDevice()
{
    const LibUsbDeviceHandle::Ptr device = UnixOSHandle::getDevice (osHandle);
    if (device == nullptr)
        return Result::fail (deviceName + " is not open.");

    if (libusb_reset_device (*device) < 0)
        return Result::fail ("Could not reset " + deviceName + String(deviceIndex) + ".");
    
    return Result::ok();
}

//==============================================================================
Result UsbDevice::controlTransfer (RequestType requestType, 
                                   uint8 request, 
                                   uint16 value, uint16 index, 
                                   uint8* data, uint16 length, 
                                   uint32 timeout)
{
    const LibUsbDeviceHandle::Ptr device = UnixOSHandle::getDevice (osHandle);
    if (device == nullptr)
        return Result::fail (deviceName + " is not open.");

    if (libusb_control_transfer (*device, requestType, request, 
                                 value, index, data, length, timeout) < 0)
        return Result::fail ("Transfer error with " + deviceName + String(deviceIndex) + ".");

    return Result::ok();
}

//==============================================================================
Result UsbDevice::bulkTransfer (EndPoint endPoint, 
                                uint8* data, 
                                int length, 
                                int& transferred, 
                                uint32 timeout)
{
    const LibUsbDeviceHandle::Ptr device = UnixOSHandle::getDevice (osHandle);
    if (device == nullptr)
        return Result::fail (deviceName + " is not open.");

    if (libusb_bulk_transfer (*device, endPoint, data, length, &transferred, 500) < 0)
        return Result::fail ("Transfer error with " + deviceName + String(deviceIndex) + ".");
        
    return Result::ok();
}
