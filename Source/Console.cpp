/*
    Console.cpp

    The Main Console
*/

#include "Console.h"

//==============================================================================
// Construction/Destruction
//
Console::Console (BlueLiteDevice::Ptr blueliteDevice_)
    : Thread ("Console Update Thread"),
      blueliteDevice (blueliteDevice_),
      faderLevelsChanged (false),
      faderCuesChanged (false),
      grandMaster (FADER_MAX_LEVEL),
      updateID (0),
      outputBeforeEffects (DMX_CHANNEL_UPDATE_BUFFER_COUNT),
      outputAfterEffects (DMX_CHANNEL_BUFFER_COUNT),
      dmxOutput (blueliteDevice->getDmxDataSize()),
      universeCount (0)
{
    // Initialize common entities
    loadEffects();
    
    // Start our update Thread
    timeEvent = new BlueLiteEvent();
    blueliteDevice->addTimeEvent (timeEvent.getObject());
    setPriority (7);
    startThread();
}

Console::~Console()
{
    signalThreadShouldExit();
    blueliteDevice->removeTimeEvent (timeEvent.getObject());
    timeEvent->signal();
    stopThread (-1);
    
    timeEvent = nullptr;
    
}

//==============================================================================
// Submaster Functions
//
Console::SliderHandle Console::addSlider()
{
    Fader* fader = new Fader();
    if (fader)
        faderList.add (fader);
    return fader;
}

void Console::removeSlider (SliderHandle slider)
{
    faderList.removeObject ((Fader*)slider);
}

int Console::setCue (SliderHandle slider, int cueNumber)
{
    Fader* fader = (Fader*)slider;
    if (faderList.contains (fader))
    {
        Cue* cue = lookupCue (cueNumber);
        
        const ScopedLock lock (faderList.getLock());
        
        if (cue)
            fader->setCue (cue);
        else
            fader->clearCue();
        faderCuesChanged = true;
        
        return fader->getCueNumber();
    }
    else
        return 0;
}

int Console::getCue (SliderHandle slider)
{
    Fader* fader = (Fader*)slider;
    if (faderList.contains (fader))
        return fader->getCueNumber();
    
    return 0;
}

void Console::setLevel (SliderHandle slider, int level)
{
    if (level < 0)
        level = 0;
    else if (level > FADER_MAX_LEVEL)
        level = FADER_MAX_LEVEL;
    
    Fader* fader = (Fader*)slider;
    if (faderList.contains (fader))
    {
        const ScopedLock lock (faderList.getLock());
        
        stopFade (slider);
        fader->setLevel (level);
        faderLevelsChanged = true;
    }
}

int Console::getLevel (SliderHandle slider)
{
    Fader* fader = (Fader*)slider;
    if (faderList.contains (fader))
        return fader->getLevel();
    
    return 0;
}

bool Console::startFade (SliderHandle slider, int target, float time)
{
    Fader* fader = (Fader*)slider;
    if (faderList.contains (fader))
    {
        const ScopedLock lock (faderList.getLock());
        
        // Stop any existing fade for this slider
        stopFade (slider);
        
        TimedFade* fade = new TimedFade;
        
        fade->fader = fader;
        fade->finalTarget = target;
        fade->current = fader->getLevel();
        if (fade->current < fade->finalTarget)
        {
            fade->isFadeUp = true;
            fade->step = (fade->finalTarget - fade->current) / (time * 30.0);
        }
        else
        {
            fade->isFadeUp = false;
            fade->step = (fade->current - fade->finalTarget) / (time * 30.0);
        }
        
        activeFades.add (fade);
        return true;
    }
    
    return false;
}

void Console::stopFade (SliderHandle slider)
{
    Fader* fader = (Fader*)slider;
    
    const ScopedLock lock (faderList.getLock());
    
    // If there is already an active fade, kill it.
    for (int n = 0; n < activeFades.size(); ++n)
    {
        if (activeFades[n]->fader == fader)
        {
            activeFades.remove (n);
            break;
        }
    }
}

void Console::setGrandMaster (int level)
{
    do {
        const ScopedLock lock (faderList.getLock());
        
        if (level < 0)
            level = 0;
        else if (level > FADER_MAX_LEVEL)
            level = FADER_MAX_LEVEL;
        
        grandMaster = level;
        faderLevelsChanged = true;
    } while (0);
    
    broadcastMessage (GrandMasterChanged, level);
}

int Console::getGrandMaster()
{
    return grandMaster;
}


