/*
    Module Description:

    The position control is derived from the Control class. It is used
    to handle the position (pan/tilt values) of the control. Most moving
    lights (devices) contain position control. The position control
    represents either two DMX channels (one for pan, one for tilt), or
    four DMX channels (16bit resolution, using two channels for pan and
    tilt).

    Each position control can have an Effect which can be turned on or
    off.
*/


#ifndef _POSITION_CONTROL_H_
#define _POSITION_CONTROL_H_

// Includes ..................................................................

#include "Control.h"
// #include "Effect.h"


// Defines ...................................................................

// Data Types ................................................................

// Class Definition ..........................................................

class PositionControl : public Control
{
public:

    PositionControl();
    PositionControl (bool is16BitResolution,
                     uint32 panCoarseChannelOffset,
                     uint32 panFineChannelOffset,
                     uint32 tiltCoarseChannelOffset,
                     uint32 tiltFineChannelOffset,
                     bool useEffects);

    virtual ~PositionControl();


    // Public Interface ....................................................

    virtual Control* ControlClone() const;
    virtual ControlType ControlGetType() const;
    virtual void ControlGetUsedChannels (Array<int>& channels,
                                         bool getSubcontrols) const;

    // Update Functions
    virtual void ControlUpdateBuffer (const uint8* pCueBuffer,
                                      uint8* pOutputBuffer,
                                      int faderLevel,
                                      int GMAdjustedLevel);

#if 0
    virtual void PositionControl::ControlCalculateEffect(
													 EffectData* pEffectData,
                                        int faderLevel );

      virtual void ControlUpdateEffect( BYTE* pOutputBuffer,
                                        EffectData* pEffectData,
                                        int faderLevel );

      virtual void ControlAdvanceEffectPosition( UINT updateID );
#endif
    
    // member access
    void getValues( bool& resolution,
                          uint32& panCoarse,
                          uint32& panFine,
                          uint32& tiltCoarse,
                          uint32& tiltFine,
                          bool& useEffects ) const;

    // save/load
//    virtual bool ControlSerialize( IStream* pStream ) const;
    virtual bool ControlLoad( ShowFile& show, uint32 version );


private:

    // Private Functions ...................................................

    // Private Members .....................................................

    // we always have an effect object associated with an position control
    // but the effect is only active when the cue has an entry in its
    // effect data list.
//      Effect m_Effect;

    // the position control can be either 8 or 16 bit. If the control is set
    // to 8bit then we ignore the fine-channels and use only the coarse
    // channels.
    bool m_16BitResolution;

    // channel offset which represent the offset from the device base
    // address. If we use 8 bit resolution we ignore the fine channels.
    uint32 m_PanCoarseChannelOffset;
    uint32 m_PanFineChannelOffset;
    uint32 m_TiltCoarseChannelOffset;
    uint32 m_TiltFineChannelOffset;

    // flag indicating to use effect or not. We only draw (show) the
    // effect faders (speed, gain, rotation) and the effect select/switch
    // controls when the effects are used.

    // ! We currently don't expose the use effect flag to the user
    // (through the property dialog). The flag is always set to true for now

    bool m_UseEffects;
};


#endif // _POSITION_CONTROL_H_

