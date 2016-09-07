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
    gmSlider->setRange (0, 8192, 0);
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


    //[UserPreSize]
    gmSlider->setValue (8192);
    updateThumb (gmSlider);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    console = new Console (blueliteDevice);

    updateStats();
    startTimerHz (1);
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
    loadedLabel->setBounds (80, 16, 280, 24);
    cuesLabel->setBounds (168, 40, 120, 24);
    devsLabel->setBounds (168, 64, 120, 24);
    universesLabel->setBounds (168, 88, 120, 24);
    newButton->setBounds (80, 80, 80, 24);
    fadersLabel->setBounds (80, 144, 120, 24);
    clearAllButton->setBounds (80, 176, 80, 24);
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

                Console::SliderHandle handle = console->addSlider();
                if (handle)
                {
                    console->setCue (handle, 1);
                    Logger::outputDebugString ("Cue: " + String (console->getCue (handle)));
                    console->setLevel (handle, FADER_MAX_LEVEL);
                }
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

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
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
          min="0" max="8192" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="30" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <TEXTBUTTON name="new button" id="674f4af2494810a4" memberName="loadButton"
              virtualName="" explicitFocusOrder="0" pos="80 48 80 24" tooltip="Load an existing show from disk"
              buttonText="Load" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="7ea17f29f38d756f" memberName="loadedLabel"
         virtualName="" explicitFocusOrder="0" pos="80 16 280 24" textCol="ffd8d8d8"
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
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