//==============================================================================
// Show Functions
//
// Create a new show (basically clear the old show)
void Console::newShow()
{
    // Lock the update thread
    const ScopedLock lock (faderList.getLock());
    
    // Unassign faders
    for (int n = 0; n < faderList.size(); ++n)
        faderList[n]->clearCue();
    
    // Clear the cues and devices
    cueList.clear();
    deviceList.clear();
    
    // Abandon all ArtNet output
    if (artnetOutput)
        artnetOutput->clearAllUniverses();
    
    broadcastMessage (Console::NewShow);
}

// Load a show from disk
bool Console::loadShow (File file, LoadListener* listener)
{
    bool result = true;
    if (listener)
        listener->reportProgress (0);
    
    newShow();  // Clear the existing show
    
    // We don't lock the fader list here because there should be
    // no cues assigned to any faders and locking would block the UI
    // from updating progress
    
    ShowFile show(file.getFullPathName());
    if (show.open())
    {
        // !!!! fail for unknown version
        uint32 version = show.getVersion();
        
        uint32 deviceCount = 0;
        while (show.isDirectory("/Devices/" + String(deviceCount) + "/"))
            deviceCount++;
        
        uint32 cueCount = 0;
        while (show.isDirectory("/Cues/" + String(cueCount) + "/"))
            cueCount++;
        
        double loadCount = 0;
        double loadTotal = deviceCount + cueCount;
        
        uint32 deviceIndex = 0;
        while (show.isDirectory("/Devices/" + String(deviceIndex) + "/"))
        {
            show.setPath ("/Devices/" + String(deviceIndex) + "/");
            ScopedPointer<Device> device = new Device();
            if (! device->DeviceLoad(show, version, nullptr))
            {
                result = false;
                break;
            }
        
            deviceList.add (device);
            device.release();
            ++deviceIndex;
            
            if (listener)
            {
                loadCount++;
                listener->reportProgress (loadCount / loadTotal);
            }
        }
    
        uint32 cueIndex = 0;
        while (show.isDirectory("/Cues/" + String(cueIndex) + "/"))
        {
            show.setPath ("/Cues/" + String(cueIndex) + "/");
            ScopedPointer<Cue> cue = new Cue();
            if (! cue->load(show, version, deviceList, effectPatterns))
            {
                result = false;
                break;
            }
            
            cueList.add (cue);
            cue.release();
            ++cueIndex;
            
            if (listener)
            {
                loadCount++;
                listener->reportProgress (loadCount / loadTotal);
            }
        }
    }
    else
        result = false;
        
    if (result == false)
    {
        cueList.clear();
        deviceList.clear();
        return false;
    }
    
    // Create ArtNet Output Universes as necessary
    createRequiredArtNetUniverses();
    
    broadcastMessage (Console::ShowLoaded);
    return true;
}

//==============================================================================
// Output Functions
//
void Console::setArtNetOutput (bool state)
{
    if (! state)
        artnetOutput = nullptr;
    else
    {
        artnetOutput = new ArtNetOutput();
        createRequiredArtNetUniverses();
    }
}

void Console::createRequiredArtNetUniverses()
{
    // We also use this as an opporunity to count universes used
    universeCount = 0;
    
    // Create ArtNet Output Universes as necessary
    for (uint32 universe = 0; universe < DMX_UNIVERSE_COUNT; ++universe)
    {
        Device* highestDevice = nullptr;
        
        for (int n = 0; n < deviceList.size(); ++n)
        {
            uint32 baseaddress = deviceList[n]->DeviceGetBaseAddress();
            if (baseaddress >= universe * DMX_CHANNELS_PER_UNIVERSE &&
                baseaddress < (universe + 1) * DMX_CHANNELS_PER_UNIVERSE)
            {
                if (! highestDevice || baseaddress > highestDevice->DeviceGetBaseAddress())
                    highestDevice = deviceList[n];
            }
        }
        
        if (highestDevice)
        {
            universeCount++;
            
            if (artnetOutput)
            {
                int channels = highestDevice->DeviceGetBaseAddress() - (universe * DMX_CHANNELS_PER_UNIVERSE);
                channels += highestDevice->DeviceGetNumberOfChannels();
            
                artnetOutput->setUniverse(universe, channels, universe / 16, universe % 16);
            }
        }
    }
}

//==============================================================================
// Admin functions
//
void Console::clearAllFaders()
{
    const ScopedLock lock (faderList.getLock());
    
    for (int n = 0; n < faderList.size(); ++n)
        faderList[n]->clearCue();
    
    faderCuesChanged = true;
    broadcastMessage (FaderCuesCleared);
}

