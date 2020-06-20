/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                   gpio.h                              *
 *                                                       *
 * This file contains the macros for setting IO pins.    *
 *                                                       *
 *                                                       *
 * By: Marius C. K. Gulbrandsen                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 

#include "../inc/gpio.h"
#include <avr/io.h>

void gpio_init()
{
	// Set the I/O pins to OUTPUT
	DDRB = 0x3F; // Sets 6 pins on port B --> 0x3F is binary 0011 1111
	DDRC = 0x3F; // Sets 6 pins on port C
	DDRD = 0xFF; // Sets 8 pins on port D
}

void gpio_all_off()
{
	// Turn all LED's off
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
}