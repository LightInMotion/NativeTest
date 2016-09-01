/*
   Module Description:

      A Cue is a central part of the application. Each Show (project) has
      a cue list which can contain an unlimited number of cues. The cue list
      is contained in the CueManager.
      Each cue has a list with devices that belong to the cue. It can be any
      device which is in the main device list (see DeviceManager), but it 
      doesn't have to include all of the devices from the show/project.

      A cue has a cue buffer which contains the cue data from all 2048 
      DMX channels (currently we have 4 DMX universes with 512 channels each).
      Each DMX channel is represented with one byte in the 
      cue buffer.

      When the update function is called on the cue (from a fader) then the 
      cue buffer is passed to all the devices which internally call the 
      update functions on the controls and the controls know how to modify
      the cue buffer (cue data).
*/

// Includes ..................................................................

#include "Cue.h"
#include "Device.h"
//#include "FileHelper.h"
//#include "resource.h"
#include "Main.h"
//#include "DeviceManager.h"
#include "Control.h"


// Local Defines .............................................................

// Local Data Types ..........................................................

// Public Interface ..........................................................

Cue Cue::dummy(0);    // 0 is reserved for an empty Cue

/*----------------------------------------------------------------------------
   Cue::Cue   

   Constructor

   Returns: no return value
----------------------------------------------------------------------------*/

Cue::Cue()
   :  m_Number(0)
{
   zeromem (m_CueBuffer, MAIN_DMX_CHANNEL_BUFFER_COUNT);
}


/*----------------------------------------------------------------------------
   Cue::Cue

   Constructor taking a cue number

   Returns: no return value
----------------------------------------------------------------------------*/

Cue::Cue( int number )
   :  m_Number( number )
{
   zeromem (m_CueBuffer, MAIN_DMX_CHANNEL_BUFFER_COUNT);
}


/*----------------------------------------------------------------------------
   Cue::~Cue

   Destructor

   Returns: no return value
----------------------------------------------------------------------------*/

Cue::~Cue()
{
   // delete all EffectData elements associated with the cue

   // for all effect data entries
//   int effectCount = m_EffectDataList.size();
//   for( int effectIndex = 0; effectIndex < effectCount; effectIndex++ )
      // delete the effect data element, don't delete the control pointer
      // (obviously)
//      delete m_EffectDataList[effectIndex].m_pEffectData;
}


// Member access functions ...................................................

/*
   Get/Set cue members like name, description and number
*/

/*----------------------------------------------------------------------------
   Cue::CueGetName

   Get the cue name

   Returns: cue name
----------------------------------------------------------------------------*/

String
Cue::CueGetName() const
{
   return m_Name;
}


/*----------------------------------------------------------------------------
   Cue::CueSetName

   set the cue name

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Cue::CueSetName (String name)
{
   // set the name
   m_Name = name;
}


/*----------------------------------------------------------------------------
   Cue::CueGetNumber

   get the cue number. There is no set cue number function. The cue number
   can't be changed once a cue is created.

   Returns: cue number
----------------------------------------------------------------------------*/

int 
Cue::CueGetNumber() const
{
   return m_Number;
}


/*----------------------------------------------------------------------------
   Cue::CueSetNumber

   !!!IMPORTANT: The cue number should NEVER be changed AFTER the cue is added
   to the cue manager (by calling CueManAddCue()). This function is ONLY 
   added for the snapshot, which creates an 'unnumbered' cue while it doesn't
   know the cue number yet. This function should not be called from anywhere
   else!!!

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Cue::CueSetNumber( int number )  // cue number
{
   // set the cue number
   m_Number = number;
}


/*----------------------------------------------------------------------------
   Cue::CueGetDescription

   get cue description

   Returns: cue description
----------------------------------------------------------------------------*/

String
Cue::CueGetDescription() const
{
   return m_Description;
}


/*----------------------------------------------------------------------------
   Cue::CueSetDescription

   set cue description

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Cue::CueSetDescription( String description )
{
   m_Description = description;
}


/*----------------------------------------------------------------------------
   Cue::CueGetBuffer

   Return the pointer to the cue buffer. This function is called from the 
   cue editor to get direct access to the cue buffer. The cue editor is
   the only instance in the system to access the cue buffer directly
   (besides the Cue of course). The Update function reads from the cue buffer
   and the cue editor writes to the cue buffer.

   Returns: pointer to cue buffer
----------------------------------------------------------------------------*/

