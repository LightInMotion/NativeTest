/*
   File Info:

      $Workfile:   FaderControl.cpp  $
      $Author:   JOE  $
      $Revision:   1.0  $
      $Modtime:   08 Mar 2005 13:56:56  $

   Module Description:

      The fader control is derived from the Control class. The fader control
      represents a fader which can represent either one DMX channel or two 
      DMX channel. It can also represent a partial DMX channel by setting
      the minimum and/or maximum value for the fader.
      The UIFaderControl is the visual representation of the FaderControl
      and gets all its values from the FaderControl when displayed.
*/

// Includes ..................................................................

#include "dmx.h"
#include "FaderControl.h"
#include "Fader.h"
//#include "FileHelper.h"


// Local Defines .............................................................

// Local Data Types ..........................................................

// Public Interface ..........................................................

/*----------------------------------------------------------------------------
   FaderControl::FaderControl

   Constructor

   Returns: no return value
----------------------------------------------------------------------------*/

FaderControl::FaderControl()
   :  Control(),
      m_2Channels(false),
      m_HighChannelOffset(0),
      m_LowChannelOffset(0),
      m_MinValue(0),
      m_MaxValue(0xFF),          // use 255 as default maximum value
      m_IsReverseFader(false),
      m_GMControlled(true)       // fader control is GM controlled by default
{
}


/*----------------------------------------------------------------------------
   FaderControl::FaderControl

   Constructor with additional parameters

   Returns: no return value
----------------------------------------------------------------------------*/
FaderControl::FaderControl( bool use2Channels,
                            uint32 highChannelOffset,
                            uint32 lowChannelOffset,
                            int minValue,
                            int maxValue,
                            bool reverse,
                            bool GMControlled )   
   :  Control(),
      m_2Channels(use2Channels),
      m_HighChannelOffset(highChannelOffset),
      m_LowChannelOffset(lowChannelOffset),
      m_MinValue(minValue),
      m_MaxValue(maxValue),
      m_IsReverseFader(reverse),
      m_GMControlled(GMControlled)
{
}


/*----------------------------------------------------------------------------
   FaderControl::~FaderControl

   Destructor

   Returns: no return value
----------------------------------------------------------------------------*/
FaderControl::~FaderControl()
{
}


/*----------------------------------------------------------------------------
   FaderControl::ControlClone

   Duplicate/Clone the control. This is a vitural function. It is called when 
   we create an device based on a given template. We clone all controls from
   the template and add them to the new inserted device.

   Returns: Control pointer, or NULL if fails
----------------------------------------------------------------------------*/

Control* 
FaderControl::ControlClone() const
{
   // create new fader control with existing fader data
    FaderControl* pNewControl = new FaderControl (m_2Channels,
                                                  m_HighChannelOffset,
                                                  m_LowChannelOffset,
                                                  m_MinValue,
                                                  m_MaxValue,
                                                  m_IsReverseFader,
                                                  m_GMControlled);
   if( ! pNewControl )
      return NULL;

   // duplicate all base class members
   ControlCloneAllData( pNewControl );

   // return new control pointer
   return pNewControl;
}


/*----------------------------------------------------------------------------
   FaderControl::ControlGetType

   Get the control type. This function is a virtual function, it is called
   from the cue editor to determine which UI control to create in order
   to visually represent the control.

   Returns: control type
----------------------------------------------------------------------------*/

ControlType 
FaderControl::ControlGetType() const
{
   // we are a fader control
   return CT_FADER;
}


/*----------------------------------------------------------------------------
   FaderControl::ControlGetUsedChannels

   This function gets called from the template and the device to determine
   how many channels are occupied by the entire Template/Device. Because
   the DMX channels can be non-continuous the template/device has to get
   all used channels and then calculate the exact occupied space.

   Returns: no return value
----------------------------------------------------------------------------*/

void 
FaderControl::ControlGetUsedChannels(
   Array<int>& channels,   // in/out: add number of used DMX
                                 // channels to the vector
   bool getSubcontrols ) const   // only used for mode control
{
   // add the low channel to the vector
   channels.add( m_LowChannelOffset + m_DeviceBaseAddress );

   // if we are using two channels then we also need to add the high channel
   // offset
   if( m_2Channels )
      channels.add( m_HighChannelOffset + m_DeviceBaseAddress );
}


