/*
    Module Description:

    The Effect object knows how to rotate patterns, scale them, sequence
    through them, and use them to offset XY pairs.  Normally, each
    position control owns one Effect object.  Since all EffectPattern
    objects use the same origin, and since all Effect objects use a single
    index, cross fading of effects is possible

    The effect manager (see EffectManager.cpp) actually loads and manages
    the patterns, patterns are passed, along with control data to Effect
    objects indirectly.  The effect manager also creates an effect for
    rendering, but that is a special case.

    Though the effect manager handles the loading of patterns, the actual
    pattern object and data objects are declared here, so that a circular
    dependancy is not created between this object and the Effect manager
*/


#ifndef _EFFECT_H_
#define _EFFECT_H_

// Includes ..................................................................

#include "../JuceLibraryCode/JuceHeader.h"
#include "ShowFile.h"
#include "EffectPattern.h"


// Defines ...................................................................

// Effect Control Limits
const int EFFECT_MAX_GAIN = 1024;      // Max/Min Gain settings
const int EFFECT_MIN_GAIN = 0;
const int EFFECT_GAIN_BIT_SHIFT = 10;	// Keep in sync with MAX_GAIN

const int EFFECT_MAX_SPEED = 100;		// Max/Min Speed settings
const int EFFECT_MIN_SPEED = 1;        // 0 = stopped!

const int EFFECT_MAX_ROTATION = 3600;  // Max/Min rotation
const int EFFECT_MIN_ROTATION = -3600; // 1/10 degree

// Effect defaults
const int EFFECT_DEFAULT_GAIN = (EFFECT_MAX_GAIN - EFFECT_MIN_GAIN) / 10;
const int EFFECT_DEFAULT_SPEED = 15;
const int EFFECT_DEFAULT_ROTATION = 0;
const bool EFFECT_DEFAULT_DIRECTION = false;


// Data Types ................................................................

class EffectData
{
public:
    // Constructors/Destructor ................................................

    // For loading
    EffectData() :
        m_Gain (0),
		m_Speed (0),
		m_Rotation (0),
		m_Reverse (false),
		m_pPattern (NULL) {};

    // For editing
    EffectData (EffectPattern* pPattern) :
			m_Gain(EFFECT_DEFAULT_GAIN),
			m_Speed(EFFECT_DEFAULT_SPEED),
			m_Rotation(EFFECT_DEFAULT_ROTATION),
			m_Reverse(EFFECT_DEFAULT_DIRECTION),
			m_pPattern (pPattern) {};

    ~EffectData(){};

    // Current Settings .......................................................

    int m_Gain;
    int m_Speed;
    int m_Rotation;
    bool m_Reverse;
    EffectPattern* m_pPattern;	// Must be last (for serialize)

    // API ....................................................................

//   bool EffectDataSerialize(IStream *stream) const;
    bool EffectDataLoad (ShowFile& show,
                         uint32 version,
                         const OwnedArray<EffectPattern>& patterns);

    JUCE_LEAK_DETECTOR (EffectData)
};

// Class Definition ..........................................................

class Effect
{
public:

    Effect();
    ~Effect();

    // Public Interface ....................................................

    void EffectCalculate (EffectData* pEffectData,
                          int faderLevel);

    void EffectUpdate (int16& xPos,
                       int16& yPos,
                       EffectData* pEffectData,
                       int faderLevel);

    void EffectAdvancePosition (uint32 updateID);


private:

    // Private Functions ...................................................

    // Private Members .....................................................

    // the following are summed in the EffectCalculate()
    // function call and reset from EffectAdvancePosition().
    int m_CombinedRotation;
    int m_CombinedSpeed;
    int m_CombinedDirection;

    // current position in the effect table
    int m_CurrentPosition;

    // the updateID gets incremented each update cycle. We need this id to
    // check if EffectAdvancePosition gets called muliple times in one
    // update cycle
    uint32 m_LastUpdateID;

    // Our sin/cos table for rotation
    static const int m_CosOffset;
    static const short m_SinTable[];
    
    JUCE_LEAK_DETECTOR (Effect)
};

#endif // _EFFECT_H_

