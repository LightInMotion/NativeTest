/*
    Module Description:

    The mode control is derived from the Control class. It is similar
    to a property page, as it has multiple 'pages'. Each page can contain
    multiple sub-controls which get only updated when the mode control
    switches to the particular page.
*/


#ifndef _MODE_CONTROL_H_
#define _MODE_CONTROL_H_

// Includes ..................................................................

#include "Control.h"


// Defines ...................................................................

// Data Types ................................................................

// the mode page contains all information of one page in a mode control.
class ModePage
{
public:
   // constructor/destructor
    ModePage() : m_Value (0), m_RangeLow (0), m_RangeHigh(0) {};
    ModePage (uint8 value, uint8 rangeLow, uint8 rangeHigh, String description )
        : m_Value (value), m_RangeLow (rangeLow), m_RangeHigh (rangeHigh),
          m_Description (description) {};
    ~ModePage(){};

   // the value of the page, must be non-zero for the update function
   // to work properly
   uint8 m_Value;

   // we also save the range of the page, this is used in case we don't
   // have a mode channel.
   uint8 m_RangeLow;
   uint8 m_RangeHigh;

   // label/description of the page
   String m_Description;

   // subcontrols
   OwnedArray<Control> m_Controls;
};


// Class Definition ..........................................................

class ModeControl : public Control
{
public:

    ModeControl();
    ModeControl (bool hasModeChannel, uint32 channelOffset);
    virtual ~ModeControl();

    // Public Interface ....................................................

    // virtual function from Control
    virtual Control* ControlClone() const;
    virtual ControlType ControlGetType() const;
    virtual void ControlGetUsedChannels (Array<int>& channels,
                                         bool getSubcontrols) const;

    virtual void ControlSetAddress (uint32 baseAddress);

    virtual void ControlUpdateBuffer (const uint8* pCueBuffer,
                                        uint8* pOutputBuffer,
                                        int faderLevel,
                                        int GMAdjustedLevel);
    // save/load
//    virtual bool ControlSerialize( IStream* pStream ) const;
    virtual bool ControlLoad (ShowFile& show, uint32 version );

    virtual void ControlCorrectSnapshotValues (uint8* pCueBuffer) const;

    // get/set values
    void getValues (bool& hasModeChannel,
                    uint32& channelOffset,
                    Array<ModePage*>& pages) const;

    void addModePage (ModePage* pNewPage);
      
private:

    // Private Functions ...................................................

    bool LoadPageControls (ShowFile& show,
                           uint32 version,
                           ModePage* pModePage);


    // Private Members .....................................................

    // a mode control always works on one DMX channel. It can use that
    // channel either exclusively to 'switch' the value, or it can just
    // use that channel as to determine on which page it is. In the later
    // case this flag is set to false. This flag is used in the update
    // function.
    bool m_HasModeChannel;

    // channel offset from the device base address
    uint32 m_ChannelOffset;

    // vector of mode pages.
    OwnedArray<ModePage> m_Pages;
};


#endif // _MODE_CONTROL_H_

