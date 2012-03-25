/*
    IntelHexReader.h

    Very simple parser for Intel Hex files
    Reads one line at a time into data with address and size info
*/

#ifndef __INTELHEXREADER_H_38F66E60__
#define __INTELHEXREADER_H_38F66E60__

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
class IntelHexReader
{
public:
    //==============================================================================
    IntelHexReader (const String& resourceName);
    IntelHexReader (const char* data, int size);
    
    ~IntelHexReader() {}

    //==============================================================================
    int getTotalLength();
    int getUnparsedLength();
    
    //==============================================================================
    bool readLineAsBinary (MemoryBlock& data, uint16& address);
    
private:
    //==============================================================================
    ScopedPointer<MemoryInputStream> dataStream;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IntelHexReader)
};

#endif  // __INTELHEXREADER_H_38F66E60__
