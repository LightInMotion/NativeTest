/*
   File Info:

      $Workfile:   Device.cpp  $
      $Author:   JOE  $
      $Revision:   1.0  $
      $Modtime:   22 Oct 2009 11:39:24  $

   Module Description:

      A Device is very similar to a Template, the only main difference
      between a template and a device is that a device can not modify, add
      or delete and controls anymore. The device also can't modify the 
      control settings/properties anymore.
      Each Device contains a (now fixed) list of controls. Once the update
      function is called (from the cue) the device walks the control list
      and calls the update functions in the controls. The controls do the
      actual work and calculate the DMX values.
*/

// Includes ..................................................................

#include "Device.h"
#include "Control.h"
//#include "Template.h"
//#include "DeviceManager.h"
#include "FaderControl.h"
#include "PositionControl.h"
#include "SelectControl.h"
//#include "ModeControl.h"


// Local Defines .............................................................

// Local Data Types ..........................................................

// Public Interface ..........................................................
/*----------------------------------------------------------------------------
   Device::Device

   Constructor

   Returns: no return value
----------------------------------------------------------------------------*/

Device::Device()
    : m_GUID ("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"),
      m_BaseAddress (0),
      m_NumberOfChannels (0),
      m_pDeviceGroup (nullptr)
{
}


/*----------------------------------------------------------------------------
   Device::Device

   Constructor with parameters

   Returns: no return value
----------------------------------------------------------------------------*/

Device::Device( String pName,
                Uuid guid )
   :  m_GUID(guid),
      m_Name(pName),
      m_BaseAddress(0),
      m_NumberOfChannels(0),
      m_pDeviceGroup(NULL)
{
}


/*----------------------------------------------------------------------------
   Device::Device

   Destructor. Delete all controls in the device list

   Returns: no return value
----------------------------------------------------------------------------*/

Device::~Device()
{
}


// Member access functions ...................................................

/*
   Access members like name and base address of the device
*/

/*----------------------------------------------------------------------------
   Device::DeviceGetName

   get name of the device

   Returns: name
----------------------------------------------------------------------------*/

String
Device::DeviceGetName() const
{
   return m_Name;
}


/*----------------------------------------------------------------------------
   Device::DeviceSetName

   set the name of the device

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Device::DeviceSetName (String pName)
{
   m_Name = pName;
}


/*----------------------------------------------------------------------------
   Device::DeviceGetBaseAddress

   return the base/start address of the device. The base address is zero based
   (for display purpose we show it one-based)

   Returns: device base address
----------------------------------------------------------------------------*/

uint32
Device::DeviceGetBaseAddress() const
{
   return m_BaseAddress;
}


/*----------------------------------------------------------------------------
   Device::DeviceSetBaseAddress

   Set the base address to the device. This function walks the control list
   and updates the absolute address for all controls. The start/base address
   is zero-based. For display purpose we show it one-based.

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Device::DeviceSetBaseAddress (uint32 address) // new zero-based start address
{
   m_BaseAddress = address;

   int count = m_ControlList.size();

   // for all controls
   for (int controlIndex = 0; controlIndex < count; controlIndex++)
      // call the set address function in the control
      m_ControlList[controlIndex]->ControlSetAddress (address);
}


/*----------------------------------------------------------------------------
   Device::DeviceGetNumberOfChannels

   Return the number of DMX channels contained in the device including all
   controls. This value is set based on the template and can't be modified
   after the device has been created.

   This value gets calculated in DeviceCalculateNumberOfChannels(). 
   (see below)

   Returns: number of DMX channels
----------------------------------------------------------------------------*/

int 
Device::DeviceGetNumberOfChannels() const
{
   // return precalculated value
   return m_NumberOfChannels;
}


