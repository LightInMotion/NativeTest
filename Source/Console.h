/*
    Console.h
    
    The big cheese. The console owns the cue and device list and maintains
    and updates arrays of cross faders and  submasters on behalf of various
    registered 'players'.
    
    Console is also the central clearing house for control input and show
    file loading and unloading.
*/

#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "BlueLiteDevice.h"
#include "Effect.h"
#include "Device.h"
#include "Cue.h"
#include "Fader.h"

class Console : public Thread
{
public:
    // Broadcast Messages
    typedef enum {
        NewShow = 0,
        ShowLoaded = 1
    } Message;
    
    // Construct/Destruct
    Console (BlueLiteDevice::Ptr blueliteDevice_);
    ~Console();

    // Show functions
    void newShow();
    bool loadShow (File file);

    // Update Thread
    void run() override;

private:
    // Initialization helpers
    bool loadEffects();
    
    // Player communication
    void broadcastMessage (Console::Message msg);
    
    BlueLiteDevice::Ptr blueliteDevice;
    BlueLiteEvent::Ptr timeEvent;
    
    OwnedArray<EffectPattern> effectPatterns;
    OwnedArray<Device> deviceList;
    OwnedArray<Cue> cueList;
    OwnedArray<Fader, CriticalSection> faderList;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Console)
};


#endif  // CONSOLE_H_INCLUDED
