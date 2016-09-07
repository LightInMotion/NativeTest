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
#include "ShowFile.h"
//[/Headers]

#include "ConsoleComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConsoleComponent::ConsoleComponent (BlueLiteDevice::Ptr blueliteDevice_)
    : blueliteDevice (blueliteDevice_)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (gmLabel = new Label ("new label",
                                            TRANS("100%")));
    gmLabel->setFont (Font (12.00f, Font::plain));
    gmLabel->setJustificationType (Justification::centred);
    gmLabel->setEditable (false, false, false);
    gmLabel->setColour (Label::textColourId, Colour (0xffd8d8d8));
    gmLabel->setColour (TextEditor::textColourId, Colours::black);
    gmLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("GM")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colour (0xffd8d8d8));
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (gmSlider = new Slider ("new slider"));
    gmSlider->setTooltip (TRANS("Grand Master"));
    gmSlider->setRange (0, 8192, 0);
    gmSlider->setSliderStyle (Slider::LinearVertical);
    gmSlider->setTextBoxStyle (Slider::NoTextBox, true, 30, 20);
    gmSlider->addListener (this);


    //[UserPreSize]
    gmSlider->setValue (8192);
    updateThumb (gmSlider);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    console = new Console (blueliteDevice);
    console->loadShow (File ("/Users/jfitzpat/X1Test.x1"));

    Console::SliderHandle handle = console->addSlider();
    if (handle)
    {
        console->setCue (handle, 1);
        Logger::outputDebugString ("Cue: " + String (console->getCue (handle)));
        console->setLevel (handle, FADER_MAX_LEVEL);
    }
    //[/Constructor]
}

ConsoleComponent::~ConsoleComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    gmLabel = nullptr;
    label = nullptr;
    gmSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConsoleComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConsoleComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    gmLabel->setBounds (16, 238, 40, 24);
    label->setBounds (16, 16, 40, 24);
    gmSlider->setBounds (12, 40, 48, 200);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConsoleComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == gmSlider)
    {
        //[UserSliderCode_gmSlider] -- add your slider handling code here..
        console->setGrandMaster((int)sliderThatWasMoved->getValue());
        updateThumb (sliderThatWasMoved);
        gmLabel->setText (String ((int)(sliderThatWasMoved->getValue() / 8192.0 * 100.0 + 0.5)) + "%", dontSendNotification);
        //[/UserSliderCode_gmSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ConsoleComponent::updateThumb (Slider* slider)
{
    int val = slider->getValue();

    if (val == 0)
        slider->setColour (Slider::thumbColourId, Colour (0xff252525));
    else if (val == 8192)
        slider->setColour (Slider::thumbColourId, Colour (0xffbFbFbF));
    else
        slider->setColour (Slider::thumbColourId, Colour (0xff757575));
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConsoleComponent" componentName=""
                 parentClasses="public Component" constructorParams="BlueLiteDevice::Ptr blueliteDevice_"
                 variableInitialisers="blueliteDevice (blueliteDevice_)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
  <LABEL name="new label" id="644af4ccad58ddb2" memberName="gmLabel" virtualName=""
         explicitFocusOrder="0" pos="16 238 40 24" textCol="ffd8d8d8"
         edTextCol="ff000000" edBkgCol="0" labelText="100%" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="4f9d8f328d7aa677" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="16 16 40 24" textCol="ffd8d8d8" edTextCol="ff000000"
         edBkgCol="0" labelText="GM" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="78e9a1645d3c105a" memberName="gmSlider"
          virtualName="" explicitFocusOrder="0" pos="12 40 48 200" tooltip="Grand Master"
          min="0" max="8192" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="30" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
