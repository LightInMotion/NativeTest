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

    UIPositionControl is the visual representation of PositionControl.
*/

// Includes ..................................................................

#include "PositionControl.h"
#include "Fader.h"

// Local Defines .............................................................

// Local Data Types ..........................................................

// Public Interface ..........................................................

/*----------------------------------------------------------------------------
    PositionControl::PositionControl

    Constructor
 
    Returns: no return value
----------------------------------------------------------------------------*/

PositionControl::PositionControl()
    : Control(),
      m_16BitResolution (false),
      m_PanCoarseChannelOffset (0),
      m_PanFineChannelOffset (0),
      m_TiltCoarseChannelOffset (0),
      m_TiltFineChannelOffset(0),
      m_UseEffects (true)           // for now always use effects
{
}


/*----------------------------------------------------------------------------
    PositionControl::PositionControl

    Constructor with some additional parameters

    Returns: no return value
----------------------------------------------------------------------------*/

PositionControl::PositionControl (bool is16BitResolution,
                                  uint32 panCoarseChannelOffset,
                                  uint32 panFineChannelOffset,
                                  uint32 tiltCoarseChannelOffset,
                                  uint32 tiltFineChannelOffset,
                                  bool useEffects )
    : Control(),
      m_16BitResolution (is16BitResolution),
      m_PanCoarseChannelOffset (panCoarseChannelOffset),
      m_PanFineChannelOffset (panFineChannelOffset),
      m_TiltCoarseChannelOffset (tiltCoarseChannelOffset),
      m_TiltFineChannelOffset (tiltFineChannelOffset),
      m_UseEffects (useEffects)
{
}


/*----------------------------------------------------------------------------
    PositionControl::~PositionControl

    Destructor

    Returns: no return value
----------------------------------------------------------------------------*/

PositionControl::~PositionControl()
{
}


/*----------------------------------------------------------------------------
    PositionControl::ControlClone

    Duplicate the control. This is a vitural function.

    Returns: Control pointer, or NULL if fails
----------------------------------------------------------------------------*/

Control* 
PositionControl::ControlClone() const
{
    // create a new position control
    PositionControl* pNewControl = new PositionControl;
    if( ! pNewControl )
        return NULL;

    // duplicate all base class members
    ControlCloneAllData (pNewControl);

    // copy all position control specific data
    pNewControl->m_16BitResolution = m_16BitResolution;
    pNewControl->m_PanCoarseChannelOffset = m_PanCoarseChannelOffset;
    pNewControl->m_PanFineChannelOffset = m_PanFineChannelOffset;
    pNewControl->m_TiltCoarseChannelOffset = m_TiltCoarseChannelOffset;
    pNewControl->m_TiltFineChannelOffset = m_TiltFineChannelOffset;
    pNewControl->m_UseEffects = m_UseEffects;

    // I don't think we actually need to copy any effect data here because
    // the template editor doesn't change any effect data. Only once the
    // control gets used in the cue editor does the effect object data change.
    pNewControl->m_Effect = m_Effect;

    return pNewControl;
}


/*----------------------------------------------------------------------------
    PositionControl::ControlGetType

    Get the control type. This function is a virtual function, it is called
    from the cue editor to determine which UI control to create in order
    to visually represent the control.

    Returns: control type
----------------------------------------------------------------------------*/

ControlType 
PositionControl::ControlGetType() const
{
    // we are a position control
    return CT_POSITION;
}


/*----------------------------------------------------------------------------
    PositionControl::ControlGetUsedChannels

    This function gets called from the template and the device to determine
    how many channels are occupied by the entire Template/Device. Because
    the DMX channels can be non-continuous the template/device has to get
    all used channels and then calculate the exact occupied space.

    Returns: no return value
----------------------------------------------------------------------------*/

void
PositionControl::ControlGetUsedChannels(
   Array<int>& channels,        // in/out: add number of used DMX
                                // channels to the vector
   bool getSubcontrols) const   // only used for mode control
{
    // add the coarse channel offsets, those are always valid
    channels.add (m_PanCoarseChannelOffset + m_DeviceBaseAddress);
    channels.add (m_TiltCoarseChannelOffset + m_DeviceBaseAddress);

    // if we are in 16bit resolution (using 4 channels) then we also have to
    // add the fine channel offsets
    if( m_16BitResolution )
    {
        channels.add (m_PanFineChannelOffset + m_DeviceBaseAddress);
        channels.add (m_TiltFineChannelOffset + m_DeviceBaseAddress);
    }
}


// Update Functions ..........................................................

/*
    This is where the real work is done. The update functions are called every
    33ms (30Hz) to update the DMX values. If any effects are active at the
    control then the effect update functions are called too.
*/