/*----------------------------------------------------------------------------
   Device::DeviceCalculateNumberOfChannels

   After we created a device (either based on a template or after we loaded
   it from a file) we have to calculate the number of DMX channels. This is
   only done once after the device creation and not repeatedly for performance
   reasons. When we draw a device we just call the function 
   DeviceGetNumberOfChannels() which returns the buffered value.
   This function obviously has to be called after adding all controls

   ! the implementation of this function is identical with
   TempGetNumberOfChannels() !

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Device::DeviceCalculateNumberOfChannels()
{
   Array<int> channels;

   // for all controls
   int controlCount = m_ControlList.size();
   for( int controlIndex = 0; controlIndex < controlCount; controlIndex++ )
      // get the number of used channels from the control. Each control adds
      // their channels to the given vector
      m_ControlList[controlIndex]->ControlGetUsedChannels( channels, true );

   // do we have any channels at all
   int channelCount = channels.size();
   if( channelCount == 0 )
   {
      // we don't contain any channels at all
      m_NumberOfChannels = 0;
      return;
   }

   int maxChannel = channels[0];

   // for all returned channels, it is possible that some channels are 
   // duplicated. E.g. the sub controls in the mode control might contain
   // the same channel.

   for( int channelIndex = 0; channelIndex < channelCount; channelIndex++ )
   {
      // update the maximum channel
      if( channels[channelIndex] > maxChannel )
         maxChannel = channels[channelIndex];
   }

   // set the number of the occupied channels
   m_NumberOfChannels = maxChannel + 1 - m_BaseAddress;
}


// control access.............................................................
/*
   Access to the controls contained in the device.
*/

/*----------------------------------------------------------------------------
   Device::DeviceGetControlCount

   Return the number of controls contained in the device

   Returns: control count
----------------------------------------------------------------------------*/

int 
Device::DeviceGetControlCount() const
{
   // return number of controls in the control vector
   return m_ControlList.size();
}


/*----------------------------------------------------------------------------
   Device::DeviceGetControl

   Return the control for the given control index. No index validation is
   performed, the index is assumed valid.

   Returns: control pointer
----------------------------------------------------------------------------*/

Control* 
Device::DeviceGetControl( int index )
{
   // return the pointer to the control
   return m_ControlList[index];
}


/*----------------------------------------------------------------------------
   Device::DeviceUpdateBuffer

   This function walks the control list of the device and calls 
   ControlUpdateBuffer on all controls. The controls are responsible of
   summing and calculation the DMX values.
   This function is called from the Cue.

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Device::DeviceUpdateBuffer( 
   const uint8* pCueBuffer, // input cue buffer
   uint8* pOutputBuffer,    // in/out: output buffer
   int faderLevel,         // fader level
   int GMAdjustedLevel )   // grand master adjusted fader level, used for 
                           // grand master controlled controls.
{
   int count = m_ControlList.size();

   // for all controls
   for( int controlIndex = 0; controlIndex < count; controlIndex++ )
   {
      // call the update function in the control
      m_ControlList[controlIndex]->ControlUpdateBuffer( pCueBuffer, 
                                                        pOutputBuffer, 
                                                        faderLevel,
                                                        GMAdjustedLevel );
   }
}


/*----------------------------------------------------------------------------
   Device::DeviceCloneControls

   This function clones all controls which are in the template and adds
   them to the device. A device can only be
   created based on a template. This function is called from the DeviceFolder
   which is the only instance which can create devices. See the function
   DevFoldAddDevice() for more detail on creating devices.

   Returns: true or false
----------------------------------------------------------------------------*/

#if 0
bool 
Device::DeviceCloneControls( const Template* pTemplate )
{
   // we duplicate all controls which are contained in the template.

   int controlCount = pTemplate->TempGetControlCount();

   // for all controls contained in the template
   for( int controlIndex = 0; controlIndex < controlCount; controlIndex++ )
   {
      // duplicate/clone the control
      Control* pControl = 
         pTemplate->TempGetControl( controlIndex )->ControlClone();

      if( ! pControl )
         return false;

      // add new control to device
      m_ControlList.push_back( pControl );
   }

   return true;
}
#endif

// device group access
/*
   Get/Set the device group. Every device can (should) belong to a device
   group.
*/

/*----------------------------------------------------------------------------
   Device::DeviceGetGroup

   Get the device group associated with the device

   Returns: device group pointer or NULL if device group doesn't exist
----------------------------------------------------------------------------*/

DeviceGroup* 
Device::DeviceGetGroup()
{
   return m_pDeviceGroup;
}


/*----------------------------------------------------------------------------
   Device::DeviceSetGroup

   Set the device group

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Device::DeviceSetGroup( DeviceGroup* pDeviceGroup )
{
   m_pDeviceGroup = pDeviceGroup;
}


// compare operators..........................................................
/*
   Compare operator. We need to compare devices for two reasons, one reason
   is the cue editor, in which we allow multiselection only for 'identical'
   devices. The other time when we need to compare devices is in the device
   view window to give different devices different colors.
*/

