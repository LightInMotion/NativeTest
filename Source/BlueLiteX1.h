/*
  ==============================================================================

    BlueLiteX1.h
    Created: 29 Mar 2012 9:40:11pm
    Author:  Joe Fitzpatrick

  ==============================================================================
*/

#ifndef __BLUELITEX1_H_DE4CA899__
#define __BLUELITEX1_H_DE4CA899__

#include "BlueLiteDevice.h"
#include "UsbDevice.h"

//==============================================================================
class BlueLiteX1 : public BlueLiteDevice,
                   public UsbBulkReadListener
{
public:
    //==============================================================================
    BlueLiteX1();
    virtual ~BlueLiteX1(); 
    
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlueLiteX1)
};

#endif  // __BLUELITEX1_H_DE4CA899__
