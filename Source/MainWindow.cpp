/*
    MainWindow.cpp

    The main window (duh) and it's content component
*/

#include "MainWindow.h"
#include "TestTabsComponent.h"
#include "BlueLiteUsbDevices.h"
#include "DemoDevice.h"
#include "pole.h"
#include "ShowFile.h"
#include "Device.h"

void visit( int indent, POLE::Storage* storage, String path )
{
    StringArray entries;
    entries = storage->entries( path );
    
    for (int it = 0; it < entries.size(); ++it)
    {
        String name = entries[it];
        String fullname = path + name;
        for( int j = 0; j < indent; j++ ) std::cout << "    ";
        ScopedPointer<POLE::Stream> ss = new POLE::Stream( storage, fullname );
        std::cout << name;
        if( ss ) if( !ss->fail() )std::cout << "  (" << ss->size() << ")";
        std::cout << std::endl;
        
        if( storage->isDirectory( fullname ) )
            visit( indent+1, storage, fullname + "/" );
    }
}


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

    ScopedPointer<POLE::Storage> storage = new POLE::Storage( "/Users/jfitzpat/X1Test.x1" );
    storage->open();
    if( storage->result() == POLE::Storage::Ok )
        visit( 0, storage, "/" );
    
    ShowFile show("/Users/jfitzpat/X1Test.x1");
    if (show.Open())
    {
        show.SetPath ("/Devices/0/Info");
        Logger::outputDebugString(show.GetPath());
        
        Uuid uid;
        show.ReadGuid (uid);
        Logger::outputDebugString (uid.toDashedString());
        
        uint32 groupindex;
        show.ReadDword (groupindex);
        
        uint32 baseaddr;
        show.ReadDword (baseaddr);
        
        uint32 numcontrols;
        show.ReadDword (numcontrols);
        
        String s;
        show.ReadString (s);
        Logger::outputDebugString (s);
        
        show.SetPath ("/Devices/0/Controls");
        uint8 outbuf[60];
        uint32 bytesread;
        show.ReadBytes (outbuf, sizeof (outbuf), bytesread);
        
        show.SetPath ("/Devices/1/");
        Device d;
        d.DeviceLoad(show, 0, nullptr);
    }
    
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
        if (AlertWindow::showOkCancelBox (AlertWindow::QuestionIcon,
                                          "No BlueLite Hardware Found",
                                          "Continue in Demo mode?",
                                          "Yes", "No"))
        {        
            blueliteDevice = new DemoDevice();
            count = blueliteDevice->getCount();
        }
    }
    
    if (count)
    {
        Result r = blueliteDevice->open (0);
        
        if (r.failed())
        {
            AlertWindow::showMessageBox (AlertWindow::InfoIcon, 
                                         "Hardware Communication Error",
                                         r.getErrorMessage(),
                                         "Ok");  

            JUCEApplication::getInstance()->systemRequestedQuit();
        }
        else
        {
            Logger::outputDebugString (blueliteDevice->getDeviceName() + " opened");
            ContentComp* contentComp = new ContentComp (blueliteDevice);
            setContentOwned(contentComp, false);
        }
    }
    else
        JUCEApplication::getInstance()->systemRequestedQuit();

//    startTimer (33);
    
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