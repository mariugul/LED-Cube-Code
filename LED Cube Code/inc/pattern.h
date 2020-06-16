#ifndef __PATTERN_H_
#define __PATTERN_H_

#include <avr/pgmspace.h>  // Store patterns in program memory

// Pattern that LED cube will display
//---------------------------------
const PROGMEM uint16_t pattern_table[] = {
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 250,
	//0x0000, 0x0000, 0x0000, 0x0000, 250,
};


#endif