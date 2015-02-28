/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  29 Mar 2012 10:34:29pm

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
      blueliteDevice (blueliteDevice_),
      timeLabel (0),
      label (0)
{
    addAndMakeVisible (timeLabel = new Label (L"Time Label",
                                              L"00:00:00:00"));
    timeLabel->setTooltip (L"Current Time");
    timeLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 24.0000f, Font::plain));
    timeLabel->setJustificationType (Justification::centredLeft);
    timeLabel->setEditable (false, false, false);
    timeLabel->setColour (Label::textColourId, Colours::azure);
    timeLabel->setColour (TextEditor::textColourId, Colours::black);
    timeLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label = new Label (L"new label",
                                          L"Writing SMPTE Timecode"));
    label->setFont (Font (15.0000f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colours::azure);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));


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

    deleteAndZero (timeLabel);
    deleteAndZero (label);


    //[Destructor]. You can add your own custom destruction code here..
    signalThreadShouldExit();
    blueliteDevice->removeTimeEvent (timeEvent.getObject());
    timeEvent->signal();
    stopThread (-1);

    timeEvent = nullptr;
    //[/Destructor]
}

//==============================================================================
void TimeComponent::paint (Graphics& /*g*/)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TimeComponent::resized()
{
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
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TimeComponent" componentName=""
                 parentClasses="public Component, Thread" constructorParams="BlueLiteDevice::Ptr blueliteDevice_"
                 variableInitialisers="Thread (&quot;Time Input Thread&quot;),&#10;blueliteDevice (blueliteDevice_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
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
