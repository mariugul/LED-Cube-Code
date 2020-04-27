/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                   pattern.h                           *
 *                                                       *
 * This file contains the patterns that the cube will    *
 * display.                                              *
 *                                                       *
 * By: Marius C. K. Gulbrandsen                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Header Guard
//---------------------------------
#ifndef __PATTERN_H__
#define __PATTERN_H__

// Includes
//---------------------------------
#include <stdint.h>
#include <avr/pgmspace.h>  // Store patterns in program memory

// Pattern that LED cube will display
//---------------------------------        
const PROGMEM uint16_t pattern_table[][5] = {
	{0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1},
	{0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x2},
	{0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x3},
	{0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x3},
	
};
	
#endif



