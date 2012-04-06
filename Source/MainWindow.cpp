/*
    MainWindow.cpp

    The main window (duh) and it's content component
*/

#include "MainWindow.h"
#include "TestTabsComponent.h"
#include "BlueLiteUsbDevices.h"
#include "DemoDevice.h"

//==============================================================================
class ContentComp : public Component
{
public:
    //==============================================================================
    ContentComp(BlueLiteDevice::Ptr blueliteDevice_)
    : blueliteDevice (blueliteDevice_)
    {
        TestTabsComponent* view = new TestTabsComponent (blueliteDevice);
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
    BlueLiteDevice::Ptr blueliteDevice;
    
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
    centreWithSize (640, 480);    
    setUsingNativeTitleBar (true);
    setVisible (true);

    blueliteDevice = new BlueLiteX1();
    int count = blueliteDevice->getCount();
    
    if (! count)
    {
        blueliteDevice = new BlueLiteX1Mini();
        count = blueliteDevice->getCount();
    }
    
    if (! count)
    {
        blueliteDevice = new BlueLitePCDJ();
        count = blueliteDevice->getCount();
    }
    
    if (! count)
    {
        blueliteDevice = new BlueLiteMiniGen1();
        count = blueliteDevice->getCount();
    }
    
    Logger::outputDebugString (String(count) + " BlueLite Device(s) found");

    if (! count)
    {
        blueliteDevice = new DemoDevice();
        count = blueliteDevice->getCount();        
    }
    
    if (count)
    {
        Result r = blueliteDevice->open (0);
        if (r.wasOk())
            Logger::outputDebugString (blueliteDevice->getDeviceName() + " opened");
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
                                     "You need to connect a BlueLite X1 or BlueLite X1 Mini to a USB port on your computer.",
                                     "Ok");

        JUCEApplication::getInstance()->systemRequestedQuit();
    }

//    startTimer (33);
    
    ContentComp* contentComp = new ContentComp (blueliteDevice);
    setContentOwned(contentComp, false);    
}

MainAppWindow::~MainAppWindow()
{
    stopTimer();
    
    clearContentComponent();
    
    if (blueliteDevice != nullptr)
    {
        blueliteDevice->close();
        Logger::outputDebugString (blueliteDevice->getDeviceName() + " closed");
    }
}

void MainAppWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}

//==============================================================================
void MainAppWindow::timerCallback()
{
    if (blueliteDevice == nullptr)
        return;
    
    if (blueliteDevice->isOpen())
    {
        Logger::outputDebugString ("Polling Input...");

        blueliteDevice->readDmxInput();
    }
}