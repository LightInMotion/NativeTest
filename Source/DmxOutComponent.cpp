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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "DmxOutComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
DmxOutComponent::DmxOutComponent (BlueLiteDevice::Ptr blueliteDevice_)
    : blueliteDevice (blueliteDevice_),
      dmxData (24)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (slider1 = new Slider ("slider1"));
    slider1->setTooltip (TRANS("Channel 1"));
    slider1->setExplicitFocusOrder (1);
    slider1->setRange (0, 255, 1);
    slider1->setSliderStyle (Slider::LinearVertical);
    slider1->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider1->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider1->addListener (this);

    addAndMakeVisible (slider2 = new Slider ("slider2"));
    slider2->setTooltip (TRANS("Channel 2"));
    slider2->setExplicitFocusOrder (2);
    slider2->setRange (0, 255, 1);
    slider2->setSliderStyle (Slider::LinearVertical);
    slider2->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider2->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider2->addListener (this);

    addAndMakeVisible (slider3 = new Slider ("slider3"));
    slider3->setTooltip (TRANS("Channel 3"));
    slider3->setExplicitFocusOrder (3);
    slider3->setRange (0, 255, 1);
    slider3->setSliderStyle (Slider::LinearVertical);
    slider3->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider3->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider3->addListener (this);

    addAndMakeVisible (slider4 = new Slider ("slider4"));
    slider4->setTooltip (TRANS("Channel 4"));
    slider4->setExplicitFocusOrder (4);
    slider4->setRange (0, 255, 1);
    slider4->setSliderStyle (Slider::LinearVertical);
    slider4->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider4->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider4->addListener (this);

    addAndMakeVisible (slider5 = new Slider ("slider5"));
    slider5->setTooltip (TRANS("Channel 5"));
    slider5->setExplicitFocusOrder (5);
    slider5->setRange (0, 255, 1);
    slider5->setSliderStyle (Slider::LinearVertical);
    slider5->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider5->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider5->addListener (this);

    addAndMakeVisible (slider6 = new Slider ("slider6"));
    slider6->setTooltip (TRANS("Channel 6"));
    slider6->setExplicitFocusOrder (6);
    slider6->setRange (0, 255, 1);
    slider6->setSliderStyle (Slider::LinearVertical);
    slider6->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider6->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider6->addListener (this);

    addAndMakeVisible (slider7 = new Slider ("slider7"));
    slider7->setTooltip (TRANS("Channel 7"));
    slider7->setExplicitFocusOrder (7);
    slider7->setRange (0, 255, 1);
    slider7->setSliderStyle (Slider::LinearVertical);
    slider7->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider7->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider7->addListener (this);

    addAndMakeVisible (slider8 = new Slider ("slider8"));
    slider8->setTooltip (TRANS("Channel 8"));
    slider8->setExplicitFocusOrder (8);
    slider8->setRange (0, 255, 1);
    slider8->setSliderStyle (Slider::LinearVertical);
    slider8->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider8->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider8->addListener (this);

    addAndMakeVisible (slider9 = new Slider ("slider9"));
    slider9->setTooltip (TRANS("Channel 9"));
    slider9->setExplicitFocusOrder (9);
    slider9->setRange (0, 255, 1);
    slider9->setSliderStyle (Slider::LinearVertical);
    slider9->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider9->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider9->addListener (this);

    addAndMakeVisible (slider10 = new Slider ("slider10"));
    slider10->setTooltip (TRANS("Channel 10"));
    slider10->setExplicitFocusOrder (10);
    slider10->setRange (0, 255, 1);
    slider10->setSliderStyle (Slider::LinearVertical);
    slider10->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider10->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider10->addListener (this);

    addAndMakeVisible (slider11 = new Slider ("slider11"));
    slider11->setTooltip (TRANS("Channel 11"));
    slider11->setExplicitFocusOrder (11);
    slider11->setRange (0, 255, 1);
    slider11->setSliderStyle (Slider::LinearVertical);
    slider11->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider11->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider11->addListener (this);

    addAndMakeVisible (slider12 = new Slider ("slider12"));
    slider12->setTooltip (TRANS("Channel 12"));
    slider12->setExplicitFocusOrder (12);
    slider12->setRange (0, 255, 1);
    slider12->setSliderStyle (Slider::LinearVertical);
    slider12->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider12->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider12->addListener (this);

    addAndMakeVisible (slider13 = new Slider ("slider13"));
    slider13->setTooltip (TRANS("Channel 13"));
    slider13->setExplicitFocusOrder (13);
    slider13->setRange (0, 255, 1);
    slider13->setSliderStyle (Slider::LinearVertical);
    slider13->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider13->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider13->addListener (this);

    addAndMakeVisible (slider14 = new Slider ("slider14"));
    slider14->setTooltip (TRANS("Channel 14"));
    slider14->setExplicitFocusOrder (14);
    slider14->setRange (0, 255, 1);
    slider14->setSliderStyle (Slider::LinearVertical);
    slider14->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider14->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider14->addListener (this);

    addAndMakeVisible (slider15 = new Slider ("slider15"));
    slider15->setTooltip (TRANS("Channel 15"));
    slider15->setExplicitFocusOrder (15);
    slider15->setRange (0, 255, 1);
    slider15->setSliderStyle (Slider::LinearVertical);
    slider15->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider15->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider15->addListener (this);

    addAndMakeVisible (slider16 = new Slider ("slider16"));
    slider16->setTooltip (TRANS("Channel 16"));
    slider16->setExplicitFocusOrder (16);
    slider16->setRange (0, 255, 1);
    slider16->setSliderStyle (Slider::LinearVertical);
    slider16->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider16->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider16->addListener (this);

    addAndMakeVisible (slider17 = new Slider ("slider17"));
    slider17->setTooltip (TRANS("Channel 17"));
    slider17->setRange (0, 255, 1);
    slider17->setSliderStyle (Slider::LinearVertical);
    slider17->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider17->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider17->addListener (this);

    addAndMakeVisible (slider18 = new Slider ("slider18"));
    slider18->setTooltip (TRANS("Channel 18"));
    slider18->setExplicitFocusOrder (18);
    slider18->setRange (0, 255, 1);
    slider18->setSliderStyle (Slider::LinearVertical);
    slider18->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider18->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider18->addListener (this);

    addAndMakeVisible (slider19 = new Slider ("slider19"));
    slider19->setTooltip (TRANS("Channel 19"));
    slider19->setExplicitFocusOrder (19);
    slider19->setRange (0, 255, 1);
    slider19->setSliderStyle (Slider::LinearVertical);
    slider19->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider19->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider19->addListener (this);

    addAndMakeVisible (slider20 = new Slider ("slider20"));
    slider20->setTooltip (TRANS("Channel 20"));
    slider20->setExplicitFocusOrder (20);
    slider20->setRange (0, 255, 1);
    slider20->setSliderStyle (Slider::LinearVertical);
    slider20->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider20->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider20->addListener (this);

    addAndMakeVisible (slider21 = new Slider ("slider21"));
    slider21->setTooltip (TRANS("Channel 21"));
    slider21->setExplicitFocusOrder (21);
    slider21->setRange (0, 255, 1);
    slider21->setSliderStyle (Slider::LinearVertical);
    slider21->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider21->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider21->addListener (this);

    addAndMakeVisible (slider22 = new Slider ("slider22"));
    slider22->setTooltip (TRANS("Channel 22"));
    slider22->setExplicitFocusOrder (22);
    slider22->setRange (0, 255, 1);
    slider22->setSliderStyle (Slider::LinearVertical);
    slider22->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider22->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider22->addListener (this);

    addAndMakeVisible (slider23 = new Slider ("slider23"));
    slider23->setTooltip (TRANS("Channel 23"));
    slider23->setExplicitFocusOrder (23);
    slider23->setRange (0, 255, 1);
    slider23->setSliderStyle (Slider::LinearVertical);
    slider23->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider23->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider23->addListener (this);

    addAndMakeVisible (slider24 = new Slider ("slider24"));
    slider24->setTooltip (TRANS("Channel 24"));
    slider24->setExplicitFocusOrder (24);
    slider24->setRange (0, 255, 1);
    slider24->setSliderStyle (Slider::LinearVertical);
    slider24->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider24->setColour (Slider::thumbColourId, Colour (0xff252525));
    slider24->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (416, 440);


    //[Constructor] You can add your own custom stuff here..
    dmxData.fillWith (0);
    sendData();
    //[/Constructor]
}

