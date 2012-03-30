/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  29 Mar 2012 9:14:07pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_TIMECOMPONENT_TIMECOMPONENT_71907473__
#define __JUCER_HEADER_TIMECOMPONENT_TIMECOMPONENT_71907473__

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
class TimeComponent  : public Component,
                       Thread
{
public:
    //==============================================================================
    TimeComponent (BlueLiteX1Mini& blueliteMini_);
    ~TimeComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    void run();

    BlueLiteX1Mini& blueliteMini;
    BlueLiteEvent::Ptr timeEvent;
    //[/UserVariables]

    //==============================================================================
    Label* timeLabel;
    Label* label;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    TimeComponent (const TimeComponent&);
    const TimeComponent& operator= (const TimeComponent&);
};


#endif   // __JUCER_HEADER_TIMECOMPONENT_TIMECOMPONENT_71907473__
