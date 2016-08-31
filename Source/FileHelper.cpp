/*
   File Info:

      $Workfile:   FileHelper.cpp  $
      $Author:   JOE  $
      $Revision:   1.0  $
      $Modtime:   22 Oct 2009 11:34:32  $

   Module Description:

      Helper functions for file access. Used from all classes which need to
      serialize and load from the structure storage file
*/

// Includes ..................................................................

#include "FileHelper.h"
#include "Main.h"


// Local Defines .............................................................

// Local Data Types ..........................................................

// Local Variables ...........................................................

// Local Functions ...........................................................


// storage access ............................................................
/*
   create and open IStorage objects inside a structure storage file
*/

/*----------------------------------------------------------------------------
   FileHelpCreateStorage

   Create new storage object. Call Release() once you're done with the 
   storage object

   Returns: IStorage object or NULL if failed
----------------------------------------------------------------------------*/

IStorage* 
FileHelpCreateStorage( 
   IStorage* pStorage,     // parent storage object
   UINT resourceIDStorage )// resource ID for string of the new storage object
{
   // load string
   const int length = 256;
   TCHAR name[length] = TEXT("");
   if( ! LoadString( MainGetHInstance(), resourceIDStorage, name, length ))
      return NULL;

   // create the new storage object with write access (we don't need read
   // access)
   IStorage* pNewStorage = NULL;
   if( pStorage->CreateStorage( name, 
                                STGM_WRITE | STGM_SHARE_EXCLUSIVE, 
                                0, 
                                0, 
                                &pNewStorage) != S_OK)
      return NULL;

   return pNewStorage;
}


/*----------------------------------------------------------------------------
   FileHelpCreateIndexedStorage

   Create new storage object using the given index as the storage name. Call 
   Release() once you're done with the storage object

   Returns: IStorage object or NULL if failed
----------------------------------------------------------------------------*/

IStorage* 
FileHelpCreateIndexedStorage( 
   IStorage* pStorage,  // parent storage object
   int index )          // index for name of new storage object
{
   // use the given index as the name for the storage object
   TCHAR name[256] = TEXT("");
   wsprintf( name, TEXT("%d"), index );

   // create the new storage object with write access (we don't need read
   // access)
   IStorage* pNewStorage = NULL;
   if( pStorage->CreateStorage( name, 
                                STGM_WRITE | STGM_SHARE_EXCLUSIVE, 
                                0, 
                                0, 
                                &pNewStorage) != S_OK)
      return NULL;

   return pNewStorage;
}


/*----------------------------------------------------------------------------
   FileHelpOpenStorage

   Open existing storage object. Call Release() once you're done with the 
   storage object

   Returns: IStorage object or NULL if failed
----------------------------------------------------------------------------*/

IStorage* 
FileHelpOpenStorage( 
   IStorage* pStorage,     // parent storage object
   UINT resourceIDStorage )// resource ID for string of the new storage object
{
   // load string
   const int length = 256;
   TCHAR name[length] = TEXT("");
   if( ! LoadString( MainGetHInstance(), resourceIDStorage, name, length ))
      return NULL;

   // open storage object with read access
   IStorage* pNewStorage = NULL;
   if( pStorage->OpenStorage( name, 
                              NULL,
                              STGM_READ | STGM_SHARE_EXCLUSIVE,
                              NULL,
                              0,
                              &pNewStorage ) != S_OK )
      return NULL;

   return pNewStorage;
}


/*----------------------------------------------------------------------------
   FileHelpOpenIndexedStorage

   Open existing storage object using the index as the storage name. Call 
   Release() once you're done with the storage object

   Returns: IStorage object or NULL if failed
----------------------------------------------------------------------------*/

IStorage* 
FileHelpOpenIndexedStorage( 
   IStorage* pStorage,  // parent storage object
   int index )          // index for name of storage object to open
{
   // use the given index as the name for the storage object
   TCHAR name[256] = TEXT("");
   wsprintf( name, TEXT("%d"), index );

   // open storage object with read access
   IStorage* pNewStorage = NULL;
   if( pStorage->OpenStorage( name, 
                              NULL,
                              STGM_READ | STGM_SHARE_EXCLUSIVE,
                              NULL,
                              0,
                              &pNewStorage ) != S_OK )
      return NULL;

   return pNewStorage;
}


// stream access .............................................................
/*
   Create and open streams inside a structure storage file
*/

