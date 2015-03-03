/*
    UsbDevice_Win.cpp

	Windows implementation of UsbDevice
*/

#include <Windows.h>
#include <winioctl.h>
#include "ezusbsys.h"
#include "usb.h"

//==============================================================================
// Helper classes/defines for windows
class SupportedDevice
{
public:
    //==============================================================================
    SupportedDevice (uint32 id_, 
                     const String& deviceName_, 
                     const String& semaphoreName_)
        : id (id_), 
          deviceName (deviceName_),
          semaphoreName (semaphoreName_) {}

    //==============================================================================
    inline const uint32 getId()             { return id; }
    inline const String& getDeviceName()    { return deviceName; }
    inline const String& getSemaphoreName() { return semaphoreName; }

private:
    //==============================================================================
    uint32 id;
    String deviceName;
    String semaphoreName;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SupportedDevice)    
};

//==============================================================================
class SupportedDevices
{
public:
    //==============================================================================
    SupportedDevices()
    {
        supportedDevices.add (new SupportedDevice (0x4a92109, "\\\\.\\BluX1-%d", "Bluelite X1 DLL Semaphore %d"));
        supportedDevices.add (new SupportedDevice (0x4a9210a, "\\\\.\\BluXm-%d", "Bluelite X1 DLL Semaphore %d"));
        supportedDevices.add (new SupportedDevice (0x4a9210b, "\\\\.\\BluDJ-%d", "Bluelite X1 DLL Semaphore %d"));
        supportedDevices.add (new SupportedDevice (0x4a9210c, "\\\\.\\BluDJ-%d", "Bluelite X1 DLL Semaphore %d"));
    }

    ~SupportedDevices() {}

    const String getDeviceName (uint16 vId, uint16 pId, int index) const
    {
        String s;

        uint32 id = vId;
        id <<= 16;
        id += pId;

        for (int n = 0; n < supportedDevices.size(); ++n)
        {
            if (id == supportedDevices[n]->getId())
            {
                s = String::formatted (supportedDevices[n]->getDeviceName(), index);
                break;
            }
        }

        return s;
    }

    const String getSemaphoreName (uint16 vId, uint16 pId, int index) const
    {
        String s;

        uint32 id = vId;
        id <<= 16;
        id += pId;

        for (int n = 0; n < supportedDevices.size(); ++n)
        {
            if (id == supportedDevices[n]->getId())
            {
                s = String::formatted (supportedDevices[n]->getSemaphoreName(), index);
                break;
            }
        }

        return s;
    }

private:
    //==============================================================================
    OwnedArray<SupportedDevice> supportedDevices;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SupportedDevices)    
};

static const SupportedDevices supportedDevices;
static const int maxDevice = 8;

//==============================================================================
class WinDevice : public ReferenceCountedObject
{
public:
    //==============================================================================    
    WinDevice (const String& deviceName)
        : deviceHandle (INVALID_HANDLE_VALUE)
    {
	    deviceHandle = CreateFile (deviceName.toUTF8(),
                                  GENERIC_WRITE,
                                  FILE_SHARE_WRITE,
                                  NULL,
                                  OPEN_EXISTING,
                                  0,
                                  NULL);
    }

    ~WinDevice()
    {
        if (deviceHandle != INVALID_HANDLE_VALUE)
            CloseHandle (deviceHandle);
    }

    //==============================================================================    
    bool isOpen()       { return deviceHandle != INVALID_HANDLE_VALUE; }
    bool isNotOpen()    { return deviceHandle == INVALID_HANDLE_VALUE; }

    //==============================================================================    
    HANDLE get()        { return deviceHandle; } const

    //==============================================================================    
    typedef ReferenceCountedObjectPtr<WinDevice> Ptr;

private:
    //==============================================================================
    HANDLE deviceHandle;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WinDevice)    
};


//==============================================================================
class WinSemaphore : public ReferenceCountedObject
{
public:
    //==============================================================================
    WinSemaphore (const String& semaphoreName)
        : semaphoreHandle (NULL),
          alreadyExists (false)
    {
        semaphoreHandle = CreateSemaphore( NULL, 0, 1, semaphoreName.toUTF8());
        if (semaphoreHandle != NULL)
            if (GetLastError() == ERROR_ALREADY_EXISTS)
                alreadyExists = true;
    }

