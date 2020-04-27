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
	// Set up TIMER1 clock to system clock, prescaler = 64
	TCCR1B &= ~(1 << CS12);
	TCCR1B |=  (1 << CS11);
	TCCR1B |=  (1 << CS10);
	
	// Set compare match value, triggers interrupt every 1ms
	OCR1A = 250; 
	
	// Enable compare match interrupt
	TIMSK1 |= (1 << OCIE1A);
	
	// Global interrupt enable
	sei();    
}