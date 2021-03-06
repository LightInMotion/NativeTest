/*
    UsbDevice_Unix.cpp

    Mac/Linux implementation of UsbDevice 
*/

#include "libusb.h"

#define _LIBUSB_TIMEOUT (5000)

//==============================================================================
// Helper classes for libusb
//
// These are all reference counted objects, so after the initial new and
// assignment to their declared ::Ptr typedef, they will be automatically
// Released when the last user goes out of scope
//
class LibUsbContext : public ReferenceCountedObject
{
public:
    //==============================================================================
    LibUsbContext()
    {
        if (libusb_init (&context) < 0)
            context = nullptr;

//      Uncomment for usb Debugging Messages 
//        libusb_set_debug (context, 3);
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LibUsbContext)    
};

//==============================================================================
class LibUsbDeviceList : public ReferenceCountedObject
{
public:
    //==============================================================================
    LibUsbDeviceList(const LibUsbContext::Ptr& context_)
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LibUsbDeviceList)
};

class LibUsbDeviceHandle : public ReferenceCountedObject
{
public:
    //==============================================================================
    LibUsbDeviceHandle (const LibUsbContext::Ptr& context_, libusb_device *device)
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LibUsbDeviceHandle)    
};

//==============================================================================
class LibUsbBulkTransfer
{
public:
    //==============================================================================
    LibUsbBulkTransfer (UsbBulkReadListener* listener_, const LibUsbDeviceHandle::Ptr& device_, 
                        UsbDevice::EndPoint endPoint_, int size)
        : listener (listener_),
          device (device_),
          endPoint (endPoint_),
          data (size),
          submitted (false),
          transfer (nullptr)
    {
        transfer = libusb_alloc_transfer (0);
        if (transfer)
        {
            libusb_fill_bulk_transfer (transfer, device->get(), endPoint, 
                                       (uint8*)data.getData(), size, 
                                       transferCallback, this, 0);
            
            // We set true before passing in because the handling
            // is in another thread and we are trusting
            // submitted to be an automic, not using a lock
            setSubmitted (true);
            if (libusb_submit_transfer (transfer) < 0)
                setSubmitted (false);
        }
    }
    
    ~LibUsbBulkTransfer () 
    {
        if (transfer != nullptr)
        {
            if (isSubmitted())
            {
                // We could hang here if the USB library doesn't
                // cancel the transfer
                if (libusb_cancel_transfer (transfer) == 0)
                    while (isSubmitted());
            }
            
            libusb_free_transfer (transfer);
        }
    }

    //==============================================================================
    // These are inline, but could be expanded if locking is required
    inline UsbDevice::EndPoint getEndPoint() { return endPoint; }
    inline UsbBulkReadListener* getListener() { return listener; }
    inline bool isSubmitted() { return submitted; }
    inline void setSubmitted (bool val) { submitted = val; }
    inline MemoryBlock& getMemoryBlock() { return data; }
    
private:
    //==============================================================================
    static void transferCallback (struct libusb_transfer *transfer)
    {
        LibUsbBulkTransfer* bulkTransfer = (LibUsbBulkTransfer*) transfer->user_data;
        if (transfer->status != LIBUSB_TRANSFER_COMPLETED)
        {
            bulkTransfer->setSubmitted (false);
            return;
        }
        else
        {
            bulkTransfer->getListener()->bulkDataRead(bulkTransfer->getEndPoint(), 
                                                      (uint8 *)bulkTransfer->getMemoryBlock().getData(),
                                                      transfer->actual_length);
        }
        
        if (libusb_submit_transfer (transfer) < 0)
            bulkTransfer->setSubmitted (false);
    }
    
    //==============================================================================
    UsbBulkReadListener* listener;
    LibUsbDeviceHandle::Ptr device;
    UsbDevice::EndPoint endPoint;
    MemoryBlock data;
    volatile bool submitted;
    struct libusb_transfer* transfer;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LibUsbBulkTransfer)    
};

//==============================================================================
//==============================================================================
// We keep our OS handles in a helper class
class UnixOSHandle : public UsbOSHandle, Thread
{
public:
    //==============================================================================
    UnixOSHandle (int usbInterface_, LibUsbContext::Ptr& context_, const LibUsbDeviceHandle::Ptr& device_)
        : Thread ("Usb Thread"),
          usbInterface (usbInterface_),
          context (context_),
          device (device_)
    {
        setPriority (10);
        startThread();
    }
    
