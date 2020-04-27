/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                   LED CUBE                            *
 *                                                       *
 * Control a 4x4x4 LED cube with low power consumption   *
 * in embedded C.                                        *
 *                                                       *
 * By: Marius C. K. Gulbrandsen                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// CPU speed for <delay.h>
//---------------------------------
#define F_CPU 16000000UL // Clock speed for delay (declare before util/delay.h)
#define BAUDRATE 9600	 // UART baudrate

// Includes
//---------------------------------
#include <avr/io.h>        // GPIO pins
#include <avr/interrupt.h> // Interrupts
#include <avr/sleep.h>	   // Power saving
#include <avr/pgmspace.h>  // Store patterns in program memory
#include <util/delay.h>    // Delay for debug
#include <stdbool.h>       // Booleans 
#include <stdint.h>        // uintx_t's
#include <stdio.h>		   // 
#include "inc/timer.h"     // Set up the timer with interrupts
#include "inc/gpio.h"      // Defines pins, ports and setting/clearing
#include "inc/pattern.h"   // Stores the pattern table

// Defines
//---------------------------------
#define CUBESIZE   64  // Number of LEDs in the cube
#define PLANESIZE  16  // Number of LEDs per plane
#define F_LED      100 // Frequency of the LEDs
#define DUTY       25  // Duty cycle in percent
#define TABLE_SIZE sizeof(pattern_table) / sizeof(pattern_table[0]) 

// Global Variables
//---------------------------------
volatile uint8_t table_row = 0; // Pattern table row
volatile uint8_t table_col = 0; // Pattern table column
volatile const uint8_t led_pin[] = {PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7, PIN8, PIN9, PIN10, PIN11, PIN12, PIN13, PINA4, PINA5};
uint16_t table_buf[5] = {};     // Holds one pattern line at a time from progmem

int main(void)
{
	// Set ports to OUTPUT
	DDRB |= 0xFF; 
	DDRC |= 0xFF; 
	DDRD |= 0xFF; 
	
	// Initialize
	set_sleep_mode(SLEEP_MODE_IDLE);
	timer_init(); 
	
	// Loop
	while (true) 
	{ 		
		// Go to sleep
		sleep_enable();
	}
}	

// Interrupt Handler
ISR (TIMER1_COMPA_vect)
{		
	// Read pattern from PROGMEM and save in buffer
	memcpy_P (table_buf, pattern_table + table_row, sizeof(table_buf));
	
	// Switch off all LEDs 
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	
	// Set LED values from pattern table
	if (table_col <= 3)
	{
		// Give power to correct LED anodes for plane #table_col
		for(int led_col = 0; led_col < PLANESIZE; led_col++)
		{
			// Set LED if there's a "1" in the pattern
			if (table_buf[table_col] & (1 << led_col)) 
			{
				SET_LED(led_col, led_pin[led_col]);	// Turn on power to anode	
			} 
		}
		// Switch the LEDs on
		SET_PLANE(table_col++); // Ground plane #table_col	
	}
	
	// Calculate how many times to display the current LED pattern line
	if (table_col == 4)
	{
		static uint16_t display_times = 0; // Keeps track of the times each pattern line has been executed
		display_times++;                   // Increment for each time 
		
		if (display_times == table_buf[table_col])
		{
			// Reset variables
			table_col     = 0;
			display_times = 0;
			
			// Check for end of table
			if (table_row == TABLE_SIZE - 1)  
				table_row = 0;
			else 
				table_row++; 
		}
		else {
			// Start on plane 1 again
			table_col = 0;
		}
	}	
}