//==============================================================================
// Player Comm functions
//
void Console::broadcastMessage (Console::Message msg, uint32 param)
{
    Logger::outputDebugString ("Console broadcast: " + String (msg) + ", " + String (param));
}

//==============================================================================
// Initialization Helpers
bool Console::loadEffects()
{
    // !!!! Should be relative to the application location
#ifdef JUCE_WINDOWS
	File f("C:\\Program Files (x86)\\BlueLite X1\\Effects\\");
#else
    File f("~/X1Effects/");
#endif
    Array<File> effectFiles;
    f.findChildFiles (effectFiles, File::findFiles, false, "*.eff");
    
    for (int i = 0; i < effectFiles.size(); ++i)
    {
        ScopedPointer<EffectPattern> pattern = new EffectPattern;
        
        if (pattern->EffectPatLoad (effectFiles[i].getFullPathName()))
        {
            effectPatterns.add (pattern);
            pattern.release();
        }
    }

    if (effectFiles.size())
        return true;
        
    return false;
}
    
//==============================================================================
// The main update thread
//
void Console::run()
{
    // Stop our update thread
    while (! threadShouldExit())
    {
        timeEvent->wait();
        if (threadShouldExit())
            return;
        do
        {
            const ScopedLock lock (faderList.getLock());
            
            // Increment our update indicator
            updateID++;
            
            // Any active fades?
            if (activeFades.size())
            {
                faderLevelsChanged = true;
                
                // Loop backwards for dropping completed fades
                for (int n = activeFades.size() - 1; n >= 0; n--)
                {
                    TimedFade* fade = activeFades[n];
                    
                    if (fade->isFadeUp)
                    {
                        fade->current += fade->step;
                        if (fade->current > fade->finalTarget)
                            fade->current = fade->finalTarget;
                    }
                    else
                    {
                        fade->current -= fade->step;
                        if (fade->current < fade->finalTarget)
                            fade->current = fade->finalTarget;
                    }
                    
                    fade->fader->setLevel ((int)(fade->current + 0.5f));
                    if (fade->current == fade->finalTarget)
                        activeFades.remove (n);
                }
            }
            
            // For certain controls to summ correctly we must update faders from
            // highest level to lowest, so we sort
            if (faderLevelsChanged == true)
                  faderList.sort (*this);
            
            // Only bother to recalculate pre-effects if a cue or level change
            // has happened
            if (faderLevelsChanged || faderCuesChanged)
            {
                outputBeforeEffects.fillWith (0);
                
                for (int faderIndex = 0; faderIndex < faderList.size(); ++faderIndex)
                {
                    if (faderList[faderIndex]->getLevel() > 0)
                        faderList[faderIndex]->updateBuffer ((uint8*)outputBeforeEffects.getData(), grandMaster);
                    else
                        break;  // Since we are sorted we can stop at first 0
                }
                
                faderLevelsChanged = false;
                faderCuesChanged = false;
            }
            
            // New or old, we copy what we have to apply effects
            outputAfterEffects.copyFrom (outputBeforeEffects.getData(), 0, DMX_CHANNEL_BUFFER_COUNT);
            
            // Effects take three passes, calculation, updating, then advancing
            for (int faderIndex = 0; faderIndex < faderList.size(); ++faderIndex)
            {
                if (faderList[faderIndex]->getLevel() > 0)
                    faderList[faderIndex]->calculateEffects();
                else
                    break;
            }

            for (int faderIndex = 0; faderIndex < faderList.size(); ++faderIndex)
            {
                if (faderList[faderIndex]->getLevel() > 0)
                    faderList[faderIndex]->updateEffects ((uint8 *)outputAfterEffects.getData());
                else
                    break;
            }

            for (int faderIndex = 0; faderIndex < faderList.size(); ++faderIndex)
            {
                if (faderList[faderIndex]->getLevel() > 0)
                    faderList[faderIndex]->advanceEffectPosition (updateID);
                else
                    break;
            }

        } while (0);

        // Output to our device
        // !!!! Alternate version of update to eliminate copy!
        dmxOutput.copyFrom (outputAfterEffects.getData(), 0, dmxOutput.getSize());
        Result r = blueliteDevice->updateDmxData(0, dmxOutput);
        if (r.failed())
            Logger::outputDebugString(r.getErrorMessage());
        
        if (artnetOutput)
            artnetOutput->updateChannels (outputAfterEffects);
    }
}

// FaderList sorting helper
inline int Console::compareElements (Fader* first, Fader* second)
{
    int f = first->getLevel();
    int s = second->getLevel();
    
    if (f > s)
        return -1;
    if (f < s)
        return 1;
    
    return 0;
}
    
