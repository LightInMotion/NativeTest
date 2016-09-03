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

// Includes ..................................................................

#include "Effect.h"		// Our stuff
#include "Fader.h"		// We need FADER defines for scaling
#include "main.h"		// For EffectData Serialize
//#include "EffectManager.h"


// Local Defines .............................................................


// Local Data Types ..........................................................

const int _EFFECT_NULL_SPEED = 0;


// Local Data ................................................................

/*
    We built a SIN table in shorts using the following code:

		#include <stdio.h>
		#include <math.h>

		void main()
		{
			double pi = 3.14159265358979;
			double deg = 0;

			while (deg <= 360.0)
			{
				for (int n = 0 ; n<10 ; n++)
				{
					double temp;
					short x;

					temp = deg * (pi / 180.0);
					temp = sin(temp);
					temp = temp * 1024;
					
					x = (short)temp;

					printf("%5d, ", x);
					deg = deg + 0.1;
				}
				printf("\n");
			}			
		}

    We then added 90 degrees to the end so that we
	could directly look up COS as well
*/

// Cosine is shifted 90 degrees forward
const int Effect::m_CosOffset = 900;

// We declare our SinTable as static, since it is read only.
const short Effect::m_SinTable[] = {
#include "sintab.hh"							// Load actual table from file
};


// Effect Data Load Serialize Methods ........................................

/*----------------------------------------------------------------------------
    EffectData::EffectDataLoad

    Load EffectData settings from a file
    Obtains an EffectPattern from the Effect Manager

    Returns: true or false
----------------------------------------------------------------------------*/

bool
EffectData::EffectDataLoad (ShowFile& show,     // Stream to load from
                            uint32 version,     // version to load
                            const OwnedArray<EffectPattern>& patterns) // Patterns to match
{
	uint32 bread;

	// Read the variables
	int csize;

	csize = sizeof(EffectData) - sizeof(EffectPattern *);

	if (! show.readBytes ((uint8*)this, csize, bread) || bread != csize)
		return false;

	// Read the guid for the pattern
	Uuid guid;
    if (! show.readGuid (guid))
		return false;

    for (int n = 0; n < patterns.size(); ++n)
    {
        Uuid pGuid;
        patterns[n]->EffectPatGetGuid(pGuid);
        if (pGuid == guid)
        {
            m_pPattern = patterns[n];
            return true;
        }
    }

    return false;
}


/*----------------------------------------------------------------------------
   EffectData::EffectDataSerialize

   Write Effect data settings to a file

   Returns: true or false
----------------------------------------------------------------------------*/

#if 0
bool
EffectData::EffectDataSerialize( IStream *pStream ) const // Stream to save to
{
	DWORD bdone;
	HRESULT hr;

	// Write the variables
	int csize;

	csize = sizeof(EffectData) - sizeof(EffectPattern *);

	hr = pStream->Write(this, csize, &bdone);
	if (hr != S_OK || bdone != csize)
		return false;

	// Write the guid for the pattern
	GUID guid;

	m_pPattern->EffectPatGetGuid(guid);

	hr = pStream->Write(&guid, sizeof(GUID), &bdone);
	if (hr != S_OK || bdone != sizeof(GUID))
		return false;

	return true;
}

#endif

// Public Interface ..........................................................

/*----------------------------------------------------------------------------
    Effect::Effect

    Constructor

    Returns: no return value
----------------------------------------------------------------------------*/

Effect::Effect()
    : m_CombinedRotation (0),
      m_CombinedSpeed (_EFFECT_NULL_SPEED),
      m_CombinedDirection (0),
      m_CurrentPosition (0),
      m_LastUpdateID (0)
{
}

/*----------------------------------------------------------------------------
    Effect::~Effect

    Destructor

    Returns: no return value
----------------------------------------------------------------------------*/

Effect::~Effect()
{
}


// Update Functions ..........................................................

/*
    The update functions are called whenever an effect is active. An effect
    is active when an EffectData entry is in a effect data entry list in an
    selected cue.

    We are actually called three times:

        EffectCalculate:		Combine speed, direction, rotation, and gain
		EffectUpdate:			Sum XY pairs using combined rotation and gain
		EffectAdvancePosition:	Advance position based upon combined speed
                                and direction, then zero everything
*/


/*----------------------------------------------------------------------------
    Effect::EffectCalculate

    We get called by the position control with a pointer to our EffectData
	and our fader level.  We use this to combine speed,
	direction and rotation, which we will later use when each effect
	is actually updated (summed into	the pan/tilt channels) and advanced

    Returns: no return value
----------------------------------------------------------------------------*/

