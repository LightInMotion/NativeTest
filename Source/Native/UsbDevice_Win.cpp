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
    JUCE_LEAK_DETECTOR(WinDevice)    
};

static const WinDevice::Ptr nullDevice = nullptr;

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
    JUCE_LEAK_DETECTOR(WinSemaphore)    
};

//==============================================================================
//==============================================================================
// We keep our OS handles in a helper class
class WindowsOSHandle : public UsbOSHandle
{
public:
    //==============================================================================
    WindowsOSHandle (WinSemaphore::Ptr& semaphoreHandle_, WinDevice::Ptr& deviceHandle_)
        : deviceHandle (deviceHandle_),
          semaphoreHandle (semaphoreHandle_) 
    {
        uint8 buffer[1000];
        DWORD bret;
        if (DeviceIoControl(deviceHandle->get(), IOCTL_Ezusb_GET_PIPE_INFO, NULL, 0, 
            buffer, sizeof(buffer), &bret, NULL) != 0)

        pipeInfo.setSize (bret);
        pipeInfo.copyFrom (buffer, 0, bret);
    }
    
    ~WindowsOSHandle() {}

    //==============================================================================
    int findPipe (UsbDevice::EndPoint endPoint)
    {
        PUSBD_INTERFACE_INFORMATION info = (PUSBD_INTERFACE_INFORMATION) pipeInfo.getData();

        for (ULONG n = 0; n < info->NumberOfPipes; ++n)
        {
            if (info->Pipes[n].EndpointAddress == endPoint)
                return n;
        }

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
    static const WinDevice::Ptr& getDevice (const ScopedPointer<UsbOSHandle>& handle)
    {
        if (handle == nullptr)
            return nullDevice;
        
        UsbOSHandle *os = handle.get();
        return ((WindowsOSHandle*)os)->deviceHandle;
    }

private:
    //==============================================================================
    
private:
    //==============================================================================
    WinDevice::Ptr deviceHandle;
    WinSemaphore::Ptr semaphoreHandle;
    MemoryBlock pipeInfo;

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

    osHandle = new WindowsOSHandle (semaphore, device);
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

    if (DeviceIoControl(device->get(), IOCTL_EZUSB_VENDOR_OR_CLASS_REQUEST, &myRequest, sizeof(myRequest), 
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
	    result = DeviceIoControl(device->get(), IOCTL_EZUSB_BULK_WRITE, 
                        &bc, sizeof(bc), data, length, &bret, NULL);
    else
	    result = DeviceIoControl(device->get(), IOCTL_EZUSB_BULK_READ, 
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
    return Result::fail (getDeviceName() + " is not open.");    
}

//==============================================================================
Result UsbDevice::removeBulkReadListener (EndPoint endPoint)
{
    return Result::fail (getDeviceName() + " is not open.");
}
