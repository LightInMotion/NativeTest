/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  29 Mar 2012 10:40:53pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_TESTTABSCOMPONENT_TESTTABSCOMPONENT_94A546B5__
#define __JUCER_HEADER_TESTTABSCOMPONENT_TESTTABSCOMPONENT_94A546B5__

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
class TestTabsComponent  : public Component
{
public:
    //==============================================================================
    TestTabsComponent (BlueLiteDevice::Ptr blueliteDevice_);
    ~TestTabsComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    BlueLiteDevice::Ptr blueliteDevice;
    //[/UserVariables]

    //==============================================================================
    TabbedComponent* tabbedComponent;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    TestTabsComponent (const TestTabsComponent&);
    const TestTabsComponent& operator= (const TestTabsComponent&);
};


#endif   // __JUCER_HEADER_TESTTABSCOMPONENT_TESTTABSCOMPONENT_94A546B5__
