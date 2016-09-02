/*
    Module Description:

    The select control is derived from the Control class. It is used for
    DMX channels with fixed values like a gobo wheel or a color wheel.
    A select control always represents exactly one DMX channel. Each value
    has a description and can be displayed with a UISelectControl which is
    the extented version of a Combobox.
*/


#ifndef _SELECT_CONTROL_H_
#define _SELECT_CONTROL_H_

// Includes ..................................................................

#include "Control.h"


// Defines ...................................................................

// Data Types ................................................................

// the select value is one entry in a select control.
class SelectValue
{
public:
    SelectValue() : m_Value(0) {};
    SelectValue (uint8 value, String description)
        : m_Value (value), m_Description (description) {};
    ~SelectValue() {};

    bool operator== (const SelectValue& value) const
    {
        if((value.m_Value == m_Value) && (value.m_Description == m_Description))
            return true;

        return false;
    };

    // DMX value and description, the description is only used for display to
    // give the user a meaningful description to the (hex) DMX value.
    uint8 m_Value;
    String m_Description;
};


// Class Definition ..........................................................

class SelectControl : public Control
{
public:

    SelectControl();
    SelectControl (uint32 channelOffset, const Array<SelectValue>& values);
    virtual ~SelectControl();

    // Public Interface ....................................................

    // virtual function from Control
    virtual Control* ControlClone() const;
    virtual ControlType ControlGetType() const;
    virtual void ControlGetUsedChannels (Array<int>& channels,
                                         bool getSubcontrols ) const;

    virtual void ControlUpdateBuffer (const uint8* pCueBuffer,
                                      uint8* pOutputBuffer,
                                      int faderLevel,
                                      int GMAdjustedLevel);
    // save/load
//    virtual bool ControlSerialize( IStream* pStream ) const;
    virtual bool ControlLoad (ShowFile& show, uint32 version);

      // get/set values
    void getValues (uint32& channelOffset,
                    Array<SelectValue>& values) const;

    void setValues (uint32 channelOffset,
                    const Array<SelectValue>& values );


private:

    // Private Functions ...................................................

    // Private Members .....................................................

    // channel offset from the device base address
    uint32 m_ChannelOffset;

    // vector of all values, containing each a Hex value and a description
    Array<SelectValue> m_Values;
};


#endif // _SELECT_CONTROL_H_

