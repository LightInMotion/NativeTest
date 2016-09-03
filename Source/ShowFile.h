/*
    ShowFile.h
 
    Simple Show File Access
    You Stream from a single specific path, so if sub classes need to
    change the stream used inside the OLE doc they should get the
    current path and restore it when done.
*/

#ifndef SHOWFILE_H_INCLUDED
#define SHOWFILE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

namespace POLE
{
    class Storage;
    class Stream;
}

class ShowFile {
public:
    ShowFile (String filename);
    ~ShowFile();
    
    // Open/Close the master file
    bool open();
    void close();
    
    // High Level Access
    uint32 getVersion();
    
    // Psuedo directory access
    bool setPath (String path);
    String getPath();
    bool isDirectory (String path);
    StringArray getDirectory();
    
    // Stream access
    bool readBytes (uint8* outbuf, uint32 readsize, uint32& bytesread);
    bool readDword (uint32& dw);
    bool readInt (int32& i);
    bool readShort (int16& i);
    bool readBool (bool& b);
    bool readByte (uint8& b);
    bool readString (String& outstring);
    bool readGuid (Uuid& uuid);
    
private:
    String filename;    // Physical filename
    String currentPath; // Virtual path inside OLE doc
    
    ScopedPointer<POLE::Storage> storage;   // POLE Handles
    ScopedPointer<POLE::Stream> stream;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShowFile)
};


#endif  // SHOWFILE_H_INCLUDED
