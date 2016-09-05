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
      blueliteDevice (blueliteDevice_)
{
    // Initialize common entities
    loadEffects();
    
    // Start our update Thread
    timeEvent = new BlueLiteEvent();
    blueliteDevice->addTimeEvent (timeEvent.getObject());
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
#if 0
    ScopedPointer<uint8> outputBuffer = new uint8[MAIN_DMX_CHANNEL_BUFFER_COUNT * 2];
    
    if (cueList.size())
    {
        Fader fader;
        
        fader.setCue (cueList[0]);
        fader.setLevel (FADER_MAX_LEVEL);
        
        zeromem (outputBuffer, MAIN_DMX_CHANNEL_BUFFER_COUNT * 2);
        fader.updateBuffer (outputBuffer, FADER_MAX_LEVEL);
        Logger::outputDebugString ("Full");
        for (int n = 0; n < 32; ++n)
            Logger::outputDebugString(String (outputBuffer[n]));
        
        zeromem (outputBuffer, MAIN_DMX_CHANNEL_BUFFER_COUNT * 2);
        fader.setLevel (FADER_MAX_LEVEL >> 2);
        fader.updateBuffer (outputBuffer, FADER_MAX_LEVEL);
        Logger::outputDebugString ("Quarter");
        for (int n = 0; n < 32; ++n)
            Logger::outputDebugString(String (outputBuffer[n]));
        
        fader.clearCue();
        Logger::outputDebugString ("It fades!");
#endif
    }
    else
        result = false;
        
    if (result == false)
    {
        cueList.clear();
        deviceList.clear();
        return false;
    }
    
    broadcastMessage (Console::ShowLoaded);
    return true;
}

//==============================================================================
// Player Comm functions
//
void Console::broadcastMessage (Console::Message msg)
{
    Logger::outputDebugString ("Console broadcast: " + String (msg));
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
    }
}