DmxOutComponent::~DmxOutComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    slider1 = nullptr;
    slider2 = nullptr;
    slider3 = nullptr;
    slider4 = nullptr;
    slider5 = nullptr;
    slider6 = nullptr;
    slider7 = nullptr;
    slider8 = nullptr;
    slider9 = nullptr;
    slider10 = nullptr;
    slider11 = nullptr;
    slider12 = nullptr;
    slider13 = nullptr;
    slider14 = nullptr;
    slider15 = nullptr;
    slider16 = nullptr;
    slider17 = nullptr;
    slider18 = nullptr;
    slider19 = nullptr;
    slider20 = nullptr;
    slider21 = nullptr;
    slider22 = nullptr;
    slider23 = nullptr;
    slider24 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void DmxOutComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void DmxOutComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    slider1->setBounds (proportionOfWidth (0.0585f), proportionOfHeight (0.0552f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider2->setBounds (proportionOfWidth (0.1330f), proportionOfHeight (0.0552f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider3->setBounds (proportionOfWidth (0.2128f), proportionOfHeight (0.0552f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider4->setBounds (proportionOfWidth (0.2872f), proportionOfHeight (0.0552f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider5->setBounds (proportionOfWidth (0.3670f), proportionOfHeight (0.0552f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider6->setBounds (proportionOfWidth (0.4442f), proportionOfHeight (0.0552f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider7->setBounds (proportionOfWidth (0.5186f), proportionOfHeight (0.0552f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider8->setBounds (proportionOfWidth (0.5931f), proportionOfHeight (0.0552f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider9->setBounds (proportionOfWidth (0.6729f), proportionOfHeight (0.0552f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider10->setBounds (proportionOfWidth (0.7473f), proportionOfHeight (0.0552f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider11->setBounds (proportionOfWidth (0.8245f), proportionOfHeight (0.0552f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider12->setBounds (proportionOfWidth (0.9016f), proportionOfHeight (0.0552f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider13->setBounds (proportionOfWidth (0.0585f), proportionOfHeight (0.5259f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider14->setBounds (proportionOfWidth (0.1330f), proportionOfHeight (0.5259f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider15->setBounds (proportionOfWidth (0.2128f), proportionOfHeight (0.5259f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider16->setBounds (proportionOfWidth (0.2872f), proportionOfHeight (0.5259f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider17->setBounds (proportionOfWidth (0.3670f), proportionOfHeight (0.5259f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider18->setBounds (proportionOfWidth (0.4442f), proportionOfHeight (0.5259f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider19->setBounds (proportionOfWidth (0.5186f), proportionOfHeight (0.5259f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider20->setBounds (proportionOfWidth (0.5931f), proportionOfHeight (0.5259f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider21->setBounds (proportionOfWidth (0.6729f), proportionOfHeight (0.5259f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider22->setBounds (proportionOfWidth (0.7473f), proportionOfHeight (0.5259f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider23->setBounds (proportionOfWidth (0.8245f), proportionOfHeight (0.5259f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    slider24->setBounds (proportionOfWidth (0.9016f), proportionOfHeight (0.5259f), proportionOfWidth (0.0346f), proportionOfHeight (0.4172f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void DmxOutComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    int index = -1;
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider1)
    {
        //[UserSliderCode_slider1] -- add your slider handling code here..
        index = 0;
        //[/UserSliderCode_slider1]
    }
    else if (sliderThatWasMoved == slider2)
    {
        //[UserSliderCode_slider2] -- add your slider handling code here..
        index = 1;
        //[/UserSliderCode_slider2]
    }
    else if (sliderThatWasMoved == slider3)
    {
        //[UserSliderCode_slider3] -- add your slider handling code here..
        index = 2;
        //[/UserSliderCode_slider3]
    }
    else if (sliderThatWasMoved == slider4)
    {
        //[UserSliderCode_slider4] -- add your slider handling code here..
        index = 3;
        //[/UserSliderCode_slider4]
    }
    else if (sliderThatWasMoved == slider5)
    {
        //[UserSliderCode_slider5] -- add your slider handling code here..
        index = 4;
        //[/UserSliderCode_slider5]
    }
    else if (sliderThatWasMoved == slider6)
    {
        //[UserSliderCode_slider6] -- add your slider handling code here..
        index = 5;
        //[/UserSliderCode_slider6]
    }
    else if (sliderThatWasMoved == slider7)
    {
        //[UserSliderCode_slider7] -- add your slider handling code here..
        index = 6;
        //[/UserSliderCode_slider7]
    }
    else if (sliderThatWasMoved == slider8)
    {
        //[UserSliderCode_slider8] -- add your slider handling code here..
        index = 7;
        //[/UserSliderCode_slider8]
    }
    else if (sliderThatWasMoved == slider9)
    {
        //[UserSliderCode_slider9] -- add your slider handling code here..
        index = 8;
        //[/UserSliderCode_slider9]
    }
    else if (sliderThatWasMoved == slider10)
    {
        //[UserSliderCode_slider10] -- add your slider handling code here..
        index = 9;
        //[/UserSliderCode_slider10]
    }
    else if (sliderThatWasMoved == slider11)
    {
        //[UserSliderCode_slider11] -- add your slider handling code here..
        index = 10;
        //[/UserSliderCode_slider11]
    }
    else if (sliderThatWasMoved == slider12)
    {
        //[UserSliderCode_slider12] -- add your slider handling code here..
        index = 11;
        //[/UserSliderCode_slider12]
    }
    else if (sliderThatWasMoved == slider13)
    {
        //[UserSliderCode_slider13] -- add your slider handling code here..
        index = 12;
        //[/UserSliderCode_slider13]
    }
    else if (sliderThatWasMoved == slider14)
    {
        //[UserSliderCode_slider14] -- add your slider handling code here..
        index = 13;
        //[/UserSliderCode_slider14]
    }
    else if (sliderThatWasMoved == slider15)
    {
        //[UserSliderCode_slider15] -- add your slider handling code here..
        index = 14;
        //[/UserSliderCode_slider15]
    }
    else if (sliderThatWasMoved == slider16)
    {
        //[UserSliderCode_slider16] -- add your slider handling code here..
        index = 15;
        //[/UserSliderCode_slider16]
    }
    else if (sliderThatWasMoved == slider17)
    {
        //[UserSliderCode_slider17] -- add your slider handling code here..
        index = 16;
        //[/UserSliderCode_slider17]
    }
    else if (sliderThatWasMoved == slider18)
    {
        //[UserSliderCode_slider18] -- add your slider handling code here..
        index = 17;
        //[/UserSliderCode_slider18]
    }
    else if (sliderThatWasMoved == slider19)
    {
        //[UserSliderCode_slider19] -- add your slider handling code here..
        index = 18;
        //[/UserSliderCode_slider19]
    }
    else if (sliderThatWasMoved == slider20)
    {
        //[UserSliderCode_slider20] -- add your slider handling code here..
        index = 19;
        //[/UserSliderCode_slider20]
    }
    else if (sliderThatWasMoved == slider21)
    {
        //[UserSliderCode_slider21] -- add your slider handling code here..
        index = 20;
        //[/UserSliderCode_slider21]
    }
    else if (sliderThatWasMoved == slider22)
    {
        //[UserSliderCode_slider22] -- add your slider handling code here..
        index = 21;
        //[/UserSliderCode_slider22]
    }
    else if (sliderThatWasMoved == slider23)
    {
        //[UserSliderCode_slider23] -- add your slider handling code here..
        index = 22;
        //[/UserSliderCode_slider23]
    }
    else if (sliderThatWasMoved == slider24)
    {
        //[UserSliderCode_slider24] -- add your slider handling code here..
        index = 23;
        //[/UserSliderCode_slider24]
    }

    //[UsersliderValueChanged_Post]
    if (index >= 0)
    {
        dmxData[index] = (uint8)sliderThatWasMoved->getValue();
        sendData();
        updateThumb (index, sliderThatWasMoved);
    }
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void DmxOutComponent::updateThumb (int index, Slider* slider)
{
if (dmxData[index] == 0)
    slider->setColour (Slider::thumbColourId, Colour (0xff252525));
else if ((uint8)dmxData[index] == 255)
    slider->setColour (Slider::thumbColourId, Colour (0xffbFbFbF));
else
    slider->setColour (Slider::thumbColourId, Colour (0xff757575));
}

void DmxOutComponent::sendData()
{
    Result r = blueliteDevice->updateDmxData (0, dmxData);
    if (r.failed())
        Logger::outputDebugString("DMX output error: " + r.getErrorMessage());
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="DmxOutComponent" componentName=""
                 parentClasses="public Component" constructorParams="BlueLiteDevice::Ptr blueliteDevice_"
                 variableInitialisers="blueliteDevice (blueliteDevice_),&#10;dmxData (24)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="416" initialHeight="440">
  <BACKGROUND backgroundColour="ffffff"/>
  <SLIDER name="slider1" id="3dd4263526f2660a" memberName="slider1" virtualName=""
          explicitFocusOrder="1" pos="5.851% 5.517% 3.457% 41.724%" tooltip="Channel 1"
          thumbcol="ff252525" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider2" id="360ef04fca23b799" memberName="slider2" virtualName=""
          explicitFocusOrder="2" pos="13.298% 5.517% 3.457% 41.724%" tooltip="Channel 2"
          thumbcol="ff252525" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider3" id="580efc4de85d7adc" memberName="slider3" virtualName=""
          explicitFocusOrder="3" pos="21.277% 5.517% 3.457% 41.724%" tooltip="Channel 3"
          thumbcol="ff252525" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider4" id="f2dde0dd416c1e84" memberName="slider4" virtualName=""
          explicitFocusOrder="4" pos="28.723% 5.517% 3.457% 41.724%" tooltip="Channel 4"
          thumbcol="ff252525" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider5" id="bfb4535b82185fed" memberName="slider5" virtualName=""
          explicitFocusOrder="5" pos="36.702% 5.517% 3.457% 41.724%" tooltip="Channel 5"
          thumbcol="ff252525" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider6" id="679f90b8f07cb4ee" memberName="slider6" virtualName=""
          explicitFocusOrder="6" pos="44.415% 5.517% 3.457% 41.724%" tooltip="Channel 6"
          thumbcol="ff252525" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider7" id="44ad98a2262cd229" memberName="slider7" virtualName=""
          explicitFocusOrder="7" pos="51.862% 5.517% 3.457% 41.724%" tooltip="Channel 7"
          thumbcol="ff252525" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider8" id="85ff76e13a1ec2a3" memberName="slider8" virtualName=""
          explicitFocusOrder="8" pos="59.309% 5.517% 3.457% 41.724%" tooltip="Channel 8"
          thumbcol="ff252525" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider9" id="776c3f04e2556496" memberName="slider9" virtualName=""
          explicitFocusOrder="9" pos="67.287% 5.517% 3.457% 41.724%" tooltip="Channel 9"
          thumbcol="ff252525" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider10" id="3ae59e3cf4f55f86" memberName="slider10" virtualName=""
          explicitFocusOrder="10" pos="74.734% 5.517% 3.457% 41.724%" tooltip="Channel 10"
          thumbcol="ff252525" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider11" id="79792787596ae791" memberName="slider11" virtualName=""
          explicitFocusOrder="11" pos="82.447% 5.517% 3.457% 41.724%" tooltip="Channel 11"
          thumbcol="ff252525" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider12" id="71d7be10add7e20b" memberName="slider12" virtualName=""
          explicitFocusOrder="12" pos="90.16% 5.517% 3.457% 41.724%" tooltip="Channel 12"
          thumbcol="ff252525" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider13" id="f4fec1d538673f4a" memberName="slider13" virtualName=""
          explicitFocusOrder="13" pos="5.851% 52.586% 3.457% 41.724%" tooltip="Channel 13"
          thumbcol="ff252525" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider14" id="2a85667136c4a974" memberName="slider14" virtualName=""
          explicitFocusOrder="14" pos="13.298% 52.586% 3.457% 41.724%"
          tooltip="Channel 14" thumbcol="ff252525" min="0" max="255" int="1"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider15" id="dd34e28ad89b9dbd" memberName="slider15" virtualName=""
          explicitFocusOrder="15" pos="21.277% 52.586% 3.457% 41.724%"
          tooltip="Channel 15" thumbcol="ff252525" min="0" max="255" int="1"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider16" id="1800066dd5b0e135" memberName="slider16" virtualName=""
          explicitFocusOrder="16" pos="28.723% 52.586% 3.457% 41.724%"
          tooltip="Channel 16" thumbcol="ff252525" min="0" max="255" int="1"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider17" id="246bcbd8f7c8a43" memberName="slider17" virtualName=""
          explicitFocusOrder="0" pos="36.702% 52.586% 3.457% 41.724%" tooltip="Channel 17"
          thumbcol="ff252525" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider18" id="b0c57e3500d80cd5" memberName="slider18" virtualName=""
          explicitFocusOrder="18" pos="44.415% 52.586% 3.457% 41.724%"
          tooltip="Channel 18" thumbcol="ff252525" min="0" max="255" int="1"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider19" id="ae0da53a6fe6f1b9" memberName="slider19" virtualName=""
          explicitFocusOrder="19" pos="51.862% 52.586% 3.457% 41.724%"
          tooltip="Channel 19" thumbcol="ff252525" min="0" max="255" int="1"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider20" id="bf3f1185e99f8568" memberName="slider20" virtualName=""
          explicitFocusOrder="20" pos="59.309% 52.586% 3.457% 41.724%"
          tooltip="Channel 20" thumbcol="ff252525" min="0" max="255" int="1"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider21" id="d00d46b0bf7a97d5" memberName="slider21" virtualName=""
          explicitFocusOrder="21" pos="67.287% 52.586% 3.457% 41.724%"
          tooltip="Channel 21" thumbcol="ff252525" min="0" max="255" int="1"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider22" id="f1e61468b0b315f8" memberName="slider22" virtualName=""
          explicitFocusOrder="22" pos="74.734% 52.586% 3.457% 41.724%"
          tooltip="Channel 22" thumbcol="ff252525" min="0" max="255" int="1"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider23" id="3c9af5933de7a732" memberName="slider23" virtualName=""
          explicitFocusOrder="23" pos="82.447% 52.586% 3.457% 41.724%"
          tooltip="Channel 23" thumbcol="ff252525" min="0" max="255" int="1"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="slider24" id="112c3bb5c3f5dbb9" memberName="slider24" virtualName=""
          explicitFocusOrder="24" pos="90.16% 52.586% 3.457% 41.724%" tooltip="Channel 24"
          thumbcol="ff252525" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
