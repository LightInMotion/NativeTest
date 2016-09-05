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

#ifndef __JUCE_HEADER_EBB4BE8016DE70C0__
#define __JUCE_HEADER_EBB4BE8016DE70C0__

//[Headers]     -- You can add your own extra header files here --
#include "BlueLiteDevice.h"
#include "../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class DmxOutComponent  : public Component,
                         public SliderListener
{
public:
    //==============================================================================
    DmxOutComponent (BlueLiteDevice::Ptr blueliteDevice_);
    ~DmxOutComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void updateThumb (int index, Slider* slider);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    void sendData();

    BlueLiteDevice::Ptr blueliteDevice;
    MemoryBlock dmxData;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> slider1;
    ScopedPointer<Slider> slider2;
    ScopedPointer<Slider> slider3;
    ScopedPointer<Slider> slider4;
    ScopedPointer<Slider> slider5;
    ScopedPointer<Slider> slider6;
    ScopedPointer<Slider> slider7;
    ScopedPointer<Slider> slider8;
    ScopedPointer<Slider> slider9;
    ScopedPointer<Slider> slider10;
    ScopedPointer<Slider> slider11;
    ScopedPointer<Slider> slider12;
    ScopedPointer<Slider> slider13;
    ScopedPointer<Slider> slider14;
    ScopedPointer<Slider> slider15;
    ScopedPointer<Slider> slider16;
    ScopedPointer<Slider> slider17;
    ScopedPointer<Slider> slider18;
    ScopedPointer<Slider> slider19;
    ScopedPointer<Slider> slider20;
    ScopedPointer<Slider> slider21;
    ScopedPointer<Slider> slider22;
    ScopedPointer<Slider> slider23;
    ScopedPointer<Slider> slider24;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DmxOutComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_EBB4BE8016DE70C0__
