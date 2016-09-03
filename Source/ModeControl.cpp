/*
    Module Description:

    The mode control is derived from the Control class. It is similar
    to a property page, as it has multiple 'pages'. Each page can contain
    multiple sub-controls which get only updated when the mode control
    switches to the particular page.
*/

// Includes ..................................................................

#include "ModeControl.h"
#include "SelectControl.h"
#include "FaderControl.h"
#include "PositionControl.h"


// Local Defines .............................................................

// Local Data Types ..........................................................

// Public Interface ..........................................................

/*----------------------------------------------------------------------------
    ModeControl::ModeControl

    Constructor

    Returns: no return value
----------------------------------------------------------------------------*/

ModeControl::ModeControl()
    : m_HasModeChannel (false),
      m_ChannelOffset (0)
{
}


/*----------------------------------------------------------------------------
    ModeControl::ModeControl

    Constructor with parameters

    Returns: no return value
----------------------------------------------------------------------------*/

ModeControl::ModeControl (bool hasModeChannel,
                          uint32 channelOffset)
    : m_HasModeChannel (hasModeChannel),
      m_ChannelOffset (channelOffset)
{
}


/*----------------------------------------------------------------------------
    ModeControl::~ModeControl

    Destructor

    Returns: no return value
----------------------------------------------------------------------------*/
ModeControl::~ModeControl()
{
    // Since the pages and controls are in owned arrays they should
    // self delete
}


/*----------------------------------------------------------------------------
    ModeControl::ControlClone

    Duplicate the control. This is a virtual function.

    Returns: Control pointer, or NULL if fails
----------------------------------------------------------------------------*/

Control* 
ModeControl::ControlClone() const
{
    // create new mode control
    ScopedPointer<ModeControl> pNewControl = new ModeControl;
    if( ! pNewControl )
        return nullptr;

    // duplicate all base class members
    ControlCloneAllData( pNewControl );

    // duplicate channel offset and mode channel flag
    pNewControl->m_ChannelOffset = m_ChannelOffset;
    pNewControl->m_HasModeChannel = m_HasModeChannel;

    // now we have to create copies of the mode pages and clone all controls
    // contained in the pages

    // for all pages
    int pageCount = m_Pages.size();
    for (int pageIndex = 0; pageIndex < pageCount; pageIndex++ )
    {
        // create new mode page
        ScopedPointer<ModePage> pNewModePage = new ModePage;
        if( ! pNewModePage )
            return nullptr;

        // get old mode page pointer
        ModePage* pOldModePage = m_Pages[pageIndex];

        // copy all mode page data, except the control vector
        pNewModePage->m_Value = pOldModePage->m_Value;
        pNewModePage->m_RangeLow = pOldModePage->m_RangeLow;
        pNewModePage->m_RangeHigh = pOldModePage->m_RangeHigh;
        pNewModePage->m_Description = pOldModePage->m_Description;

        // for all control in the page
        int subControlCount = pOldModePage->m_Controls.size();
        for (int controlIndex = 0; controlIndex < subControlCount; controlIndex++)
        {
            // clone the control
            Control* pNewControl =
                pOldModePage->m_Controls[controlIndex]->ControlClone();

            if (! pNewControl)
                return nullptr;

            // add the new control to the control vector of the new mode page
            pNewModePage->m_Controls.add (pNewControl);
        }

        // add the page to the new control
        pNewControl->m_Pages.add (pNewModePage.get());
        pNewModePage.release();
   }

    ModeControl* p = pNewControl.get();
    pNewControl.release();
    return p;
}


/*----------------------------------------------------------------------------
    ModeControl::ControlGetType

    Get the control type. This function is a virtual function, it is called
    from the cue editor to determine which UI control to create in order
    to visually represent the control.

    Returns: control type
----------------------------------------------------------------------------*/

ControlType 
ModeControl::ControlGetType() const
{
    // we are a mode control
    return CT_MODE;
}


/*----------------------------------------------------------------------------
    ModeControl::ControlGetUsedChannels

    This function gets called from the template and the device to determine
    how many channels are occupied by the entire Template/Device. Because
    the DMX channels can be non-continuous the template/device has to get
    all used channels and then calculate the exact occupied space.

    Returns: no return value
----------------------------------------------------------------------------*/

