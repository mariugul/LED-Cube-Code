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
	// Set up timer interrupt
	OCR1A = 39;						     // 39 gives 2.5ms interrupts with 1024 prescaler = 10ms patterns and 50Hz
	TCCR1B |= (1 << WGM12);				 // Mode 4, CTC on OCR1A
	TIMSK1 |= (1 << OCIE1A);			 // Set interrupt on compare match
	TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024 and start the timer
	
}

void global_interrupt_enable()
{
	// Enable Global Interrupts
	sei();
}

void global_interrupt_disable()
{
	// Disable Global Interrupts
	cli();
}