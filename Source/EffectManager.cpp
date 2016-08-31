/*
   File Info:

      $Workfile:   EffectManager.cpp  $
      $Author:   JOE  $
      $Revision:   1.0  $
      $Modtime:   22 Oct 2009 11:41:52  $

   Module Description:

      The effect manager loads and manages EffectPattern (simple
      vector graphic) objects.  Currently effects are loaded
      at Initialization and released at shutdown, but the current
      design should support pattern serialization.

      All patterns are currently loaded from Structured Storage
      files from a directory obtained from the Registry module.

      In normal operation, the Cue Object obtains an effect pattern
      from this manager, then passes it to a control, along with settings,
      in a EffectData object.  The control, in turn, uses an Effect
      object (see Effect.cpp) to execute the pattern and settings as
      an offset to an XY coordinate pair.
*/

// Includes ..................................................................

#include "EffectManager.h"    // Our stuff
#include "Registry.h"         // We need to find our directory
#include "resource.h"
#include "main.h"					// We show error message (if any) on init
#include "fader.h"				// We need fader range for transform
#include "FileHelper.h"			// For structured storage
#include <tchar.h>				// For directory strings
#include <Shlwapi.h>				// and path functions...
#include "debug.h"


// Local Defines .............................................................


// Local Data Types ..........................................................


// Public Interface ..........................................................

/*----------------------------------------------------------------------------
   EffectManager::EffectManager

   Constructor

   Returns: no return value
----------------------------------------------------------------------------*/

EffectManager::EffectManager()
{
}


/*----------------------------------------------------------------------------
   EffectManager::~EffectManager

   Destructor

   Returns: no return value
----------------------------------------------------------------------------*/

EffectManager::~EffectManager()
{
   // Free all loaded patterns
   int patternCount = m_EffectPatternList.size();
   for( int patternIndex = 0; patternIndex < patternCount; patternIndex++ )
      delete m_EffectPatternList[patternIndex];
}


// initialize ................................................................

/*
   Initialize, has to be called from the main module during startup. No 
   cleanup function needs to be called. All cleanup is done in the 
   destructor.
*/

/*----------------------------------------------------------------------------
   EffectManager::EffectManInitialize

   Load the effect path from the registry and verify that the directory
   exists. The directory and the registry key has to be created from the 
   installer. 
   
   Load all effect patterns and create pattern objects in memory.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
EffectManager::EffectManInitialize()
{
   // load the effect path from the registry. The registry key has to 
   // be created during installation. The installer also copies all the
   // predefined effects into that folder.
	
	std::wstring epath;

   if( ! RegLoadPath( IDS_REGISTRY_VALUE_EFFECT_PATH, epath ))
   {
      // if we can't find that registry key then we abort. The function will
      // only fail if the installer was not run or something else is terrible
      // wrong. If we would continue we would not be able to play shows
		// with effects

      MainShowErrorMessage( NULL, IDS_ERROR_OPEN_EFFECT_KEY );
      return false;
   }

   // verify that the template directory exists
   if( ! PathIsDirectory( epath.c_str()))
   {
      // warn the user that we couldn't find the template folder and abort.
      // The folder for loading/saving templates has to exist in order
      // for the application to run.
      MainShowErrorMessage( NULL, IDS_ERROR_EFFECT_PATH_MISSING );
      return false;
   }

	// Load all the effects in the folder
   bool b = LoadAllEffectPatterns(epath.c_str());

#if 0	// For Joe Testing !!!!
	if (b == true)
	{
		if (EffectManGetPatternCount())
		{
			int shapes = EffectManGetPatternCount();

			for (int idx = 0 ; idx < shapes ; idx++)
			{
				EffectPattern * pPattern;
				
				pPattern = EffectManGetPattern(idx);
				std::wstring name;
				pPattern->EffectPatGetName(name);
				MessageBox(NULL, name.c_str(), TEXT("Debug"), MB_OK);
				EffectData *effectdata = new EffectData(pPattern);

				RECT r;
				r.left =0; r.right = 500;
				r.top = 0; r.bottom = 500;
				POINT points[3000];
				int count = 3000;
				WORD x = 32750, y = 32750;

				HDC hdc = GetDC(NULL);
				HPEN hpen = CreatePen(PS_SOLID, 0, RGB(255,100,50));
				HPEN holdpen = (HPEN)SelectObject(hdc, hpen);

				effectdata->m_Rotation = 450;
				effectdata->m_Gain = 512;

				EffectManTransform(x, y, effectdata, r, count, points);

				delete effectdata;

				MoveToEx(hdc, points[0].x, points[0].y, NULL);
				for (int n=1 ; n< count ; n++)
					LineTo(hdc, points[n].x, points[n].y);

				SelectObject(hdc, holdpen);
				DeleteObject(hpen);
 				ReleaseDC(NULL, hdc);
			}
		}
/*
      if (EffectManGetPatternCount() >= 2)
      {
			EffectPattern * pPattern1;
         EffectPattern * pPattern2;
         			
			pPattern1 = EffectManGetPattern(0);
         pPattern2 = EffectManGetPattern(0);

			EffectData *effectdata1 = new EffectData(pPattern1);
         EffectData *effectdata2 = new EffectData(pPattern2);

			effectdata1->m_Rotation = 450;
			effectdata1->m_Gain = 512;

			effectdata2->m_Rotation = 450;
			effectdata2->m_Gain = 1024;

			RECT r;
			r.left =0; r.right = 500;
			r.top = 0; r.bottom = 500;
			POINT points[3000];
			int count = 3000;
			WORD x = 32750, y = 32750;

         std::vector <EffectData *>elist;
         std::vector <int *>flist;

         int fader1, fader2;

         elist.push_back(effectdata1);
         elist.push_back(effectdata2);

         flist.push_back(&fader1);
         flist.push_back(&fader2);

			HDC hdc = GetDC(NULL);
			HPEN hpen = CreatePen(PS_SOLID, 0, RGB(255,100,50));
			HPEN holdpen = (HPEN)SelectObject(hdc, hpen);

         for (int findex = FADER_MAX_LEVEL ; findex >= 0 ; findex -= 512)
         {
            fader1 = findex;
            fader2 = FADER_MAX_LEVEL - findex;

            Debug_Printf(TEXT("Fade: %d %d"), fader1, fader2);
            MessageBox(NULL, TEXT("Step"), TEXT("Debug"), MB_OK);
            			
			   EffectManTransform(x, y, elist, flist, r, count, points);

   			MoveToEx(hdc, points[0].x, points[0].y, NULL);
   			for (int n=1 ; n< count ; n++)
   				LineTo(hdc, points[n].x, points[n].y);

//		LineTo(hdc, points[0].x, points[0].y);
         }

			SelectObject(hdc, holdpen);
			DeleteObject(hpen);
			ReleaseDC(NULL, hdc);

			delete effectdata1;
         delete effectdata2;
      }
*/
	}
