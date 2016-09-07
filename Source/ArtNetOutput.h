/*
    ArtNetOutput.h

    Simple ArtNet Ouptut
*/

#ifndef ARTNETOUTPUT_H_INCLUDED
#define ARTNETOUTPUT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class ArtNetOutput : private Thread
{
public:
    
    // Construction/Destruction
    ArtNetOutput();
    ~ArtNetOutput();
    
    // Write Data
    void updateChannels (MemoryBlock& block)
        { outputBuffer = block; if (universeList.size()) event.signal(); }
    
    // Set/Update a universe for ArtNet
    void setUniverse (int physcialUniverse, int channels, int subnet, int universe);
    void clearUniverse (int physicalUniverse);
    void clearAllUniverses() { universeList.clear(); }
    
    int getUniverseCount() { return universeList.size(); }
    
private:
    // Update Thread
    void run() override;
  
    typedef struct
    {
        int physical;
        int channels;
        int subnet;
        int universe;
    } ArtNetUniverse;
    
    Array<ArtNetUniverse, CriticalSection> universeList;
    MemoryBlock outputBuffer;
    WaitableEvent event;
};



#endif  // ARTNETOUTPUT_H_INCLUDED
