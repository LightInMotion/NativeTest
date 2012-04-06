/*
    DemoDevice.h

    Bogus device for running without hardware
*/

#ifndef __DEMODEVICE_H_F4D55BB1__
#define __DEMODEVICE_H_F4D55BB1__

#include "BlueLiteDevice.h"

class DemoDevice : public BlueLiteDevice,
                   Thread
{
public:
    //==============================================================================
    DemoDevice() : Thread ("Demo Thread"), dmxData (2048), timeInput (10) 
    {
        dmxData.fillWith (0);
        timeInput.fillWith (0);
    }
    
    virtual ~DemoDevice() { stopThread (-1); }
    
    //==============================================================================
    void run();
    
    //==============================================================================
    const int getCount() { return 1; }
    
    Result open (int index) { startThread(); return Result::ok(); }
    bool isOpen() { return isThreadRunning(); }
    void close() { stopThread (-1); }
    
    //==============================================================================
    const String getDeviceName() { return String ("Demo Device"); }
    
    //==============================================================================
    Result updateDmxData (uint16 offset, const MemoryBlock& newData)
    {
        dmxData.copyFrom (newData.getData(), offset, newData.getSize());
        return Result::ok();
    }
    
    MemoryBlock readDmxData() { return MemoryBlock (dmxData); }
    
    //==============================================================================
    void addInputEvent (BlueLiteEvent* event) {}
    void removeInputEvent (BlueLiteEvent* event) {}
    
    MemoryBlock readDmxInput() { return MemoryBlock (0); }
    
    //==============================================================================
    void addTimeEvent (BlueLiteEvent* event)
    {
        timeEventList.addIfNotAlreadyThere (event);
    }
    
    void removeTimeEvent (BlueLiteEvent* event)
    {
        timeEventList.removeObject (event);
    }
    
    MemoryBlock readTimeInput()
    {
        const ScopedLock lock (timeEventList.getLock());
        return (MemoryBlock (timeInput));
    }
    
    //==============================================================================
    const int getMaxDevice() { return 1; }
    const int getUniverseCount() { return 4; }
    
    const int getDmxDataSize() { return 2048; }
    const int getDmxInputSize() { return 48; }
    
private:
    MemoryBlock dmxData;
    ReferenceCountedArray<BlueLiteEvent, CriticalSection> timeEventList;
    MemoryBlock timeInput;
};



#endif  // __DEMODEVICE_H_F4D55BB1__
