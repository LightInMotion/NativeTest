/*
    Module Description:

    The select control is derived from the Control class. It is used for
    DMX channels with fixed values like a gobo wheel or a color wheel.
    A select control always represents exactly one DMX channel. Each value
    has a description and can be displayed with a UISelectControl which is
    the extented version of a Combobox.
*/

// Includes ..................................................................

#include "SelectControl.h"


// Local Defines .............................................................

// Local Data Types ..........................................................

// Public Interface ..........................................................

/*----------------------------------------------------------------------------
    SelectControl::SelectControl

    Constructor

    Returns: no return value
----------------------------------------------------------------------------*/

SelectControl::SelectControl()
    : m_ChannelOffset(0)
{
}


/*----------------------------------------------------------------------------
    SelectControl::SelectControl

    Constructor with parameters

    Returns: no return value
----------------------------------------------------------------------------*/

SelectControl::SelectControl (uint32 channelOffset,
                              const Array<SelectValue>& values )
    : m_ChannelOffset(channelOffset)
{
    // copy values
    m_Values = values;
}
  

/*----------------------------------------------------------------------------
    SelectControl::~SelectControl

    Destructor

    Returns: no return value
----------------------------------------------------------------------------*/
SelectControl::~SelectControl()
{
}


/*----------------------------------------------------------------------------
    SelectControl::ControlClone

    Duplicate the control. This is a virtual function.

    Returns: Control pointer, or NULL if fails
----------------------------------------------------------------------------*/

Control* 
SelectControl::ControlClone() const
{
    // create new select control
    SelectControl* pNewControl = new SelectControl;
    if( ! pNewControl )
        return nullptr;

    // duplicate all base class members
    ControlCloneAllData (pNewControl);

    // copy all select control specific data
    pNewControl->m_ChannelOffset = m_ChannelOffset;

    // copy all SelectValues
    pNewControl->m_Values = m_Values;

    return pNewControl;
}


/*----------------------------------------------------------------------------
    SelectControl::ControlGetType

    Get the control type. This function is a virtual function, it is called
    from the cue editor to determine which UI control to create in order
    to visually represent the control.

    Returns: control type
----------------------------------------------------------------------------*/

ControlType 
SelectControl::ControlGetType() const
{
    // we are a select control
    return CT_SELECT;
}


/*----------------------------------------------------------------------------
    SelectControl::ControlGetUsedChannels

    This function gets called from the template and the device to determine
    how many channels are occupied by the entire Template/Device. Because
    the DMX channels can be non-continuous the template/device has to get
    all used channels and then calculate the exact occupied space.

    Returns: no return value
----------------------------------------------------------------------------*/

void
SelectControl::ControlGetUsedChannels(
   Array<int>& channels,        // in/out: add number of used DMX
                                // channels to the vector
   bool getSubcontrols) const   // only used for mode control
{
    // add the used channel
    channels.add (m_ChannelOffset + m_DeviceBaseAddress);
}


/*----------------------------------------------------------------------------
    SelectControl::ControlUpdateBuffer

    This is where the real work is done. We calculate/sum the DMX values here.

    Returns: no return value
----------------------------------------------------------------------------*/

void 
SelectControl::ControlUpdateBuffer( 
   const uint8* pCueBuffer, // input cue buffer
   uint8* pOutputBuffer,    // in/out: output buffer to modify
   int faderLevel,          // fader level
   int GMAdjustedLevel)     // grand master adjusted fader level, used for
                            // grand master controlled controls.
{
    // fading between select controls works the following way:
    // The Console sorts all faders according to their fader levels from high
    // to low.
    // The select control with the highest fader level takes precedence.
    // With those assumptions the actual updating of the buffer is very simple,
    // we only have to check if the current output buffer value is zero and if
    // not we just take our current (cue buffer) value and put it in the
    // output buffer. The next fader sees that the value
    // is non-zero and does nothing, leaving us at the end with the value from
    // the fader with the hightest fader value.
    // This logic only works if the cue buffer value is non-zero. We have to
    // enforce this in the template editor. The values are always a range, so
    // having a non-zero value should be possible.
   
    if (*(pOutputBuffer + m_DeviceBaseAddress + m_ChannelOffset) == 0)
    {
        // set the output buffer to our cue buffer value
        *(pOutputBuffer + m_DeviceBaseAddress + m_ChannelOffset) =
            *(pCueBuffer + m_DeviceBaseAddress + m_ChannelOffset);
    }
}