/*----------------------------------------------------------------------------
   Device::operator==()

   Equal operator, compares the devices. Returns true if the device is 
   identical. A device is considered identical when the GUID is identical.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Device::operator==( const Device& device ) const
{
   if ( m_GUID == device.m_GUID )
      return true;

   return false;
}


/*----------------------------------------------------------------------------
   Device::operator!=()

   Not equal operator

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Device::operator!=( const Device& device ) const
{
   return ! ( *this == device );
}


// save/load .................................................................
/*
   Save and load the device to/from the structure storage file. For details
   about the file structure see ShowFileFormat.txt
*/

/*----------------------------------------------------------------------------
   Device::DeviceSerialize

   Save the device data to the structure storage file. We don't lock
   the critical section from the main module while saving, since we don't 
   modify any data (notice the const)

   Returns: true or false
----------------------------------------------------------------------------*/

#if 0
bool 
Device::DeviceSerialize( 
   IStorage* pStorage,                       // storage object for device data
   const DeviceManager* pDeviceManager)const // device manager to find the
                                             // device group index
{
   // serialize device data to "Info" stream
   if( ! SerializeInfo( pStorage, pDeviceManager ))
      return false;

   // serialize control data
   if( ! SerializeControls( pStorage ))
      return false;

   return true;
}
#endif

/*----------------------------------------------------------------------------
   Device::DeviceLoad

   Load the device from the structure storage file. As with
   all load functions, the critical section from the main module has to be 
   locked before calling this function.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Device::DeviceLoad( 
   ShowFile& show,  // storage containing the device data
   uint32 version,       // file version to load
   const OwnedArray<DeviceGroup>* groupList )// device group vector to
                                               // look up device group pointer
                                               // from the given device group
                                               // index
{
   // load basic device info from the "Info" stream
   uint32 controlCount = 0;
   if( ! LoadInfo( show, groupList, controlCount ))
      return false;

   // load all controls from the "Controls" stream
   if( ! LoadControls( show, version, controlCount ))
      return false;

   // We set the loaded base address to ourself, this will also update the
   // base address in all controls. This is necessary so that the update 
   // function works correct later.
   DeviceSetBaseAddress( m_BaseAddress );
   
   // after we successfully loaded all control we have to calculate the
   // number of DMX channels for the device. This is done only once here
   // for performance reasons and not repeatedly.
   DeviceCalculateNumberOfChannels();

   return true;
}


// find for saving ...........................................................
/*
   During save we need to find the indices to the pointers we keep around.
   That's what those functions are for. They are called from the cue during
   saving. 
*/
/*----------------------------------------------------------------------------
   Device::DeviceFindPositionControl

   Search all controls and compare the given control pointer. If the 
   given control pointer was found it returns the index of the control.

   Returns: true if the control is found in this device, false otherwise
----------------------------------------------------------------------------*/

bool 
Device::DeviceFindPositionControl( 
   const Control* pControl,   // given position control pointer to compare
   int& controlIndex ) const  // returned control index, invalid if failed
{
   // for all controls
   int controlCount = m_ControlList.size();
   for( int index = 0; index < controlCount; index++ )
   {
      // does the control pointer match
      if( m_ControlList[index] == pControl )
      {
         // set the returned control index and return true
         controlIndex = index;
         return true;
      }
   }

   // control is not found in this device
   return false;
}


// Private Functions .........................................................

// save/load subfunctions ....................................................
/*
   subfunctions of the serialize and load functions. The device has two
   streams, an "Info" stream for the basic device data and a "Control" stream
   for all control data.
*/

#if 0
/*----------------------------------------------------------------------------
   Device::SerializeInfo

   Serialize the basic device data to the "Info" stream

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Device::SerializeInfo( 
   IStorage* pStorage,                      // storage object for device data
   const DeviceManager* pDeviceManager)const// device manager to find the
                                            // device group index
{
   bool result = true;

   // create stream "Info"
   IStream* pStreamInfo = FileHelpCreateStream(pStorage,IDS_FILE_DEVICE_INFO);
   if( pStreamInfo )
   {
      // write the GUID of the device
      if( pStreamInfo->Write( &m_GUID, sizeof(GUID), NULL ) != S_OK )
         result = false;

      // assume 'int' as 32bit

      // find the device index to the device group pointer. The returned index
      // should always be valid.
      // This function call violates the coding conventions, since it calls
      // back to the device manager from where this function gets called.
      // Any other idea how to solve this in a 'nice' way ?

      int groupIndex = pDeviceManager->DevManFindGroupIndex( m_pDeviceGroup );

      // write group index to file
      if( ! FileHelpWriteInt( pStreamInfo, groupIndex ))
         result = false;

      // write base address to file
      if( ! FileHelpWriteInt( pStreamInfo, m_BaseAddress ))
         result = false;

      // write number of controls
      DWORD controlCount = m_ControlList.size();
      if( ! FileHelpWriteDWORD( pStreamInfo, controlCount ))
         result = false;

      // write device name
      if( ! FileHelpWriteString( pStreamInfo, m_Name ))
         result = false;

      // close stream "Info"
      pStreamInfo->Release();
   }
   else
      result = false;

   return result;
}

/*----------------------------------------------------------------------------
   Device::SerializeControls

   Serialize all control data to the "Control" stream

   Returns: true or false
----------------------------------------------------------------------------*/