void
ModeControl::ControlGetUsedChannels(
    Array<int>& channels,        // in/out: add number of used DMX
                                // channels to the vector
    bool getSubcontrols) const
{
    // if we have a mode channel then we add the mode channel to the vector
    if( m_HasModeChannel )
        channels.add (m_ChannelOffset + m_DeviceBaseAddress);

    // if we don't need to return the sub control channels then we can return
    if( ! getSubcontrols )
        return;

    // for all pages
    int pageCount = m_Pages.size();
    for (int pageIndex = 0; pageIndex < pageCount; pageIndex++)
    {
        // get mode page
        ModePage* pPage = m_Pages[pageIndex];

        // for all controls in that page
        int controlCount = pPage->m_Controls.size();
        for (int controlIndex = 0; controlIndex < controlCount; controlIndex++)
        {
            // get the channels from the control
            pPage->m_Controls[controlIndex]->
                ControlGetUsedChannels (channels, getSubcontrols);
        }
    }
}


/*----------------------------------------------------------------------------
    ModeControl::ControlSetAddress

    This is a virtual function. Set the device base address to all nested
    subcontrols.

    Returns: no return value
----------------------------------------------------------------------------*/

void 
ModeControl::ControlSetAddress (uint32 baseAddress)
{
    // call base class implementation
    Control::ControlSetAddress( baseAddress );

    // for all pages
    int pageCount = m_Pages.size();
    for (int pageIndex = 0; pageIndex < pageCount; pageIndex++)
    {
        // get page
        ModePage* pModePage = m_Pages[pageIndex];

        // for all controls of that page
        int controlCount = pModePage->m_Controls.size();
        for (int controlIndex = 0; controlIndex < controlCount; controlIndex++)
            // set the base address of the control
            pModePage->m_Controls[controlIndex]->ControlSetAddress (baseAddress);
    }
}


/*----------------------------------------------------------------------------
    ModeControl::ControlUpdateBuffer

    This is where the real work is done. We calculate/sum the DMX values here.

    Returns: no return value
----------------------------------------------------------------------------*/