// save/load .................................................................
/*
    save and load the control specific data to the structure storage file
*/

#if 0
/*----------------------------------------------------------------------------
   SelectControl::ControlSerialize

   Save the select control specific data to the file
      
   Returns: true or false
----------------------------------------------------------------------------*/

bool 
SelectControl::ControlSerialize( IStream* pStream ) const
{
   // save base control data first
   if( ! Control::ControlSerialize( pStream ))
      return false;

   // save channel offset
   if( ! FileHelpWriteUINT( pStream, m_ChannelOffset ))
      return false;

   int valueCount = m_Values.size();

   // save value count
   if( ! FileHelpWriteInt( pStream, valueCount ))
      return false;

   // for all select values
   for( int valueIndex = 0; valueIndex < valueCount; valueIndex++ )
   {
      // save the value
      if( ! FileHelpWriteBYTE( pStream, m_Values[valueIndex].m_Value ))
         return false;

      // save value description
      if( ! FileHelpWriteString(pStream, m_Values[valueIndex].m_Description))
         return false;
   }

   return true;
}

#endif

/*----------------------------------------------------------------------------
    SelectControl::ControlLoad

    load the control data from the stream
      
    Returns: true or false
----------------------------------------------------------------------------*/

bool 
SelectControl::ControlLoad (ShowFile& show,
                            uint32 version)
{
    // first load the base control data
    if (! Control::ControlLoad (show, version))
        return false;

    // load channel offset
    if (! show.readDword (m_ChannelOffset))
        return false;

    // load value count
    int valueCount = 0;
    if (! show.readInt (valueCount))
        return false;

    // for all values
    for (int valueIndex = 0; valueIndex < valueCount; valueIndex++)
    {
        SelectValue value;

        // load value
        uint32 bytesRead = 0;
        if (! show.readBytes (&(value.m_Value), sizeof (uint8), bytesRead ))
            return false;

        if (bytesRead != sizeof(uint8))
            return false;

        // load value description
        if (! show.readString (value.m_Description))
            return false;

        // add select value to vector
        m_Values.add (value);
    }

    return true;
}


// get/set values ............................................................
/*
    The control values must only be changed from the template editor. Once a
    control belongs to a device (and not a template) the values are fixed and
    can't be changed anymore. The set values function is therefor only called
    from the template editor.

    The get values function is used from the UISelectControl to get all the
    values for display purpose.
*/

/*----------------------------------------------------------------------------
    SelectControl::getValues

    Get all values from the select control. This function is called from the
    UISelectControl to initialize its values.

    Returns: no return value
----------------------------------------------------------------------------*/

void 
SelectControl::getValues( 
   uint32& channelOffset,              // returned channel offset
   Array<SelectValue>& values ) const  // returned values
{
    // copy member variables to the return values
    channelOffset = m_ChannelOffset;
    values = m_Values;
}


/*----------------------------------------------------------------------------
    SelectControl::setValues

    Set the control values, called only from the template editor

    Returns: no return value
----------------------------------------------------------------------------*/

void 
SelectControl::setValues( 
   uint32 channelOffset,                // new channel offset
   const Array<SelectValue>& values )   // new values
{
    // set channel offset
    m_ChannelOffset = channelOffset;

    // copy the new values to the vector
    m_Values = values;
}