/*----------------------------------------------------------------------------
    PositionControl::ControlUpdateBuffer

    This is where the real work is done. We calculate/sum the DMX values here.

    Returns: no return value
----------------------------------------------------------------------------*/

void 
PositionControl::ControlUpdateBuffer( 
   const uint8* pCueBuffer, // input cue buffer
   uint8* pOutputBuffer,    // in/out: output buffer to modify
   int faderLevel,          // fader level
   int GMAdjustedLevel )    // grand master adjusted fader level, used for
                            // grand master controlled controls.
{
    // get the coarse position for the output and cue buffer

    int xPosOutput =
        *(pOutputBuffer + m_DeviceBaseAddress + m_PanCoarseChannelOffset ) << 8;

    int yPosOutput =
        *(pOutputBuffer + m_DeviceBaseAddress + m_TiltCoarseChannelOffset ) <<8;

    int xPosCue =
        *(pCueBuffer + m_DeviceBaseAddress + m_PanCoarseChannelOffset ) << 8;

    int yPosCue =
        *(pCueBuffer + m_DeviceBaseAddress + m_TiltCoarseChannelOffset ) << 8;

    // do we have 16bit resolution. If not we ignore the fine channels
    if (m_16BitResolution)
    {
        // add the fine values

        xPosOutput +=
            *(pOutputBuffer + m_DeviceBaseAddress + m_PanFineChannelOffset );

        yPosOutput +=
            *(pOutputBuffer + m_DeviceBaseAddress + m_TiltFineChannelOffset );

        xPosCue +=
            *(pCueBuffer + m_DeviceBaseAddress + m_PanFineChannelOffset );

        yPosCue +=
            *(pCueBuffer + m_DeviceBaseAddress + m_TiltFineChannelOffset );
    }

    // sum the cue value to the existing output value

    xPosOutput += (xPosCue * faderLevel) >> FADER_BIT_SHIFT;
    yPosOutput += (yPosCue * faderLevel) >> FADER_BIT_SHIFT;

    // If we aren't 16 bit, round
    if (! m_16BitResolution)
    {
        xPosOutput += 128;
        yPosOutput += 128;
    }

    // cap the output at the maximum
    if( xPosOutput > 0xFFFF )
        xPosOutput = 0xFFFF;

    if( yPosOutput > 0xFFFF )
        yPosOutput = 0xFFFF;

    // move the coarse values back to the output buffer
    *(pOutputBuffer + m_DeviceBaseAddress + m_PanCoarseChannelOffset) =
        (uint8)( xPosOutput >> 8 );

    *(pOutputBuffer + m_DeviceBaseAddress + m_TiltCoarseChannelOffset) =
        (uint8)( yPosOutput >> 8 );

    // do we use 16bit
    if( m_16BitResolution )
    {
        // move the fine values back to the output buffer

        *(pOutputBuffer + m_DeviceBaseAddress + m_PanFineChannelOffset) =
            (uint8)xPosOutput;

        *(pOutputBuffer + m_DeviceBaseAddress + m_TiltFineChannelOffset) =
            (uint8)yPosOutput;
    }
}

/*----------------------------------------------------------------------------
    PositionControl::ControlUpdateEffect

    This call gives the effects a chance to properly combine virtual settings,
	like speed and rotation, before actually using them to alter data in
	effect update

    Returns: no return value
----------------------------------------------------------------------------*/

void 
PositionControl::ControlCalculateEffect( EffectData* pEffectData,
                                         int faderLevel )
{
    // call the update function on the effect
    m_Effect.EffectCalculate (pEffectData, faderLevel);
}

/*----------------------------------------------------------------------------
    PositionControl::ControlUpdateEffect

    We check if the position control is set to 2 or 4 channels (one or two
    channels per axis) and call the EffectUpdate() function. All the effect
    calculation is done in the effect class.

    Returns: no return value
----------------------------------------------------------------------------*/

