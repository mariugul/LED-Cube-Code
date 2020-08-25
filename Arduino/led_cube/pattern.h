#ifndef __PATTERN_H__
#define __PATTERN_H__

// Includes
//---------------------------------
#include <stdint.h>        // Use uint_t
#include <avr/pgmspace.h>  // Store patterns in program memory

// Pattern that LED cube will display
//--------------------------------- 
const PROGMEM uint16_t pattern_table[] = {
     // Blink all LEDs every 250ms
     0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 250,
     0x0000, 0x0000, 0x0000, 0x0000, 250,
};
#endif
