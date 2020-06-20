/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                   LED CUBE                            *
 *                                                       *
 * Control a 4x4x4 LED cube with low power consumption   *
 * in embedded C.                                        *
 *                                                       *
 * By: Marius C. K. Gulbrandsen                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/pattern.h"

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

// Global Variables
// -------------------------------------------

// Holds one pattern line at a time from progmem
uint16_t pattern_buf[5] = {};

// Contains the values for setting the I/O ports
uint8_t port_b = 0x00;
uint8_t port_c = 0x00;
uint8_t port_d = 0x00;


int main(void)
{
	// Variables
	//----------------------------------------
	const uint16_t nr_of_lines  = (sizeof(pattern_table) / sizeof(pattern_table[0]) / 5); // Number of lines in pattern table
	const uint8_t  plane_mask[] = {PLANE1_MASK, PLANE2_MASK, PLANE3_MASK, PLANE4_MASK};   // Holds the masks to set the correct plane
	const uint8_t  pattern_buf_size = 5; // Length of the buffer holding one pattern line
	
	int16_t  current_line    = -1;   // Current read line in pattern table
	uint32_t pattern_counter = 0;    // Used to copy the pattern lines in pattern table to pattern buffer
	uint8_t  current_plane   = 0;    // The plane that is going to be switched on
	bool     get_new_line    = true; // True when a new line should be retreived from progmem
	
	uint16_t time_counter = 0;
	
	
	// Initialize
	//----------------------------------------
	// Set the I/O pins to OUTPUT
	DDRB = 0x3F; // Sets 6 pins on port B --> 0x3F is binary 0011 1111
	DDRC = 0x3F; // Sets 6 pins on port C
	DDRD = 0xFF; // Sets 8 pins on port D
	
	// Turn all LED's off
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	
	// Set up timer interrupt
	OCR1A = 39;						     // 39 gives 2.5ms interrupts with 1024 prescaler = 10ms patterns and 50Hz
	TCCR1B |= (1 << WGM12);				 // Mode 4, CTC on OCR1A
	TIMSK1 |= (1 << OCIE1A);			 // Set interrupt on compare match
	TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024 and start the timer
	
	// Enable global interrupts
	sei();
	
	// Enable sleep mode
	sleep_enable();
	set_sleep_mode(SLEEP_MODE_IDLE);
	
	
	// Main Loop
	//----------------------------------------
	while (true)
	{
		// Read a new pattern line from program memory
		if (get_new_line)
		{
			// Read one pattern line from PROGMEM to temp buffer e.g. [0x0, 0x0, 0x0, 0x0, 10]
			memcpy_P (pattern_buf, pattern_table + pattern_counter, 5 * sizeof(uint16_t));
			current_line++;
			
			// Logic for getting the correct lines from pattern table on next access
			if (current_line == nr_of_lines - 1)
			{
				// Reset at the end of the table
				pattern_counter =  0;
				current_line    = -1;
			}
			else
				// Increment to get next line from pattern table
				pattern_counter += pattern_buf_size; 
			
			get_new_line = false;
		}
		
		// Calculate port values
		port_b =  (pattern_buf[current_plane] & PORT_B_MASK) >> SHIFT_PORT_B; 
		port_c = ((pattern_buf[current_plane] & PORT_C_MASK) >> SHIFT_PORT_C) ^ plane_mask[current_plane]; // XOR to find the current PLANE to turn on
		port_d =  (pattern_buf[current_plane] & PORT_D_MASK); // Don't need a shift because it's already in the right place
		
		// Logic for switching correct plane and time
		if (current_plane == NR_OF_PLANES - 1)
		{
			// Reset to sart calculating from the first plane again
			current_plane = 0;
			
			// Increment every time one pattern has finished
			time_counter++; 
			
			// Logic for the amount of time for each plane
			if (time_counter == pattern_buf[TIME_IDX] / MIN_PATTERN_TIME)
			{
				// Get new line only when the pattern has run the correct amount of times corresponding to the time variable
				get_new_line = true;
				time_counter = 0;
			}
		}
		else
			// Increment to calculate ports for the next plane
			current_plane++;
		
		
		// Sleep until interrupt from timer
		sleep_cpu(); 
	}
}

// Interrupt Service Routine
ISR (TIMER1_COMPA_vect)
{
	// Switch on the LEDs for the current plane
	PORTB = port_b;
	PORTD = port_d;
	PORTC = port_c; // Port C is last because it turns on the plane also
}