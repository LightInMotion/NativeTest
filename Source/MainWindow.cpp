/*
    MainWindow.cpp

    The main window (duh) and it's content component
*/

#include "MainWindow.h"

#include "BlueLiteX1Mini.h"

//==============================================================================
MainAppWindow::MainAppWindow()
    : DocumentWindow (JUCEApplication::getInstance()->getApplicationName(),
                      Colours::lightgrey,
                      DocumentWindow::allButtons)
{
    setResizable (true, false);
    setResizeLimits (100, 100, 8192, 8192);
    centreWithSize (320, 480);    
    setUsingNativeTitleBar (true);
    setVisible (true);

    if (! blueliteMini.isOpen())
    {
        int count = blueliteMini.getCount();
        Logger::outputDebugString (String(count) + " BlueLite Mini(s) found");
        if (count)
        {
            Result r = blueliteMini.open (0);
            if (r.wasOk())
                Logger::outputDebugString ("BlueLite 0 opened");
            else
                AlertWindow::showMessageBox (AlertWindow::InfoIcon, 
                                             "Hardware Communication Error",
                                             r.getErrorMessage(),
                                             "Ok");            
        }
        else
            AlertWindow::showMessageBox (AlertWindow::InfoIcon, 
                                         "No Compatible Hardware Found",
                                         "You need to connect a BlueLite X1 Mini to a USB port on your computer.",
                                         "Ok");            
        
    }
//    startTimer (1000);
}

MainAppWindow::~MainAppWindow()
{
    stopTimer();
    blueliteMini.close();
    Logger::outputDebugString ("BlueLite 0 closed");
}

void MainAppWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}

//==============================================================================
void MainAppWindow::timerCallback()
{
}