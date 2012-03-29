/*
    MainWindow.cpp

    The main window (duh) and it's content component
*/

#include "MainWindow.h"
#include "DmxInComponent.h"
#include "BlueLiteX1Mini.h"

//==============================================================================
class ContentComp : public Component
{
public:
    //==============================================================================
    ContentComp(BlueLiteX1Mini& blueliteMini_)
    : blueliteMini (blueliteMini_)
    {
        DmxInComponent* view = new DmxInComponent (blueliteMini);
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
};

//==============================================================================
MainAppWindow::MainAppWindow()
    : DocumentWindow (JUCEApplication::getInstance()->getApplicationName(),
                      Colours::lightgrey,
                      DocumentWindow::allButtons),
      lastTestValue (0)
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
            {
                Logger::outputDebugString ("BlueLite 0 opened");
                testData.setSize (blueliteMini.universeSize);
                testData.fillWith (lastTestValue);
            }
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
    startTimer (33);
    
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
        Logger::outputDebugString ("DMX Send " + String(lastTestValue));

        Result r = blueliteMini.updateUniverseData (0, testData);
        if (! r.wasOk())
            Logger::outputDebugString ("DMX test write error: " + r.getErrorMessage());
        
        testData.fillWith(++lastTestValue);
    }
}