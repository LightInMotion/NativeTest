/*
    UsbDevice.cpp

    (Semi) Generic USB Device Access
*/

#include "UsbDevice.h"

#if JUCE_MAC || JUCE_LINUX
  #include "Native/UsbDevice_Unix.cpp"
#elif JUCE_WINDOWS
  #include "Native/UsbDevice_Win.cpp"
#endif

//==============================================================================
UsbBulkReader::UsbBulkReader (const UsbDevice& usbDevice_, 
                        UsbDevice::EndPoint endPoint_,
                        int readSize_,
                        const UsbBulkReadListener& listener_)
    : Thread ("UsbBulkReader Thread"),
      usbDevice (usbDevice_),
      endPoint (endPoint_),
      readSize (readSize_),
      listener (listener_),
      data (readSize_)
{
    setPriority (10);
    startThread();
}

UsbBulkReader::~UsbBulkReader()
{
    stopThread (-1);
}

void UsbBulkReader::run()
{
    while (! threadShouldExit())
    {
        int transferred;
        Result r = usbDevice.bulkTransfer (endPoint, (uint8 *)data.getData(), 
                                           readSize, transferred);
        if (r.wasOk())
        {
            if (transferred != readSize)
                data.setSize (transferred);

            listener.bulkDataRead (this, data);

            if (transferred != readSize)
                data.setSize (readSize);
        }
        else 
        {
            if (! r.getErrorMessage().startsWith ("Timeout"))
            {
                Logger::outputDebugString ("UsbBulkReader aborting: " + r.getErrorMessage());
                data.setSize (0);
                listener.bulkDataRead (this, data);
                return;
            }
            Logger::outputDebugString ("UsbBulkReader timeout");
        }
    }
    
    Logger::outputDebugString ("UsbBulkReader thread exiting normally");
}