uint8*
Cue::CueGetBuffer()
{
   // return pointer to cue buffer
   return m_CueBuffer;
}


// update functions...........................................................
/*
   Core functionality of the system. The update functions get called from
   the main update thread every 33ms to update all cues.
*/

/*----------------------------------------------------------------------------
   Cue::CueUpdateBuffer

   This function walks the device list and calls DeviceUpdateBuffer on
   all devices in the list.

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Cue::CueUpdateBuffer( 
   uint8* pOutputBuffer,
   int faderLevel,      // fader level
   int GMAdjustedLevel )// grand master adjusted fader level, used for grand
                        // master controlled controls.
{
   // get number of devices contained in the cue
   int deviceCount = m_DeviceList.size();

   // for all devices in the list
   for( int deviceIndex = 0; deviceIndex < deviceCount; deviceIndex++ )
   {
      // call the update function on the device, passing in the cue buffer
      // and the given output buffer
      m_DeviceList[deviceIndex]->DeviceUpdateBuffer( m_CueBuffer,
                                                     pOutputBuffer,
                                                     faderLevel,
                                                     GMAdjustedLevel );
   }
}

#if 0
/*----------------------------------------------------------------------------
   Cue::CueCalculateEffects

   This function looks if the effect data list is non empty. If so it walks
   the list and calls ControlCalculateEffect on all entries.

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Cue::CueCalculateEffects( int faderLevel )
{
   // effect date entries
   int effectCount = m_EffectDataList.size();

   // for all (if any) effects in the effect data list
   for( int effectIndex = 0; effectIndex < effectCount; effectIndex++ )
   {
      // call the update effect function on the position control pointer
      m_EffectDataList[effectIndex].m_pControl->
         ControlCalculateEffect( m_EffectDataList[effectIndex].m_pEffectData,
                              faderLevel );
   }
}


/*----------------------------------------------------------------------------
   Cue::CueUpdateEffects

   This function looks if the effect data list is non empty. If so it walks
   the list and calls ControlUpdateEffect on all entries. It passes the 
   output buffer to add the effect data to the already existing dmx data.

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Cue::CueUpdateEffects( BYTE* pOutputBuffer, 
                       int faderLevel )
{
   // effect date entries
   int effectCount = m_EffectDataList.size();

   // for all (if any) effects in the effect data list
   for( int effectIndex = 0; effectIndex < effectCount; effectIndex++ )
   {
      // call the update effect function on the position control pointer
      m_EffectDataList[effectIndex].m_pControl->
         ControlUpdateEffect( pOutputBuffer,
                              m_EffectDataList[effectIndex].m_pEffectData,
                              faderLevel );
   }
}


/*----------------------------------------------------------------------------
   Cue::CueAdvanceEffectPositions

   This function walks the effect data list (if non empty) and calls 
   PosConAdvanceEffectPosition() on all PositionControls in the list.

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Cue::CueAdvanceEffectPositions( UINT updateID )
{
   // effect date entries
   int effectCount = m_EffectDataList.size();

   // for all (if any) effects in the effect data list
   for( int effectIndex = 0; effectIndex < effectCount; effectIndex++ )
   {
      // call the advance position function on the position control
      m_EffectDataList[effectIndex].m_pControl->
               ControlAdvanceEffectPosition( updateID );
   }
}

#endif

// Device Access..............................................................
/*
   Access to the devices contained in the cue.
*/

/*----------------------------------------------------------------------------
   Cue::CueGetDeviceCount

   Return the number of devices in the cue

   Returns: number of devices
----------------------------------------------------------------------------*/

int 
Cue::CueGetDeviceCount() const
{
   // return number of devices in cue
   return m_DeviceList.size();
}


/*----------------------------------------------------------------------------
   Cue::CueGetDevice

   Get the specified device in the cue. The device index has to be a valid
   device index

   Returns: device pointer
----------------------------------------------------------------------------*/

Device* 
Cue::CueGetDevice( int index ) const   // device index
{
   // return the device pointer
   return m_DeviceList[index];
}


