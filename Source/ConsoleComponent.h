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
#include "Console.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ConsoleComponent  : public Component,
                          Timer,
                          public SliderListener,
                          public ButtonListener
{
public:
    //==============================================================================
    ConsoleComponent (BlueLiteDevice::Ptr blueliteDevice_);
    ~ConsoleComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback() override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    void updateThumb (Slider* slider);
    void updateStats();

    BlueLiteDevice::Ptr blueliteDevice;
    ScopedPointer<Console> console;

    Console::SliderHandle xFader;
    Console::SliderHandle yFader;

    int numberOfFaders;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> gmLabel;
    ScopedPointer<Label> label;
    ScopedPointer<Slider> gmSlider;
    ScopedPointer<TextButton> loadButton;
    ScopedPointer<Label> loadedLabel;
    ScopedPointer<Label> cuesLabel;
    ScopedPointer<Label> devsLabel;
    ScopedPointer<Label> universesLabel;
    ScopedPointer<TextButton> newButton;
    ScopedPointer<Label> fadersLabel;
    ScopedPointer<TextButton> clearAllButton;
    ScopedPointer<Label> xLabel;
    ScopedPointer<Label> label2;
    ScopedPointer<Slider> xSlider;
    ScopedPointer<Label> yLabel;
    ScopedPointer<Label> label3;
    ScopedPointer<Slider> ySlider;
    ScopedPointer<TextButton> xCueButton;
    ScopedPointer<TextButton> yCueButton;
    ScopedPointer<ToggleButton> artnetButton;
    ScopedPointer<Label> dmxLabel;
    ScopedPointer<Drawable> drawable1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConsoleComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_945E0AE88D0433AC__
