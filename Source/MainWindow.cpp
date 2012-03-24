/*
    MainWindow.cpp

    The main window (duh) and it's content component
*/

#include "MainWindow.h"

#include "UsbDevice.h"
#include "IntelHexReader.h"


//==============================================================================
MainAppWindow::MainAppWindow()
    : DocumentWindow (JUCEApplication::getInstance()->getApplicationName(),
                      Colours::lightgrey,
                      DocumentWindow::allButtons)
{
    centreWithSize (500, 400);
    setVisible (true);
    
    Logger::outputDebugString ("Loading firmware on mini-0 (if found)");
    
    UsbDevice usbDevice (0x4a9, 0x210c, 0);
    if (usbDevice.getCount() > 0)
    {
        if (usbDevice.openDevice (0).wasOk())
        {
            if (! usbDevice.setInterfaceAlternateSetting (1).wasOk())
                Logger::outputDebugString ("Could not make alternate setting");

            uint8 b = 1;            
            if (! usbDevice.controlTransfer((2 << 5), 0xa0, 0xe600, 0, &b, 1, 500).wasOk())
                Logger::outputDebugString ("Could not set reset");
            
            IntelHexReader hexReader ("minifirm_hex");
            MemoryBlock block;
            uint16 address;
            while (hexReader.readLineAsBinary (block, address))
            {
                if (! usbDevice.controlTransfer ((2 << 5), 0xa0, address, 0,
                                                 (uint8*)block.getData(), block.getSize(), 500))
                    Logger::outputDebugString ("Code transfer error");
            }
                        
            b = 0;
            if (! usbDevice.controlTransfer((2 << 5), 0xa0, 0xe600, 0, &b, 1, 500).wasOk())
                Logger::outputDebugString ("Could not release reset");
            
            usbDevice.closeDevice();
        }
        else
            Logger::outputDebugString ("Could not open device");
    }
    else
        Logger::outputDebugString ("No devices found");
}

MainAppWindow::~MainAppWindow()
{
}

void MainAppWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}
