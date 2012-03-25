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
    centreWithSize (500, 400);
    setVisible (true);
    
    BlueLiteX1Mini blueliteMini;
    
    int count = blueliteMini.getCount();
    Logger::outputDebugString (String(count) + " BlueLite Mini(s) found");
    if (count)
    {
        Result r = blueliteMini.open (0);
        if (r.wasOk())
        {
            Logger::outputDebugString ("BlueLite 0 opened");
            blueliteMini.close();
            Logger::outputDebugString ("BlueLite 0 closed");
        }
        else
            Logger::outputDebugString (r.getErrorMessage());
    }
}

MainAppWindow::~MainAppWindow()
{
}

void MainAppWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}