#endif

	return b;
}


// Member access..............................................................


/*----------------------------------------------------------------------------
   EffectManager::EffectManGetPatternCount

   Get the number of loaded effects

   Returns: number of effect patterns
----------------------------------------------------------------------------*/

int 
EffectManager::EffectManGetPatternCount() const
{
   return m_EffectPatternList.size();
}

      
/*----------------------------------------------------------------------------
   EffectManager::EffectManGetPattern   

   Get a loaded pattern by index.  No index validation is
   performed!

   Returns: effect pattern pointer
----------------------------------------------------------------------------*/

EffectPattern *
EffectManager::EffectManGetPattern( int index )
{
   return m_EffectPatternList[index];
}


/*----------------------------------------------------------------------------
   EffectManager::EffectManGetPattern   

   Get a loaded pattern by guid.  

   Returns: effect pattern pointer, or NULL
----------------------------------------------------------------------------*/

EffectPattern *
EffectManager::EffectManGetPattern( const GUID& guid )
{
   for (DWORD index=0 ; index < m_EffectPatternList.size() ; index++)
   {
		GUID pGuid;

		m_EffectPatternList[index]->EffectPatGetGuid(pGuid);

      if (pGuid == guid)
			return m_EffectPatternList[index];
   }

   return NULL;
}


/*----------------------------------------------------------------------------
   EffectManager::EffectManTransform

   Perform rotation and scaling on an effect and produce a designated
	number of points for rendering.  Specified points must not exceed
	EFFECT_MAX_POINTS.

   Returns: true for success, false for failure
----------------------------------------------------------------------------*/

bool 
EffectManager::EffectManTransform( WORD xPos, WORD yPos, // XY position
                    EffectData *pEffectData,		// Effect and settings to use
						  const RECT& rect,				// Origin, width, and height
						  const int count, 				// Number of points to render
						  POINT *pPoints )				// OUT: Rendered coordinates
{
   Effect effect;    // We'll need an effect

	// Check for valid points
	if ((count < 0) || (count > EFFECT_PAT_MAX_POINT))
		return false;

	// Calculate our x and y scaling factors
	WORD xscale, yscale;

	xscale = (WORD)(65535 / (rect.right - rect.left));
	yscale = (WORD)(65535 / (rect.bottom - rect.top));

	// Save the old speed and plug in ours
	// 'speed' is basically how far we will step each advance
	int oldspeed = pEffectData->m_Speed;
	pEffectData->m_Speed = (EFFECT_PAT_MAX_POINT / count);

	// Build the points
	for (int index = 0 ; index < count ; index++)
	{
		WORD tempX, tempY;

		// Start by updating the point normally
		tempX = xPos;
		tempY = yPos;

		effect.EffectCalculate(pEffectData, FADER_MAX_LEVEL);
		effect.EffectUpdate(tempX, tempY, pEffectData, FADER_MAX_LEVEL);
		effect.EffectAdvancePosition((WORD)index+1);

		// Next, we want to scale the point to our width and height
		tempX /= xscale;
		tempY /= yscale;

		// Last, we add the offset
		// !!!! Do we want to invert Y?
		tempX += (WORD)rect.left;
		tempY += (WORD)rect.top;

		// And store the point
		pPoints[index].x = tempX;
		pPoints[index].y = tempY;
	}

	// Restore speed
	pEffectData->m_Speed = oldspeed;
	return true;
}