/*----------------------------------------------------------------------------
   Cue::CueAddDevice

   Add a device (pointer) to the cue list. The device itself belongs to the
   device manager and the device manager has to make sure to delete any 
   references to a device before it gets deleted.

   This function does not check if the device already exits, therefor the
   caller of this function has to make sure that the device pointer is not
   already in the device list of the cue.

   It is recommended to get the critical section from the main module to
   halt the main update thread, because the main update thread works on the
   devices in the cue. It might still work correctly without getting the
   critical section (because we are only adding devices) but we don't want
   to take the chance.

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Cue::CueAddDevice( Device* pDevice )
{
   // add the device pointer to the list
   m_DeviceList.add( pDevice );
}


/*----------------------------------------------------------------------------
   Cue::CueRemoveDevice

   Remove a device from the device list. This function doesn't delete the 
   device itself, it only removes it from the list and clears the cue buffer.
   This function is called from the cue manager. The caller of this function 
   has to make sure that the main update thread is halted by getting the main
   critical section from the main module.

   This function also removes all entries (Control pointers) from the effect 
   data list, if the selected device contains controls with activated effects.

   ! Important: The device still has to exist when calling this function.
   Call this function before calling DevManRemoveDevice() !

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Cue::CueRemoveDevice( Device* pDevice )
{
   // walk the device list and remove the pointer if it matches.

   int deviceCount = m_DeviceList.size();

   // for all devices
   for( int deviceIndex = 0; deviceIndex < deviceCount; deviceIndex++ )
   {
      // does the device pointer match
      if( m_DeviceList[deviceIndex] == pDevice )
      {
         // for all controls of that device
         int controlCount = pDevice->DeviceGetControlCount();
         for(int controlIndex = 0; controlIndex < controlCount;controlIndex++)
         {
            // remove the effect data entry if it exists. This function 
            // also gets the critical section from the main update thread
            // (again). But this is ok, since a critical section doesn't
            // block if it gets locked from the same thread twice.

             ;
//           CueRemoveEffectData( pDevice->DeviceGetControl( controlIndex ));
         }

         // get the base address and number of channels occupied by the 
         // device. The base address is zero based.
         uint32 baseAddress = pDevice->DeviceGetBaseAddress();
         int numberOfChannels = pDevice->DeviceGetNumberOfChannels();

         // clear the cue buffer which was occupied by this device
         zeromem (m_CueBuffer + baseAddress, numberOfChannels);

         // remove it from the list and return
         m_DeviceList.remove (deviceIndex);
         return;
      }
   }
}


/*----------------------------------------------------------------------------
   Cue::CueMoveDevice

   This function gets called when a device changes its base address. We check
   if that device exists in this cue and copy the cue data to the new 
   destination. We also have to clear the old cue data.

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Cue::CueMoveDevice(
   const Device* pDevice,  // device which is being moved
   int oldAddress,         // old base address before the move
   int newAddress )        // new base address after the move
{
   int deviceCount = m_DeviceList.size();

   // for all devices
   for( int deviceIndex = 0; deviceIndex < deviceCount; deviceIndex++ )
   {
      // does the device pointer match
      if( m_DeviceList[deviceIndex] == pDevice )
      {
         // get number of channels
         int numberOfChannels = pDevice->DeviceGetNumberOfChannels();

         // create temporary buffer for cue data.
         uint8* pTempBuffer = new uint8[numberOfChannels];
         if( pTempBuffer )
         {
            // copy the cue data to a temporary buffer. This is necessary in
            // case the new devcie overlaps the old device
            
            memcpy ( pTempBuffer,
                     m_CueBuffer + oldAddress,
                     numberOfChannels );

            // clear the old cue data
            zeromem ( m_CueBuffer + oldAddress, numberOfChannels );

            // copy the data to the new destination
            memcpy ( m_CueBuffer + newAddress,
                        pTempBuffer, 
                        numberOfChannels );

            delete[] pTempBuffer;
         }
      }
   }
}


/*----------------------------------------------------------------------------
   Cue::CueIsDeviceInUse

   Check if the given device is used in that cue

   Returns: true if the device is used, false otherwise
----------------------------------------------------------------------------*/

