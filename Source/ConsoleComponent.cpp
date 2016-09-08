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

#ifdef JUCE_WINDOWS
#pragma warning(disable: 4100)
#endif
//[/Headers]

#include "ConsoleComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConsoleComponent::ConsoleComponent (BlueLiteDevice::Ptr blueliteDevice_)
    : blueliteDevice (blueliteDevice_)
{
    //[Constructor_pre] You can add your own custom stuff here..
    numberOfFaders = -1;
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
    gmSlider->setRange (0, 8192, 1);
    gmSlider->setSliderStyle (Slider::LinearVertical);
    gmSlider->setTextBoxStyle (Slider::NoTextBox, true, 30, 20);
    gmSlider->addListener (this);

    addAndMakeVisible (loadButton = new TextButton ("new button"));
    loadButton->setTooltip (TRANS("Load an existing show from disk"));
    loadButton->setButtonText (TRANS("Load"));
    loadButton->addListener (this);

    addAndMakeVisible (loadedLabel = new Label ("new label",
                                                TRANS("Loaded:")));
    loadedLabel->setFont (Font (15.00f, Font::plain));
    loadedLabel->setJustificationType (Justification::centredLeft);
    loadedLabel->setEditable (false, false, false);
    loadedLabel->setColour (Label::textColourId, Colour (0xffd8d8d8));
    loadedLabel->setColour (TextEditor::textColourId, Colours::black);
    loadedLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cuesLabel = new Label ("new label",
                                              TRANS("Cues:")));
    cuesLabel->setFont (Font (15.00f, Font::plain));
    cuesLabel->setJustificationType (Justification::centredLeft);
    cuesLabel->setEditable (false, false, false);
    cuesLabel->setColour (Label::textColourId, Colour (0xffd8d8d8));
    cuesLabel->setColour (TextEditor::textColourId, Colours::black);
    cuesLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (devsLabel = new Label ("new label",
                                              TRANS("Devs:")));
    devsLabel->setFont (Font (15.00f, Font::plain));
    devsLabel->setJustificationType (Justification::centredLeft);
    devsLabel->setEditable (false, false, false);
    devsLabel->setColour (Label::textColourId, Colour (0xffd8d8d8));
    devsLabel->setColour (TextEditor::textColourId, Colours::black);
    devsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (universesLabel = new Label ("new label",
                                                   TRANS("Universes:")));
    universesLabel->setFont (Font (15.00f, Font::plain));
    universesLabel->setJustificationType (Justification::centredLeft);
    universesLabel->setEditable (false, false, false);
    universesLabel->setColour (Label::textColourId, Colour (0xffd8d8d8));
    universesLabel->setColour (TextEditor::textColourId, Colours::black);
    universesLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (newButton = new TextButton ("new button"));
    newButton->setTooltip (TRANS("Create a new show"));
    newButton->setButtonText (TRANS("New"));
    newButton->addListener (this);

    addAndMakeVisible (fadersLabel = new Label ("new label",
                                                TRANS("Faders:")));
    fadersLabel->setFont (Font (15.00f, Font::plain));
    fadersLabel->setJustificationType (Justification::centredLeft);
    fadersLabel->setEditable (false, false, false);
    fadersLabel->setColour (Label::textColourId, Colour (0xffd8d8d8));
    fadersLabel->setColour (TextEditor::textColourId, Colours::black);
    fadersLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (clearAllButton = new TextButton ("new button"));
    clearAllButton->setTooltip (TRANS("Clear all fader cue assignements"));
    clearAllButton->setButtonText (TRANS("Clear All"));
    clearAllButton->addListener (this);

    addAndMakeVisible (xLabel = new Label ("new label",
                                           TRANS("100%")));
    xLabel->setFont (Font (12.00f, Font::plain));
    xLabel->setJustificationType (Justification::centred);
    xLabel->setEditable (false, false, false);
    xLabel->setColour (Label::textColourId, Colour (0xffd8d8d8));
    xLabel->setColour (TextEditor::textColourId, Colours::black);
    xLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("X")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centred);
    label2->setEditable (false, false, false);
    label2->setColour (Label::textColourId, Colour (0xffd8d8d8));
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (xSlider = new Slider ("new slider"));
    xSlider->setTooltip (TRANS("X Fader"));
    xSlider->setRange (0, 8192, 1);
    xSlider->setSliderStyle (Slider::LinearVertical);
    xSlider->setTextBoxStyle (Slider::NoTextBox, true, 30, 20);
    xSlider->addListener (this);

    addAndMakeVisible (yLabel = new Label ("new label",
                                           TRANS("0%")));
    yLabel->setFont (Font (12.00f, Font::plain));
    yLabel->setJustificationType (Justification::centred);
    yLabel->setEditable (false, false, false);
    yLabel->setColour (Label::textColourId, Colour (0xffd8d8d8));
    yLabel->setColour (TextEditor::textColourId, Colours::black);
    yLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Y")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centred);
    label3->setEditable (false, false, false);
    label3->setColour (Label::textColourId, Colour (0xffd8d8d8));
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (ySlider = new Slider ("new slider"));
    ySlider->setTooltip (TRANS("Y Fader"));
    ySlider->setRange (0, 8192, 1);
    ySlider->setSliderStyle (Slider::LinearVertical);
    ySlider->setTextBoxStyle (Slider::NoTextBox, true, 30, 20);
    ySlider->addListener (this);

    addAndMakeVisible (xCueButton = new TextButton ("new button"));
    xCueButton->setTooltip (TRANS("Crossfade to X"));
    xCueButton->setButtonText (TRANS("0"));
    xCueButton->addListener (this);

    addAndMakeVisible (yCueButton = new TextButton ("new button"));
    yCueButton->setTooltip (TRANS("Crossfade to Y"));
    yCueButton->setButtonText (TRANS("0"));
    yCueButton->addListener (this);


    //[UserPreSize]
    gmSlider->setValue (8192, dontSendNotification);
    updateThumb (gmSlider);
    xSlider->setValue (8192, dontSendNotification);
    updateThumb (xSlider);
    ySlider->setValue (8192, dontSendNotification);
    updateThumb (ySlider);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    console = new Console (blueliteDevice);

    xFader = console->addSlider();
    console->setLevel (xFader, 8192);
    yFader = console->addSlider();

    updateStats();
    startTimerHz (15);
    //[/Constructor]
}

