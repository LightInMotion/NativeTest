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

#include "TimeComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#if JUCE_WINDOWS
  #pragma warning (push)
  #pragma warning (disable: 4127)
#endif
//[/MiscUserDefs]

//==============================================================================
TimeComponent::TimeComponent (BlueLiteDevice::Ptr blueliteDevice_)
    : Thread ("Time Input Thread"),
      blueliteDevice (blueliteDevice_)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (timeLabel = new Label ("Time Label",
                                              TRANS("00:00:00:00")));
    timeLabel->setTooltip (TRANS("Current Time"));
    timeLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 24.00f, Font::plain));
    timeLabel->setJustificationType (Justification::centredLeft);
    timeLabel->setEditable (false, false, false);
    timeLabel->setColour (Label::textColourId, Colours::azure);
    timeLabel->setColour (TextEditor::textColourId, Colours::black);
    timeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Writing SMPTE Timecode")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colours::azure);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    timeEvent = new BlueLiteEvent();
    blueliteDevice->addTimeEvent (timeEvent.getObject());
    startThread();
    //[/Constructor]
}

TimeComponent::~TimeComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    timeLabel = nullptr;
    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    signalThreadShouldExit();
    blueliteDevice->removeTimeEvent (timeEvent.getObject());
    timeEvent->signal();
    stopThread (-1);

    timeEvent = nullptr;
    //[/Destructor]
}

//==============================================================================
void TimeComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TimeComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    timeLabel->setBounds (40, 48, 144, 32);
    label->setBounds (40, 16, 159, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TimeComponent::run()
{
    while (! threadShouldExit())
    {
        timeEvent->wait();
        if (threadShouldExit())
            return;

        MemoryBlock lastTime = blueliteDevice->readTimeInput();
        uint8* data = (uint8*) lastTime.getData();

        String s;
        s << int (data[2]) << int (data[3]) << ':' << int (data[4]) << int (data[5]) << ':';
        s << int (data[6]) << int (data[7]) << ':' << int (data[8]) << int (data[9]);

        do
        {
            const MessageManagerLock mml (Thread::getCurrentThread());
            if (! mml.lockWasGained())
                return;

            timeLabel->setText (s, dontSendNotification);

        } while (0);

        // We don't want to update more than 20 Hz
        sleep(50);
    }
}

#if JUCE_WINDOWS
  #pragma warning (pop)
#endif
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TimeComponent" componentName=""
                 parentClasses="public Component, Thread" constructorParams="BlueLiteDevice::Ptr blueliteDevice_"
                 variableInitialisers="Thread (&quot;Time Input Thread&quot;),&#10;blueliteDevice (blueliteDevice_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
  <LABEL name="Time Label" id="673b9c273c4ebc5e" memberName="timeLabel"
         virtualName="" explicitFocusOrder="0" pos="40 48 144 32" tooltip="Current Time"
         textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0" labelText="00:00:00:00"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default monospaced font" fontsize="24" bold="0" italic="0"
         justification="33"/>
  <LABEL name="new label" id="a3352c40cfd209cf" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="40 16 159 24" textCol="fff0ffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Writing SMPTE Timecode"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
