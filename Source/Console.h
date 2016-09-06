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
        ShowLoaded = 1,
        GrandMasterChanged = 2
    } Message;
    
    typedef void* SliderHandle;
    
    // Construct/Destruct
    Console (BlueLiteDevice::Ptr blueliteDevice_);
    ~Console();

    // Show functions
    void newShow();
    bool loadShow (File file);


    // Slider functions
    SliderHandle addSlider();
    void removeSlider (SliderHandle slider);
    
    int setCue (SliderHandle slider, int cueNumber);
    int getCue (SliderHandle slider);
    void setLevel (SliderHandle slider, int level);
    inline int getLevel (SliderHandle slider);
    inline void setGrandMaster (int level);
    inline int getGrandMaster();
    
    // Update Thread stuff, don't call externally!
    inline static int compareElements (Fader* first, Fader* second);
    void run() override;

private:
    // Initialization helpers
    bool loadEffects();
    
    // Cue List helper
    Cue* lookupCue (int cueNumber)
    {
        for (int n = 0; n < cueList.size(); ++n)
            if (cueList[n]->getNumber() == cueNumber)
                return cueList[n];
        
        return nullptr;
    }
    
    // Player communication
    void broadcastMessage (Console::Message msg, uint32 param = 0);
    
    BlueLiteDevice::Ptr blueliteDevice;
    BlueLiteEvent::Ptr timeEvent;
    
    OwnedArray<EffectPattern> effectPatterns;
    OwnedArray<Device> deviceList;
    OwnedArray<Cue> cueList;
    
    bool faderLevelsChanged;
    bool faderCuesChanged;
    OwnedArray<Fader, CriticalSection> faderList;
    
    int grandMaster;
    
    uint32 updateID;
    
    MemoryBlock outputBeforeEffects;
    MemoryBlock outputAfterEffects;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Console)
};


#endif  // CONSOLE_H_INCLUDED
