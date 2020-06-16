/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                     timer.c                           *
 *                                                       *
 * This file initializes the timer for use of interrupts *
 *                                                       *
 *                                                       *
 * By: Marius C. K. Gulbrandsen                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// Includes
//---------------------------------
#include "../inc/timer.h"
#include <avr/interrupt.h>

// Defines
//---------------------------------

// Function Definitions
//---------------------------------
void timer_init()
{
	//OCR1A = 0x3D08;
	OCR1A = 156; // 10ms with 1024 prescaler

	// Mode 4, CTC on OCR1A
	TCCR1B |= (1 << WGM12);

	//Set interrupt on compare match
	TIMSK1 |= (1 << OCIE1A);
	
	// Set prescaler to 1024 and start the timer
	TCCR1B |= (1 << CS12) | (1 << CS10);
	
	// Global interrupt enable
	sei();
}
