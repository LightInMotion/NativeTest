/*
    Module Description:

	This module is an 'effect pattern', basically a shape scanned by the
	effect class.  It knows how to load itself from a filename, or from
	an istream.

	Effect is a 'friend' because the actual coordinate pairs are fetched
	directly for speed.
*/

// Includes ..................................................................

#include "EffectPattern.h"


// Local Defines .............................................................

// effect file versions.
const uint32 _EFFECT_FILE_VERSION_1_00    = 0x0100;

// current version
const uint32 _EFFECT_FILE_VERSION_CURRENT = _EFFECT_FILE_VERSION_1_00;


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
EffectPattern::EffectPatLoad (String file)
{
    bool result = false;
    
    ShowFile show (file);
	
    if (show.open())
    {
		// If we got here, it is structured storage and
		// is supposed to be an EffectFile
		// Try to read the info and points
        if (VerifyVersion(show) == true)
            if (ReadInfo (show) == true)
                if (ReadPoints (show) == true)
                    result = true;

        show.close();
	}

    return result;
}


/*----------------------------------------------------------------------------
	EffectPattern:EffectPatGetGuid

	Fetch the GUID for a pattern
----------------------------------------------------------------------------*/

void
EffectPattern::EffectPatGetGuid (Uuid &guid )	// OUT:  Guid to retrieve
{
	guid = m_Guid;
}


/*----------------------------------------------------------------------------
	EffectPattern:EffectPatGetName

	Fetch the Name for a pattern
----------------------------------------------------------------------------*/

String
EffectPattern::EffectPatGetName ()
{
    return m_Name;
}


// Effect File Helpers .......................................................

/*
    This bundles up the structured storage stuff and version checking, etc.
    for effect files
*/


/*----------------------------------------------------------------------------
   EffectPattern::VerifyVersion

   read the effect version from the structore storage file and verify that
   it is the correct version.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
EffectPattern::VerifyVersion (ShowFile& show)
{
    bool result = false;

    // Save Path
    String oldpath = show.getPath();

    // open version stream
    if (show.setPath (oldpath + "EffectX1"))
    {
        // load effect file version
        uint32 fileVersion = 0;
        if (show.readDword (fileVersion))
        {
            // verify the version. Currently we have only one effect file
            // version and we don't support any other version.
            // Should we change the file format in a later version then we
            // have to be able to load new and old versions.

            if (fileVersion == _EFFECT_FILE_VERSION_CURRENT)
                result = true;
        }
    }

    show.setPath (oldpath);
    return result;
}


/*----------------------------------------------------------------------------
   EffectPattern::ReadInfo

   Get the GUID, name, and count from the effect file.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
EffectPattern::ReadInfo (ShowFile& show)			// Open file
{
    bool result = false;

    // Save Path
    String oldpath = show.getPath();

    // open info stream
    if (show.setPath (oldpath + "Info"))
    {
        do
        {
            // Load the GUID
            if (! show.readGuid(m_Guid))
                break;

			// Load the Count
            if (! show.readShort(m_EffectPatCount) || m_EffectPatCount != EFFECT_PAT_MAX_POINT)
                break;

			// Read the name
			if (! show.readString (m_Name))
				break;
            
            result = true;

        } while (0);
    }

    show.setPath (oldpath);
    return result;
}


/*----------------------------------------------------------------------------
    EffectPattern::ReadPoints

    Get the data points from the effect file.

    Returns: true or false
----------------------------------------------------------------------------*/

bool 
EffectPattern::ReadPoints (ShowFile& show)  // Open file
{
    bool result = false;

    // Save Path
    String oldpath = show.getPath();
    
    // open info stream
    if (show.setPath (oldpath + "Points"))
    {
		uint32 bread;

		// Load the Points
		int count = sizeof(EffectPoint) * m_EffectPatCount;
		if (show.readBytes ((uint8*)(&m_EffectPatData), count, bread) && bread == (uint32)count)
            result = true;
    }
    
    show.setPath (oldpath);
    return result;
}
