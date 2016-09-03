/*
    Module Description:

    The effect data entry is used in the cue to associate a effect data
    object (which points to an effect pattern) with an position control.

    The position control (more precisely the UIPositionControl) adds and
    removes effect data entries to the cue by calling CueAddEffectData()
    and CueRemoveEffectData().
*/


#ifndef _EFFECT_DATA_ENTRY_H_
#define _EFFECT_DATA_ENTRY_H_

// Includes ..................................................................

#include "../JuceLibraryCode/JuceHeader.h"
#include "ShowFile.h"
#include "Device.h"
#include "EffectPattern.h"

class Control;
class EffectData;


// Defines ...................................................................

// Data Types ................................................................

// Class Definition ..........................................................

class EffectDataEntry
{
public:

    EffectDataEntry();
    EffectDataEntry (Control* pControl,
                     EffectData* pEffectData);

    ~EffectDataEntry();

    // public functions ....................................................

    // load/serialize
    bool EffDatEntryLoad (ShowFile& show, uint32 version,
                          const OwnedArray<Device>& devices,
                          const OwnedArray<EffectPattern>& patterns);
//    bool EffDatEntrySerialize( IStream* pStream ) const;


    // public members ......................................................

    Control* m_pControl;
    ScopedPointer<EffectData> m_pEffectData;
};

#endif // _EFFECT_DATA_ENTRY_H_

