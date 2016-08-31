/*
  ==============================================================================

    ShowFile.cpp
    Created: 30 Aug 2016 8:20:17pm
    Author:  Joseph Fitzpatrick

  ==============================================================================
*/

#include "ShowFile.h"

ShowFile::ShowFile (String _filename)
    : filename (_filename),
      currentPath ("/")
{
    storage = new POLE::Storage (filename);
}

ShowFile::~ShowFile()
{
//    stream = nullptr;
}

bool ShowFile::Open()
{
    storage->open();
    if (storage->result() == POLE::Storage::Ok)
        return true;
    
    return false;
}

void ShowFile::Close()
{
    storage->close();
}

bool ShowFile::SetPath (String path)
{
    currentPath = path;
    
    if (path.endsWithChar('/'))
        return true;
    
    stream = new POLE::Stream (storage, path);
    if (stream == nullptr || stream->fail())
    {
        stream = nullptr;
        return false;
    }
    
    return true;
}

String ShowFile::GetPath()
{
    return currentPath;
}

bool ShowFile::IsDirectory (String path)
{
    return storage->isDirectory (path);
}

StringArray ShowFile::GetDirectory()
{
    return storage->entries (currentPath);
}

//bool ReadBytes (uint8* outbuf, uint32 readsize, uint32& bytesread);
//bool ReadString (String& outstring);