bool 
Cue::CueIsDeviceInUse( 
   const Device* pDevice ) const  // device to check for usage
{
   // for all devices
   int deviceCount = m_DeviceList.size();
   for( int deviceIndex = 0; deviceIndex < deviceCount; deviceIndex++ )
   {
      // does the device pointer match
      if( m_DeviceList[deviceIndex] == pDevice )
         return true;
   }

   // device is not in use
   return false;
}


// save/load .................................................................
/*
   Save and load the cue data to/from the structure storage file
*/
#if 0
/*----------------------------------------------------------------------------
   Cue::CueSerialize

   Save the cue data in the structure storage file. We don't lock
   the critical section from the main module while saving, since we don't 
   modify any data (notice the const)

   Returns: 
----------------------------------------------------------------------------*/

bool
Cue::CueSerialize( IStorage* pStorage ) const
{
   bool result = true;

   // serialize basic cue data in the "Info" stream
   if( ! SerializeInfo( pStorage ))
      result = false;

   // serialize device data in the device stream
   if( ! SerializeDevices( pStorage ))
      result = false;

   // serialize effect data in the effect stream
   if( ! SerializeEffects( pStorage ))
      result = false;

   // create stream "Data"
   IStream* pStreamData = FileHelpCreateStream( pStorage, IDS_FILE_CUE_DATA );
   if( pStreamData )
   {
      // encode and serialize the cue buffer
      if( ! SerializeBuffer( pStreamData ))
         result = false;

      pStreamData->Release();
   }
   else
      result = false;

   return result;
}

#endif 

/*----------------------------------------------------------------------------
   Cue::CueLoad

   Load all cue data from the structure storage file. As with all load 
   functions, the critical section from the main module has to be locked
   before calling this function.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Cue::CueLoad( ShowFile& show,
              uint32 version,
              const OwnedArray<Device>& devicelist )
{
   uint32 deviceCount = 0;
   uint32 effectCount = 0;

   // load basic data from the "Info" stream
   if( ! LoadInfo( show, deviceCount, effectCount ))
      return false;

   // do we have any devices to load
   if( deviceCount > 0 )
   {
      // load device data 
      if( ! LoadDevices( show, deviceCount, devicelist ))
         return false;
   }

   // do we have any effect data to load
//   if( effectCount > 0 )
//   {
      // load effect data
//      if( ! LoadEffects( pStorage, effectCount, version ))
//         return false;
//   }

   bool result = true;

   // open "Data" stream for cue buffer
   String oldpath = show.GetPath();

   if (show.SetPath (oldpath + "Data"))
   {
      if( ! LoadBuffer( show ))
         result = false;
   }
   else
      result = false;;

   show.SetPath (oldpath);
   return result;
}


/*----------------------------------------------------------------------------
   Cue::CueClone

   Doublicate/Clone the cue. The new cue number has to be an non-existing
   valid cue number. No validation is performed here.

   Returns: new created/cloned cue, or NULL if failed
----------------------------------------------------------------------------*/

Cue* 
Cue::CueClone( 
   int newNumber ) const   // new cue number, has to be an non-existing
                           // valid cue number
{
   // We don't need to get the critical section from the main module, 
   // because the new created cue is not on any fader (yet) and therefor
   // doesn't get called from the update thread and the cue we are cloning 
   // will not be modified.

   // create new cue
   Cue* pNewCue = new Cue( newNumber );
   if( ! pNewCue )
      return NULL;

   // copy name and description (we will most likely overwrite the name and
   // description after we have the new cue, but for completeness I also clone
   // it here
   pNewCue->m_Name = m_Name;
   pNewCue->m_Description = m_Description;

   // ! Don't copy the cue number (of course) !

   // copy the cue buffer
   memcpy( &(pNewCue->m_CueBuffer),
               &m_CueBuffer, 
               MAIN_DMX_CHANNEL_BUFFER_COUNT );

   // the cue contains pointers to existing devices and  controls. We can just
   // copy the entire vector. 
   pNewCue->m_DeviceList = m_DeviceList;

   // The EffectData objects get managed from the Cue (dynamically created 
   // and destroyed) and we have to duplicate them here.

   // for all existing effect data entries
#if 0
    int effectCount = m_EffectDataList.size();
   for( int effectIndex = 0; effectIndex < effectCount; effectIndex++ )
   {
      // create new effect data entry, copy the existing data.
      EffectDataEntry newEntry( m_EffectDataList[effectIndex] );

      // create new EffectData and assign the pointer to the new effect data
      // entry.
      newEntry.m_pEffectData = new EffectData;
      if( ! newEntry.m_pEffectData )
         return NULL;

      // copy the EffectData object
      *(newEntry.m_pEffectData) = 
         *(m_EffectDataList[effectIndex].m_pEffectData);

      // add the new EffectDataEntry to the new cue
      pNewCue->m_EffectDataList.push_back( newEntry );
   }
#endif
   // return cloned cue
   return pNewCue;
}


