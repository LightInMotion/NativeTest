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

#ifndef __JUCER_HEADER_DMXINCOMPONENT_DMXINCOMPONENT_3B52A217__
#define __JUCER_HEADER_DMXINCOMPONENT_DMXINCOMPONENT_3B52A217__

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
class DmxInComponent  : public Component,
                        Thread
{
public:
    //==============================================================================
    DmxInComponent (BlueLiteX1Mini& blueliteMini_);
    ~DmxInComponent();

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
    WaitableEvent inputEvent;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    DmxInComponent (const DmxInComponent&);
    const DmxInComponent& operator= (const DmxInComponent&);
};


#endif   // __JUCER_HEADER_DMXINCOMPONENT_DMXINCOMPONENT_3B52A217__
