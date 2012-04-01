/*
    BlueLiteUsbDevice.h

    Common code for X1 and X1 Mini
*/

#ifndef __BLUELITEUSBDEVICE_H_FBDED78E__
#define __BLUELITEUSBDEVICE_H_FBDED78E__

#include "BlueLiteDevice.h"
#include "UsbDevice.h"

//==============================================================================
class BlueLiteUsbDevice : public BlueLiteDevice,
                          public UsbBulkReadListener
{
public:
    //==============================================================================
    BlueLiteUsbDevice(int vendorID, int productID,
                      int interface, const String& devName,
                      int universeCount,
                      int dmxDataSize, int dmxInputSize,
                      int resetAddress, const String& fwName,
                      UsbDevice::EndPoint timeEndpoint,
                      UsbDevice::EndPoint dmxInEndpoint,
                      UsbDevice::EndPoint dmxOutEndpoint);
    
    virtual ~BlueLiteUsbDevice(); 
    
    //==============================================================================
    const int getCount() { return usbDevice.getCount(); }
    
    //==============================================================================
    Result open (int index);
    bool isOpen() { return usbDevice.isOpen(); }
    void close();
    
    const String getDeviceName() { return usbDevice.getDeviceName(); }
    
    //==============================================================================
    Result updateDmxData (uint16 offset, const MemoryBlock& newData);
    MemoryBlock readDmxData();
    
    //==============================================================================
    void addInputEvent (BlueLiteEvent* event);
    void removeInputEvent (BlueLiteEvent* event);
    
    MemoryBlock readDmxInput();
    
    //==============================================================================
    void addTimeEvent (BlueLiteEvent* event);
    void removeTimeEvent (BlueLiteEvent* event);
    
    MemoryBlock readTimeInput();
    
    //==============================================================================
    const int getMaxDevice()     { return maxDevice; }
    const int getUniverseCount() { return universeCount; }
    const int getDmxDataSize()   { return dmxDataSize; }
    const int getDmxInputSize()  { return dmxInputSize; }
    
private:    
    //==============================================================================
    void bulkDataRead (UsbDevice::EndPoint endPoint, const uint8* data, int size);
    
    //==============================================================================
    Result loadFirmware (const String& firmware);
    
    //==============================================================================
    Result sendConfig();
    Result sendTime();
    
private:
    //==============================================================================
    const int maxDevice;
    const int universeCount;
    const int dmxDataSize;
    const int dmxInputSize;
    
    UsbDevice usbDevice;
    
    uint16 resetAddress;
    const String fwName;
    
    UsbDevice::EndPoint timeEndpoint;
    UsbDevice::EndPoint dmxInEndpoint;
    UsbDevice::EndPoint dmxOutEndpoint;
    
    MemoryBlock dmxPacket;
    
    ReferenceCountedArray<BlueLiteEvent, CriticalSection> inputEventList;
    MemoryBlock dmxInput;
    
    ReferenceCountedArray<BlueLiteEvent, CriticalSection> timeEventList;
    MemoryBlock timeInput;
};




#endif  // __BLUELITEUSBDEVICE_H_FBDED78E__
