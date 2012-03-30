/*
    BlueLiteDevice.h

    Generic BlueLite Device
*/

#ifndef __BLUELITEDEVICE_H_3C6AC1F6__
#define __BLUELITEDEVICE_H_3C6AC1F6__

#include "../JuceLibraryCode/JuceHeader.h"

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
class BlueLiteDevice : public ReferenceCountedObject
{
public:
    //==============================================================================
    BlueLiteDevice() {}
    virtual ~BlueLiteDevice() {} 
    
    //==============================================================================
    virtual const int getCount() = 0;
    
    //==============================================================================
    virtual Result open (int index) = 0;
    virtual bool isOpen() = 0;
    virtual void close() = 0;
    
    //==============================================================================
    virtual Result updateDmxData (uint16 offset, const MemoryBlock& newData) = 0;
    virtual MemoryBlock readDmxData() = 0;
    
    //==============================================================================
    virtual void addInputEvent (BlueLiteEvent* event) = 0;
    virtual void removeInputEvent (BlueLiteEvent* event) = 0;
    
    virtual MemoryBlock readDmxInput() = 0;
    
    //==============================================================================
    virtual void addTimeEvent (BlueLiteEvent* event) = 0;
    virtual void removeTimeEvent (BlueLiteEvent* event) = 0;
    
    virtual MemoryBlock readTimeInput() = 0;
    
    //==============================================================================
    virtual const int getMaxDevice() = 0;
    virtual const int getDmxDataSize() = 0;
    virtual const int getDmxInputSize() = 0;
    
    //==============================================================================    
    typedef ReferenceCountedObjectPtr<BlueLiteDevice> Ptr;    
};


#endif  // __BLUELITEDEVICE_H_3C6AC1F6__