/*----------------------------------------------------------------------------
   EffectManager::EffectManTransform

   Perform rotation and scaling on an effect and produce a designated
	number of points for rendering.  Specified points must not exceed
	EFFECT_MAX_POINTS.

   This version takes a list of effectdata and a list of fader values
   and combines them.  It is primarily for testing, but may be useful
   for rendering combined effects.

   Returns: true for success, false for failure
----------------------------------------------------------------------------*/

bool 
EffectManager::EffectManTransform( WORD xPos, WORD yPos,       // XY position
                    std::vector <EffectData *> effectDataList,	// settings
                    std::vector <int *> faderList, // fader values
						  const RECT& rect,				   // Origin, width, and height
						  const int count, 				   // Number of points to render
						  POINT *pPoints )				   // OUT: Rendered coordinates
{
   Effect effect;    // We'll need an effect

	// Check for valid points
	if ((count < 0) || (count > EFFECT_PAT_MAX_POINT))
		return false;

   int faderCount = faderList.size();

	// Calculate our x and y scaling factors
	WORD xscale, yscale;

	xscale = (WORD)(65535 / (rect.right - rect.left));
	yscale = (WORD)(65535 / (rect.bottom - rect.top));

   // Calculate our 'speed' (how far we will step)
   int ourspeed = (EFFECT_PAT_MAX_POINT / count);


	// Build the points
	for (int index = 0 ; index < count ; index++)
	{
		WORD tempX, tempY;
		int findex;

		// Start by updating the point normally
		tempX = xPos;
		tempY = yPos;

		// Combine speed, direction, and rotation
      for (findex = 0 ; findex < faderCount ; findex++)
      {
      	// Save the old speed and plug in ours
	      // 'speed' is basically how far we will step each advance
	      int oldspeed = effectDataList[findex]->m_Speed;
	      effectDataList[findex]->m_Speed = ourspeed;

		   effect.EffectCalculate(effectDataList[findex], *(faderList[findex]));

      	// Restore speed
	      effectDataList[findex]->m_Speed = oldspeed;
      }

		// Do actual image combining
      for (findex = 0 ; findex < faderCount ; findex++)
      {
		   effect.EffectUpdate(tempX, tempY, 
		      effectDataList[findex], *(faderList[findex]));
      }

		// Next Point
		effect.EffectAdvancePosition((WORD)index+1);

		// Next, we want to scale the point to our width and height
		tempX /= xscale;
		tempY /= yscale;

		// Last, we add the offset
		// !!!! Do we want to invert Y?
		tempX += (WORD)rect.left;
		tempY += (WORD)rect.top;

		// And store the point
		pPoints[index].x = tempX;
		pPoints[index].y = tempY;
	}
	return true;
}


// Private Functions .........................................................

/*----------------------------------------------------------------------------
   EffectManager::LoadAllEffectPatterns

   Load all effect patterns from the given folder. This function is called 
   during initialization

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
EffectManager::LoadAllEffectPatterns( LPCTSTR pFolder )
{
   bool success = true;

   // load the template file extension from the resources
   const int extensionLength = 50;
   TCHAR fileExtension[extensionLength];
   LoadString( MainGetHInstance(), 
               IDS_EFFECT_FILE_EXTENSION, 
               fileExtension, 
               extensionLength );

   // create search path for folder
   std::wstring searchPath = pFolder;
   searchPath += TEXT("\\*");
   searchPath += fileExtension;

   // find file structure
   WIN32_FIND_DATA fileStruct;
   ZeroMemory( &fileStruct, sizeof(fileStruct));

   // find first template file
   HANDLE hFile = FindFirstFile( searchPath.c_str(), &fileStruct );
   if( hFile != INVALID_HANDLE_VALUE )
   {
      // for all template files in that folder
      do
      {
         // make sure it is a file
         if((fileStruct.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == 0)
         {
				std::wstring fileName;

				// Try to load it
				EffectPattern *pPattern;

				fileName = pFolder;
				fileName += TEXT("\\");
				fileName += fileStruct.cFileName;

				pPattern = new EffectPattern;

				if (pPattern->EffectPatLoad(fileName.c_str()) == TRUE)
					m_EffectPatternList.push_back(pPattern);
				else
					delete pPattern;
         }
     
      // find next template file
      } while( FindNextFile( hFile, &fileStruct ));

      // close search handle
      FindClose( hFile );
   }

   return success;
}