bool
Device::SerializeControls(IStorage* pStorage ) const
{
   bool result = true;

   // create stream "Controls"
   IStream* pStreamControls = FileHelpCreateStream(pStorage, 
                                                   IDS_FILE_DEVICE_CONTROLS);
   if( pStreamControls )
   {
      // for all controls
      int controlCount = m_ControlList.size();
      for( int controlIndex = 0; controlIndex < controlCount; controlIndex++ )
      {
         // ! Important: Save the control type first, so that we can 
         // instantiate the appropriate control when reading the data back !

         // save control type as a DWORD
         DWORD controlType = m_ControlList[controlIndex]->ControlGetType();
         if( ! FileHelpWriteDWORD( pStreamControls, controlType ))
         {
            result = false;
            break;
         }

         // serialize the control.
         // Important: The controls have to be loaded (and stored in the
         // control vector) in the same order as they are saved, because the
         // cue saves the control index of the position controls with 
         // effects active.

         if( ! m_ControlList[controlIndex]->ControlSerialize(pStreamControls))
         {
            result = false;
            break;
         }
      }

      // close stream "Controls"
      pStreamControls->Release();
   }
   else
      result = false;

   return result;
}

#endif

/*----------------------------------------------------------------------------
   Device::LoadInfo

   Load all device data from the "Info" stream

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Device::LoadInfo( 
   ShowFile& show,                        // storage for device data

   const OwnedArray<DeviceGroup>* groupList,// group vector to look up
                                              // group pointer based on saved
                                              // group index

   uint32& controlCount )                      // returned control count,
                                              // invalid if function fails
{
   bool result = true;

   // open stream "Info"
   String oldpath = show.getPath();
   
   if (show.setPath (oldpath + "Info"))
   {
      // Load the GUID
      if (! show.readGuid(m_GUID))
          result = false;
 
      // load the device group index
      int groupIndex = 0;

      if (! show.readInt (groupIndex))
          return false;
       
       m_pDeviceGroup = nullptr;
#if 0
       if( FileHelpReadInt( pStreamInfo, groupIndex ))
      {
         // check if the group index is a valid index
         if(( groupIndex >= 0 ) && ( groupIndex < (int)groupList.size()))
         {
            // get the device group pointer from the vector and save it in
            // our private member
            m_pDeviceGroup = groupList[groupIndex];
         }
         else
            result = false;
      }
      else
         result = false;
#endif
       
      // load base address
      if (! show.readDword (m_BaseAddress))
         result = false;

      // load number of controls
      if (! show.readDword (controlCount))
         result = false;

      // load device name
      if (! show.readString (m_Name))
          result = false;
   }
   else
      result = false;

   show.setPath (oldpath);
   return result;
}


/*----------------------------------------------------------------------------
   Device::LoadControls

   Load all control data from the "Control" stream

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Device::LoadControls( 
   ShowFile& show,  // storage object for device data
   uint32 version,       // file version to load
   uint32 controlCount ) // control count read from the "Info" stream
{
   bool result = true;

   // open stream "Controls"
   String oldpath = show.getPath();
    
   if (show.setPath (oldpath + "Controls"))
   {
      // for all controls
      for (uint32 controlIndex = 0; controlIndex < controlCount; controlIndex++)
      {
         // The first element for each control is always the control
         // type. We have to read the type first so that we can create
         // the correct control object.

         Control* pControl = nullptr;

         // read control type
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
//                  pControl = new ModeControl;
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
            if (pControl->ControlLoad(show, version ))
               // add the control to the control vector
               m_ControlList.add (pControl);
            else
            {
               // set error flag and delete control
               result = false;
               delete pControl;
               break;
            }               
         }
         else
         {
            result = false;
            break;
         }
      }
   }
   else
      result = false;

   show.setPath (oldpath);
   return result;
}
















