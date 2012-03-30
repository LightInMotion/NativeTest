/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  29 Mar 2012 10:33:41pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_DMXOUTCOMPONENT_DMXOUTCOMPONENT_5FB2D384__
#define __JUCER_HEADER_DMXOUTCOMPONENT_DMXOUTCOMPONENT_5FB2D384__

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
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    void sendData();

    BlueLiteDevice::Ptr blueliteDevice;
    MemoryBlock dmxData;
    //[/UserVariables]

    //==============================================================================
    Slider* slider1;
    Slider* slider2;
    Slider* slider3;
    Slider* slider4;
    Slider* slider5;
    Slider* slider6;
    Slider* slider7;
    Slider* slider8;
    Slider* slider9;
    Slider* slider10;
    Slider* slider11;
    Slider* slider12;
    Slider* slider13;
    Slider* slider14;
    Slider* slider15;
    Slider* slider16;
    Slider* slider17;
    Slider* slider18;
    Slider* slider19;
    Slider* slider20;
    Slider* slider21;
    Slider* slider22;
    Slider* slider23;
    Slider* slider24;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    DmxOutComponent (const DmxOutComponent&);
    const DmxOutComponent& operator= (const DmxOutComponent&);
};


#endif   // __JUCER_HEADER_DMXOUTCOMPONENT_DMXOUTCOMPONENT_5FB2D384__
