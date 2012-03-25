/*
    IntelHexReader.cpp
*/

#include "IntelHexReader.h"

//==============================================================================
IntelHexReader::IntelHexReader (const String& resourceName)
    : dataStream (0)
{
    int size;
    const char* data = BinaryData::getNamedResource (resourceName.toUTF8(), size);
    
    if (data != nullptr)
        dataStream = new MemoryInputStream (data, size, false);
}


IntelHexReader::IntelHexReader (const char* data, int size)
    : dataStream (0)
{
    if (data != nullptr)
        dataStream = new MemoryInputStream (data, size, false);    
}

//==============================================================================
int IntelHexReader::getTotalLength()
{
    if (dataStream == nullptr)
        return 0;

    return static_cast<int>(dataStream->getTotalLength());
}

//==============================================================================
int IntelHexReader::getUnparsedLength()
{
    if (dataStream == nullptr)
        return 0;
    
    if (dataStream->isExhausted())
        return 0;
    
    return static_cast<int>(dataStream->getTotalLength() - dataStream->getPosition());
}

//==============================================================================
bool IntelHexReader::readLineAsBinary (MemoryBlock& data, uint16& address)
{
    if (dataStream == nullptr)
        return false;
    
    // Get next line from stream
    // First, find the beginning of the line
    char c;
    do 
    {
        c = dataStream->readByte();
        if (c == 0)
            return false;
        
    } while (c != ':');

    // Next read till the end
    String hexString;
    
    while (1)
    {
        c = dataStream->readByte();
        if (c == '\n' || c == 0)
            break;
        
        hexString += c;
    }
    
    // Convert the whole thing to binary
    data.loadFromHexString (hexString);
    if (data.getSize() == 0)
        return false;
    
    // Malformed?
    if (data.getSize() != data[0] + 5)
        return false;
    
    // check type
    if (data[3] != 0)
        return false;
    
    // get address
    address = data[1];
    address <<= 8;
    address += data[2];
    
    // trim prefix and csum
    data.removeSection (data.getSize() - 1, 1);
    data.removeSection (0, 4);
    return true;
}

