/*
   File Info:

      $Workfile:   EffectManager.h  $
      $Author:   JOE  $
      $Revision:   1.0  $
      $Modtime:   12 Jul 2004 09:20:50  $

   Module Description:

      The effect manager loads and manages EffectPattern (simple
      vector graphic) objects.  Currently effects are loaded
      at Initialization and released at shutdown, but the current
      design should support pattern serialization.

      All patterns are currently loaded from Structured Storage
      files from a directory obtained from the Registry module.

      In normal operation, the Cue Object obtains an effect pattern
      from this manager, then passes it to a control, along with settings,
      in a EffectData object.  The control, in turn, uses an Effect
      object (see Effect.cpp) to execute the pattern and settings as
      an offset to an XY coordinate pair.
*/

#ifndef _EFFECT_MANAGER_H_
#define _EFFECT_MANAGER_H_

// Includes ..................................................................

#include <vector>
#include "effect.h"        // We need EffectData and EffectPattern

// Defines ...................................................................

// Data Types ................................................................

// Class Definition ..........................................................

class EffectManager
{
   public:

      EffectManager();
      ~EffectManager();

      // Public Interface ....................................................

      // initialize
      bool EffectManInitialize();

      // Pattern access
      int EffectManGetPatternCount() const;
      EffectPattern* EffectManGetPattern(int index);
      EffectPattern* EffectManGetPattern(const GUID& guid);

      // Rotate and Scale for display
      bool EffectManTransform(WORD xPos, WORD yPos, EffectData *pEffectData, 
         const RECT& rect, const int count, POINT *pPoints);

      bool EffectManTransform(WORD xPos, WORD yPos, 
         std::vector <EffectData *> effectDataList,
         std::vector <int *> faderList, 
         const RECT& rect, const int count, POINT *pPoints);

   private:

      // Private Functions ...................................................

      // Folder Enumeration
      bool LoadAllEffectPatterns( LPCTSTR pFolder );


      // Private Members .....................................................

      // template folders
      std::vector< EffectPattern* > m_EffectPatternList;
};

#endif // _EFFECT_MANAGER_H_

