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

// Typedefs
//---------------------------------
enum {PLANE1, PLANE2, PLANE3, PLANE4};

// Macros for setting pins
//---------------------------------
#define SET(PORTX, N) (PORTX |=  (1 << N)) // Set a pin HIGH
#define CLR(PORTX, N) (PORTX &= ~(1 << N)) // Clear a pin to LOW

// Decodes what port the pin belongs to and sets it
#define SET_LED(IDX, PIN)										\
	({															\
		if      (IDX >= 0 && IDX <= 7)  PORTD |= (1 << PIN);	\
		else if (IDX > 7 && IDX <= 13)  PORTB |= (1 << PIN);	\
		else if (IDX > 13 && IDX <= 15)	PORTC |= (1 << PIN);	\
	})
			
// Connect plane to ground
#define SET_PLANE(PLANE)								\
({														\
	if      (PLANE == PLANE1)  PORTC |= (1 << PINA0);   \
	else if (PLANE == PLANE2)  PORTC |= (1 << PINA1);   \
	else if (PLANE == PLANE3)  PORTC |= (1 << PINA2);	\
	else if (PLANE == PLANE4)  PORTC |= (1 << PINA3);	\
})


// Define pins to Arduino numbering
//---------------------------------
#define LEDPIN 5 // Test LED speed 

// PORTB 
#define PIN13 5
#define PIN12 4
#define PIN11 3
#define PIN10 2
#define PIN9  1
#define PIN8  0

// PORTD
#define PIN7 7
#define PIN6 6
#define PIN5 5
#define PIN4 4
#define PIN3 3
#define PIN2 2
#define PIN1 1
#define PIN0 0

// PORTC
#define PINA5 5
#define PINA4 4
#define PINA3 3
#define PINA2 2
#define PINA1 1
#define PINA0 0

// Define PORT indexes for knowing which port the pin numbers relate to
//---------------------------------
#define PORTD_IDX 7  // The first 7 pins belong to PORTD
#define PORTB_IDX 13 // The next 6 pins belong to PORTB
#define PORTC_IDX 15 // The next 2 pins belong to PORTC

#endif