ConsoleComponent::~ConsoleComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    stopTimer();
    //[/Destructor_pre]

    gmLabel = nullptr;
    label = nullptr;
    gmSlider = nullptr;
    loadButton = nullptr;
    loadedLabel = nullptr;
    cuesLabel = nullptr;
    devsLabel = nullptr;
    universesLabel = nullptr;
    newButton = nullptr;
    fadersLabel = nullptr;
    clearAllButton = nullptr;
    xLabel = nullptr;
    label2 = nullptr;
    xSlider = nullptr;
    yLabel = nullptr;
    label3 = nullptr;
    ySlider = nullptr;
    xCueButton = nullptr;
    yCueButton = nullptr;


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
    loadButton->setBounds (80, 48, 80, 24);
    loadedLabel->setBounds (80, 16, 208, 24);
    cuesLabel->setBounds (168, 40, 120, 24);
    devsLabel->setBounds (168, 64, 120, 24);
    universesLabel->setBounds (168, 88, 120, 24);
    newButton->setBounds (80, 80, 80, 24);
    fadersLabel->setBounds (80, 144, 120, 24);
    clearAllButton->setBounds (80, 176, 80, 24);
    xLabel->setBounds (304, 238, 40, 24);
    label2->setBounds (304, 16, 40, 24);
    xSlider->setBounds (300, 40, 48, 200);
    yLabel->setBounds (376, 238, 40, 24);
    label3->setBounds (376, 16, 40, 24);
    ySlider->setBounds (372, 40, 48, 200);
    xCueButton->setBounds (292, 264, 64, 24);
    yCueButton->setBounds (364, 264, 64, 24);
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
    else if (sliderThatWasMoved == xSlider)
    {
        //[UserSliderCode_xSlider] -- add your slider handling code here..
        console->setLevel (xFader, (int)sliderThatWasMoved->getValue());
        updateThumb (sliderThatWasMoved);
        xLabel->setText (String ((int)(sliderThatWasMoved->getValue() / 8192.0 * 100.0 + 0.5)) + "%", dontSendNotification);
        //[/UserSliderCode_xSlider]
    }
    else if (sliderThatWasMoved == ySlider)
    {
        //[UserSliderCode_ySlider] -- add your slider handling code here..
        console->setLevel (yFader, 8192 - (int)sliderThatWasMoved->getValue());
        updateThumb (sliderThatWasMoved);
        yLabel->setText (String ((int)((8192.0 - sliderThatWasMoved->getValue()) / 8192.0 * 100.0 + 0.5)) + "%", dontSendNotification);
        //[/UserSliderCode_ySlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void ConsoleComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == loadButton)
    {
        //[UserButtonCode_loadButton] -- add your button handler code here..
        FileChooser chooser ("Select X1 Show file to load...",
                             File::getSpecialLocation (File::userHomeDirectory),
                             "*.x1");

        if (chooser.browseForFileToOpen())
        {
            File show (chooser.getResult());

            if (console->loadShow (show))
            {
                loadedLabel->setText ("Loaded: " + show.getFileName(), dontSendNotification);
                updateStats();

                int n;
                for (n = 1; n < 1000000; ++n)
                    if (console->setCue (xFader, n) == n)
                        break;

                if (n < 1000000)
                    xCueButton->setButtonText (String (n));

                for (++n; n < 1000000; ++n)
                    if (console->setCue (yFader, n) == n)
                        break;

                if (n < 1000000)
                    yCueButton->setButtonText (String (n));
            }
        }
        //[/UserButtonCode_loadButton]
    }
    else if (buttonThatWasClicked == newButton)
    {
        //[UserButtonCode_newButton] -- add your button handler code here..
        console->newShow();
        loadedLabel->setText ("Loaded:", dontSendNotification);
        updateStats();
        //[/UserButtonCode_newButton]
    }
    else if (buttonThatWasClicked == clearAllButton)
    {
        //[UserButtonCode_clearAllButton] -- add your button handler code here..
        console->clearAllFaders();
        //[/UserButtonCode_clearAllButton]
    }
    else if (buttonThatWasClicked == xCueButton)
    {
        //[UserButtonCode_xCueButton] -- add your button handler code here..
        console->startFade (xFader, 8192, 3.0);
        console->startFade (yFader, 0, 3.0);
        //[/UserButtonCode_xCueButton]
    }
    else if (buttonThatWasClicked == yCueButton)
    {
        //[UserButtonCode_yCueButton] -- add your button handler code here..
        console->startFade (xFader, 0, 3.0);
        console->startFade (yFader, 8192, 3.0);
        //[/UserButtonCode_yCueButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ConsoleComponent::updateThumb (Slider* slider)
{
    int val = (int)slider->getValue();
    if (slider == ySlider)
        val = 8192 - val;

    if (val == 0)
        slider->setColour (Slider::thumbColourId, Colour (0xff252525));
    else if (val == 8192)
        slider->setColour (Slider::thumbColourId, Colour (0xffbFbFbF));
    else
        slider->setColour (Slider::thumbColourId, Colour (0xff757575));
}

void  ConsoleComponent::updateStats()
{
    cuesLabel->setText("Cues: " + String (console->getCueCount()), dontSendNotification);
    devsLabel->setText("Devs: " + String (console->getDeviceCount()), dontSendNotification);
    universesLabel->setText("Universes: " + String (console->getUniverseCount()), dontSendNotification);
}

void ConsoleComponent::timerCallback()
{
    int n = console->getFaderCount();
    if (n != numberOfFaders)
    {
        numberOfFaders = n;
        fadersLabel->setText ("Faders: " + String (numberOfFaders), dontSendNotification);
    }

    int x = console->getLevel (xFader);
    if (x != (int)xSlider->getValue())
    {
        xSlider->setValue (x, dontSendNotification);
        updateThumb (xSlider);
    }
    
    int y = console->getLevel (yFader);
    if (y != 8192 - (int)ySlider->getValue())
    {
        ySlider->setValue (8192 - y, dontSendNotification);
        updateThumb (ySlider);
    }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConsoleComponent" componentName=""
                 parentClasses="public Component, Timer" constructorParams="BlueLiteDevice::Ptr blueliteDevice_"
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
          min="0" max="8192" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="30" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <TEXTBUTTON name="new button" id="674f4af2494810a4" memberName="loadButton"
              virtualName="" explicitFocusOrder="0" pos="80 48 80 24" tooltip="Load an existing show from disk"
              buttonText="Load" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="7ea17f29f38d756f" memberName="loadedLabel"
         virtualName="" explicitFocusOrder="0" pos="80 16 208 24" textCol="ffd8d8d8"
         edTextCol="ff000000" edBkgCol="0" labelText="Loaded:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="dd3ec43eadf1ea48" memberName="cuesLabel"
         virtualName="" explicitFocusOrder="0" pos="168 40 120 24" textCol="ffd8d8d8"
         edTextCol="ff000000" edBkgCol="0" labelText="Cues:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="376108cecbdd7679" memberName="devsLabel"
         virtualName="" explicitFocusOrder="0" pos="168 64 120 24" textCol="ffd8d8d8"
         edTextCol="ff000000" edBkgCol="0" labelText="Devs:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b1043d718f9855e9" memberName="universesLabel"
         virtualName="" explicitFocusOrder="0" pos="168 88 120 24" textCol="ffd8d8d8"
         edTextCol="ff000000" edBkgCol="0" labelText="Universes:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="61869a5b86ebd3df" memberName="newButton"
              virtualName="" explicitFocusOrder="0" pos="80 80 80 24" tooltip="Create a new show"
              buttonText="New" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="73601fe355fe9669" memberName="fadersLabel"
         virtualName="" explicitFocusOrder="0" pos="80 144 120 24" textCol="ffd8d8d8"
         edTextCol="ff000000" edBkgCol="0" labelText="Faders:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="506e419a6b143eb0" memberName="clearAllButton"
              virtualName="" explicitFocusOrder="0" pos="80 176 80 24" tooltip="Clear all fader cue assignements"
              buttonText="Clear All" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="673ff7e328cc28f2" memberName="xLabel" virtualName=""
         explicitFocusOrder="0" pos="304 238 40 24" textCol="ffd8d8d8"
         edTextCol="ff000000" edBkgCol="0" labelText="100%" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="bceb4029973f3ff4" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="304 16 40 24" textCol="ffd8d8d8"
         edTextCol="ff000000" edBkgCol="0" labelText="X" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="92a1f57ad4893958" memberName="xSlider"
          virtualName="" explicitFocusOrder="0" pos="300 40 48 200" tooltip="X Fader"
          min="0" max="8192" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="30" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <LABEL name="new label" id="fe45cc5b811191a5" memberName="yLabel" virtualName=""
         explicitFocusOrder="0" pos="376 238 40 24" textCol="ffd8d8d8"
         edTextCol="ff000000" edBkgCol="0" labelText="0%" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="a967f9ed0a8fda55" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="376 16 40 24" textCol="ffd8d8d8"
         edTextCol="ff000000" edBkgCol="0" labelText="Y" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="9b89e8f28e93d447" memberName="ySlider"
          virtualName="" explicitFocusOrder="0" pos="372 40 48 200" tooltip="Y Fader"
          min="0" max="8192" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="30" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <TEXTBUTTON name="new button" id="a851097a5860e164" memberName="xCueButton"
              virtualName="" explicitFocusOrder="0" pos="292 264 64 24" tooltip="Crossfade to X"
              buttonText="0" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="ccbed26f7922afc2" memberName="yCueButton"
              virtualName="" explicitFocusOrder="0" pos="364 264 64 24" tooltip="Crossfade to Y"
              buttonText="0" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