// effect data access ........................................................
/*
   The effect data access functions get called from the UIPositionControl
   when the user switches effects on or off. The add/remove functions have
   to be synchronized with the main update thread, since CueUpdateEffects()
   walks the effect data entry vector which gets modified from the add/remove
   functions.
*/

#if 0
/*----------------------------------------------------------------------------
   Cue::CueAddEffectData

   Add a new effect data entry to the vector. This function has to be 
   synchronized with the main update thread. This function is called from 
   the UIPositionControl.

   Each position control can only have exactly one effect data entry. This
   function doesn't check if an effect data entry already exists, therefor
   the caller has to make sure to only call this function if no effect 
   exists yet.

   Returns: pointer to the new allocated EffectData
----------------------------------------------------------------------------*/

EffectData* 
Cue::CueAddEffectData( 
   Control* pControl,         // pointer to the PositionControl
   EffectPattern* pPattern)   // effect pattern to add.
{
   // create new effect data, using the default setting for speed, gain
   // and rotation.
   EffectData* pNewEffectData = new EffectData( pPattern );
   if( ! pNewEffectData )
      return NULL;

   // we need to synchronize the add/remove with the main update thread
   // since the update function walks the same vector at the same time.
   MainGetDeletionCriticalSection();
   {
      // add new effect data entry
      m_EffectDataList.push_back( EffectDataEntry(pControl, pNewEffectData));
   }
   MainReleaseDeletionCriticalSection();

   // return new effect data pointer
   return pNewEffectData;
}


/*----------------------------------------------------------------------------
   Cue::CueRemoveEffectData

   This function removes the effect from the given position control. It gets
   called from the UI position control and has to be synchronized with the 
   main update thread.

   This function is also called from CueRemoveDevice() to make sure we don't 
   have any invalid entries in the effect data list after deleting a device.

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Cue::CueRemoveEffectData( 
   const Control* pControl )// position control containing the effect to 
                            // remove
{
   // we need to synchronize the add/remove with the main update thread
   // since the update function walks the same vector at the same time.
   MainGetDeletionCriticalSection();
   {
      // for all effect data entries (all effects used for that cue)
      int effectCount = m_EffectDataList.size();
      for( int effectIndex = 0; effectIndex < effectCount; effectIndex++ )
      {
         // compare the control pointer with the given control pointer
         if( m_EffectDataList[effectIndex].m_pControl == pControl )
         {
            // delete the effect data element
            delete m_EffectDataList[effectIndex].m_pEffectData;

            // remove the effect data entry element from the vector
            m_EffectDataList.erase( m_EffectDataList.begin() + effectIndex );

            // exit for loop
            break;
         }
      }
   }
   MainReleaseDeletionCriticalSection();
}


/*----------------------------------------------------------------------------
   Cue::CueFindEffectData

   This function gets called from the UIPositionControl in order to initialize
   itself. The UIPositionControl has to know if an effect is turned on or not.
   That's what this function is for.

   Returns: EffectData pointer if an entry exists for this position control,
            NULL if no effect is turned on.
----------------------------------------------------------------------------*/

EffectData* 
Cue::CueFindEffectData( 
   const Control* pControl ) const // position control to check the effect 
                                   // data entry for.
{
   // this function doesn't add or remove any effect data entries from our
   // vector, therefor we don't have to halt the main update thread while
   // we search/access the vector. The vector is multithread save (at least
   // if you compile with the multithread standard library)

   // for all effect data entries (all effects used for that cue)
   int effectCount = m_EffectDataList.size();
   for( int effectIndex = 0; effectIndex < effectCount; effectIndex++ )
   {
      // compare the control pointer with the given control pointer
      if( m_EffectDataList[effectIndex].m_pControl == pControl )
         // return the effect data pointer 
         return m_EffectDataList[effectIndex].m_pEffectData;
   }

   // no effect turned on for that position control
   return NULL;
}

