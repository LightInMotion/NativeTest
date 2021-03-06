/*
  ==============================================================================

    BlueLiteUsbDevices.h
    Created: 29 Mar 2012 11:54:50pm
    Author:  Joe Fitzpatrick

  ==============================================================================
*/

#ifndef __BLUELITEUSBDEVICES_H_7FFD1699__
#define __BLUELITEUSBDEVICES_H_7FFD1699__

#include "BlueLiteUsbDevice.h"
#include "BlueLiteUsb.h"

//==============================================================================
class BlueLiteX1 : public BlueLiteUsbDevice
{
public:
    BlueLiteX1() : BlueLiteUsbDevice (0x4a9, 0x2109, 0, "BlueLite X1",
                                      BlueLite::X1UniverseCount,
                                      BlueLite::X1DmxDataSize, BlueLite::DmxInputSize,
                                      0x7f92, "X1FIRM_HEX", UsbDevice::EndIn1, 
                                      UsbDevice::EndIn2, UsbDevice::EndOut2) {}
    virtual ~BlueLiteX1() {}

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlueLiteX1)
};


//==============================================================================
//==============================================================================
class BlueLiteMiniGen1 : public BlueLiteUsbDevice
{
public:
    BlueLiteMiniGen1() : BlueLiteUsbDevice (0x4a9, 0x210a, 0, "BlueLite Mini (orig)",
                                    BlueLite::MiniUniverseCount,
                                    BlueLite::X1DmxDataSize, BlueLite::DmxInputSize,
                                    0x7f92, "X1FIRM_HEX", UsbDevice::EndIn1, 
                                    UsbDevice::EndIn2, UsbDevice::EndOut2) {}
    virtual ~BlueLiteMiniGen1() {}
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlueLiteMiniGen1)
};


//==============================================================================
//==============================================================================
class BlueLitePCDJ : public BlueLiteUsbDevice
{
public:
    BlueLitePCDJ() 
        : BlueLiteUsbDevice (0x4a9, 0x210b, 0, "BlueLite Mini",
                             BlueLite::MiniUniverseCount,
                             BlueLite::MiniDmxDataSize, BlueLite::DmxInputSize,
                             0xe600, "minifirm_hex", UsbDevice::EndIn1, 
                             UsbDevice::EndIn6, UsbDevice::EndOut2) {}
    virtual ~BlueLitePCDJ() {}
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlueLitePCDJ)    
};

//==============================================================================
//==============================================================================
class BlueLiteX1Mini : public BlueLiteUsbDevice
{
public:
    BlueLiteX1Mini() 
        : BlueLiteUsbDevice (0x4a9, 0x210c, 0, "BlueLite Mini",
                             BlueLite::MiniUniverseCount,
                             BlueLite::MiniDmxDataSize, BlueLite::DmxInputSize,
                             0xe600, "minifirm_hex", UsbDevice::EndIn1, 
                             UsbDevice::EndIn6, UsbDevice::EndOut2) {}
    virtual ~BlueLiteX1Mini() {}

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlueLiteX1Mini)    
};

#endif  // __BLUELITEUSBDEVICES_H_7FFD1699__
