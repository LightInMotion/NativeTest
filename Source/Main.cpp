/*
    Main.cpp
 
    Code starts here (see the macro at the bottom. This also is where
    we declare our inherited version of JUCEApplication
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"


//==============================================================================
class NativeTestApplication  : public JUCEApplication
{
public:
    //==============================================================================
    NativeTestApplication()
    {
    }

    ~NativeTestApplication()
    {
    }

    //==============================================================================
    void initialise (const String& commandLine)
    {
        // Do your application's initialisation code here..
        mainWindow = new MainAppWindow();
    }

    void shutdown()
    {
        // Do your application's shutdown code here..
        mainWindow = 0;
    }

    //==============================================================================
    void systemRequestedQuit()
    {
        quit();
    }

    //==============================================================================
    const String getApplicationName()
    {
        return ProjectInfo::projectName;
    }

    const String getApplicationVersion()
    {
        return ProjectInfo::versionString;
    }

    bool moreThanOneInstanceAllowed()
    {
        return true;
    }

    void anotherInstanceStarted (const String& commandLine)
    {
        
    }

private:
    ScopedPointer <MainAppWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that starts the app.
START_JUCE_APPLICATION(NativeTestApplication)