#endif

// Private Functions .........................................................

// save/load subfunctions ....................................................
/*
   Subfunctions of CueSerialize() and CueLoad() functions.
*/

/*----------------------------------------------------------------------------
   Cue::SerializeInfo

   Save basic cue data to the "Info" stream

   Returns: true or false
----------------------------------------------------------------------------*/
#if 0

bool 
Cue::SerializeInfo( IStorage* pStorage ) const
{
   bool result = true;

   // create stream "Info"
   IStream* pStreamInfo = FileHelpCreateStream( pStorage, IDS_FILE_CUE_INFO );
   if( pStreamInfo )
   {
      // save cue number
      if( ! FileHelpWriteInt( pStreamInfo, m_Number ))
         result = false;

      // save cue name
      if( ! FileHelpWriteString( pStreamInfo, m_Name ))
         result = false;

      // save comment
      if( ! FileHelpWriteString( pStreamInfo, m_Description ))
         result = false;

      // save number of devices
      DWORD deviceCount = m_DeviceList.size();
      if( ! FileHelpWriteDWORD( pStreamInfo, deviceCount ))
         result = false;

      // save number of effects
      DWORD effectCount = m_EffectDataList.size();
      if( ! FileHelpWriteDWORD( pStreamInfo, effectCount ))
         result = false;

      pStreamInfo->Release();
   }
   else
      result = false;

   return result;
}

#endif

/*----------------------------------------------------------------------------
   Cue::LoadInfo

   Load basic cue data from the "Info" stream

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Cue::LoadInfo( ShowFile& show,
               uint32& deviceCount,
               uint32& effectCount )
{
   bool result = true;

   // open stream "Info"
   String oldpath = show.GetPath();
    
   if (show.SetPath (oldpath + "Info"))
   {
      // load cue number
      if (! show.ReadInt(m_Number))
         result = false;

      // load cue name
      if (! show.ReadString (m_Name))
         result = false;

      // load cue comment
      if (! show.ReadString (m_Description))
         result = false;

      // load number of devices
      if(! show.ReadDword (deviceCount))
         result = false;

      // load number of effects
      if(! show.ReadDword (effectCount))
         result = false;
   }
   else
      result = false;

   show.SetPath (oldpath);
   return result;
}


/*----------------------------------------------------------------------------
   Cue::SerializeDevices

   Save device data to the "Devices" stream

   Returns: true or false
----------------------------------------------------------------------------*/

#if 0
bool 
Cue::SerializeDevices( IStorage* pStorage ) const
{
   bool result = true;

   // create stream "Devices"
   IStream* pStreamDevices = FileHelpCreateStream( pStorage, 
                                                   IDS_FILE_CUE_DEVICES );
   if( pStreamDevices )
   {
      DeviceManager* pDeviceManager = MainGetDeviceManager();

      // for all devices
      int deviceCount = m_DeviceList.size();
      for( int deviceIndex = 0; deviceIndex < deviceCount; deviceIndex++ )
      {
         // the cue has a vector of device pointers for faster access, but 
         // we can't save the pointers in the file, instead we save the 
         // device index from the device manager vector. Call the device 
         // manager to find the correlating index to the pointer
         int indexToSave = pDeviceManager->
               DevManFindDeviceIndex( m_DeviceList[deviceIndex] );

         // save index
         if( ! FileHelpWriteInt( pStreamDevices, indexToSave ))
         {
            result = false;
            break;
         }
      }

      pStreamDevices->Release();
   }
   else
      result = false;

   return result;
}

#endif

