/*
    DemoDevice.cpp
 
    Bogus device for running without hardware
*/

#include "DemoDevice.h"


//==============================================================================
void DemoDevice::run()
{
    while (! threadShouldExit())
    {
        sleep (33);
        if (! threadShouldExit())
        {
            const ScopedLock lock (timeEventList.getLock());
        
            // Update Time !!!!
            int listSize = timeEventList.size();
            for (int n = 0; n < listSize; ++n)
                timeEventList[n]->signal();
        
        }
    }
}