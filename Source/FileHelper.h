/*
   File Info:

      $Workfile:   FileHelper.h  $
      $Author:   JOE  $
      $Revision:   1.0  $
      $Modtime:   02 Sep 2004 23:08:38  $

   Module Description:

      Helper functions for file access. Used from all classes which need to
      serialize and load from the structure storage file
*/


#ifndef _FILE_HELPER_H_
#define _FILE_HELPER_H_

// Includes ..................................................................

#include <string>


// Defines ...................................................................

// Data Types ................................................................

// Public Functions ..........................................................

// storage access
IStorage* FileHelpCreateStorage( IStorage* pStorage, UINT resourceIDStorage );
IStorage* FileHelpCreateIndexedStorage( IStorage* pStorage, int index );
IStorage* FileHelpOpenStorage( IStorage* pStorage, UINT resourceIDStorage );
IStorage* FileHelpOpenIndexedStorage( IStorage* pStorage, int index );

// stream access
IStream* FileHelpCreateStream( IStorage* pStorage, UINT resourceIDStream );
IStream* FileHelpOpenStream( IStorage* pStorage, UINT resourceIDStream );

// write functions
bool FileHelpWriteString(IStream* pStream, const std::wstring& stringToSave);
bool FileHelpWriteDWORD( IStream* pStream, DWORD value );
bool FileHelpWriteInt( IStream* pStream, int value );
bool FileHelpWriteUINT( IStream* pStream, UINT value );
bool FileHelpWriteBool( IStream* pStream, bool value );
bool FileHelpWriteBYTE( IStream* pStream, BYTE value );

// read functions
bool FileHelpReadString( IStream* pStream, std::wstring& stringToRead );
bool FileHelpReadDWORD( IStream* pStream, DWORD& value );
bool FileHelpReadInt( IStream* pStream, int& value );
bool FileHelpReadUINT( IStream* pStream, UINT& value );
bool FileHelpReadBool( IStream* pStream, bool& value );
bool FileHelpReadBYTE( IStream* pStream, BYTE& value );

#endif // _FILE_HELPER_H_


