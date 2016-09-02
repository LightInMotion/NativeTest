/*
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


// Local Defines .............................................................

// Local Data Types ..........................................................

// Public Interface ..........................................................

/*----------------------------------------------------------------------------
    Fader::Fader

    Constructor

    Returns: no return value
----------------------------------------------------------------------------*/

Fader::Fader()
    : m_Level (0),
      m_pCue (&Cue::dummy)
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


// Level/Cue Access ..........................................................

/*
    Access functions to the cues and the fader levels.
*/

/*----------------------------------------------------------------------------
    Fader::getCueNumber

    get the cue asigned to the fader.

    Returns: cue number
----------------------------------------------------------------------------*/

int 
Fader::getCueNumber() const
{
    //get the cue number
    return m_pCue->getNumber();
}


/*----------------------------------------------------------------------------
    Fader::setCue

    Assign a new cue to the fader.

    Returns: no return value
----------------------------------------------------------------------------*/

void
Fader::setCue (Cue* cue)
{
    // assign new cue to the fader, must exist.
    m_pCue = cue;
}

/*----------------------------------------------------------------------------
    Fader::clearCue

    Clear the cue if it matches the givel cue number.

    Returns: no return value
----------------------------------------------------------------------------*/

void 
Fader::clearCue (int cueNumber)    // number for cue to remove from any faders
{
    // check if the cue matches the cue on the fader
    if (cueNumber == m_pCue->getNumber())
    {
        // replace the cue pointer with the given dummy cue pointer. This
        // ensures that the fader always has a valid cue pointer and never
        // has to validate the cue pointer.
        m_pCue = &Cue::dummy;
    }
}

void
Fader::clearCue (Cue* cue)
{
    // Check for pointer match
    if (m_pCue == cue)
        m_pCue = &Cue::dummy;
}

void
Fader::clearCue()
{
    m_pCue = &Cue::dummy;
}

// Update ....................................................................

/*
    The update functions get called from the console to update the the output
    buffer. The update functions get called every 33ms to reflect any changes
    in fader values or cue assignments to the faders.
*/
      
/*----------------------------------------------------------------------------
    Fader::updateBuffer

    Calls updateBuffer() on the assigned cue.

    Returns: no return value
----------------------------------------------------------------------------*/

void 
Fader::updateBuffer (uint8* pOutputBuffer,
                     int GMLevel)  // grand master level
{
    // If we are zero, nothing to do
    if (! m_Level)
        return;
    
    // we precalculate the fader level with the given grand master level and
    // pass both values to the Cue/Device/Control. If a control is grand master
    // controlled (currently only the FaderControl is), then it can use the
    // precalculated GM value instead of the fader value.

    int GMAdjustedLevel = GMLevel * m_Level;
    GMAdjustedLevel = GMAdjustedLevel >> FADER_BIT_SHIFT;

    // call the update function on the cue, pass the fader level and the
    // precalculated GM fader level.
    m_pCue->updateBuffer (pOutputBuffer, m_Level, GMAdjustedLevel);
}


#if 0
/*----------------------------------------------------------------------------
   Fader::calculateEffects

   Calls CueUpdateEffects() on the assigned cue 

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Fader::calculateEffects( )
{
   // call the update effect function on the cue
   m_pCue->CueCalculateEffects( m_Level );
}

/*----------------------------------------------------------------------------
   Fader::updateEffects

   Calls CueUpdateEffects() on the assigned cue 

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Fader::updateEffects( BYTE* pOutputBuffer )
{
   // call the update effect function on the cue
   m_pCue->CueUpdateEffects( pOutputBuffer, m_Level );
}


/*----------------------------------------------------------------------------
   Fader::advanceEffectPosition

   Calls CueAdvanceEffectPosition on the assigned cue

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Fader::advanceEffectPosition( unsigned int updateID )
{
   // call the advance position on the cue.
   m_pCue->CueAdvanceEffectPositions( updateID );
}

#endif


// Private Functions .........................................................

/*----------------------------------------------------------------------------

    Returns:
----------------------------------------------------------------------------*/