/*----------------------------------------------------------------------------
   FileHelpCreateStream

   Create new stream object. Call Release() once you're done with the 
   stream object

   Returns: IStream object or NULL if failed
----------------------------------------------------------------------------*/

IStream* 
FileHelpCreateStream( 
   IStorage* pStorage,     // parent storage object
   UINT resourceIDStream ) // resource ID for string of the new stream object
{
   // load string
   const int length = 256;
   TCHAR name[length] = TEXT("");
   if( ! LoadString( MainGetHInstance(), resourceIDStream, name, length ))
      return NULL;

   // create new stream with write access (no read access)
   IStream* pNewStream = NULL;
   if( pStorage->CreateStream( name, 
                               STGM_WRITE | STGM_SHARE_EXCLUSIVE, 
                               0, 
                               0, 
                               &pNewStream ) != S_OK)
      return NULL;

   return pNewStream;
}


/*----------------------------------------------------------------------------
   FileHelpOpenStream

   Open existing stream object. Call Release() once you're done with the 
   stream object

   Returns: IStream object or NULL if failed
----------------------------------------------------------------------------*/

IStream* 
FileHelpOpenStream( 
   IStorage* pStorage,     // parent storage object
   UINT resourceIDStream ) // resource ID for string of the new storage object
{
   // load string
   const int length = 256;
   TCHAR name[length] = TEXT("");
   if( ! LoadString( MainGetHInstance(), resourceIDStream, name, length ))
      return NULL;

   // open stream with read access
   IStream* pNewStream = NULL;
   if( pStorage->OpenStream( name, 
                             NULL,
                             STGM_READ | STGM_SHARE_EXCLUSIVE,
                             0,
                             &pNewStream ) != S_OK )
      return NULL;

   return pNewStream;
}


// write functions ...........................................................
/*
   write data to the file
*/

/*----------------------------------------------------------------------------
   FileHelpWriteString

   write a string to a stream. We write the length of the string first and
   then the string without writing the NULL terminator.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
FileHelpWriteString( IStream* pStream, 
                     const std::wstring& stringToSave )
{
   // write length first in bytes 
   DWORD length = stringToSave.size() * sizeof(WCHAR);
   if( ! FileHelpWriteDWORD( pStream, length ))
      return false;

   // write string as unicode string without null termination
   if( pStream->Write( stringToSave.c_str(), 
                       length, 
                       NULL ) != S_OK )
      return false;

   return true;
}


/*----------------------------------------------------------------------------
   FileHelpWriteDWORD

   Save DWORD value

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
FileHelpWriteDWORD( IStream* pStream, 
                    DWORD value )
{
   // save value as DWORD
   if( pStream->Write( &value, sizeof(DWORD), NULL ) != S_OK )
      return false;

   return true;
}


/*----------------------------------------------------------------------------
   FileHelpWriteInt

   Save integer

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
FileHelpWriteInt( IStream* pStream, 
                  int value )
{
   // we assume that 'int' is a 32bit value !!!! This application has to be
   // modified to run in 64bit (or at least if it gets compiled as a 64bit
   // application)

   // save value as int
   if( pStream->Write( &value, sizeof(int), NULL ) != S_OK )
      return false;

   return true;
}


/*----------------------------------------------------------------------------
   FileHelpWriteUINT

   Save unsigned int

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
FileHelpWriteUINT( IStream* pStream, 
                   UINT value )
{
   // save value as UINT
   if( pStream->Write( &value, sizeof(UINT), NULL ) != S_OK )
      return false;

   return true;
}


/*----------------------------------------------------------------------------
   FileHelpWriteBool

   Write bool value to the file. We save all bool values as DWORDs. (32 bit
   values)

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
FileHelpWriteBool( IStream* pStream, 
                   bool value )
{
   // convert bool to DWORD
   DWORD dwordValue = FALSE;
   if( value )
      dwordValue = TRUE;

   // save value as DWORD
   if( pStream->Write( &dwordValue, sizeof(DWORD), NULL ) != S_OK )
      return false;

   return true;
}


/*----------------------------------------------------------------------------
   FileHelpWriteBYTE

   Save byte

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
FileHelpWriteBYTE( IStream* pStream, 
                   BYTE value )
{
   // save value as int
   if( pStream->Write( &value, sizeof(BYTE), NULL ) != S_OK )
      return false;

   return true;
}


// read functions ............................................................
/*
   read data from the structure storage file
*/

