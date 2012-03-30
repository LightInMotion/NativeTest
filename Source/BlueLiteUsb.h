/*
  ==============================================================================

    BlueLiteUsb.h
    Created: 29 Mar 2012 9:59:02pm
    Author:  Joe Fitzpatrick

  ==============================================================================
*/

#ifndef __BLUELITEUSB_H_EB3CE118__
#define __BLUELITEUSB_H_EB3CE118__

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
namespace BlueLite
{
    const int MaxDevice = 8;
    
    const int DmxUniverseSize = 512;
    const int DmxPageSize = 32;
    const int DmxAllPages = (DmxUniverseSize / DmxPageSize);

    const int X1DmxDataSize = (4 * DmxUniverseSize);
    const int MiniDmxDataSize = (1 * DmxUniverseSize);
    const int DmxInputSize = 48;
    
    
    enum PacketType 
    {
        DataType = 1,
        TimeType = 2,
        ConfigType = 3
    };
    
    enum TimeCommand
    {
        IdleCmd = 0,
        WriteCmd = 1,
        ReadCmd = 2
    };
    
    enum TimeControl
    {
        FreezeControl = 1,
        NoPhysControl = 2,
        BlinkControl = 4
    };
    
    enum SmpteFlags
    {
        SmpteSync = 0x20,
        SmpteReading = 0x40
    };
    
    enum SmpteType
    {
        Smpte30fps = 1,
        SmpteDropFrame = 2,
        Smpte25fps = 3,
        Smpte24fps = 4
    };
    
#pragma pack(push)
#pragma pack(1)
    
    struct DataPacket
    {
        uint8	type;		// = DataPacketType
        uint8	rsvd[63];
    };
    
    struct TimePacket
    {
        uint8	type;		// = TimePacketType
        uint8	command;	// 0=idle, 1=write, 2=read
        uint8	control;	// 1= freeze (no inc), 2= no physical output, 4= blink
        uint8	htens;      // Time
        uint8	hunits;     // We split time this way so we can encode user bits
        uint8	mtens;
        uint8	munits;
        uint8	stens;
        uint8	sunits;
        uint8	ftens;
        uint8	funits;
        uint8	stype;      // Time Type, 1=30, 2=df, 3=25, 4=24
        uint8	rsvd[52];
    };
    
    struct ConfigPacket
    {
        uint8 type;         // = ConfigPacketType
        uint8 dmx1;         // DMX Max Page counts
        uint8 dmx2;
        uint8 dmx3;
        uint8 dmx4;
        uint8 inBaseH;      // Input base
        uint8 inBaseL;
        uint8 rsvd[57];
    };
    
#pragma pack(pop)
    
}

#endif  // __BLUELITEUSB_H_EB3CE118__
