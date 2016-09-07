/*
    DMX.h
    
    Basic DMX Defines
*/


#ifndef _DMX_H_
#define _DMX_H_

// Includes ..................................................................


// Defines ...................................................................

// DMX channel constants
const int DMX_UNIVERSE_COUNT = 64;
const int DMX_CHANNELS_PER_UNIVERSE = 512;

const int DMX_CHANNEL_BUFFER_COUNT = DMX_UNIVERSE_COUNT 
                                     * DMX_CHANNELS_PER_UNIVERSE;
const int DMX_CHANNEL_UPDATE_BUFFER_COUNT = DMX_CHANNEL_BUFFER_COUNT * 2;


// Data Types ................................................................


// Public Functions ..........................................................


#endif // _DMX_H_

