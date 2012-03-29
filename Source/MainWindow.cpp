/*
    MainWindow.cpp

    The main window (duh) and it's content component
*/

#include "MainWindow.h"
#include "TestTabsComponent.h"
#include "BlueLiteX1Mini.h"

//==============================================================================
class ContentComp : public Component
{
public:
    //==============================================================================
    ContentComp(BlueLiteX1Mini& blueliteMini_)
    : blueliteMini (blueliteMini_)
    {
        TestTabsComponent* view = new TestTabsComponent (blueliteMini);
        showView (view);
    }
    
    ~ContentComp()
    {
    }
    
    //==============================================================================
    void resized()
    {
        currentView->setBounds (0, 0, getWidth(), getHeight());
    }
    
    //==============================================================================
    void showView (Component* viewComp)
    {
        currentView = viewComp;
        addAndMakeVisible (currentView);
        resized();
    }
    
private:
    ScopedPointer<Component> currentView;
    BlueLiteX1Mini& blueliteMini;
    
    TooltipWindow tooltipWindow; // to add tooltips to an application, you
    // just need to create one of these and leave it
    // there to do its work..    
};

//==============================================================================
MainAppWindow::MainAppWindow()
    : DocumentWindow (JUCEApplication::getInstance()->getApplicationName(),
                      Colour (0xff233746),
                      DocumentWindow::allButtons)
{
    setResizable (true, false);
    setResizeLimits (100, 100, 8192, 8192);
    centreWithSize (480, 320);    
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
            {
                AlertWindow::showMessageBox (AlertWindow::InfoIcon, 
                                             "Hardware Communication Error",
                                             r.getErrorMessage(),
                                             "Ok");  

                JUCEApplication::getInstance()->systemRequestedQuit();
            }
        }
        else
        {
            AlertWindow::showMessageBox (AlertWindow::InfoIcon, 
                                         "No Compatible Hardware Found",
                                         "You need to connect a BlueLite X1 Mini to a USB port on your computer.",
                                         "Ok");

            JUCEApplication::getInstance()->systemRequestedQuit();
        }
        
    }
//    startTimer (33);
    
    ContentComp* contentComp = new ContentComp (blueliteMini);
    setContentOwned(contentComp, false);    
}

MainAppWindow::~MainAppWindow()
{
    stopTimer();
    
    clearContentComponent();
    
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
    if (blueliteMini.isOpen())
    {
        Logger::outputDebugString ("Polling Input...");

        blueliteMini.readDmxInput();
    }
}