void 
PositionControl::ControlUpdateEffect (uint8* pOutputBuffer,
                                      EffectData* pEffectData,
                                      int faderLevel )
{
    // get the coarse position for the output buffer

    int16 xPosOutput =
        *(pOutputBuffer + m_DeviceBaseAddress + m_PanCoarseChannelOffset ) << 8;

    int16 yPosOutput =
        *(pOutputBuffer + m_DeviceBaseAddress + m_TiltCoarseChannelOffset ) <<8;

    // do we have 16bit resolution. If not we ignore the fine channels
    if( m_16BitResolution )
    {
        // add the fine values

        xPosOutput +=
            *(pOutputBuffer + m_DeviceBaseAddress + m_PanFineChannelOffset );

        yPosOutput +=
            *(pOutputBuffer + m_DeviceBaseAddress + m_TiltFineChannelOffset );
    }

    // call the update function on the effect
    m_Effect.EffectUpdate (xPosOutput, yPosOutput, pEffectData, faderLevel);

    *(pOutputBuffer + m_DeviceBaseAddress + m_PanCoarseChannelOffset ) =
        (uint8)( xPosOutput >> 8 );

    *(pOutputBuffer + m_DeviceBaseAddress + m_TiltCoarseChannelOffset ) =
        (uint8)( yPosOutput >> 8 );

    // do we use 16bit
    if( m_16BitResolution )
    {
        // move the fine values back to the output buffer

        *(pOutputBuffer + m_DeviceBaseAddress + m_PanFineChannelOffset ) =
            (uint8)( xPosOutput );

        *(pOutputBuffer + m_DeviceBaseAddress + m_TiltFineChannelOffset ) =
            (uint8)( yPosOutput );
   }
}


/*----------------------------------------------------------------------------
    PositionControl::ControlAdvanceEffectPosition

    Advance the effect position. Call EffectAdvancePosition().

    Returns: no return value
----------------------------------------------------------------------------*/

void 
PositionControl::ControlAdvanceEffectPosition (uint32 updateID)
{
   // call the advance position in the effect object
   m_Effect.EffectAdvancePosition( updateID );
}


// member access..............................................................
/*
    Member access functions called from the UIPositionControl.
*/

/*----------------------------------------------------------------------------
    PositionControl::getValues

    Get the pan/tilt values. Called from the UIPositionControl

    Returns: no return value
----------------------------------------------------------------------------*/

void 
PositionControl::getValues (bool& resolution,
                                  uint32& panCoarse,
                                  uint32& panFine,
                                  uint32& tiltCoarse,
                                  uint32& tiltFine,
                                  bool& useEffects ) const
{
    // copy all values
    resolution = m_16BitResolution;
    panCoarse = m_PanCoarseChannelOffset;
    panFine = m_PanFineChannelOffset;
    tiltCoarse = m_TiltCoarseChannelOffset;
    tiltFine = m_TiltFineChannelOffset;
    useEffects = m_UseEffects;
}


// save/load .................................................................
/*
    save and load the control specific data to the structure storage file.
    These functions are virtual function from Control and have to call
    the base class implementation first.
*/

#if 0
/*----------------------------------------------------------------------------
    PositionControl::ControlSerialize

    Save the position control specific data to the file
      
    Returns: true or false
----------------------------------------------------------------------------*/

bool 
PositionControl::ControlSerialize( IStream* pStream ) const
{
   // save base control data first
   if( ! Control::ControlSerialize( pStream ))
      return false;

   // write is-16 bit resolution flag
   if( ! FileHelpWriteBool( pStream, m_16BitResolution ))
      return false;

   // save pan coarse
   if( ! FileHelpWriteUINT( pStream, m_PanCoarseChannelOffset ))
      return false;

   // save pan fine
   if( ! FileHelpWriteUINT( pStream, m_PanFineChannelOffset ))
      return false;

   // save tilt coarse
   if( ! FileHelpWriteUINT( pStream, m_TiltCoarseChannelOffset ))
      return false;

   // save tilt fine
   if( ! FileHelpWriteUINT( pStream, m_TiltFineChannelOffset ))
      return false;

   // save use effect flag. We currently don't allow the user to change this
   // flag but we save it anyhow for consistancy
   if( ! FileHelpWriteBool( pStream, m_UseEffects ))
      return false;

   return true;
}

#endif

/*----------------------------------------------------------------------------
    PositionControl::ControlLoad
  
    Load all control data from the given stream

    Returns: true or false
----------------------------------------------------------------------------*/

bool 
PositionControl::ControlLoad (ShowFile& show,
                              uint32 version )
{
    // first load the base control data
    if (! Control::ControlLoad (show, version))
        return false;

    // load is-16 bit flag
    if (! show.readBool (m_16BitResolution))
        return false;

    // load pan coarse value
    if (! show.readDword (m_PanCoarseChannelOffset))
      return false;

    // load pan fine value
    if (! show.readDword (m_PanFineChannelOffset))
        return false;

    // load tilt coarse value
    if (! show.readDword (m_TiltCoarseChannelOffset))
        return false;

    // load tilt fine value
    if (! show.readDword (m_TiltFineChannelOffset))
        return false;

    // load use effect flag
    if (! show.readBool (m_UseEffects))
        return false;

    return true;
}