/*----------------------------------------------------------------------------
   Cue::LoadDevices

   Load device data from the "Devices stream

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Cue::LoadDevices( ShowFile& show,
                  uint32 deviceCount,
                  const OwnedArray<Device>& deviceList)
{
   bool result = true;

   // get device manager and device count, so that we can lookup the device
   // pointers from the loaded device indices.
//   DeviceManager* pDeviceManager = MainGetDeviceManager();
//   int devicesInVector = pDeviceManager->DevManGetDeviceCount();
    int devicesInVector = deviceList.size();
    
   // open stream "Devices"
   String oldpath = show.GetPath();
   if (show.SetPath(oldpath + "Devices"))
   {
      // for all devices in the stream
      for (uint32 index = 0; index < deviceCount; index++)
      {
         // load the device index, this is the index into the device vector
         // in the device manager.
         // ! Important: All devices have to be loaded BEFORE loading the
         // cues so that we can get the device pointers here !

         int deviceIndex = 0;
         if (show.ReadInt (deviceIndex))
         {
            // check if the index is valid
            if(( deviceIndex >= 0 ) && ( deviceIndex < devicesInVector ))
            {
               // get the device pointer from the device vector in the 
               // device manager
               Device* pDevice = deviceList[deviceIndex];

               // add the device pointer to the cue device vector
               m_DeviceList.add( pDevice );
            }
            else
            {
               // exit for loop
               result = false;
               break;
            }
         }
         else
         {
            // exit for loop
            result = false;
            break;
         }
      }
   }
   else
      result = false;

   show.SetPath (oldpath);
   return result;
}


#if 0
/*----------------------------------------------------------------------------
   Cue::SerializeEffects

   Save effect data to the "Effects" stream

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Cue::SerializeEffects( IStorage* pStorage ) const
{
   bool result = true;

   // create stream "Effects"
   IStream* pStreamEffects = FileHelpCreateStream( pStorage, 
                                                   IDS_FILE_CUE_EFFECTS );
   if( pStreamEffects )
   {
      // for all effects (effect data entries)
      int effectCount = m_EffectDataList.size();
      for( int effectIndex = 0; effectIndex < effectCount; effectIndex++ )
      {
         // serialize the effect data entry and the associated effect
         // data object
         if( ! m_EffectDataList[effectIndex].
                  EffDatEntrySerialize( pStreamEffects ))
         {
            result = false;
            break;
         }
      }

      pStreamEffects->Release();
   }
   else
      result = false;

   return result;
}


/*----------------------------------------------------------------------------
   Cue::LoadEffects

   Load effect data from the "Effects" stream

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Cue::LoadEffects( IStorage* pStorage, 
                  DWORD effectCount,   // number of effects to load
						DWORD version )		// file version being loaded
{
   bool result = true;

   // open stream "Effects"
   IStream* pStreamEffects = FileHelpOpenStream( pStorage, 
                                                 IDS_FILE_CUE_EFFECTS );
   if( pStreamEffects )
   {
      // for all effects
      for( DWORD index = 0; index < effectCount; index++ )
      {
         EffectDataEntry newEntry;

         // load the effect data entry and the associated effect data
         if( ! newEntry.EffDatEntryLoad( pStreamEffects, version ))
         {
            // exit for loop
            result = false;
            break;
         }

         // add effect data entry to the effect vector
         m_EffectDataList.push_back( newEntry );
      }

      // close stream "Effects"
      pStreamEffects->Release();
   }
   else
      result = false;

   return result;
}


// save/load buffer ..........................................................
/*
   Save and load the cue buffer. We encode the cue buffer to save space
*/

/*----------------------------------------------------------------------------
   Cue::SerializeBuffer

   Encode the buffer and save it to the stream

   Returns: 
----------------------------------------------------------------------------*/

