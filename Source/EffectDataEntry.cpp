/*
    Module Description:

    The effect data entry is used in the cue to associate a effect data
    object (which points to an effect pattern) with an position control.

    The position control (more precisely the UIPositionControl) adds and
    removes effect data entries to the cue by calling CueAddEffectData()
    and CueRemoveEffectData().
*/

// Includes ..................................................................

#include "EffectDataEntry.h"
//#include "DeviceManager.h"
#include "effect.h"
#include "Main.h"
#include "Device.h"
#include "Control.h"


// Local Defines .............................................................

// Local Data Types ..........................................................

// Public Interface ..........................................................

/*----------------------------------------------------------------------------
    EffectDataEntry::EffectDataEntry

    Constructor

    Returns: no return value
----------------------------------------------------------------------------*/

EffectDataEntry::EffectDataEntry() 
    : m_pControl (nullptr),
      m_pEffectData (nullptr)
{
}


/*----------------------------------------------------------------------------
    EffectDataEntry::EffectDataEntry

    Constructor taking parameters

    Returns: no return value
----------------------------------------------------------------------------*/

EffectDataEntry::EffectDataEntry (Control* pControl,
                                  EffectData* pEffectData)
    : m_pControl (pControl),
      m_pEffectData (pEffectData)
{
}


/*----------------------------------------------------------------------------
    EffectDataEntry::~EffectDataEntry

    Destructor

    Returns: no return value
----------------------------------------------------------------------------*/

EffectDataEntry::~EffectDataEntry()
{
}


// public functions ..........................................................

// load/serialize ............................................................
/*
    The effect data entries get serialized and loaded from the Cue.
    ! It is very important that all devices and controls get loaded in the
    exact same order as they get serialized to keep the indices identical.
    This is essential because we save convert the position control pointer
    in the effect data entry into a valid control index and device index.
    (since we can't save pointers in a show file) !

    In order to lock up the correct indices we also have to make sure that
    all devices and controls get loaded BEFORE loading the cues and its
    effect datas.
*/

/*----------------------------------------------------------------------------
    EffectDataEntry::EffDatEntryLoad

    Load the effect data entry associated with the cue. If the effect data
    points to an effect which does not exist (that should never happen, since
    we provide fixed effect pattern with our official release) then this
    function will fail.

    Returns: true or false
----------------------------------------------------------------------------*/

bool 
EffectDataEntry::EffDatEntryLoad (ShowFile& show,
                                  uint32 version,
                                  const OwnedArray<Device>& devices,
                                  const OwnedArray<EffectPattern>& patterns)

{
    // each effect data has a pointer to a position control. The
    // position control belongs to a device. Therefor we saved the
    // device index and the control index which identifies the
    // position control. We will load both those indices and
    // validate them and find the correlating positon control

    int deviceIndex = 0;
    int controlIndex = 0;

    // load the device index
    if (! show.readInt (deviceIndex))
        return false;

    // load control index
    if (! show.readInt (controlIndex))
        return false;

    // get device count
    int deviceCount = devices.size();

    // validate the device index
    if (( deviceIndex < 0 ) || ( deviceIndex >= deviceCount))
        return false;

    // get the device pointer from the device manager
    Device* pDevice = devices[deviceIndex];

    // get the control count
    int controlCount = pDevice->DeviceGetControlCount();

    // validate the control index
    if (( controlIndex < 0 ) || ( controlIndex >= controlCount))
        return false;

    // get the control pointer from the device and assign it to our member
    m_pControl = pDevice->DeviceGetControl (controlIndex);

    // double check that it is a position control
    if (m_pControl->ControlGetType() != CT_POSITION)
        return false;

    // create empty effect data object
    ScopedPointer<EffectData>pEffectData = new EffectData;
    if (! pEffectData )
        return false;

    // load the effect data
    if (! pEffectData->EffectDataLoad (show, version, patterns))
        return false;

    // assign the new effect data to our member
    m_pEffectData = pEffectData;
    pEffectData.release();

    return true;
}

#if 0
/*----------------------------------------------------------------------------
   EffectDataEntry::EffDatEntrySerialize

   Serialize the effect data entry to a stream (structure storage file).

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
EffectDataEntry::EffDatEntrySerialize( IStream* pStream ) const
{
   int deviceIndex = 0;
   int controlIndex = 0;

   // we have the position control pointer in the effect data entry for
   // faster access during the main update. Therefor we need to find
   // the correlating device index and control index from the device
   // manager.

   if( ! MainGetDeviceManager()->DevManFindPositionControl( m_pControl,
                                                            deviceIndex,
                                                            controlIndex ))
      return false;

   // save the device index in the file
   if( ! FileHelpWriteInt( pStream, deviceIndex ))
      return false;

   // save control index
   if( ! FileHelpWriteInt( pStream, controlIndex ))
      return false;

   // save effect data
   if( ! m_pEffectData->EffectDataSerialize( pStream ))
	   return false;

   return true;
}

#endif


