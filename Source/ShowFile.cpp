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
    {
        stream = nullptr;
        return true;
    }
    
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

bool ShowFile::ReadBytes (uint8* outbuf, uint32 readsize, uint32& bytesread)
{
    if (stream == nullptr)
        return false;
    
    uint64 read = stream->read (outbuf, readsize);
    bytesread = (uint32)read;
    return true;
}

bool ShowFile::ReadDword (uint32& dw)
{
    uint32 bytesread;
    
    if (ReadBytes ((uint8 *)(&dw), sizeof (dw), bytesread))
        if (bytesread == sizeof (dw))
            return true;
    
    return false;
}

bool ShowFile::ReadInt (int32& i)
{
    uint32 bytesread;
    
    if (ReadBytes ((uint8 *)(&i), sizeof (i), bytesread))
        if (bytesread == sizeof (i))
            return true;
    
    return false;
}

bool ShowFile::ReadBool (bool& b)
{
    uint32 dw;
    
    if (! ReadDword (dw))
        return false;
    
    if (dw)
        b = true;
    else
        b = false;
    
    return true;
}

bool ShowFile::ReadGuid (Uuid& uuid)
{
    uint8 rawid[16];
    uint32 bytesread;
    
    if (ReadBytes (rawid, sizeof (rawid), bytesread))
        if (bytesread == sizeof (rawid))
        {
            uuid = Uuid(rawid);
            return true;
        }
    
    return false;
}

bool ShowFile::ReadString (String& outstring)
{
    uint32 length;
    if (! ReadDword (length))
        return false;
    
    if (length > 2000)
        return false;
    
    ScopedPointer<uint8> tempBuf = new uint8[length + 2];
    
    uint32 bytesread;
    if (! ReadBytes(tempBuf, length, bytesread))
        return false;
    
    tempBuf[length] = tempBuf[length + 1] = 0;
    outstring = CharPointer_UTF16 ((CharPointer_UTF16::CharType *)(tempBuf.get()));
    return true;
}
