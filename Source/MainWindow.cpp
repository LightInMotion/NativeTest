/*
    MainWindow.cpp

    The main window (duh) and it's content component
*/

#include "MainWindow.h"

#include "UsbDevice.h"

#define MAX_INTEL_HEX_RECORD_LENGTH 16

typedef struct _INTEL_HEX_RECORD
{
    uint8  Length;
    uint16  Address;
    uint8  Type;
    uint8  Data[MAX_INTEL_HEX_RECORD_LENGTH];
} INTEL_HEX_RECORD, *PINTEL_HEX_RECORD;

INTEL_HEX_RECORD x1idle[] = {
    16,
    0x0,
    0,
    {0x02,0x00,0x03,0x75,0x81,0x07,0x90,0x7F,0xAB,0x74,0x18,0xF0,0x90,0x78,0x49,0x74},
    16,
    0x10,
    0,
    {0x01,0xF0,0xD2,0x0F,0xD2,0x0A,0xC2,0x0B,0xD2,0x08,0x85,0x21,0xB1,0x75,0xB6,0x8D},
    16,
    0x20,
    0,
    {0x75,0x20,0x00,0x85,0x20,0xB0,0x75,0xB5,0x03,0x90,0x7F,0xAB,0xE0,0x30,0xE3,0x03},
    16,
    0x30,
    0,
    {0x02,0x00,0x41,0x78,0x50,0xA4,0xA4,0xA4,0xA4,0xD8,0xFA,0xC2,0x0F,0x85,0x21,0xB1},
    8,
    0x40,
    0,
    {0xA4,0xD2,0x0F,0x85,0x21,0xB1,0x80,0xE1},
    0,
    0x0,
    1,
    {0}
};


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
            
            int idx = 0;
            while (x1idle[idx].Type == 0)
            {
                if (! usbDevice.controlTransfer((2 << 5), 0xa0, x1idle[idx].Address,
                        0, x1idle[idx].Data, x1idle[idx].Length, 500).wasOk())
                    Logger::outputDebugString ("Code transfer error");
                idx++;
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
