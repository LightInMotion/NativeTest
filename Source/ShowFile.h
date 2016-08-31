/*
  ==============================================================================

    ShowFile.h
    Created: 30 Aug 2016 8:20:17pm
    Author:  Joseph Fitzpatrick

  ==============================================================================
*/

#ifndef SHOWFILE_H_INCLUDED
#define SHOWFILE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "pole.h"

class ShowFile {
public:
    ShowFile (String filename);
    ~ShowFile();
    
    bool Open();
    void Close();
    
    bool SetPath (String path);
    String GetPath();
    bool IsDirectory (String path);
    StringArray GetDirectory();
    
    bool ReadBytes (uint8* outbuf, uint32 readsize, uint32& bytesread);
    bool ReadDword (uint32& dw);
    bool ReadString (String& outstring);
    
private:
    String filename;
    String currentPath;
    
    ScopedPointer<POLE::Storage> storage;
    ScopedPointer<POLE::Stream> stream;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShowFile)
};


#endif  // SHOWFILE_H_INCLUDED
