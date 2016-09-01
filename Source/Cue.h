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


#ifndef _CUE_H_
#define _CUE_H_

// Includes ..................................................................

#include "../JuceLibraryCode/JuceHeader.h"
#include "ShowFile.h"
#include "Main.h"
//#include "Effect.h"
//#include "EffectDataEntry.h"

class Device;
class Control;


// Defines ...................................................................

// maximum cue number
static const int CUE_MAXIMUM_NUMBER = 1000000;


// Data Types ................................................................

// Class Definition ..........................................................

class Cue
{
   public:

      Cue();
      Cue( int number );
      ~Cue();

      // Public Interface ....................................................

      // member access
      String CueGetName() const;
      void CueSetName( String name );
      int CueGetNumber() const;
      void CueSetNumber( int number );
      String CueGetDescription() const;
      void CueSetDescription (String description);

      uint8* CueGetBuffer();

      // update functions
      void CueUpdateBuffer( uint8* pOutputBuffer,
                            int faderLevel, 
                            int GMAdjustedLevel );

//      void CueCalculateEffects( int faderLevel );
//      void CueUpdateEffects( BYTE* pOutputBuffer, int faderLevel );
//      void CueAdvanceEffectPositions( UINT updateID );

      // device access
      int CueGetDeviceCount() const;
      Device* CueGetDevice( int index ) const;

      void CueAddDevice( Device* pDevice );
      void CueRemoveDevice( Device* pDevice );
      void CueMoveDevice( const Device* pDevice, 
                          int oldAddress, 
                          int newAddress );
      bool CueIsDeviceInUse( const Device* pDevice ) const;

      // save/load
//      bool CueSerialize( IStorage* pStorage ) const;
      bool CueLoad( ShowFile& show, uint32 version, const OwnedArray<Device>& devicelist );

      Cue* CueClone( int newNumber ) const;

      // effect data access
//      EffectData* CueAddEffectData( Control* pControl,
//                                    EffectPattern* pPattern );

//      void CueRemoveEffectData( const Control* pControl );
//      EffectData* CueFindEffectData( const Control* pControl ) const;


    static Cue dummy; // An empty cue
    
   private:

      // Private Functions ...................................................

      // save/load subfunctions
//      bool SerializeInfo( IStorage* pStorage ) const;
      bool LoadInfo( ShowFile& show,
                     uint32& deviceCount,
                     uint32& effectCount );

//      bool SerializeDevices( IStorage* pStorage ) const;
      bool LoadDevices (ShowFile& show, uint32 deviceCount, const OwnedArray<Device>& devicelist);
//      bool SerializeEffects( IStorage* pStorage ) const;
      bool LoadEffects (ShowFile& show, uint32 effectCount, uint32 version );

      // save/load buffer
//      bool SerializeBuffer( IStream* pStream ) const;
      bool LoadBuffer (ShowFile& show);


      // Private Members .....................................................

      // name and description of the cue.
      String m_Name;
      String m_Description;

      // cue number, has to be unique. Can't be changed once the cue is
      // created. Although the cue can be duplicated/cloned using a different
      // cue number
      int m_Number;

      // the cue buffer. It contains all the settings for that cue. The 
      // controls know what the values 'mean' and can modify them.
      uint8 m_CueBuffer[ MAIN_DMX_CHANNEL_BUFFER_COUNT ];

      // we use std::vector instead of std::list because access it is much 
      // faster (shown in performance tests)

      // vector of devices in this cue
      Array<Device*> m_DeviceList;

      // vector of effect data entries. 
//      Array<EffectDataEntry> m_EffectDataList;
};

#endif // _CUE_H_

