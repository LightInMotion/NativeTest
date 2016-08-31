/*
   File Info:

      $Workfile:   Main.h  $
      $Author:   JOE  $
      $Revision:   1.0  $
      $Modtime:   15 Feb 2006 10:46:38  $

   Module Description:


      The main module contains the WinMain function and the main window
      message loop.

      It also contains the UpdateThread which is the heart beat of the system.
      The update thread gets triggered every 33ms from the DMXDll. It calls
      the event manager's and the console's update function.

      The main module has now a second thread, the input thread. It waits on
      an event from the DMX dll. Once the event is triggered it gets an update
      mask and sets all changed submaster values accordingly.

      The main module also instanciates the Console, EventManager, CueManager,
      DeviceManager, TemplateManager, EffectManager and the main window.
*/


#ifndef _MAIN_H_
#define _MAIN_H_

// Includes ..................................................................


// Defines ...................................................................

#if 0
// forward declarations
class Console;
class EventManager;
class CueManager;
class DeviceManager;
class TemplateManager;
class EffectManager;
class UIChangeManager;


const int MAIN_SUBMASTER_COUNT = 24;
const int MAIN_AUX_SUBMASTER_COUNT = 4;
const int MAIN_EVENTLIST_COUNT = 4;
const int MAIN_CHASER_COUNT = 0; // ?
const int MAIN_PRESET_COUNT = 24;
#endif

// DMX channel constants
const int MAIN_DMX_UNIVERSE_COUNT = 64;
const int MAIN_DMX_CHANNELS_PER_UNIVERSE = 512;

const int MAIN_DMX_CHANNEL_BUFFER_COUNT = MAIN_DMX_UNIVERSE_COUNT 
                                        * MAIN_DMX_CHANNELS_PER_UNIVERSE;


// Data Types ................................................................


// Public Functions ..........................................................

#if 0
// base functions
HINSTANCE MainGetHInstance();
ATOM MainRegisterWindow( UINT resourceIDClassName,
                         WNDPROC windowProc,
                         UINT style = 0,
                         UINT resourceIDIcon = 0,
                         HCURSOR hCursor = LoadCursor( NULL, IDC_ARROW ),
                         UINT resourceIDMenu = NULL );

// Critical Section Access
void MainGetDeletionCriticalSection();
void MainReleaseDeletionCriticalSection();

// Mode Information
bool MainIsDemoActive();

// Access Function to the main objects
Console* MainGetConsole();
EventManager* MainGetEventManager();
CueManager* MainGetCueManager();
DeviceManager* MainGetDeviceManager();
TemplateManager* MainGetTemplateManager();
EffectManager* MainGetEffectManager();
UIChangeManager* MainGetUIChangeManager();

// message boxes
void MainShowErrorMessage( HWND hParent, UINT resourceID );
int MainShowMessageBox( HWND hParent, UINT resourceID, UINT type );

void MainSetActiveWindow( HWND hActiveWindow );
HWND MainGetActiveWindow();
#endif

#endif // _MAIN_H_

