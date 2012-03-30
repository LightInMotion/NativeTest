/*
    MainWindow.cpp
 
    The main window (duh)
*/

#ifndef __MAINWINDOW_H_FC7EECA1__
#define __MAINWINDOW_H_FC7EECA1__

#include "BlueLiteX1Mini.h"
#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
class MainAppWindow   : public DocumentWindow, public Timer
{
public:
    //==============================================================================
    MainAppWindow();
    ~MainAppWindow();

    void closeButtonPressed();

    /* Note: Be careful when overriding DocumentWindow methods - the base class
       uses a lot of them, so by overriding you might break its functionality.
       It's best to do all your work in you content component instead, but if
       you really have to override any DocumentWindow methods, make sure your
       implementation calls the superclass's method.
    */

    //==============================================================================
    void timerCallback();
    
private:
    //==============================================================================
    BlueLiteDevice::Ptr blueliteDevice;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainAppWindow)
};


#endif  // __MAINWINDOW_H_FC7EECA1__