void 
ModeControl::ControlUpdateBuffer( 
   const uint8* pCueBuffer, // input cue buffer
   uint8* pOutputBuffer,    // in/out: output buffer to modify
   int faderLevel,          // fader level
   int GMAdjustedLevel )    // grand master adjusted fader level, used for
                            // grand master controlled controls.
{
    // ! Important: The functionality of this function has some similarity
    // to the functionality in ControlCorrectSnapshotValues(). If you change
    // the implementation here, then you should change the functionality
    // in ControlCorrectSnapshotValues(), too.

    // do we have a mode-channel
    if( m_HasModeChannel )
    {
        // the functionality here is similar to the update function in the
        // select control. We check if the current output buffer value is
        // zero, and if so use our current value (from the cue buffer) and
        // call all sub-controls to let them update.
        // If the current output buffer value is non-zero then we do nothing

        // is the current value zero
        if (*(pOutputBuffer + m_DeviceBaseAddress + m_ChannelOffset) == 0)
        {
            // set the output buffer to our cue buffer value
            *(pOutputBuffer + m_DeviceBaseAddress + m_ChannelOffset) =
                *(pCueBuffer + m_DeviceBaseAddress + m_ChannelOffset);

            // make copy of cue buffer value
            uint8 cueValue =
                *(pCueBuffer + m_DeviceBaseAddress + m_ChannelOffset);

            // we have to find the appropriate page in order to call all
            // sub-controls
            int pageCount = m_Pages.size();
            for (int pageIndex = 0; pageIndex < pageCount; pageIndex++)
            {
                // does the cue buffer value match with the page value
                if( m_Pages[pageIndex]->m_Value == cueValue )
                {
                    // for all controls
					int controlCount = m_Pages[pageIndex]->m_Controls.size();

                    for (int controlIndex = 0;
                         controlIndex < controlCount;
                         controlIndex++ )
                    {
                        // update the control
                        m_Pages[pageIndex]->m_Controls[controlIndex]->
                        ControlUpdateBuffer (pCueBuffer,
                                             pOutputBuffer,
                                             faderLevel,
                                             GMAdjustedLevel);
                    }

                    // exit the for loop
                    break;
                }
            }
        }
    }
    // we don't have a mode channel
    else
    {
        // if we don't have a mode channel then we do the following:
        // If the current output value is zero then we call the update function
        // on our sub-controls. If the value is non-zero then we check if our
        // cue buffer value is in the same range as the output buffer value. If
        // it is than we are on the same page as the control before and we also
        // update all our sub-controls.

        // is the output buffer zero
        uint8 outputValue = *(pOutputBuffer+m_DeviceBaseAddress+m_ChannelOffset);
        if (outputValue == 0)
        {
            // make copy of cue buffer value
            uint8 cueValue =
                *(pCueBuffer + m_DeviceBaseAddress + m_ChannelOffset);

            // we have to find the appropriate page in order to call all
            // sub-controls
            int pageCount = m_Pages.size();
            for( int pageIndex = 0; pageIndex < pageCount; pageIndex++ )
            {
                ModePage* pModePage = m_Pages[pageIndex];

                // is the cue value from this page
                if ((pModePage->m_RangeHigh >= cueValue) &&
                    (pModePage->m_RangeLow <= cueValue))
                {
                    // for all control
                    int controlCount = pModePage->m_Controls.size();
                    for (int controlIndex = 0;
                         controlIndex < controlCount;
                         controlIndex++)
                    {
                        // update the control
                        pModePage->m_Controls[controlIndex]->
                        ControlUpdateBuffer (pCueBuffer,
                                             pOutputBuffer,
                                             faderLevel,
                                             GMAdjustedLevel);
                    }

                    // exit the for loop
                    break;
                }
            }
        }
        // the output value is non-zero
        else
        {
            // get the current output value
            uint8 outputValue =
                *(pOutputBuffer + m_DeviceBaseAddress + m_ChannelOffset);

            // get the current cue buffer value
            uint8 cueValue =
                *(pCueBuffer + m_DeviceBaseAddress + m_ChannelOffset);

            // for all pages
            int pageCount = m_Pages.size();
            for (int pageIndex = 0; pageIndex < pageCount; pageIndex++)
            {
                ModePage* pModePage = m_Pages[pageIndex];

                // is the cue buffer value in that page
                if ((pModePage->m_RangeHigh >= cueValue) &&
                    (pModePage->m_RangeLow <= cueValue))
                {
                    // only update if the current output buffer value is in the
                    // same range as the selected page value
                    if((pModePage->m_RangeHigh >= outputValue) &&
                       (pModePage->m_RangeLow <= outputValue))
                    {
                        // for all control
                        int controlCount = pModePage->m_Controls.size();
                        for (int controlIndex = 0;
                             controlIndex < controlCount;
                             controlIndex++)
                        {
                            // update the control
                            pModePage->m_Controls[controlIndex]->
                                ControlUpdateBuffer (pCueBuffer,
                                                     pOutputBuffer,
                                                     faderLevel,
                                                     GMAdjustedLevel);
                        }
                    }

                    // exit the for loop
                    break;
                }
            }
        }
    }
}


// save/load .................................................................
/*
    save and load the control specific data to the structure storage file
*/

#if 0
/*----------------------------------------------------------------------------
   ModeControl::ControlSerialize

   Save the mode control specific data to the file
      
   Returns: true or false
----------------------------------------------------------------------------*/