/*----------------------------------------------------------------------------
   FileHelpReadString

   read a string from the given stream. All strings are saved in PASCAL 
   format, length first (as DWORD). The strings are not NULL terminated.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
FileHelpReadString( IStream* pStream, 
                    std::wstring& stringToRead )
{
   // read string length from the stream in bytes
   DWORD length = 0;
   if( ! FileHelpReadDWORD( pStream, length ))
      return false;

   // do we have an empty string
   if( length == 0 )
   {
      // clear string and return true
      stringToRead = TEXT("");
      return true;
   }

   // add insanity check
   if( length > 100000 )
      return false;

   bool result = true;

   // length in characters
   int charLength = length / sizeof(WCHAR);

   // allocate a temporary WCHAR buffer with room for the NULL terminator
   WCHAR* pTempString = new WCHAR[charLength + 1];
   if( pTempString )
   {
      // read the string data into the temporary string buffer. The string
      // in the stream doesn't contain a NULL terminator
      ULONG bytesRead = 0;
      if( pStream->Read( pTempString, length, &bytesRead ) != S_OK )
         result = false;

      // double check bytes read
      if( bytesRead != length )
         result = false;

      // add the NULL terminator to the end of the buffer
      pTempString[charLength] = L'\0';

      // copy the temporary string to the returned string
      stringToRead = pTempString;
      
      delete[] pTempString;
   }

   return result;
}


/*----------------------------------------------------------------------------
   FileHelpReadDWORD

   Read a DWORD from the stream

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
FileHelpReadDWORD( IStream* pStream, 
                   DWORD& value )
{
   static int dwordSize = sizeof(DWORD);

   // read the DWORD from the stream
   ULONG bytesRead = 0;
   if( pStream->Read( &value, dwordSize, &bytesRead ) != S_OK )
      return false;
   
   // double check the read bytes. The function also returns S_OK when it 
   // reads less data (because it reaches the end of the stream), therefor
   // we have to double check the read bytes.
   if( bytesRead != dwordSize )
      return false;

   return true;
}


/*----------------------------------------------------------------------------
   FileHelpReadInt

   Read an integer from the stream

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
FileHelpReadInt( IStream* pStream, 
                 int& value )
{
   // we assume "sizeof(DWORD) == sizeof(int)"
   static int intSize = sizeof(int);

   // read the DWORD from the stream
   ULONG bytesRead = 0;
   if( pStream->Read( &value, intSize, &bytesRead ) != S_OK )
      return false;
   
   // double check the read bytes. The function also returns S_OK when it 
   // reads less data (because it reaches the end of the stream), therefor
   // we have to double check the read bytes.
   if( bytesRead != intSize )
      return false;

   return true;
}


/*----------------------------------------------------------------------------
   FileHelpReadUINT

   Read an unsigned integer from the stream

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
FileHelpReadUINT( IStream* pStream, 
                  UINT& value )
{
   // we assume "sizeof(DWORD) == sizeof(int)"
   static int intSize = sizeof(int);

   // read the DWORD from the stream
   ULONG bytesRead = 0;
   if( pStream->Read( &value, intSize, &bytesRead ) != S_OK )
      return false;
   
   // double check the read bytes. The function also returns S_OK when it 
   // reads less data (because it reaches the end of the stream), therefor
   // we have to double check the read bytes.
   if( bytesRead != intSize )
      return false;

   return true;
}


/*----------------------------------------------------------------------------
   FileHelpReadBool
   
   read a bool value from the stream. All bool values are saved as DWORD
   (32 bit) values.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
FileHelpReadBool( IStream* pStream, 
                  bool& value )
{
   // read value as a DWORD
   DWORD dwordValue = FALSE;
   if( ! FileHelpReadDWORD( pStream, dwordValue ))
      return false;

   // convert 'BOOL' to 'bool'
   if( dwordValue == TRUE )
      value = true;
   else
      value = false;

   return true;
}


/*----------------------------------------------------------------------------
   FileHelpReadBYTE
   
   read a BYTE value from the stream. 

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
FileHelpReadBYTE( IStream* pStream, 
                  BYTE& value )
{
   // read the BYTE from the stream
   ULONG bytesRead = 0;
   if( pStream->Read( &value, 1, &bytesRead ) != S_OK )
      return false;
   
   // double check the read bytes. The function also returns S_OK when it 
   // reads less data (because it reaches the end of the stream), therefor
   // we have to double check the read bytes.
   if( bytesRead != 1 )
      return false;

   return true;
}







