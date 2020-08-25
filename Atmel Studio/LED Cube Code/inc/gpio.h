/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                   gpio.h                              *
 *                                                       *
 * This file contains the macros for setting IO pins.    *
 *                                                       *
 *                                                       *
 * By: Marius C. K. Gulbrandsen                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Header Guard
//---------------------------------
#ifndef __GPIO_H__
#define __GPIO_H__

// Includes
//---------------------------------
#include <avr/io.h>

// Defines
// -------------------------------------------
// Bitmask for extracting the correct part of the pattern
#define PORT_B_MASK 0x3F00
#define PORT_C_MASK 0xC000
#define PORT_D_MASK 0x00FF

// Shifts correct values from pattern buffer to port-variables
#define SHIFT_PORT_B 8
#define SHIFT_PORT_C 10

// Bitmask for the correct plane IO output
#define PLANE1_MASK 0x01
#define PLANE2_MASK 0x02
#define PLANE3_MASK 0x04
#define PLANE4_MASK 0x08

// Number of planes in cube
#define NR_OF_PLANES 4

// Base Frequency of LED cube
#define FREQUENCY 50

// Minimum possible time variable
#define MIN_PATTERN_TIME 10

// Index of pattern table buffer time variable
#define TIME_IDX 4

// Function Prototypes
// -------------------------------------------
void gpio_init();

#endif