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
#include "Cue.h"
#include "Fader.h"

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

//    ScopedPointer<POLE::Storage> testwrite = new POLE::Storage("/Users/jfitzpat/test.xx");
//    testwrite->open (true, true);
//    if (testwrite->result() == POLE::Storage::Ok)
//    {
//        ScopedPointer<POLE::Stream> ss = new POLE::Stream( testwrite, "/Booger/Test", true );
//        ss->write ((uint8 *)"Yo mamma", 8);
//        ss->flush();
//        testwrite->close();
//    }
    
    ScopedPointer<POLE::Storage> storage = new POLE::Storage( "/Users/jfitzpat/X1Test.x1" );
    storage->open();
    if( storage->result() == POLE::Storage::Ok )
        visit( 0, storage, "/" );
    
    ShowFile show("/Users/jfitzpat/X1Test.x1");
    if (show.Open())
    {
        OwnedArray<Device> deviceList;
        OwnedArray<Cue> cueList;
        
        uint32 deviceIndex = 0;
        while (show.IsDirectory("/Devices/" + String(deviceIndex) + "/"))
        {
            show.SetPath ("/Devices/" + String(deviceIndex) + "/");
            ScopedPointer<Device> device = new Device();
            if (! device->DeviceLoad(show, 1, nullptr))
                break;
            
            deviceList.add (device);
            device.release();
            ++deviceIndex;
        }
        
        uint cueIndex = 0;
        while (show.IsDirectory("/Cues/" + String(cueIndex) + "/"))
        {
            show.SetPath ("/Cues/" + String(cueIndex) + "/");
            ScopedPointer<Cue> cue = new Cue();
            if (! cue->CueLoad(show, 1, deviceList))
                break;
            
            cueList.add (cue);
            cue.release();
            ++cueIndex;
        }
        
        ScopedPointer<uint8> outputBuffer = new uint8[MAIN_DMX_CHANNEL_BUFFER_COUNT * 2];
        
        if (cueList.size())
        {
            zeromem (outputBuffer, MAIN_DMX_CHANNEL_BUFFER_COUNT * 2);
            cueList[0]->CueUpdateBuffer(outputBuffer, FADER_MAX_LEVEL, FADER_MAX_LEVEL);
            Logger::outputDebugString ("Full");
            for (int n = 0; n < 32; ++n)
                Logger::outputDebugString(String (outputBuffer[n]));
            zeromem (outputBuffer, MAIN_DMX_CHANNEL_BUFFER_COUNT * 2);
            cueList[0]->CueUpdateBuffer(outputBuffer, FADER_MAX_LEVEL >> 2, FADER_MAX_LEVEL >> 2);
            Logger::outputDebugString ("Half");
            for (int n = 0; n < 32; ++n)
                Logger::outputDebugString(String (outputBuffer[n]));
            Logger::outputDebugString ("It fades!");
        }
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