    ~UnixOSHandle() 
    {
        // If there are handles when we are deleted, release the interface        
        if (device != nullptr)
        {
            transfers.clear();
            stopThread (-1);        
            
            if (usbInterface >= 0)
                libusb_release_interface (*device, usbInterface);            
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
    bool addTransfer (UsbBulkReadListener* listener, const LibUsbDeviceHandle::Ptr& device,
                      UsbDevice::EndPoint endPoint, int size)
    {
        if (findTransferIndex(endPoint, nullptr))
            return false;
        
        transfers.add (new LibUsbBulkTransfer(listener, device, endPoint, size));
        return true;
    }

    //==============================================================================
    bool removeTransfer (UsbDevice::EndPoint endPoint)
    {
        int index;
        if (! findTransferIndex (endPoint, &index))
            return false;
        
        transfers.remove (index);
        return true;
    }
    
private:
    //==============================================================================
    int usbInterface;
    LibUsbContext::Ptr context;
    LibUsbDeviceHandle::Ptr device;
    OwnedArray<LibUsbBulkTransfer> transfers;
    
private:
    //==============================================================================
    bool findTransferIndex (UsbDevice::EndPoint endPoint, int* index)
    {
        for (int n = 0; n < transfers.size(); ++n)
        {
            if (transfers[n]->getEndPoint() == endPoint)
            {
                if (index != nullptr)
                    *index = n;
                return true;
            }
        }
        
        return false;
    }

    //==============================================================================
    void run()
    {
        struct timeval tv = { 0, 500000 };

        while (! threadShouldExit())
        {
            if (libusb_handle_events_timeout (*context, &tv) < 0)
                return;
        }
    }
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UnixOSHandle)
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
                    return Result::fail ("Could not open " + getDeviceName() + ".");
 
                // Configuration might have been selected by OS (or another app)
                int config;
                if (libusb_get_configuration (*devH, &config) < 0)
                    return Result::fail ("Could not read current configuration from " +
                                         getDeviceName() + ".");
                
                if (config != 1)
                {
                    if (libusb_set_configuration (*devH, 1) < 0)
                        return Result::fail (getDeviceName() + " could not be set to config 1.");
                }
                
                if (libusb_claim_interface (*devH, usbInterface) < 0)
                    return Result::fail (getDeviceName() + " is already in use.");
                                                
                osHandle = new UnixOSHandle (usbInterface, c, devH);
                return Result::ok();
            }
            
            ++count;
        }
	}
    
    return Result::fail ("Could not find " + getDeviceName() + ".");
}

//==============================================================================
Result UsbDevice::setInterfaceAlternateSetting (int alternateSetting)
{
    const LibUsbDeviceHandle::Ptr device = UnixOSHandle::getDevice (osHandle);
    if (device == nullptr)
        return Result::fail (getDeviceName() + " is not open.");
    
    if (libusb_set_interface_alt_setting (*device, 
                                          usbInterface, 
                                          alternateSetting) < 0)
        return Result::fail ("Could not set alternate interface on " + 
                             getDeviceName() + String(deviceIndex) + ".");

    return Result::ok();
}

//==============================================================================
Result UsbDevice::controlTransfer (RequestType requestType, 
                                   uint8 request, 
                                   uint16 value, uint16 index, 
                                   uint8* data, uint16 length) const
{
    const LibUsbDeviceHandle::Ptr device = UnixOSHandle::getDevice (osHandle);
    if (device == nullptr)
        return Result::fail (getDeviceName() + " is not open.");

    if (libusb_control_transfer (*device, requestType, request, 
                                 value, index, data, length, _LIBUSB_TIMEOUT) < 0)
        return Result::fail ("Transfer error with " + getDeviceName() + ".");

    return Result::ok();
}

//==============================================================================
Result UsbDevice::bulkTransfer (EndPoint endPoint, 
                                uint8* data, 
                                int length, 
                                int& transferred) const
{
    const LibUsbDeviceHandle::Ptr device = UnixOSHandle::getDevice (osHandle);
    if (device == nullptr)
        return Result::fail (getDeviceName() + " is not open.");

    int n = libusb_bulk_transfer (*device, endPoint, data, length, &transferred, _LIBUSB_TIMEOUT);
    if (n < 0)
    {
        if (n == LIBUSB_ERROR_TIMEOUT)
            return Result::fail ("Timeout for " + getDeviceName() + ".");
        
        return Result::fail ("Transfer error with " + getDeviceName() + ".");
    }
    return Result::ok();
}

//==============================================================================
Result UsbDevice::addBulkReadListener (UsbBulkReadListener* listener, 
                                       EndPoint endPoint, int size)
{
    const LibUsbDeviceHandle::Ptr device = UnixOSHandle::getDevice (osHandle);
    if (device == nullptr)
        return Result::fail (getDeviceName() + " is not open.");
    
    UnixOSHandle* unixHandle = UnixOSHandle::getSelf (osHandle);
    
    if (! unixHandle->addTransfer (listener, device, endPoint, size))
        return Result::fail ("Endpoint " + String(endPoint) + " already in use.");
        
    return Result::ok();
}

//==============================================================================
Result UsbDevice::removeBulkReadListener (EndPoint endPoint)
{
    const LibUsbDeviceHandle::Ptr device = UnixOSHandle::getDevice (osHandle);
    if (device == nullptr)
        return Result::fail (getDeviceName() + " is not open.");
    
    UnixOSHandle* unixHandle = UnixOSHandle::getSelf (osHandle);

    if (! unixHandle->removeTransfer (endPoint))
        return Result::fail ("Endpoint " + String(endPoint) + " is not streaming.");
    
    return Result::ok();
}
