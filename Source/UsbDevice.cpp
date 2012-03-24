/*
    UsbDevice.cpp

    (Semi) Generic USB Device Access
*/

#include "UsbDevice.h"

#if JUCE_MAC || JUCE_LINUX
  #include "Native/UsbDevice_Unix.cpp"
#elif JUCE_WINDOWS
  #include "Native/UsbDevice_Win.cpp"
#endif

