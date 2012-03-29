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

#ifndef __JUCER_HEADER_TESTTABSCOMPONENT_TESTTABSCOMPONENT_1A83E643__
#define __JUCER_HEADER_TESTTABSCOMPONENT_TESTTABSCOMPONENT_1A83E643__

//[Headers]     -- You can add your own extra header files here --
#include "BlueLiteX1Mini.h"
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
    TestTabsComponent (BlueLiteX1Mini& blueliteMini_);
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
    BlueLiteX1Mini& blueliteMini;
    //[/UserVariables]

    //==============================================================================
    TabbedComponent* tabbedComponent;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    TestTabsComponent (const TestTabsComponent&);
    const TestTabsComponent& operator= (const TestTabsComponent&);
};


#endif   // __JUCER_HEADER_TESTTABSCOMPONENT_TESTTABSCOMPONENT_1A83E643__
