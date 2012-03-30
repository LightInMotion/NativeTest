/*
    BlueLiteX1Mini.h

    Low Level Access to X1 Mini 
*/

#ifndef __BLUELITEX1MINI_H_554C97D0__
#define __BLUELITEX1MINI_H_554C97D0__

#include "../JuceLibraryCode/JuceHeader.h"
#include "UsbDevice.h"

//==============================================================================
/*
    Make our own event object, which is reference counted so that
    it can't be deleted while we are still signalling it
*/
class BlueLiteEvent : public WaitableEvent, public ReferenceCountedObject
{
public:
    BlueLiteEvent() {}
    ~BlueLiteEvent() {}
    
    //==============================================================================    
    typedef ReferenceCountedObjectPtr<BlueLiteEvent> Ptr;
    
private:
    //==============================================================================
    JUCE_LEAK_DETECTOR(BlueLiteEvent)    
};

//==============================================================================
//==============================================================================
class BlueLiteX1Mini : public UsbBulkReadListener
{
public:
    //==============================================================================
    BlueLiteX1Mini();
    ~BlueLiteX1Mini(); 
    
    //==============================================================================
    inline int getCount() { return usbDevice.getCount(); }
    
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
    const int maxDevice;
    const int dmxDataSize;
    const int dmxInputSize;

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
    UsbDevice usbDevice;
    MemoryBlock dmxPacket;
    
    ReferenceCountedArray<BlueLiteEvent, CriticalSection> inputEventList;
    MemoryBlock dmxInput;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlueLiteX1Mini)
};

#endif  // __BLUELITEX1MINI_H_554C97D0__
