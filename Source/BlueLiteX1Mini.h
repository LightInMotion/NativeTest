/*
    BlueLiteX1Mini.h

    Low Level Access to X1 Mini 
*/

#ifndef __BLUELITEX1MINI_H_554C97D0__
#define __BLUELITEX1MINI_H_554C97D0__

#include "../JuceLibraryCode/JuceHeader.h"
#include "UsbDevice.h"

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
    Result updateUniverseData (uint16 offset, const MemoryBlock& newData);
    MemoryBlock readUniverseData();
    
    //==============================================================================
    void addInputEvent (const WaitableEvent* event);
    void removeInputEvent (const WaitableEvent* event);
    
    MemoryBlock readDmxInput();
    
    //==============================================================================
    const int maxDevice;
    const int universeSize;
    const int inputChannelCount;

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
    
    Array <const WaitableEvent*, CriticalSection> inputEventList;
    MemoryBlock dmxInput;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlueLiteX1Mini)
};

#endif  // __BLUELITEX1MINI_H_554C97D0__