    ~WinSemaphore()
    {
        if (semaphoreHandle != NULL)
            CloseHandle (semaphoreHandle);
    }

    //==============================================================================
    bool isInUse()
    {
        if (semaphoreHandle == NULL)
            return true;

        return alreadyExists;
    }

    //==============================================================================    
    typedef ReferenceCountedObjectPtr<WinSemaphore> Ptr;

private:
    //==============================================================================
    HANDLE semaphoreHandle;
    bool alreadyExists;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WinSemaphore)    
};

//==============================================================================
class WinUsbBulkTransfer : Thread
{
public:
    //==============================================================================
    WinUsbBulkTransfer (UsbBulkReadListener* listener_, 
                        const WinDevice::Ptr& mainDevice_, const WinDevice::Ptr& device_, 
                        UsbDevice::EndPoint endPoint_, int pipe_, int size)
        : listener (listener_),
          mainDevice (mainDevice_),
          device (device_),
          endPoint (endPoint_),
          pipe (pipe_),
          data (size),
          Thread ("Usb Bulk Thread")
    {
        setPriority (10);
        startThread();
    }
    
    ~WinUsbBulkTransfer () 
    {
        ULONG p = pipe;
        DWORD bret;
		DeviceIoControl(mainDevice->get(), IOCTL_Ezusb_ABORTPIPE, 
				&p, sizeof(p), NULL, 0, &bret, NULL);

        stopThread (-1);
    }

    //==============================================================================
    UsbDevice::EndPoint getEndPoint() { return endPoint; }

private:
    //==============================================================================
    void run()
    {
	    BULK_TRANSFER_CONTROL bc;
        bc.pipeNum = pipe;

        while (! threadShouldExit())
        {
            DWORD bret;

            if (DeviceIoControl (device->get(), IOCTL_EZUSB_BULK_READ, 
                        &bc, sizeof(bc), data.getData(), (DWORD) data.getSize(), &bret, NULL) != 0)
                listener->bulkDataRead (endPoint, (uint8*) data.getData(), bret);
            else
                return;
        }        
    }
    
    //==============================================================================
    UsbBulkReadListener* listener;
    WinDevice::Ptr mainDevice;
    WinDevice::Ptr device;
    UsbDevice::EndPoint endPoint;
    int pipe;
    MemoryBlock data;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WinUsbBulkTransfer)    
};

//==============================================================================
//==============================================================================
// We keep our OS handles in a helper class
class WindowsOSHandle : public UsbOSHandle
{
public:
    //==============================================================================
    WindowsOSHandle (uint16 vendorID_, uint16 productID_, int deviceIndex_,
                     WinSemaphore::Ptr& semaphoreHandle_, WinDevice::Ptr& deviceHandle_)
        :
		  #if defined (_WIN32)
		    isWin64 (false),
		  #endif
		  vendorID (vendorID_),
          productID (productID_),
          deviceIndex (deviceIndex_),
          deviceHandle (deviceHandle_),
          semaphoreHandle (semaphoreHandle_) 
    {
		#if defined (_WIN32)
			BOOL f64;
			IsWow64Process (GetCurrentProcess(), &f64);
			if (f64)
				isWin64 = true;
			else
				isWin64 = false;
		#endif

        readPipeInfo();
    }
    
    ~WindowsOSHandle() 
    {
        transfers.clear();
    }

    //==============================================================================
    int findPipe (UsbDevice::EndPoint endPoint)
    {
		// This is ugly, but we might be running Win32 app on a Win64 machine, in which
		// case the driver structure we retrieved earlier has the wrong size pointers
		#if defined (_WIN32)

			if (! isWin64)
			{
				PUSBD_INTERFACE_INFORMATION info = (PUSBD_INTERFACE_INFORMATION) pipeInfo.getData();

				for (ULONG n = 0; n < info->NumberOfPipes; ++n)
				{
					if (info->Pipes[n].EndpointAddress == endPoint)
						return n;
				}
			}
			else
			{
				PUSBD_INTERFACE_INFORMATION64 info = (PUSBD_INTERFACE_INFORMATION64) pipeInfo.getData();

				for (ULONG n = 0; n < info->NumberOfPipes; ++n)
				{
					if (info->Pipes[n].EndpointAddress == endPoint)
						return n;
				}
			}
		#else
			PUSBD_INTERFACE_INFORMATION info = (PUSBD_INTERFACE_INFORMATION) pipeInfo.getData();

			for (ULONG n = 0; n < info->NumberOfPipes; ++n)
			{
				if (info->Pipes[n].EndpointAddress == endPoint)
					return n;
			}
		#endif

        return -1;
    }

