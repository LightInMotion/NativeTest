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
      outputAfterEffects (DMX_CHANNEL_BUFFER_COUNT)
{
    artnetOut = new ArtNetOutput;
    
    // Initialize common entities
    loadEffects();
    
    // Start our update Thread
    timeEvent = new BlueLiteEvent();
    blueliteDevice->addTimeEvent (timeEvent.getObject());
    setPriority (6);
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
    artnetOut->clearAllUniverses();
    
    broadcastMessage (Console::NewShow);
}

// Load a show from disk
bool Console::loadShow (File file)
{
    bool result = true;
    
    newShow();  // Clear the existing show
    
    // Lock the update thread
    const ScopedLock lock (faderList.getLock());

    ShowFile show(file.getFullPathName());
    if (show.open())
    {
        // !!!! fail for unknown version
        uint32 version = show.getVersion();
        
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
        }
    
        uint cueIndex = 0;
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
    for (int universe = 0; universe < DMX_UNIVERSE_COUNT; ++universe)
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
            int channels = highestDevice->DeviceGetBaseAddress() - (universe * DMX_CHANNELS_PER_UNIVERSE);
            channels += highestDevice->DeviceGetNumberOfChannels();
            
            artnetOut->setUniverse(universe, channels, universe / 16, universe % 16);
        }
    }
    
    broadcastMessage (Console::ShowLoaded);
    return true;
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
    File f("~/X1Effects/");
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

        artnetOut->updateChannels (outputAfterEffects);
        
#if 0
        String outstr("B: ");
        uint8* bytes = (uint8 *)outputBeforeEffects.getData();
        for (int n = 0; n < 16; ++n)
            outstr += (String (bytes[n]) + " ");
        Logger::outputDebugString (outstr);
        outstr = "A: ";
        bytes = (uint8 *)outputAfterEffects.getData();
        for (int n = 0; n < 16; ++n)
            outstr += (String (bytes[n]) + " ");
        Logger::outputDebugString (outstr);
#endif
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
    
