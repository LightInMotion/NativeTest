/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.2.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_945E0AE88D0433AC__
#define __JUCE_HEADER_945E0AE88D0433AC__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "BlueLiteDevice.h"
#include "Device.h"
#include "Cue.h"
#include "Fader.h"
#include "EffectPattern.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ConsoleComponent  : public Component,
                          Thread
{
public:
    //==============================================================================
    ConsoleComponent (BlueLiteDevice::Ptr blueliteDevice_);
    ~ConsoleComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    bool loadFile (File file);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    void run() override;

    BlueLiteDevice::Ptr blueliteDevice;
    BlueLiteEvent::Ptr timeEvent;
    
    OwnedArray<EffectPattern> effectPatterns;
    OwnedArray<Device> deviceList;
    OwnedArray<Cue> cueList;
    OwnedArray<Fader> faderList;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConsoleComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_945E0AE88D0433AC__
