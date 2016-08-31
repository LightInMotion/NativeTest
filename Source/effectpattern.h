/*
   File Info:

      $Workfile:   effectpattern.h  $
      $Author:   JOE  $
      $Revision:   1.0  $
      $Modtime:   13 Jul 2004 18:01:00  $

   Module Description:

	This module is an 'effect pattern', basically a shape scanned by the
	effect class.  It knows how to load itself from a filename, or from
	an istream.

	Effect is a 'friend' because the actual coordinate pairs are fetched
	directly for speed.
*/


#ifndef _EFFECT_PATTERN_H_
#define _EFFECT_PATTERN_H_

// Includes ..................................................................

#include <string>


// Defines ...................................................................

// Pattern size
const int EFFECT_PAT_MAX_POINT = 3000;	// All patterns are fixed size


// Data Types ................................................................

// Basic Effect Coordinate
class EffectPoint
{
public:
   EffectPoint(){};
   ~EffectPoint(){};

   // XY pair
   short m_X;
   short m_Y;
};


// Class Definition ..........................................................

class EffectPattern
{
	friend class Effect;

	public:
		EffectPattern(){}
		~EffectPattern(){};

		// Public Interface ....................................................
		bool EffectPatLoad( LPCTSTR pFile );

		void EffectPatGetGuid(GUID &guid);
		void EffectPatGetName(std::wstring &name);

	private:

		// Private Functions ...................................................
		// Effect file access
		IStorage* OpenFileForRead( LPCTSTR pFile );
		bool VerifyVersion( IStorage* pStorage );
		bool ReadInfo( IStorage* pStorage );
		bool ReadPoints( IStorage* pStorage );

		// Private Members .....................................................

		GUID m_Guid;
		std::wstring m_Name;

		// Semi Private Members ................................................
		// Accessed by Friend class Effect (yuck)
		short m_EffectPatCount;
		EffectPoint m_EffectPatData[EFFECT_PAT_MAX_POINT];
};



#endif // _EFFECT_H_