bool 
Cue::SerializeBuffer( IStream* pStream ) const
{
   /*
      We encode the buffer the following way:
      We use one byte for the length with the first bit serving as a flag.
      If the flag is 1 then the remaining 7 bits are the length of a repeating
      byte pattern. If the flag is zero then the 7 bits is the length of 
      'normal' data.
   */

   // start and end of cue buffer, the end points to the first byte outside
   // the cue buffer (we will never try to access that byte)
   const BYTE* pStart = m_CueBuffer;
   const BYTE* pEnd = pStart + MAIN_DMX_CHANNEL_BUFFER_COUNT;

   // current and next pointer for byte compare
   const BYTE* pCurrent = pStart;
   const BYTE* pNext = pStart + 1;

   // while not reached end of buffer
   while( pStart < pEnd )
   {
      bool match = false;

      // do the first two bytes match
      if( *pCurrent == *pNext )
      {
         match = true;

         // read until the bytes don't match anymore, or we reach the 
         // 128 length limit (7 bits). Or until we reach the end of the cue
         // buffer
         while(( pNext < pEnd ) && 
               ( *pCurrent == *pNext ) &&
               (( pNext - pStart ) < 128 ))
               
         {
            pCurrent++;
            pNext++;
         }
      }
      // the first two bytes don't match
      else
      {
         // read until the bytes match again, or we reach the 
         // 128 length limit (7 bits). Or until we reach the end of the cue
         // buffer
         while(( pNext < pEnd ) &&
               ( *pCurrent != *pNext ) &&
               (( pNext - pStart ) < 128 ))
         {
            pCurrent++;
            pNext++;
         }

         // did we not reach the end of the stream and we are matching again
         if(( pNext < pEnd ) && ( *pCurrent == *pNext ))
         {
            // decrement the pointers again so that the new matching 
            // values can be stored in the next pattern block
            pCurrent--;
            pNext--;
         }
      }

      // now the block from start to current is exactly the byte block 
      // which we want to save. If the match flag is true then that block
      // consists of bytes with the same value. If not then the byte block
      // has all different values.

      // length of the byte block, not exceeding 128
      int length = pNext - pStart;

      // save the length in the flag byte,
      // substract one from the length so that we can save the value in 7 
      // bits. 0 means length 1, 127 means length 128, length of zero is
      // not valid (we always have at least one byte).
      BYTE flagByte = (BYTE) (length - 1);

      // set first bit if the bytes match
      if( match )
         flagByte |= 0x80;

      // write the flag byte to the stream
      if( pStream->Write( &flagByte, 1, NULL ) != S_OK )
         return false;

      // do we have matching bytes
      if( match )
      {
         // write only one byte with the one and only byte
         if( pStream->Write( pStart, 1, NULL ) != S_OK )
            return false;
      }
      else
      {
         // write the entire byte block, which consists of all non-matching
         // bytes
         if( pStream->Write( pStart, length, NULL ) != S_OK )
            return false;
      }

      // advance to the next block
      pStart = pNext;
      pCurrent = pStart;
      pNext = pStart + 1;
   }

   return true;
}

#endif

/*----------------------------------------------------------------------------
   Cue::LoadBuffer

   Read the cue buffer from the stream and encode it. See SerializeBuffer()
   for a description of the decoding.

   Returns: 
----------------------------------------------------------------------------*/

bool 
Cue::LoadBuffer( ShowFile& show )
{
   // position into the cue buffer
   uint32 position = 0;

   // flag byte, the first bit indicates repeating patterns, see 
   // SeriazlieBuffer() for more details
   uint8 flagByte = 0;

   uint32 bytesRead = 0;

   // as long as we can read the next flag byte and we don't exceed the
   // maximum of the cue buffer
   while(( show.ReadBytes( &flagByte, 1, bytesRead )) &&
         ( bytesRead == 1 ) &&
         ( position < MAIN_DMX_CHANNEL_BUFFER_COUNT ))
   {
      // extract the length from the flag byte, the length consists of the
      // 7 least significant bits of the flag byte plus one
      uint32 length = ( flagByte & 0x7F ) + 1;

      // double check that the current position plus the new length doesn't
      // exceed the cue buffer
      if(( position + length ) > MAIN_DMX_CHANNEL_BUFFER_COUNT )
         return false;

      // is the most significant bit set (the flag)
      if(( flagByte & 0x80 ) == 0x80 )
      {
         // we have a repeating pattern and the next byte represents the 
         // pattern, read it.
         uint8 patternByte = 0;
         if (! show.ReadBytes( &patternByte, 1, bytesRead ))
            return false;

         if( bytesRead != 1 )
            return false;

         // duplicate the pattern bytes and copy it to the cue buffer
         for( uint32 index = 0; index < length; index++ )
            m_CueBuffer[position + index] = patternByte;
      }
      // flag not set
      else
      {
         // if the flag is not set then the bytes have to be copied directly
         // to the cue buffer
         if(! show.ReadBytes( &m_CueBuffer[position], length, bytesRead))
            return false;

         if( bytesRead != length )
            return false;
      }

      // advance position
      position += length;
   }

   // double check if we filled the cue buffer completely
   if( position != MAIN_DMX_CHANNEL_BUFFER_COUNT  &&
	   position != (MAIN_DMX_CHANNEL_BUFFER_COUNT >> 2))	// Old files
      return false;

   return true;
}









