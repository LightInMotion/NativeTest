/*
    BlueLiteX1Mini.h

    Low Level Access to X1 Mini 
*/

#ifndef __BLUELITEX1MINI_H_554C97D0__
#define __BLUELITEX1MINI_H_554C97D0__

#include "BlueLiteDevice.h"
#include "UsbDevice.h"

//==============================================================================
class BlueLiteX1Mini : public BlueLiteDevice,
                       public UsbBulkReadListener
{
public:
    //==============================================================================
    BlueLiteX1Mini();
    virtual ~BlueLiteX1Mini(); 
    
    //==============================================================================
    const int getCount() { return usbDevice.getCount(); }
    
    //==============================================================================
    Result open (int index);
    bool isOpen() { return usbDevice.isOpen(); }
    void close();

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
    const int dmxDataSize;
    const int dmxInputSize;

    UsbDevice usbDevice;
    MemoryBlock dmxPacket;
    
    ReferenceCountedArray<BlueLiteEvent, CriticalSection> inputEventList;
    MemoryBlock dmxInput;
    
    ReferenceCountedArray<BlueLiteEvent, CriticalSection> timeEventList;
    MemoryBlock timeInput;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlueLiteX1Mini)
};

#endif  // __BLUELITEX1MINI_H_554C97D0__
