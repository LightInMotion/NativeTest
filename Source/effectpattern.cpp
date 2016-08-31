/*
   File Info:

      $Workfile:   effectpattern.cpp  $
      $Author:   JOE  $
      $Revision:   1.0  $
      $Modtime:   30 Aug 2004 12:52:28  $

   Module Description:

	This module is an 'effect pattern', basically a shape scanned by the
	effect class.  It knows how to load itself from a filename, or from
	an istream.

	Effect is a 'friend' because the actual coordinate pairs are fetched
	directly for speed.
*/

// Includes ..................................................................

#include "EffectPattern.h"		// Our stuff
#include "filehelper.h"
#include "resource.h"


// Local Defines .............................................................

// effect file versions.
const DWORD _EFFECT_FILE_VERSION_1_00    = 0x0100;

// current version
const DWORD _EFFECT_FILE_VERSION_CURRENT = _EFFECT_FILE_VERSION_1_00;


// Local Data Types ..........................................................


// Local Data ................................................................


// Public Interface ..........................................................

/*
	A pattern is asked to load itself from disk here.
*/

/*----------------------------------------------------------------------------
   EffectPattern::EffectPatLoad

   Load an individual pattern from a file

   Returns: true or false
----------------------------------------------------------------------------*/

bool
EffectPattern::EffectPatLoad( LPCTSTR pFile )
{
	IStorage *pStorage;
	
	pStorage = OpenFileForRead(pFile);

	if (pStorage != NULL)
	{
		// If we got here, it is structured storage and
		// is supposed to be an EffectFile
		// Try to read the info and points
		if (ReadInfo(pStorage) == true)
		{
			if (ReadPoints(pStorage) == true)
			{
				pStorage->Release();
				return true;
			}
		}

		pStorage->Release();
	}

	return false;
}


/*----------------------------------------------------------------------------
	EffectPattern:EffectPatGetGuid

	Fetch the GUID for a pattern
----------------------------------------------------------------------------*/

void
EffectPattern::EffectPatGetGuid( GUID &guid )	// OUT:  Guid to retrieve
{
	guid = m_Guid;
}


/*----------------------------------------------------------------------------
	EffectPattern:EffectPatGetName

	Fetch the Name for a pattern
----------------------------------------------------------------------------*/

void
EffectPattern::EffectPatGetName(std::wstring &name ) // OUT: Name
{
	name = m_Name;
}


// Effect File Helpers .......................................................

/*
	This bundles up the structured storage stuff and version checking, etc.
	for effect files
*/

/*----------------------------------------------------------------------------
   EffectPattern::OpenFileForRead

   Open the effect file for reading. This function is called from LoadPattern()
	We also check for the file version here

   Returns: root storage pointer or NULL if failed
----------------------------------------------------------------------------*/

IStorage* 
EffectPattern::OpenFileForRead( LPCTSTR pFile )
{
   // open structure storage file with read access
   IStorage* pStorage = NULL;
   if( StgOpenStorageEx( pFile, 
                         STGM_READ | STGM_SHARE_DENY_WRITE | STGM_DIRECT,// STGM_SHARE_EXCLUSIVE 
                         STGFMT_STORAGE,
                         0,
                         NULL,
                         0,
                         IID_IStorage,
                         (void**)&pStorage ) == S_OK )
   {
      // verify the template version and return the storage object
      if( VerifyVersion( pStorage ))
         return pStorage;
      else
      {
         pStorage->Release();
         return NULL;
      }
   }

   return NULL;
}


/*----------------------------------------------------------------------------
   EffectPattern::VerifyVersion

   read the effect version from the structore storage file and verify that
   it is the correct version.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
EffectPattern::VerifyVersion( IStorage* pStorage )
{
   bool result = true;

   // open version stream
   IStream* pStreamVersion = FileHelpOpenStream( pStorage, 
                                                 IDS_EFFECT_FILE_VERSION );
   if( pStreamVersion )
   {
      // load effect file version
      DWORD fileVersion = 0;
      if( FileHelpReadDWORD( pStreamVersion, fileVersion ))
      {
         // verify the version. Currently we have only one template file
         // version and we don't support any other version.
         // Should we change the file format in a later version then we
         // have to be able to load new and old versions.

         if( fileVersion != _EFFECT_FILE_VERSION_CURRENT )
            result = false;
      }
      else
         result = false;

      // close version stream
      pStreamVersion->Release();
   }
   else
      result = false;

   return result;
}


/*----------------------------------------------------------------------------
   EffectPattern::ReadInfo

   Get the GUID, name, and count from the effect file.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
EffectPattern::ReadInfo( IStorage* pStorage )			// Open file
{
   bool result = true;

   // open info stream
   IStream* pStreamInfo = FileHelpOpenStream( pStorage, 
                                              IDS_EFFECT_FILE_INFO );
   if( pStreamInfo )
   {
		do
		{
			HRESULT hr;
			DWORD bread;

			// Load the GUID
			hr = pStreamInfo->Read(&(m_Guid), sizeof(GUID), &bread);
			if ( (hr != S_OK) || (bread != sizeof(GUID)) )
			{
				result = false;
				break;
			}

			// Load the Count
			hr = pStreamInfo->Read(&(m_EffectPatCount), sizeof(short), &bread);
			if ( (hr != S_OK) || (bread != sizeof(short)) || 
				  (m_EffectPatCount < 0) || (m_EffectPatCount != EFFECT_PAT_MAX_POINT) )
			{
				result = false;
				break;
			}

			// Read the name
			if (FileHelpReadString(pStreamInfo, m_Name) == false)
			{
				result = false;
				break;
			}

		} while (0);

      // close info stream
      pStreamInfo->Release();
   }
   else
      result = false;

   return result;
}


/*----------------------------------------------------------------------------
   EffectPattern::ReadPoints

   Get the data points from the effect file.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
EffectPattern::ReadPoints( IStorage* pStorage )				// Open file
{
   bool result = true;

   // open info stream
   IStream* pStreamPoints = FileHelpOpenStream( pStorage, 
                                                IDS_EFFECT_FILE_POINTS );
   if( pStreamPoints )
   {
		HRESULT hr;
		DWORD bread;

		// Load the Points
		int count = sizeof(EffectPoint) * m_EffectPatCount;
		hr = pStreamPoints->Read(&(m_EffectPatData), count, &bread);
		if ( (hr != S_OK) || (bread != count) )
			result = false;

      // close point stream
      pStreamPoints->Release();
   }
   else
      result = false;

   return result;
}
