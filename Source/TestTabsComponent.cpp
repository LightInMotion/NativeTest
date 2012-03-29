/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  29 Mar 2012 10:11:25am

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

#include "TestTabsComponent.h"
#include "DmxOutComponent.h"
#include "DmxInComponent.h"
#include "TimeComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TestTabsComponent::TestTabsComponent (BlueLiteX1Mini& blueliteMini_)
    : blueliteMini (blueliteMini_),
      tabbedComponent (0)
{
    addAndMakeVisible (tabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    tabbedComponent->setTabBarDepth (35);
    tabbedComponent->addTab (L"DMX Output", Colour (0xff344756), new DmxOutComponent (blueliteMini), true);
    tabbedComponent->addTab (L"DMX Input", Colour (0xff435666), new DmxInComponent (blueliteMini), true);
    tabbedComponent->addTab (L"Time", Colour (0xff546675), new TimeComponent (blueliteMini), true);
    tabbedComponent->setCurrentTabIndex (0);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TestTabsComponent::~TestTabsComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (tabbedComponent);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TestTabsComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TestTabsComponent::resized()
{
    tabbedComponent->setBounds (-1, 0, proportionOfWidth (1.0076f), proportionOfHeight (1.0023f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TestTabsComponent" componentName=""
                 parentClasses="public Component" constructorParams="BlueLiteX1Mini&amp; blueliteMini_"
                 variableInitialisers="blueliteMini (blueliteMini_)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330000013" fixedSize="0"
                 initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
  <TABBEDCOMPONENT name="new tabbed component" id="16b48baabf12e68c" memberName="tabbedComponent"
                   virtualName="" explicitFocusOrder="0" pos="-1 0 100.821% 100.228%"
                   orientation="top" tabBarDepth="35" initialTab="0">
    <TAB name="DMX Output" colour="ff344756" useJucerComp="1" contentClassName=""
         constructorParams="blueliteMini" jucerComponentFile="DmxOutComponent.cpp"/>
    <TAB name="DMX Input" colour="ff435666" useJucerComp="1" contentClassName=""
         constructorParams="blueliteMini" jucerComponentFile="DmxInComponent.cpp"/>
    <TAB name="Time" colour="ff546675" useJucerComp="1" contentClassName=""
         constructorParams="blueliteMini" jucerComponentFile="TimeComponent.cpp"/>
  </TABBEDCOMPONENT>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