    //==============================================================================
    static WindowsOSHandle* getSelf (const ScopedPointer<UsbOSHandle>& handle)
    {
        if (handle == nullptr)
            return nullptr;
        
        UsbOSHandle *os = handle.get();
        return (WindowsOSHandle*)os;
    }

    //==============================================================================
    static const WinDevice::Ptr getDevice (const ScopedPointer<UsbOSHandle>& handle)
    {
        if (handle == nullptr)
            return nullptr;
        
        UsbOSHandle *os = handle.get();
        return ((WindowsOSHandle*)os)->deviceHandle;
    }

    //==============================================================================
    void readPipeInfo ()
    {
        pipeInfo.setSize (0);

        uint8 buffer[1000];
        DWORD bret;
        if (DeviceIoControl(deviceHandle->get(), IOCTL_Ezusb_GET_PIPE_INFO, NULL, 0, 
            buffer, sizeof(buffer), &bret, NULL) != 0)

        pipeInfo.setSize (bret);
        pipeInfo.copyFrom (buffer, 0, bret);
    }

    //==============================================================================
    bool addTransfer (UsbBulkReadListener* listener,
                      UsbDevice::EndPoint endPoint, int size)
    {
        if (findTransferIndex(endPoint, nullptr))
            return false;
        
        int pipe = findPipe (endPoint);
        if (pipe < 0)
            return false;

        String s = supportedDevices.getDeviceName (vendorID, productID, deviceIndex);
        if (s.isEmpty())
            return false;

        WinDevice::Ptr device = new WinDevice (s);
        if (device->isNotOpen())
            return false;

        transfers.add (new WinUsbBulkTransfer(listener, deviceHandle, device, endPoint, pipe, size));
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

private:
    //==============================================================================
#if defined (_WIN32)
	bool isWin64;
#endif
    uint16 vendorID;
    uint16 productID;
    int deviceIndex;
    WinDevice::Ptr deviceHandle;
    WinSemaphore::Ptr semaphoreHandle;
    MemoryBlock pipeInfo;
    OwnedArray<WinUsbBulkTransfer> transfers;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowsOSHandle)    
};


