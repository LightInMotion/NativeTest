/*
    UsbDevice_Win.cpp

	Windows implementation of UsbDevice
*/


//==============================================================================
// We keep our OS handles in a helper class
class WindowsOSHandle : public UsbOSHandle
{
public:
    //==============================================================================
    WindowsOSHandle ()
    {
    }
    
    ~WindowsOSHandle() 
    {
        // If there are handles when we are deleted, release the interface        
    }
        
private:
    //==============================================================================
    
private:
    //==============================================================================
    
private:
    //==============================================================================
    JUCE_LEAK_DETECTOR(WindowsOSHandle)
};


//==============================================================================
//==============================================================================
// Our implementation for UsbDevice methods
int UsbDevice::getCount()
{
    return 0;
}

//==============================================================================
Result UsbDevice::openDevice (int index)
{
    // Close open session (if any)
    osHandle = nullptr;
    
    // Save the index
    deviceIndex = index;
    
    return Result::fail ("Could not find " + getDeviceName() + ".");
}


//==============================================================================
Result UsbDevice::setInterfaceAlternateSetting (int alternateSetting)
{
    return Result::fail (getDeviceName() + " is not open.");
}

//==============================================================================
Result UsbDevice::controlTransfer (RequestType requestType, 
                                   uint8 request, 
                                   uint16 value, uint16 index, 
                                   uint8* data, uint16 length) const
{
    return Result::fail (getDeviceName() + " is not open.");    
}

//==============================================================================
Result UsbDevice::bulkTransfer (EndPoint endPoint, 
                                uint8* data, 
                                int length, 
                                int& transferred) const
{
    return Result::fail (getDeviceName() + " is not open.");    
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
