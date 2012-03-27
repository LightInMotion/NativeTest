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
BulkReader::BulkReader (const UsbDevice& usbDevice_, 
                        UsbDevice::EndPoint endPoint_,
                        int readSize_,
                        const BulkReadListener& listener_)
    : Thread ("BulkReader Thread"),
      usbDevice (usbDevice_),
      endPoint (endPoint_),
      readSize (readSize_),
      listener (listener_),
      data (readSize_)
{
    startThread();
}

BulkReader::~BulkReader()
{
    stopThread (-1);
}

void BulkReader::run()
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
                Logger::outputDebugString ("BulkReader aborting: " + r.getErrorMessage());
                data.setSize (0);
                listener.bulkDataRead (this, data);
                return;
            }
            Logger::outputDebugString ("BulkReader timeout");
        }
    }
    
    Logger::outputDebugString ("BulkReader thread exiting normally");
}
