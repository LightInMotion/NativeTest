/*
   File Info:

      $Workfile:   Fader.cpp  $
      $Author:   JOE  $
      $Revision:   1.0  $
      $Modtime:   25 Aug 2004 14:58:22  $

   Module Description:

      Faders are included in the console. They can be either submasters,
      x/y faders or chasers. They have two main elements, one is the fader
      level and one is a cue pointer.

      The update functions get called from the console and get redirected
      to the associated cue.
*/

// Includes ..................................................................

#include "Fader.h"
#include "Cue.h"
#include "CueManager.h"


// Local Defines .............................................................

// Local Data Types ..........................................................

// Public Interface ..........................................................

/*----------------------------------------------------------------------------
   Fader::Fader

   Constructor

   Returns: no return value
----------------------------------------------------------------------------*/

Fader::Fader()
   :  m_Level(0),
      m_pCue(NULL)
{
}


/*----------------------------------------------------------------------------
   Fader::~Fader

   Destructor

   Returns: no return value
----------------------------------------------------------------------------*/

Fader::~Fader()
{
}


// Initialize ..............................................................//

/*
   Initialize function, has to be called before calling any other functions
   get called. No cleanup function has to be called. Cleanup is done in 
   the desctructor.
*/

/*----------------------------------------------------------------------------
   Fader::FaderInitialize

   Initialize the fader. Assigns a dummy cue to the cue pointer.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Fader::FaderInitialize()
{
   // assign the dummy cue to the cue pointer
   m_pCue = MainGetCueManager()->CueManGetDummyCue();
   return true;
}


// Level/Cue Access ..........................................................

/*
   Access functions to the cues and the fader levels.
*/

/*----------------------------------------------------------------------------
   Fader::FaderGetCueNumber   

   get the cue asigned to the fader. 

   Returns: cue number
----------------------------------------------------------------------------*/

int 
Fader::FaderGetCueNumber() const
{
   //get the cue number
   return m_pCue->CueGetNumber();
}


/*----------------------------------------------------------------------------
   Fader::FaderSetCue   

   Assign a new cue to the fader.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Fader::FaderSetCue( int cueNumber )
{
   // assign new cue to the fader. If the cue number doesn't exist we receive
   // a dummy cue
   m_pCue = MainGetCueManager()->CueManGetCue( cueNumber );

   return true; // ???
}


/*----------------------------------------------------------------------------
   Fader::FaderClearCue   

   Clear the cue if it matches the givel cue number.

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Fader::FaderClearCue(
   int cueNumber,    // number for cue to remove from any faders
   Cue* pDummyCue )  // dummy cue pointer to replace any cue reference with
{
   // check if the cue matches the cue on the fader
   if( cueNumber == m_pCue->CueGetNumber())
   {
      // replace the cue pointer with the given dummy cue pointer. This 
      // ensures that the fader always has a valid cue pointer and never
      // has to validate the cue pointer.
      m_pCue = pDummyCue;
   }
}


// Update ....................................................................

/*
   The update functions get called from the console to update the the output
   buffer. The update functions get called every 33ms to reflect any changes
   in fader values or cue assignments to the faders.
*/
      
/*----------------------------------------------------------------------------
   Fader::FaderUpdateBuffer   

   Calls CueUpdateBuffer() on the assigned cue. 

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Fader::FaderUpdateBuffer( 
   BYTE* pOutputBuffer,
   int GMLevel )        // grand master level
{
   // In the function Console::SortFaders() all faders with the value zero
   // are already sorted out, therefor we don't need to check here if the
   // fader level is zero.

   // we precalculate the fader level with the given grand master level and
   // pass both values to the Cue/Device/Control. If a control is grand master
   // controlled (currently only the FaderControl is), then it can use the
   // precalculated GM value instead of the fader value.

   int GMAdjustedLevel = GMLevel * m_Level;
   GMAdjustedLevel = GMAdjustedLevel >> FADER_BIT_SHIFT;

   // call the update function on the cue, pass the fader level and the 
   // precalculated GM fader level.
   m_pCue->CueUpdateBuffer( pOutputBuffer, m_Level, GMAdjustedLevel );
}


/*----------------------------------------------------------------------------
   Fader::FaderCalculateEffects   

   Calls CueUpdateEffects() on the assigned cue 

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Fader::FaderCalculateEffects( )
{
   // call the update effect function on the cue
   m_pCue->CueCalculateEffects( m_Level );
}

/*----------------------------------------------------------------------------
   Fader::FaderUpdateEffects   

   Calls CueUpdateEffects() on the assigned cue 

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Fader::FaderUpdateEffects( BYTE* pOutputBuffer )
{
   // call the update effect function on the cue
   m_pCue->CueUpdateEffects( pOutputBuffer, m_Level );
}


/*----------------------------------------------------------------------------
   Fader::FaderAdvanceEffectPosition   

   Calls CueAdvanceEffectPosition on the assigned cue

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Fader::FaderAdvanceEffectPosition( unsigned int updateID )
{
   // call the advance position on the cue.
   m_pCue->CueAdvanceEffectPositions( updateID );
}



// Private Functions .........................................................

/*----------------------------------------------------------------------------

   Returns:
----------------------------------------------------------------------------*/

