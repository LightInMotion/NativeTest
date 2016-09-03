/*
   Module Description:

      This is the base class of all the derived control variations. The 
      virtual function ControlUpdateBuffer() has to be implemented by the
      derived control (unless the control has no DMX functionality like the
      label control).
*/


#ifndef _CONTROL_H_
#define _CONTROL_H_

// Includes ..................................................................


#include "../JuceLibraryCode/JuceHeader.h"
#include "ShowFile.h"
#include "Effect.h"


// Defines ...................................................................

// Data Types ................................................................

// The control type is used by the cue editor to determine the control type.
// Each UI control can represent multiple (core) controls.
// The control type is also used for saving/loading the controls. Don't change
// the numbering because when we serialize and load the control the numbering
// has to match exactly. When adding new types always add them to the end of
// the enumeration.
enum ControlType
{
   CT_SELECT   =  1,
   CT_FADER    =  2,
   CT_MODE     =  3,
   CT_SWITCH   =  4,
   CT_POSITION =  5,
   CT_LABEL    =  6
};


// Class Definition ..........................................................

class Control
{
   public:
      Control();
      virtual ~Control();

      // Public Interface ....................................................
    
      typedef Rectangle<int32> Position;

      Position ControlGetPosition() const;
      void ControlSetPosition (const Position& position);

      uint32 ControlGetAddress() const;
      virtual void ControlSetAddress (uint32 baseAddress );

      virtual void ControlUpdateBuffer (const uint8* pCueBuffer,
                                        uint8* pOutputBuffer,
                                        int faderLevel,
                                        int GMAdjustedLevel) = 0;

      virtual Control* ControlClone() const = 0;

      virtual ControlType ControlGetType() const = 0;
      virtual void ControlGetUsedChannels( Array<int>& channels,
                                           bool getSubcontrols ) const = 0;

      // name
      String ControlGetName() const;
      void ControlSetName (String name);

      // save/load
//      virtual bool ControlSerialize( IStream* pStream ) const;
      virtual bool ControlLoad (ShowFile& show, uint32 version);

      // effects (only used from position control)

      virtual void ControlCalculateEffect (EffectData* pEffectData,
                                           int faderLevel) {};
      virtual void ControlUpdateEffect (uint8* pOutputBuffer,
                                        EffectData* pEffectData,
                                        int faderLevel) {};
      virtual void ControlAdvanceEffectPosition (uint32 updateID) {};

      virtual void ControlCorrectSnapshotValues (uint8* pCueBuffer) const {};


   protected:

      // Protected Functions ...................................................

      void ControlCloneAllData (Control* pNewControl) const;


      // Protected Members .....................................................

      // position for visual representation, given in coordinates relative to 
      // the cue control view and template control view, respectively.
      // The position is NOT identical with the windows position if the
      // UI control is a nested UI control (e.g. used in the UIModeControl).
      Position m_Position;

      // base address of the device. See description of m_BaseAddress in 
      // Device.h for more detail.
      uint32 m_DeviceBaseAddress;

      // name
      String m_Name;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Control)
};

#endif // _CONTROL_H_