void 
Effect::EffectCalculate (EffectData* pEffectData,
                         int faderLevel )
{
	// Start by scaling speed, and rotation
	int speed = ((pEffectData->m_Speed) * faderLevel) >> FADER_BIT_SHIFT;

	int rotation;

	if (pEffectData->m_Rotation < 0)
	{
		int temp_rot = 0 - pEffectData->m_Rotation;

		temp_rot = (temp_rot * faderLevel) >> FADER_BIT_SHIFT;

		rotation = 0 - temp_rot;
	}
	else
		rotation = ((pEffectData->m_Rotation) * faderLevel) >> FADER_BIT_SHIFT;

	// Combine speed
	m_CombinedSpeed += speed;

	// Combine direction
	if (pEffectData->m_Reverse == true)
		m_CombinedDirection -= faderLevel;
	else
		m_CombinedDirection += faderLevel;

	// Combine rotation
	// We 'wrap' in each direction
	m_CombinedRotation += rotation;
	if (m_CombinedRotation > EFFECT_MAX_ROTATION)
		m_CombinedRotation -= EFFECT_MAX_ROTATION;
	else if (m_CombinedRotation < EFFECT_MIN_ROTATION)
		m_CombinedRotation += EFFECT_MIN_ROTATION;
}


/*----------------------------------------------------------------------------
    Effect::EffectUpdate

    This function gets called from the position control. The position control
    passes the x/y positions as WORDs and the update function modifies them.

    Returns: no return value
----------------------------------------------------------------------------*/

void 
Effect::EffectUpdate (int16& xPos,
                      int16& yPos,
                      EffectData* pEffectData, 
                      int faderLevel)
{
	// Start by scaling our gain
	int gain = ((pEffectData->m_Gain) * faderLevel) >> FADER_BIT_SHIFT;


	// Fetch our coordinates
	int x,y;

	x = y = 0;

	// Average everything covered in the current speed range
	int ioffset = m_CurrentPosition;
//	for (int n=0 ; n < m_CombinedSpeed ; n++)
//	{
		x += pEffectData->m_pPattern->m_EffectPatData[ioffset].m_X;
		y += pEffectData->m_pPattern->m_EffectPatData[ioffset].m_Y;

//		ioffset++;
//		if (ioffset >= EFFECT_PAT_MAX_POINT)
//			ioffset = 0;
//	}

//	x /= m_CombinedSpeed;
//	y /= m_CombinedSpeed;

	// Fetch our trig values and rotate the point
	int sin, cos, negsin;
	int rx, ry;

	int rotation = m_CombinedRotation;

	// Don't rotate if rotation is 0
	if (rotation != 0)
	{
		// Change negative rotation into our normal 360 table
		if (rotation < 0)
			rotation += EFFECT_MAX_ROTATION;

		// Lookup sin, cos, and -sin
		sin = m_SinTable[rotation];
		negsin = 0 - sin;		// !!!! optimize?
		cos = m_SinTable[rotation + m_CosOffset];

		// |x y| | cos sin|
		//       |-sin cos|

		rx = x * cos + y * sin;
		ry = x * negsin + y * cos;

		// Sin table is scalled 1024
		rx /= 1024;		// !!!! optimize?
		ry /= 1024;
	}
	else
	{
		rx = x;
		ry = y;
	}

	// Scale per our gain
	x = (rx * gain) >> EFFECT_GAIN_BIT_SHIFT;
	y = (ry * gain) >> EFFECT_GAIN_BIT_SHIFT;

	// Offset and clip
	x += xPos;

	if (x < 0)
		x = 0;
	else if (x > 0xFFFF)
		x = 0xFFFF;

	// Save it
	xPos = (int16)x;

	// Offset and clip
	// Note, Y axis is inverted on
	// control (0,0=upper left !!!!
	y = 0 - y;
	y += yPos;

	if (y < 0)
		y = 0;
	else if (y > 0xFFFF)
		y = 0xFFFF;

	// Save it
	yPos = (int16)y;
}


/*----------------------------------------------------------------------------
    Effect::EffectAdvancePosition

    Advance the effect position and reset the combined speed and direction.
    The updateID is unique for one update cycle and can be compared with the
    last update ID.

    Returns: no return value
----------------------------------------------------------------------------*/

// !!!! Why is Effect Reset not happening more often? !!!!

void 
Effect::EffectAdvancePosition (unsigned int updateID)
{
	// Only advance if updateID is new
	if (updateID != m_LastUpdateID)
	{
		int newposition;

		// Reset position if effect has been off
		if ((updateID - m_LastUpdateID) != 1)
		{
//			Debug_Printf(TEXT("Effect Reset"));
			m_CurrentPosition = 0;
		}

		// Limit combined speed to allowed range
		if (m_CombinedSpeed > EFFECT_MAX_SPEED)
			m_CombinedSpeed = EFFECT_MAX_SPEED;
		if (m_CombinedSpeed < EFFECT_MIN_SPEED)
			m_CombinedSpeed = EFFECT_MIN_SPEED;

		// Forward?
		if (m_CombinedDirection >= 0)
		{
			// Advance
			newposition = m_CurrentPosition + m_CombinedSpeed;

			// Check for wrap
			if (newposition >= EFFECT_PAT_MAX_POINT)
				newposition -= EFFECT_PAT_MAX_POINT;
		}
		else
		{
			// Backwards
			newposition = m_CurrentPosition - m_CombinedSpeed;

			// Check for wrap
			if (newposition < 0)
				newposition += EFFECT_PAT_MAX_POINT;
		}

		// Store the new position
		m_CurrentPosition = newposition;

		// Reset composit values
        m_CombinedSpeed = _EFFECT_NULL_SPEED;
		m_CombinedDirection = 0;
		m_CombinedRotation = 0;

		// Update the ID
		m_LastUpdateID = updateID;
	}
}

