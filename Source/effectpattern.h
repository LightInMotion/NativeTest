/*
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

#include "../JuceLibraryCode/JuceHeader.h"
#include "ShowFile.h"


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
    bool EffectPatLoad (String pFile);

    void EffectPatGetGuid(Uuid &guid);
    String EffectPatGetName();

private:

    // Private Functions ...................................................
    // Effect file access
    bool VerifyVersion (ShowFile& show);
    bool ReadInfo (ShowFile& show);
    bool ReadPoints (ShowFile& show);

    // Private Members .....................................................

    Uuid m_Guid;
    String m_Name;

    // Semi Private Members ................................................
    // Accessed by Friend class Effect (yuck)
    short m_EffectPatCount;
    EffectPoint m_EffectPatData[EFFECT_PAT_MAX_POINT];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectPattern)
};



#endif // _EFFECT_H_

