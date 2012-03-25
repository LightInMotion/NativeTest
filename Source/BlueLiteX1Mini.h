/*
    BlueLiteX1Mini.h

    Low Level Access to X1 Mini 
*/

#ifndef __BLUELITEX1MINI_H_554C97D0__
#define __BLUELITEX1MINI_H_554C97D0__

#include "../JuceLibraryCode/JuceHeader.h"
#include "UsbDevice.h"

class UsbDevice;

//==============================================================================
class BlueLiteX1Mini
{
public:
    //==============================================================================
    BlueLiteX1Mini() : usbDevice (0x4a9, 0x210c, 0, "BlueLite Mini") {}

    ~BlueLiteX1Mini() 
    { 
        if (usbDevice.isOpen())
            close(); 
    }
    
    //==============================================================================
    inline int getCount() { return usbDevice.getCount(); }
    
    Result open (int index);
    void close();
    
private:
    //==============================================================================
    UsbDevice usbDevice;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlueLiteX1Mini)
};

#endif  // __BLUELITEX1MINI_H_554C97D0__
