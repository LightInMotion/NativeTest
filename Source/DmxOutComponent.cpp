/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  29 Mar 2012 9:48:39am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "DmxOutComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
DmxOutComponent::DmxOutComponent (BlueLiteX1Mini& blueliteMini_)
    : blueliteMini (blueliteMini_),
      dmxData (24),
      slider1 (0),
      slider2 (0),
      slider3 (0),
      slider4 (0),
      slider5 (0),
      slider6 (0),
      slider7 (0),
      slider8 (0),
      slider9 (0),
      slider10 (0),
      slider11 (0),
      slider12 (0),
      slider13 (0),
      slider14 (0),
      slider15 (0),
      slider16 (0),
      slider17 (0),
      slider18 (0),
      slider19 (0),
      slider20 (0),
      slider21 (0),
      slider22 (0),
      slider23 (0),
      slider24 (0)
{
    addAndMakeVisible (slider1 = new Slider (L"slider1"));
    slider1->setTooltip (L"Channel 1");
    slider1->setExplicitFocusOrder (1);
    slider1->setRange (0, 255, 1);
    slider1->setSliderStyle (Slider::LinearVertical);
    slider1->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider1->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider1->addListener (this);

    addAndMakeVisible (slider2 = new Slider (L"slider2"));
    slider2->setTooltip (L"Channel 2");
    slider2->setExplicitFocusOrder (2);
    slider2->setRange (0, 255, 1);
    slider2->setSliderStyle (Slider::LinearVertical);
    slider2->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider2->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider2->addListener (this);

    addAndMakeVisible (slider3 = new Slider (L"slider3"));
    slider3->setTooltip (L"Channel 3");
    slider3->setExplicitFocusOrder (3);
    slider3->setRange (0, 255, 1);
    slider3->setSliderStyle (Slider::LinearVertical);
    slider3->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider3->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider3->addListener (this);

    addAndMakeVisible (slider4 = new Slider (L"slider4"));
    slider4->setTooltip (L"Channel 4");
    slider4->setExplicitFocusOrder (4);
    slider4->setRange (0, 255, 1);
    slider4->setSliderStyle (Slider::LinearVertical);
    slider4->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider4->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider4->addListener (this);

    addAndMakeVisible (slider5 = new Slider (L"slider5"));
    slider5->setTooltip (L"Channel 5");
    slider5->setExplicitFocusOrder (5);
    slider5->setRange (0, 255, 1);
    slider5->setSliderStyle (Slider::LinearVertical);
    slider5->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider5->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider5->addListener (this);

    addAndMakeVisible (slider6 = new Slider (L"slider6"));
    slider6->setTooltip (L"Channel 6");
    slider6->setExplicitFocusOrder (6);
    slider6->setRange (0, 255, 1);
    slider6->setSliderStyle (Slider::LinearVertical);
    slider6->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider6->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider6->addListener (this);

    addAndMakeVisible (slider7 = new Slider (L"slider7"));
    slider7->setTooltip (L"Channel 7");
    slider7->setExplicitFocusOrder (7);
    slider7->setRange (0, 255, 1);
    slider7->setSliderStyle (Slider::LinearVertical);
    slider7->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider7->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider7->addListener (this);

    addAndMakeVisible (slider8 = new Slider (L"slider8"));
    slider8->setTooltip (L"Channel 8");
    slider8->setExplicitFocusOrder (8);
    slider8->setRange (0, 255, 1);
    slider8->setSliderStyle (Slider::LinearVertical);
    slider8->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider8->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider8->addListener (this);

    addAndMakeVisible (slider9 = new Slider (L"slider9"));
    slider9->setTooltip (L"Channel 9");
    slider9->setExplicitFocusOrder (9);
    slider9->setRange (0, 255, 1);
    slider9->setSliderStyle (Slider::LinearVertical);
    slider9->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider9->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider9->addListener (this);

    addAndMakeVisible (slider10 = new Slider (L"slider10"));
    slider10->setTooltip (L"Channel 10");
    slider10->setExplicitFocusOrder (10);
    slider10->setRange (0, 255, 1);
    slider10->setSliderStyle (Slider::LinearVertical);
    slider10->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider10->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider10->addListener (this);

    addAndMakeVisible (slider11 = new Slider (L"slider11"));
    slider11->setTooltip (L"Channel 11");
    slider11->setExplicitFocusOrder (11);
    slider11->setRange (0, 255, 1);
    slider11->setSliderStyle (Slider::LinearVertical);
    slider11->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider11->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider11->addListener (this);

    addAndMakeVisible (slider12 = new Slider (L"slider12"));
    slider12->setTooltip (L"Channel 12");
    slider12->setExplicitFocusOrder (12);
    slider12->setRange (0, 255, 1);
    slider12->setSliderStyle (Slider::LinearVertical);
    slider12->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider12->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider12->addListener (this);

    addAndMakeVisible (slider13 = new Slider (L"slider13"));
    slider13->setTooltip (L"Channel 13");
    slider13->setExplicitFocusOrder (13);
    slider13->setRange (0, 255, 1);
    slider13->setSliderStyle (Slider::LinearVertical);
    slider13->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider13->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider13->addListener (this);

    addAndMakeVisible (slider14 = new Slider (L"slider14"));
    slider14->setTooltip (L"Channel 14");
    slider14->setExplicitFocusOrder (14);
    slider14->setRange (0, 255, 1);
    slider14->setSliderStyle (Slider::LinearVertical);
    slider14->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider14->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider14->addListener (this);

    addAndMakeVisible (slider15 = new Slider (L"slider15"));
    slider15->setTooltip (L"Channel 15");
    slider15->setExplicitFocusOrder (15);
    slider15->setRange (0, 255, 1);
    slider15->setSliderStyle (Slider::LinearVertical);
    slider15->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider15->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider15->addListener (this);

    addAndMakeVisible (slider16 = new Slider (L"slider16"));
    slider16->setTooltip (L"Channel 16");
    slider16->setExplicitFocusOrder (16);
    slider16->setRange (0, 255, 1);
    slider16->setSliderStyle (Slider::LinearVertical);
    slider16->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider16->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider16->addListener (this);

    addAndMakeVisible (slider17 = new Slider (L"slider17"));
    slider17->setTooltip (L"Channel 17");
    slider17->setRange (0, 255, 1);
    slider17->setSliderStyle (Slider::LinearVertical);
    slider17->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider17->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider17->addListener (this);

    addAndMakeVisible (slider18 = new Slider (L"slider18"));
    slider18->setTooltip (L"Channel 18");
    slider18->setExplicitFocusOrder (18);
    slider18->setRange (0, 255, 1);
    slider18->setSliderStyle (Slider::LinearVertical);
    slider18->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider18->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider18->addListener (this);

    addAndMakeVisible (slider19 = new Slider (L"slider19"));
    slider19->setTooltip (L"Channel 19");
    slider19->setExplicitFocusOrder (19);
    slider19->setRange (0, 255, 1);
    slider19->setSliderStyle (Slider::LinearVertical);
    slider19->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider19->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider19->addListener (this);

    addAndMakeVisible (slider20 = new Slider (L"slider20"));
    slider20->setTooltip (L"Channel 20");
    slider20->setExplicitFocusOrder (20);
    slider20->setRange (0, 255, 1);
    slider20->setSliderStyle (Slider::LinearVertical);
    slider20->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider20->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider20->addListener (this);

    addAndMakeVisible (slider21 = new Slider (L"slider21"));
    slider21->setTooltip (L"Channel 21");
    slider21->setExplicitFocusOrder (21);
    slider21->setRange (0, 255, 1);
    slider21->setSliderStyle (Slider::LinearVertical);
    slider21->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider21->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider21->addListener (this);

    addAndMakeVisible (slider22 = new Slider (L"slider22"));
    slider22->setTooltip (L"Channel 22");
    slider22->setExplicitFocusOrder (22);
    slider22->setRange (0, 255, 1);
    slider22->setSliderStyle (Slider::LinearVertical);
    slider22->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider22->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider22->addListener (this);

    addAndMakeVisible (slider23 = new Slider (L"slider23"));
    slider23->setTooltip (L"Channel 23");
    slider23->setExplicitFocusOrder (23);
    slider23->setRange (0, 255, 1);
    slider23->setSliderStyle (Slider::LinearVertical);
    slider23->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider23->setColour (Slider::thumbColourId, Colour (0xff757575));
    slider23->addListener (this);

    addAndMakeVisible (slider24 = new Slider (L"slider24"));
    slider24->setTooltip (L"Channel 24");
    slider24->setExplicitFocusOrder (24);
    slider24->setRange (0, 255, 1);
    slider24->setSliderStyle (Slider::LinearVertical);
    slider24->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider24->setColour (Slider::thumbColourId, Colour (0xff757575));
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

    deleteAndZero (slider1);
    deleteAndZero (slider2);
    deleteAndZero (slider3);
    deleteAndZero (slider4);
    deleteAndZero (slider5);
    deleteAndZero (slider6);
    deleteAndZero (slider7);
    deleteAndZero (slider8);
    deleteAndZero (slider9);
    deleteAndZero (slider10);
    deleteAndZero (slider11);
    deleteAndZero (slider12);
    deleteAndZero (slider13);
    deleteAndZero (slider14);
    deleteAndZero (slider15);
    deleteAndZero (slider16);
    deleteAndZero (slider17);
    deleteAndZero (slider18);
    deleteAndZero (slider19);
    deleteAndZero (slider20);
    deleteAndZero (slider21);
    deleteAndZero (slider22);
    deleteAndZero (slider23);
    deleteAndZero (slider24);


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
    slider1->setBounds (proportionOfWidth (0.0579f), proportionOfHeight (0.0547f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider2->setBounds (proportionOfWidth (0.1335f), proportionOfHeight (0.0547f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider3->setBounds (proportionOfWidth (0.2116f), proportionOfHeight (0.0547f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider4->setBounds (proportionOfWidth (0.2871f), proportionOfHeight (0.0547f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider5->setBounds (proportionOfWidth (0.3652f), proportionOfHeight (0.0547f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider6->setBounds (proportionOfWidth (0.4408f), proportionOfHeight (0.0547f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider7->setBounds (proportionOfWidth (0.5189f), proportionOfHeight (0.0547f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider8->setBounds (proportionOfWidth (0.5945f), proportionOfHeight (0.0547f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider9->setBounds (proportionOfWidth (0.6725f), proportionOfHeight (0.0547f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider10->setBounds (proportionOfWidth (0.7481f), proportionOfHeight (0.0547f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider11->setBounds (proportionOfWidth (0.8262f), proportionOfHeight (0.0547f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider12->setBounds (proportionOfWidth (0.9018f), proportionOfHeight (0.0547f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider13->setBounds (proportionOfWidth (0.0579f), proportionOfHeight (0.5262f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider14->setBounds (proportionOfWidth (0.1335f), proportionOfHeight (0.5262f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider15->setBounds (proportionOfWidth (0.2116f), proportionOfHeight (0.5262f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider16->setBounds (proportionOfWidth (0.2871f), proportionOfHeight (0.5262f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider17->setBounds (proportionOfWidth (0.3652f), proportionOfHeight (0.5262f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider18->setBounds (proportionOfWidth (0.4408f), proportionOfHeight (0.5262f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider19->setBounds (proportionOfWidth (0.5189f), proportionOfHeight (0.5262f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider20->setBounds (proportionOfWidth (0.5945f), proportionOfHeight (0.5262f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider21->setBounds (proportionOfWidth (0.6725f), proportionOfHeight (0.5262f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider22->setBounds (proportionOfWidth (0.7481f), proportionOfHeight (0.5262f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider23->setBounds (proportionOfWidth (0.8262f), proportionOfHeight (0.5262f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    slider24->setBounds (proportionOfWidth (0.9018f), proportionOfHeight (0.5262f), proportionOfWidth (0.0353f), proportionOfHeight (0.4169f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void DmxOutComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider1)
    {
        //[UserSliderCode_slider1] -- add your slider handling code here..
        dmxData[0] = (uint8)slider1->getValue();
        sendData();
        //[/UserSliderCode_slider1]
    }
    else if (sliderThatWasMoved == slider2)
    {
        //[UserSliderCode_slider2] -- add your slider handling code here..
        dmxData[1] = (uint8)slider2->getValue();
        sendData();
        //[/UserSliderCode_slider2]
    }
    else if (sliderThatWasMoved == slider3)
    {
        //[UserSliderCode_slider3] -- add your slider handling code here..
        dmxData[2] = (uint8)slider3->getValue();
        sendData();
        //[/UserSliderCode_slider3]
    }
    else if (sliderThatWasMoved == slider4)
    {
        //[UserSliderCode_slider4] -- add your slider handling code here..
        dmxData[3] = (uint8)slider4->getValue();
        sendData();
        //[/UserSliderCode_slider4]
    }
    else if (sliderThatWasMoved == slider5)
    {
        //[UserSliderCode_slider5] -- add your slider handling code here..
        dmxData[4] = (uint8)slider5->getValue();
        sendData();
        //[/UserSliderCode_slider5]
    }
    else if (sliderThatWasMoved == slider6)
    {
        //[UserSliderCode_slider6] -- add your slider handling code here..
        dmxData[5] = (uint8)slider6->getValue();
        sendData();
        //[/UserSliderCode_slider6]
    }
    else if (sliderThatWasMoved == slider7)
    {
        //[UserSliderCode_slider7] -- add your slider handling code here..
        dmxData[6] = (uint8)slider7->getValue();
        sendData();
        //[/UserSliderCode_slider7]
    }
    else if (sliderThatWasMoved == slider8)
    {
        //[UserSliderCode_slider8] -- add your slider handling code here..
        dmxData[7] = (uint8)slider8->getValue();
        sendData();
        //[/UserSliderCode_slider8]
    }
    else if (sliderThatWasMoved == slider9)
    {
        //[UserSliderCode_slider9] -- add your slider handling code here..
        dmxData[8] = (uint8)slider9->getValue();
        sendData();
        //[/UserSliderCode_slider9]
    }
    else if (sliderThatWasMoved == slider10)
    {
        //[UserSliderCode_slider10] -- add your slider handling code here..
        dmxData[9] = (uint8)slider10->getValue();
        sendData();
        //[/UserSliderCode_slider10]
    }
    else if (sliderThatWasMoved == slider11)
    {
        //[UserSliderCode_slider11] -- add your slider handling code here..
        dmxData[10] = (uint8)slider11->getValue();
        sendData();
        //[/UserSliderCode_slider11]
    }
    else if (sliderThatWasMoved == slider12)
    {
        //[UserSliderCode_slider12] -- add your slider handling code here..
        dmxData[11] = (uint8)slider12->getValue();
        sendData();
        //[/UserSliderCode_slider12]
    }
    else if (sliderThatWasMoved == slider13)
    {
        //[UserSliderCode_slider13] -- add your slider handling code here..
        dmxData[12] = (uint8)slider13->getValue();
        sendData();
        //[/UserSliderCode_slider13]
    }
    else if (sliderThatWasMoved == slider14)
    {
        //[UserSliderCode_slider14] -- add your slider handling code here..
        dmxData[13] = (uint8)slider14->getValue();
        sendData();
        //[/UserSliderCode_slider14]
    }
    else if (sliderThatWasMoved == slider15)
    {
        //[UserSliderCode_slider15] -- add your slider handling code here..
        dmxData[14] = (uint8)slider15->getValue();
        sendData();
        //[/UserSliderCode_slider15]
    }
    else if (sliderThatWasMoved == slider16)
    {
        //[UserSliderCode_slider16] -- add your slider handling code here..
        dmxData[15] = (uint8)slider16->getValue();
        sendData();
        //[/UserSliderCode_slider16]
    }
    else if (sliderThatWasMoved == slider17)
    {
        //[UserSliderCode_slider17] -- add your slider handling code here..
        dmxData[16] = (uint8)slider17->getValue();
        sendData();
        //[/UserSliderCode_slider17]
    }
    else if (sliderThatWasMoved == slider18)
    {
        //[UserSliderCode_slider18] -- add your slider handling code here..
        dmxData[17] = (uint8)slider18->getValue();
        sendData();
        //[/UserSliderCode_slider18]
    }
    else if (sliderThatWasMoved == slider19)
    {
        //[UserSliderCode_slider19] -- add your slider handling code here..
        dmxData[18] = (uint8)slider19->getValue();
        sendData();
        //[/UserSliderCode_slider19]
    }
    else if (sliderThatWasMoved == slider20)
    {
        //[UserSliderCode_slider20] -- add your slider handling code here..
        dmxData[19] = (uint8)slider20->getValue();
        sendData();
        //[/UserSliderCode_slider20]
    }
    else if (sliderThatWasMoved == slider21)
    {
        //[UserSliderCode_slider21] -- add your slider handling code here..
        dmxData[20] = (uint8)slider21->getValue();
        sendData();
        //[/UserSliderCode_slider21]
    }
    else if (sliderThatWasMoved == slider22)
    {
        //[UserSliderCode_slider22] -- add your slider handling code here..
        dmxData[21] = (uint8)slider22->getValue();
        sendData();
        //[/UserSliderCode_slider22]
    }
    else if (sliderThatWasMoved == slider23)
    {
        //[UserSliderCode_slider23] -- add your slider handling code here..
        dmxData[22] = (uint8)slider23->getValue();
        sendData();
        //[/UserSliderCode_slider23]
    }
    else if (sliderThatWasMoved == slider24)
    {
        //[UserSliderCode_slider24] -- add your slider handling code here..
        dmxData[23] = (uint8)slider24->getValue();
        sendData();
        //[/UserSliderCode_slider24]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void DmxOutComponent::sendData()
{
    Result r = blueliteMini.updateDmxData (0, dmxData);
    if (! r.wasOk())
        Logger::outputDebugString("DMX output error: " + r.getErrorMessage());
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="DmxOutComponent" componentName=""
                 parentClasses="public Component" constructorParams="BlueLiteX1Mini&amp; blueliteMini_"
                 variableInitialisers="blueliteMini (blueliteMini_),&#10;dmxData (24)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="416" initialHeight="440">
  <BACKGROUND backgroundColour="ffffff"/>
  <SLIDER name="slider1" id="3dd4263526f2660a" memberName="slider1" virtualName=""
          explicitFocusOrder="1" pos="5.749% 5.467% 3.491% 41.686%" tooltip="Channel 1"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider2" id="360ef04fca23b799" memberName="slider2" virtualName=""
          explicitFocusOrder="2" pos="13.347% 5.467% 3.491% 41.686%" tooltip="Channel 2"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider3" id="580efc4de85d7adc" memberName="slider3" virtualName=""
          explicitFocusOrder="3" pos="21.15% 5.467% 3.491% 41.686%" tooltip="Channel 3"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider4" id="f2dde0dd416c1e84" memberName="slider4" virtualName=""
          explicitFocusOrder="4" pos="28.747% 5.467% 3.491% 41.686%" tooltip="Channel 4"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider5" id="bfb4535b82185fed" memberName="slider5" virtualName=""
          explicitFocusOrder="5" pos="36.55% 5.467% 3.491% 41.686%" tooltip="Channel 5"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider6" id="679f90b8f07cb4ee" memberName="slider6" virtualName=""
          explicitFocusOrder="6" pos="44.148% 5.467% 3.491% 41.686%" tooltip="Channel 6"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider7" id="44ad98a2262cd229" memberName="slider7" virtualName=""
          explicitFocusOrder="7" pos="51.951% 5.467% 3.491% 41.686%" tooltip="Channel 7"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider8" id="85ff76e13a1ec2a3" memberName="slider8" virtualName=""
          explicitFocusOrder="8" pos="59.548% 5.467% 3.491% 41.686%" tooltip="Channel 8"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider9" id="776c3f04e2556496" memberName="slider9" virtualName=""
          explicitFocusOrder="9" pos="67.351% 5.467% 3.491% 41.686%" tooltip="Channel 9"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider10" id="3ae59e3cf4f55f86" memberName="slider10" virtualName=""
          explicitFocusOrder="10" pos="74.743% 5.467% 3.491% 41.686%" tooltip="Channel 10"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider11" id="79792787596ae791" memberName="slider11" virtualName=""
          explicitFocusOrder="11" pos="82.546% 5.467% 3.491% 41.686%" tooltip="Channel 11"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider12" id="71d7be10add7e20b" memberName="slider12" virtualName=""
          explicitFocusOrder="12" pos="90.144% 5.467% 3.491% 41.686%" tooltip="Channel 12"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider13" id="f4fec1d538673f4a" memberName="slider13" virtualName=""
          explicitFocusOrder="13" pos="5.749% 52.62% 3.491% 41.686%" tooltip="Channel 13"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider14" id="2a85667136c4a974" memberName="slider14" virtualName=""
          explicitFocusOrder="14" pos="13.347% 52.62% 3.491% 41.686%" tooltip="Channel 14"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider15" id="dd34e28ad89b9dbd" memberName="slider15" virtualName=""
          explicitFocusOrder="15" pos="21.15% 52.62% 3.491% 41.686%" tooltip="Channel 15"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider16" id="1800066dd5b0e135" memberName="slider16" virtualName=""
          explicitFocusOrder="16" pos="28.747% 52.62% 3.491% 41.686%" tooltip="Channel 16"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider17" id="246bcbd8f7c8a43" memberName="slider17" virtualName=""
          explicitFocusOrder="0" pos="36.55% 52.62% 3.491% 41.686%" tooltip="Channel 17"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider18" id="b0c57e3500d80cd5" memberName="slider18" virtualName=""
          explicitFocusOrder="18" pos="44.148% 52.62% 3.491% 41.686%" tooltip="Channel 18"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider19" id="ae0da53a6fe6f1b9" memberName="slider19" virtualName=""
          explicitFocusOrder="19" pos="51.951% 52.62% 3.491% 41.686%" tooltip="Channel 19"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider20" id="bf3f1185e99f8568" memberName="slider20" virtualName=""
          explicitFocusOrder="20" pos="59.548% 52.62% 3.491% 41.686%" tooltip="Channel 20"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider21" id="d00d46b0bf7a97d5" memberName="slider21" virtualName=""
          explicitFocusOrder="21" pos="67.351% 52.62% 3.491% 41.686%" tooltip="Channel 21"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider22" id="f1e61468b0b315f8" memberName="slider22" virtualName=""
          explicitFocusOrder="22" pos="74.743% 52.62% 3.491% 41.686%" tooltip="Channel 22"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider23" id="3c9af5933de7a732" memberName="slider23" virtualName=""
          explicitFocusOrder="23" pos="82.546% 52.62% 3.491% 41.686%" tooltip="Channel 23"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider24" id="112c3bb5c3f5dbb9" memberName="slider24" virtualName=""
          explicitFocusOrder="24" pos="90.144% 52.62% 3.491% 41.686%" tooltip="Channel 24"
          thumbcol="ff757575" min="0" max="255" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
