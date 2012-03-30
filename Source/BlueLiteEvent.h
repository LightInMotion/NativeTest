/*
    BlueLiteEvent.h

    Reference Countable veersion of Waitable Event
*/

#ifndef __BLUELITEEVENT_H_C68B622E__
#define __BLUELITEEVENT_H_C68B622E__

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
 Make our own event object, which is reference counted so that
 it can't be deleted while we are still signalling it
 */
class BlueLiteEvent : public WaitableEvent, public ReferenceCountedObject
{
public:
    BlueLiteEvent() {}
    ~BlueLiteEvent() {}
    
    //==============================================================================    
    typedef ReferenceCountedObjectPtr<BlueLiteEvent> Ptr;
    
private:
    //==============================================================================
    JUCE_LEAK_DETECTOR(BlueLiteEvent)    
};




#endif  // __BLUELITEEVENT_H_C68B622E__