bool 
ModeControl::ControlSerialize( IStream* pStream ) const
{
   // save base control data first
   if( ! Control::ControlSerialize( pStream ))
      return false;

   // save channel offset
   if( ! FileHelpWriteInt( pStream, m_ChannelOffset ))
      return false;

   // save has mode channel flag
   if( ! FileHelpWriteBool( pStream, m_HasModeChannel ))
      return false;

   // save number of pages
   int pageCount = m_Pages.size();
   if( ! FileHelpWriteInt( pStream, pageCount ))
      return false;

   // for all pages
   for( int pageIndex = 0; pageIndex < pageCount; pageIndex++ )
   {
      // get page pointer
      ModePage* pPage = m_Pages[pageIndex];

      // save page value
      if( ! FileHelpWriteBYTE( pStream, pPage->m_Value ))
         return false;

      // save page range low
      if( ! FileHelpWriteBYTE( pStream, pPage->m_RangeLow ))
         return false;

      // save page range high
      if( ! FileHelpWriteBYTE( pStream, pPage->m_RangeHigh ))
         return false;

      // save page label
      if( ! FileHelpWriteString( pStream, pPage->m_Description ))
         return false;

      // save number of controls in page
      int controlCount = pPage->m_Controls.size();
      if( ! FileHelpWriteInt( pStream, controlCount ))
         return false;

      // for all controls int the page
      for( int controlIndex = 0; controlIndex < controlCount; controlIndex++ )
      {
         // ! Important we have to first save the control type, so that we
         // can instantiate the correct control when we load the file

         // save control type as a DWORD
         DWORD controlType =pPage->m_Controls[controlIndex]->ControlGetType();
         if(  ! FileHelpWriteDWORD( pStream, controlType ))
            return false;

         // serialize the control
         pPage->m_Controls[controlIndex]->ControlSerialize( pStream );
      }
   }

   return true;
}
#endif

/*----------------------------------------------------------------------------
    ModeControl::ControlLoad

    load the control data from the stream. The mode control has to load all
    sub controls from all pages it contains.
      
    Returns: true or false
----------------------------------------------------------------------------*/

bool 
ModeControl::ControlLoad (ShowFile& show,
                          uint32 version )    // file version
{
    // first load the base control data
    if (! Control::ControlLoad (show, version))
        return false;

    // load channel offset
    if (! show.readDword (m_ChannelOffset))
        return false;

    // load has mode channel flag
    if (! show.readBool (m_HasModeChannel))
        return false;

    // load page count
    int pageCount = 0;
    if (! show.readInt (pageCount))
        return false;

    // for all pages
    for (int pageIndex = 0; pageIndex < pageCount; pageIndex++)
    {
        // create new page
        ScopedPointer<ModePage> pNewPage = new ModePage;
        if (! pNewPage)
            return false;

        // load page value
        if (! show.readByte (pNewPage->m_Value))
            return false;

        // load low range value
        if (! show.readByte (pNewPage->m_RangeLow))
            return false;

        // load high range value
        if (! show.readByte (pNewPage->m_RangeHigh))
            return false;

        // load label description for page
        if (! show.readString (pNewPage->m_Description))
            return false;

        // load all sub controls for that page
        if (! LoadPageControls (show, version, pNewPage))
            return false;

        // add page to vector
        m_Pages.add (pNewPage);
        pNewPage.release();
    }

    return true;
}


/*----------------------------------------------------------------------------
    ModeControl::ControlCorrectSnapshotValues

    Virtual function from Control. This function is used to correct cue buffer
    values after taking a snapshot. Currently only the reversed fader control
    needs to correct values.

    Returns: no return value
----------------------------------------------------------------------------*/