/*----------------------------------------------------------------------------
   FaderControl::ControlUpdateBuffer

   This is where the real work is done. We calculate/sum the DMX values here.

   Returns: no return value
----------------------------------------------------------------------------*/

void 
FaderControl::ControlUpdateBuffer( 
   const uint8* pCueBuffer, // input cue buffer
   uint8* pOutputBuffer,    // in/out: output buffer to modify
   int faderLevel,         // fader level
   int GMAdjustedLevel )   // grand master adjusted fader level, used for 
                           // grand master controlled controls.
{
   int level;
   int outputValue = 0;
   int cueValue = 0;

   // if we are grand master controlled then we use the precalculated
   // (adjusted) grand master fader level. If not we use the full fader
   // level.
   if( m_GMControlled )
      level = GMAdjustedLevel;
   else
      level = faderLevel;

   // do we use two channels
   if( m_2Channels )
   {
      // get the high output value
      outputValue = 
         *(pOutputBuffer + m_DeviceBaseAddress + m_HighChannelOffset) << 8;

      // get the high cue value
      cueValue = 
         *(pCueBuffer + m_DeviceBaseAddress + m_HighChannelOffset) << 8;
   }

   // get the low output value
   outputValue += *(pOutputBuffer + m_DeviceBaseAddress + m_LowChannelOffset);

   // get the low cue value
   cueValue += *(pCueBuffer + m_DeviceBaseAddress + m_LowChannelOffset);

   // is it a reverse fader
   if( m_IsReverseFader )
   {
      // Get our state flag.  0 = first pass, 1 = work subtractively
      uint8 *pFlag = pOutputBuffer + m_DeviceBaseAddress
                  + m_LowChannelOffset + DMX_CHANNEL_BUFFER_COUNT;

      // Turn into a range
 		cueValue -= m_MinValue;

      // Clip
      if (cueValue < 0)
         cueValue = 0;

		//	Reverse faders work from max to min, instead of min to max
		// So, the first time we run we init with a value offset from max.
		// Once we have a value, the remaining faders work substractively,
		// that is, we subtract the scaled percentage of the fader range
		if (*pFlag)
			outputValue -= (cueValue * level) >> FADER_BIT_SHIFT;
		else
      {
			outputValue = m_MaxValue - (( cueValue * level ) >> FADER_BIT_SHIFT );
         *pFlag |= 1;   // Set the flag
      }
   }
   else
	{
		// If we aren't a reverse fader, we start by removing our min value,
		// which we will add back in after the scale
		cueValue -= m_MinValue;

		// substract the minimum from the output buffer, but make sure it is never
		// negative
		outputValue -= m_MinValue;
		if( outputValue < 0 )
			outputValue = 0;

      // sum the cue value to the existing output value
      outputValue += (( cueValue * level ) >> FADER_BIT_SHIFT ) + m_MinValue;
	}

   // cap the value at the maximum/minimum
   if( outputValue > m_MaxValue )
      outputValue = m_MaxValue;
   else if( outputValue < m_MinValue )
      outputValue = m_MinValue;

   if( m_2Channels )
   {
      // move the high byte back to the output buffer
      *(pOutputBuffer + m_DeviceBaseAddress + m_HighChannelOffset ) =
         (uint8)( outputValue >> 8 );
   }

   // move the low byte back to the output buffer
   *(pOutputBuffer + m_DeviceBaseAddress + m_LowChannelOffset ) =
      (uint8)outputValue;
}


/*----------------------------------------------------------------------------
   FaderControl::FadConGetValues

   Get all values from the fader control. This function is called from the 
   UIFaderControl to initialize its values.

   Returns: no return value
----------------------------------------------------------------------------*/

