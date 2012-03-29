/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  29 Mar 2012 12:15:31pm

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

#include "DmxInComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
DmxInComponent::DmxInComponent (BlueLiteX1Mini& blueliteMini_)
    : Thread ("Dmx Input Thread"),
      blueliteMini (blueliteMini_)
{

    //[UserPreSize]
    //[/UserPreSize]

    setSize (416, 440);


    //[Constructor] You can add your own custom stuff here..
    blueliteMini.addInputEvent (&inputEvent);
    startThread();
    //[/Constructor]
}

DmxInComponent::~DmxInComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    signalThreadShouldExit();
    blueliteMini.removeInputEvent (&inputEvent);
    inputEvent.signal();
    stopThread (-1);
    //[/Destructor]
}

//==============================================================================
void DmxInComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void DmxInComponent::resized()
{
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void DmxInComponent::run()
{
    while (! threadShouldExit())
    {
        inputEvent.wait();
        if (threadShouldExit())
            return;
        
        Logger::outputDebugString ("Input!");
//        sleep(100);
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="DmxInComponent" componentName=""
                 parentClasses="public Component, Thread" constructorParams="BlueLiteX1Mini&amp; blueliteMini_"
                 variableInitialisers="Thread (&quot;Dmx Input Thread&quot;),&#10;blueliteMini (blueliteMini_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="416" initialHeight="440">
  <BACKGROUND backgroundColour="ffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
