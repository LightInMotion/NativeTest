/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  29 Mar 2012 4:58:01pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_DMXINCOMPONENT_DMXINCOMPONENT_D06B56FC__
#define __JUCER_HEADER_DMXINCOMPONENT_DMXINCOMPONENT_D06B56FC__

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
    BlueLiteEvent::Ptr inputEvent;
    
    Array<Label*> labels;
    
    //[/UserVariables]

    //==============================================================================
    Label* label1;
    Label* label2;
    Label* label3;
    Label* label4;
    Label* label5;
    Label* label6;
    Label* label7;
    Label* label8;
    Label* label9;
    Label* label10;
    Label* label11;
    Label* label12;
    Label* label13;
    Label* label14;
    Label* label15;
    Label* label16;
    Label* label17;
    Label* label18;
    Label* label19;
    Label* label20;
    Label* label21;
    Label* label22;
    Label* label23;
    Label* label24;
    Label* label25;
    Label* label26;
    Label* label27;
    Label* label28;
    Label* label29;
    Label* label30;
    Label* label31;
    Label* label32;
    Label* label33;
    Label* label34;
    Label* label35;
    Label* label36;
    Label* label37;
    Label* label38;
    Label* label39;
    Label* label40;
    Label* label41;
    Label* label42;
    Label* label43;
    Label* label44;
    Label* label45;
    Label* label46;
    Label* label47;
    Label* label48;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    DmxInComponent (const DmxInComponent&);
    const DmxInComponent& operator= (const DmxInComponent&);
};


#endif   // __JUCER_HEADER_DMXINCOMPONENT_DMXINCOMPONENT_D06B56FC__
