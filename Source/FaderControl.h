/*
   File Info:

      $Workfile:   FaderControl.h  $
      $Author:   JOE  $
      $Revision:   1.0  $
      $Modtime:   08 Mar 2005 13:56:56  $

   Module Description:

      The fader control is derived from the Control class. The fader control
      represents a fader which can represent either one DMX channel or two 
      DMX channel. It can also represent a partial DMX channel by setting
      the minimum and/or maximum value for the fader.
      The UIFaderControl is the visual representation of the FaderControl
      and gets all its values from the FaderControl when displayed.
*/


#ifndef _FADER_CONTROL_H_
#define _FADER_CONTROL_H_

// Includes ..................................................................

#include "Control.h"


// Defines ...................................................................

// Data Types ................................................................

// Class Definition ..........................................................

class FaderControl : public Control
{
   public:

      FaderControl();
      FaderControl( bool use2Channels,
                    UINT highChannelOffset,
                    UINT lowChannelOffset,
                    int minValue,
                    int maxValue,
                    bool reverse,
                    bool GMControlled );

      virtual ~FaderControl();

      // Public Interface ....................................................

      virtual Control* ControlClone() const;
      virtual ControlType ControlGetType() const;
      virtual void ControlGetUsedChannels( std::vector<int>& channels,
                                           bool getSubcontrols ) const;

      virtual void ControlUpdateBuffer( const BYTE* pCueBuffer,
                                        BYTE* pOutputBuffer,
                                        int faderLevel,
                                        int GMAdjustedLevel );

      void FadConGetValues( bool& is2Channel, 
                            UINT& highChannelOffset,
                            UINT& lowChannelOffset,
                            int& minValue,
                            int& maxValue,
                            bool& reverse,
                            bool& GMControlled ) const;

      // save/load
      virtual bool ControlSerialize( IStream* pStream ) const;
      virtual bool ControlLoad( IStream* pStream, DWORD version );

      virtual void ControlCorrectSnapshotValues( BYTE* pCueBuffer ) const;


   private:

      // Private Functions ...................................................

      // Private Members .....................................................

      // flag to indicate if we use two or one channel for the fader control.
      // If the flag is false we only use the low channel offset
      bool m_2Channels;

      // the channel offset gets added to the device base address to get the
      // absolute channel of the fader control. The high channel offset is
      // only valid if the m_2Channels flag is set to true.
      UINT m_HighChannelOffset;
      UINT m_LowChannelOffset;

      // minimum and maximum value.
      int m_MinValue;
      int m_MaxValue;

      // flag to indicate if it is a reverse fader. A reverse fader fades in
      // from the maximum to the minimum.
      bool m_IsReverseFader;

      // a fader control can be grand master controlled or not, it is GM
      // controlled by default.
      bool m_GMControlled;
};


#endif // _FADER_CONTROL_H_