//==============================================================================
//==============================================================================
// Our implementation for UsbDevice methods
int UsbDevice::getCount()
{
    int count = 0;

    for (int n = 0; n < maxDevice ; n++)
    {
        String s = supportedDevices.getDeviceName (vendorID, productID, n);
        if (s.isNotEmpty())
        {
            WinDevice device (s);
            if (device.isOpen())
                count++;
            else
                break;
        }
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

    String deviceName = supportedDevices.getDeviceName (vendorID, productID, index);
    if (deviceName.isEmpty())
        return Result::fail (getDeviceName() + " is not a supported device.");

    String semaphoreName = supportedDevices.getSemaphoreName (vendorID, productID, index);

    WinSemaphore::Ptr semaphore = new WinSemaphore (semaphoreName);
    if (semaphore->isInUse())
        return Result::fail (getDeviceName() + " is already in use.");

    WinDevice::Ptr device = new WinDevice (deviceName);
    if (device->isNotOpen())
        return Result::fail ("Could not open " + getDeviceName() + ".");

    osHandle = new WindowsOSHandle (vendorID, productID, deviceIndex, semaphore, device);
    return Result::ok();
}


//==============================================================================
Result UsbDevice::setInterfaceAlternateSetting (int alternateSetting)
{
    const WinDevice::Ptr device = WindowsOSHandle::getDevice (osHandle);
    if (device == nullptr)
        return Result::fail (getDeviceName() + " is not open.");

	// Set Our Interface
	DWORD bret;
	SET_INTERFACE_IN si;

	si.interfaceNum = (UCHAR) usbInterface;
	si.alternateSetting = (UCHAR) alternateSetting;

	if (DeviceIoControl(device->get(), IOCTL_Ezusb_SETINTERFACE, &si, sizeof(si), NULL, 0, &bret, NULL) == 0)
    {
        DWORD err = GetLastError();
        return Result::fail ("Could not set alternate interface on " + getDeviceName() + " (" + String((int)err) + ").");
    }

    WindowsOSHandle* windowsHandle = WindowsOSHandle::getSelf (osHandle);
    windowsHandle->readPipeInfo();

    return Result::ok();
}

//==============================================================================
Result UsbDevice::controlTransfer (RequestType requestType, 
                                   uint8 request, 
                                   uint16 value, uint16 index, 
                                   uint8* data, uint16 length) const
{
    const WinDevice::Ptr device = WindowsOSHandle::getDevice (osHandle);
    if (device == nullptr)
        return Result::fail (getDeviceName() + " is not open.");

    _VENDOR_OR_CLASS_REQUEST_CONTROL	myRequest;

    myRequest.direction = requestType & 1;
    myRequest.requestType = (UCHAR) (requestType >> 5);
    myRequest.recepient = 0;
    myRequest.requestTypeReservedBits = 0;
    myRequest.request = request;
    myRequest.value = value;
    myRequest.index = index;

    DWORD bret;

    if (DeviceIoControl (device->get(), IOCTL_EZUSB_VENDOR_OR_CLASS_REQUEST, &myRequest, sizeof(myRequest), 
        data, length, &bret, NULL) == 0)
    {
        DWORD err = GetLastError();
        return Result::fail ("Could not make control transfer to " + getDeviceName() + " (" + String((int)err) + ").");
    }

    return Result::ok();
}

//==============================================================================
Result UsbDevice::bulkTransfer (EndPoint endPoint, 
                                uint8* data, 
                                int length, 
                                int& transferred) const
{
    const WinDevice::Ptr device = WindowsOSHandle::getDevice (osHandle);
    if (device == nullptr)
        return Result::fail (getDeviceName() + " is not open.");

    int pipe = WindowsOSHandle::getSelf (osHandle)->findPipe (endPoint);
    if (pipe < 0)
        return Result::fail (getDeviceName() + " does not have endpoint: " + String(endPoint) + ".");

    BULK_TRANSFER_CONTROL bc;
	bc.pipeNum = pipe;

	DWORD result;
    DWORD bret;

    if (! (endPoint & 0x80))
	    result = DeviceIoControl (device->get(), IOCTL_EZUSB_BULK_WRITE, 
                        &bc, sizeof(bc), data, length, &bret, NULL);
    else
	    result = DeviceIoControl (device->get(), IOCTL_EZUSB_BULK_READ, 
                        &bc, sizeof(bc), data, length, &bret, NULL);

    transferred = (int)bret;

    if (result == 0)
    {
        DWORD err = GetLastError();
        return Result::fail ("Bulk transfer error with " + getDeviceName() + " (" + String((int)err) + ").");
    }

    return Result::ok();
}

//==============================================================================
Result UsbDevice::addBulkReadListener (UsbBulkReadListener* listener, 
                                       EndPoint endPoint, int size)
{
    WindowsOSHandle* windowsHandle = WindowsOSHandle::getSelf (osHandle);
    if (windowsHandle == nullptr)
        return Result::fail (getDeviceName() + " is not open.");
    
    if (! windowsHandle->addTransfer (listener, endPoint, size))
        return Result::fail ("Endpoint " + String(endPoint) + " already in use.");
        
    return Result::ok();
}

//==============================================================================
Result UsbDevice::removeBulkReadListener (EndPoint endPoint)
{
    const WinDevice::Ptr device = WindowsOSHandle::getDevice (osHandle);
    if (device == nullptr)
        return Result::fail (getDeviceName() + " is not open.");
    
    WindowsOSHandle* windowsHandle = WindowsOSHandle::getSelf (osHandle);

    if (! windowsHandle->removeTransfer (endPoint))
        return Result::fail ("Endpoint " + String(endPoint) + " is not streaming.");
    
    return Result::ok();
}