void 
FaderControl::FadConGetValues( bool& is2Channel, 
                               uint32& highChannelOffset,
                               uint32& lowChannelOffset,
                               int& minValue,
                               int& maxValue,
                               bool& reverse,
                               bool& GMControlled ) const
{
   // return all values
   is2Channel = m_2Channels;
   highChannelOffset = m_HighChannelOffset;
   lowChannelOffset = m_LowChannelOffset;
   minValue = m_MinValue;
   maxValue = m_MaxValue;
   reverse = m_IsReverseFader;
   GMControlled = m_GMControlled;
}


// save/load .................................................................
/*
   save and load the control specific data to the structure storage file
*/

/*----------------------------------------------------------------------------
   FaderControl::ControlSerialize

   Save the fader control specific data to the file
      
   Returns: true or false
----------------------------------------------------------------------------*/
#if 0
bool 
FaderControl::ControlSerialize( IStream* pStream ) const
{
   // save base control data first
   if( ! Control::ControlSerialize( pStream ))
      return false;

   // write is-2 channel flag
   if( ! FileHelpWriteBool( pStream, m_2Channels ))
      return false;

   // save high channel offset
   if( ! FileHelpWriteUINT( pStream, m_HighChannelOffset ))
      return false;

   // save low channel offset
   if( ! FileHelpWriteUINT( pStream, m_LowChannelOffset ))
      return false;

   // save maximum value
   if( ! FileHelpWriteInt( pStream, m_MaxValue ))
      return false;

   // save minimum value
   if( ! FileHelpWriteInt( pStream, m_MinValue ))
      return false;

   // save reverse value
   if( ! FileHelpWriteBool( pStream, m_IsReverseFader ))
      return false;

   // save grand master controlled flag
   if( ! FileHelpWriteBool( pStream, m_GMControlled ))
      return false;

   return true;
}

#endif

/*----------------------------------------------------------------------------
   FaderControl::ControlLoad

   load the control data from the stream
      
   Returns: true or false
----------------------------------------------------------------------------*/

bool 
FaderControl::ControlLoad( ShowFile& show,
                           uint32 version )
{
   // first load the base control data
   if (! Control::ControlLoad (show, version))
      return false;

   // read is-2 channel flag
   if (! show.readBool (m_2Channels))
      return false;

   // load high offset
   if (! show.readDword (m_HighChannelOffset))
      return false;

   // load low offset
   if (! show.readDword (m_LowChannelOffset))
      return false;

   // load max value
   if (! show.readInt (m_MaxValue))
      return false;

   // load min value
   if (! show.readInt (m_MinValue))
      return false;

   // load reverse value
   if (! show.readBool (m_IsReverseFader))
      return false;

   // load grand master controlled flag
   if (! show.readBool (m_GMControlled))
      return false;

   return true;
}


/*----------------------------------------------------------------------------
   FaderControl::ControlCorrectSnapshotValues

   Virtual function from Control. This function is used to correct cue buffer
   values after taking a snapshot. Currently only the reversed fader control
   needs to correct values.

   Returns: no return value
----------------------------------------------------------------------------*/

void 
FaderControl::ControlCorrectSnapshotValues(
   uint8* pCueBuffer ) const   // cue buffer for which we need to adjust the
                              // values
{
   // if we are a reversed fader then we need to replace the cue buffer value
   // with the reciprocal value. The cue buffer always contains the reciprocal
   // value to the output buffer.

   int cueValue = 0;

   if( m_IsReverseFader )
   {
      // get the cue value

      // do we use two channels
      if( m_2Channels )
      {
         // get the high cue value
         cueValue = 
            *(pCueBuffer + m_DeviceBaseAddress + m_HighChannelOffset) << 8;
      }

      // get the low cue value
      cueValue += *(pCueBuffer + m_DeviceBaseAddress + m_LowChannelOffset);

      // set the value to its reciprocal value
      cueValue = m_MaxValue - cueValue + m_MinValue;

      // write the value back

      if( m_2Channels )
      {
         // move the high byte back to the cue buffer
         *(pCueBuffer + m_DeviceBaseAddress + m_HighChannelOffset ) =
            (uint8)( cueValue >> 8 );
      }

      // move the low byte back to the cue buffer
      *(pCueBuffer + m_DeviceBaseAddress + m_LowChannelOffset ) =
         (uint8)cueValue;
   }
}







