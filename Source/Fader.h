/*
   Module Description:

      Faders are included in the console. They can be either submasters,
      x/y faders or chasers. They have two main elements, one is the fader
      level and one is a cue pointer.

      The update functions get called from the console and get redirected
      to the associated cue.
*/


#ifndef _FADER_H_
#define _FADER_H_

// Includes ..................................................................

#include "../JuceLibraryCode/JuceHeader.h"

class Cue;


// Defines ...................................................................

// we use those defines when we sum the channels. The maximum level has can't 
// be larger than 16bit and has to be a 2-increment so that we can shift it.
const int FADER_MAX_LEVEL = 8192;
const int FADER_BIT_SHIFT = 13;


// Data Types ................................................................

// Class Definition ..........................................................

class Fader
{
   public:

      Fader();
      ~Fader();

      // Public Interface ....................................................

      // Level/Cue Access
      inline int FaderGetLevel() const { return m_Level; };
      inline void FaderSetLevel( int level ) { m_Level = level; };

      int FaderGetCueNumber() const;
      bool FaderSetCue( Cue* cue );
      void FaderClearCue( int cueNumber );
      
      // Update
      void FaderUpdateBuffer( uint8* pOutputBuffer, int GMLevel );
		void FaderCalculateEffects();
      void FaderUpdateEffects( uint8* pOutputBuffer );
      void FaderAdvanceEffectPosition( unsigned int updateID );


   private:

      // Private Functions ...................................................

      // Private Members .....................................................

      // fader level
      int m_Level;
      
      // the cue pointer is always valid. If no 'real' cue is assigned we
      // assign a dummy cue.
      Cue* m_pCue;
};


#endif // _FADER_H_

