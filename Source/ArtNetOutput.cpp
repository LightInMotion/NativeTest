/*
    ArtNetOutput.cpp

    Simple ArtNet Output
*/

#include "ArtNetOutput.h"
#include "DMX.h"
#include "art-net.h"

//==============================================================================
// Construction/Destruction
//
ArtNetOutput::ArtNetOutput()
    : Thread ("ArtNet Output Thread"),
      outputBuffer (DMX_CHANNEL_BUFFER_COUNT)
{
    startThread();
}

ArtNetOutput::~ArtNetOutput()
{
    signalThreadShouldExit();
    event.signal();
    stopThread (-1);
}

//==============================================================================
// Universe Management
//
void ArtNetOutput::setUniverse (int physcialUniverse, int channels, int subnet, int universe_)
{
    // Clear it if it already exists
    clearUniverse (physcialUniverse);
    
    ArtNetUniverse universe;
    universe.physical = physcialUniverse;
    universe.channels = channels;
    universe.subnet = subnet;
    universe.universe = universe_;
    
    universeList.add (universe);
}

void ArtNetOutput::clearUniverse (int physicalUniverse)
{
    // If it already exists, remove it
    for (int n = 0; n < universeList.size(); ++n)
    {
        if (universeList[n].physical == physicalUniverse)
        {
            universeList.remove (n);
            break;
        }
    }
}

//==============================================================================
// Background Thread
//
void ArtNetOutput::run()
{
    // Setup our broadcast Socket
    DatagramSocket socket (true);    
    socket.bindToPort (DefaultPort);
    
    // Default ArtNet output packet
    T_ArtDmx tdmx;
    zeromem (&tdmx, sizeof (tdmx));
    strcpy ((char *)tdmx.ID, "Art-Net");
    tdmx.OpCode = OpOutput;
    tdmx.Version = ProtocolVersion;

    while (! threadShouldExit())
    {
        event.wait();
        if (threadShouldExit())
            return;

        // Send any universes that have been set
        for (int n = 0; n < universeList.size(); ++n)
        {
            int channels = universeList[n].channels;
            
            tdmx.Universe = universeList[n].subnet;
            tdmx.Universe <<= 4;
            tdmx.Universe += universeList[n].universe;
            tdmx.Physical = universeList[n].universe;
            ((uint8*)(&tdmx.Length))[0] = (uint8)(channels >> 8);
            ((uint8*)(&tdmx.Length))[1] = (uint8)(channels & 0xFF);
            memcpy(tdmx.Data, (uint8*)outputBuffer.getData() + (universeList[n].physical * 512),
                   universeList[n].channels);
            
            socket.write ("255.255.255.255", DefaultPort, &tdmx, sizeof (tdmx) - 512 + channels);
        }
    }
}