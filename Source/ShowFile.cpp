/*
    ShowFile.cpp
 
    Simple Show File Access
*/

#include "ShowFile.h"
#include "pole.h"

//==============================================================================
//==============================================================================
// Constructor/Destructor
//
ShowFile::ShowFile (String _filename)
    : filename (_filename),
      currentPath ("/")
{
    storage = new POLE::Storage (filename);
}

ShowFile::~ShowFile()
{
}

//==============================================================================
// File open Close
//
bool ShowFile::open()
{
    storage->open();
    if (storage->result() == POLE::Storage::Ok)
        return true;
    
    return false;
}

void ShowFile::close()
{
    storage->close();
}

//==============================================================================
// Virtual Path Management
//
bool ShowFile::setPath (String path)
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

String ShowFile::getPath()
{
    return currentPath;
}

bool ShowFile::isDirectory (String path)
{
    return storage->isDirectory (path);
}

StringArray ShowFile::getDirectory()
{
    return storage->entries (currentPath);
}

//==============================================================================
// Stream Access
//
bool ShowFile::readBytes (uint8* outbuf, uint32 readsize, uint32& bytesread)
{
    if (stream == nullptr)
        return false;
    
    uint64 read = stream->read (outbuf, readsize);
    bytesread = (uint32)read;
    return true;
}

bool ShowFile::readDword (uint32& dw)
{
    uint32 bytesread;
    
    if (readBytes ((uint8 *)(&dw), sizeof (dw), bytesread))
        if (bytesread == sizeof (dw))
            return true;
    
    return false;
}

bool ShowFile::readInt (int32& i)
{
    uint32 bytesread;
    
    if (readBytes ((uint8 *)(&i), sizeof (i), bytesread))
        if (bytesread == sizeof (i))
            return true;
    
    return false;
}

bool ShowFile::readBool (bool& b)
{
    uint32 dw;
    
    if (! readDword (dw))
        return false;
    
    if (dw)
        b = true;
    else
        b = false;
    
    return true;
}

bool ShowFile::readGuid (Uuid& uuid)
{
    uint8 rawid[16];
    uint32 bytesread;
    
    if (readBytes (rawid, sizeof (rawid), bytesread))
    {
        if (bytesread == sizeof (rawid))
        {
            uuid = Uuid(rawid);
            return true;
        }
    }
    return false;
}

bool ShowFile::readString (String& outstring)
{
    // Strings are always UTF_16, stored Pascal style (length, no terminator)
    uint32 length;
    if (! readDword (length))
        return false;
    
    // Reality check
    if (length > 2000)
        return false;
    
    ScopedPointer<uint8> tempBuf = new uint8[length + 2];
    
    uint32 bytesread;
    if (! readBytes(tempBuf, length, bytesread))
        return false;
    
    // Terminate and cast to a String
    tempBuf[length] = tempBuf[length + 1] = 0;
    outstring = CharPointer_UTF16 ((CharPointer_UTF16::CharType *)(tempBuf.get()));
    return true;
}