void 
ModeControl::ControlCorrectSnapshotValues( 
   uint8* pCueBuffer) const   // cue buffer for which we need to adjust the
                              // values
{
    // ! The functionality is very similar to the functionality of
    // ControlUpdateBuffer() !

    // get cue buffer value
    uint8 cueValue = *(pCueBuffer + m_DeviceBaseAddress + m_ChannelOffset);

    // do we have a mode-channel
    if (m_HasModeChannel)
    {
        // we have to find the appropriate page in order to call all
        // sub-controls
        int pageCount = m_Pages.size();
        for (int pageIndex = 0; pageIndex < pageCount; pageIndex++)
        {
            // does the cue buffer value match with the page value
            if (m_Pages[pageIndex]->m_Value == cueValue)
            {
                // for all controls
				int controlCount = m_Pages[pageIndex]->m_Controls.size();

                for (int controlIndex = 0;
                     controlIndex < controlCount;
                     controlIndex++)
                {
                    // correct the snapshot values for the subcontrols
                    m_Pages[pageIndex]->m_Controls[controlIndex]->
                        ControlCorrectSnapshotValues (pCueBuffer);
                }

                // exit the for loop
                break;
            }
        }
    }
    // we don't have a mode channel
    else
    {
        // we have to find the appropriate page in order to call all
        // sub-controls
        int pageCount = m_Pages.size();
        for (int pageIndex = 0; pageIndex < pageCount; pageIndex++)
        {
            ModePage* pModePage = m_Pages[pageIndex];

            // is the cue value from this page
            if ((pModePage->m_RangeHigh >= cueValue) &&
                (pModePage->m_RangeLow <= cueValue ))
            {
                // for all control
                int controlCount = pModePage->m_Controls.size();
                for (int controlIndex = 0;
                     controlIndex < controlCount;
                     controlIndex++)
                {
                    // correct the snapshot values for the subcontrols
                    pModePage->m_Controls[controlIndex]->
                        ControlCorrectSnapshotValues( pCueBuffer );
                }

                // exit the for loop
                break;
            }
        }
    }
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
    ModeControl::getValues

    Get all values from the select control. This function is called from the
    UIModeControl to initialize its values.

    Returns: no return value
----------------------------------------------------------------------------*/

void 
ModeControl::getValues( 
   bool& hasModeChannel,
   uint32& channelOffset,
   Array<ModePage*>& pages) const
{
    // copy values
    hasModeChannel = m_HasModeChannel;
    channelOffset = m_ChannelOffset;

    // copy mode pages vector. This will only copy the pointers of the mode
    // pages, but that's exactly what we want here.
    for (int n = 0; n < m_Pages.size(); ++n)
        pages.add (m_Pages[n]);
}


/*----------------------------------------------------------------------------
    ModeControl::addModePage

    Add mode page to the control.

    Returns: true or false
----------------------------------------------------------------------------*/

void 
ModeControl::addModePage (ModePage* pNewPage)
{
    // add mode page to mode control vector
    m_Pages.add (pNewPage);
}


// Private Functions .........................................................

/*----------------------------------------------------------------------------
    ModeControl::LoadPageControls

    Load all sub controls of the given page

    Returns: true or false
----------------------------------------------------------------------------*/

bool 
ModeControl::LoadPageControls( 
   ShowFile& show,          // stream to load data from
   uint32 version,          // file version
   ModePage* pModePage )    // new mode page to store data in
{
    bool result = true;

    // read number of controls in that page
    int controlCount = 0;
    if (! show.readInt (controlCount))
        return false;

    // for all controls
    for (int controlIndex = 0; controlIndex < controlCount; controlIndex++)
    {
        // The first element for each control is always the control
        // type. We have to read the type first so that we can create
        // the correct control object.

        ScopedPointer<Control> pControl;

        // read control type, the control type is saved as a DWORD
        uint32 controlType = 0;
        if (show.readDword (controlType))
        {
            // check the control type
            switch( controlType )
            {
                case CT_SELECT:
                    // create select control, check result below
                    pControl = new SelectControl;
                    break;

                case CT_FADER:
                    // create fader control, check result below
                    pControl = new FaderControl;
                    break;

                case CT_MODE:
                    // create mode control, check result below
                    pControl = new ModeControl;
                    break;

                case CT_SWITCH:
                    // create switch control, check result below
                    // !!!! todo
                    break;

                case CT_POSITION:
                    // create position control, check result below
                    pControl = new PositionControl;
                    break;

                case CT_LABEL:
                    // create label control, check result below
                    // !!!! todo
                    break;

                default:
                    // invalid control type
                    result = false;
                    break;
            }
        }
        else
            result = false;

        // did we successful create a control
        if (result && pControl)
        {
            // load the control data from the stream
            if (pControl->ControlLoad (show, version))
            {
                // add the control to the control vector
                pModePage->m_Controls.add (pControl);
                pControl.release();
            }
            else
            {
                // set error flag
                result = false;
                break;
            }
        }
        else
        {
            result = false;
            break;
        }
    }

    return result;
}

