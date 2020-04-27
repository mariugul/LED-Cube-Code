/*
 * adc.c
 *
 * Created: 10.12.2019 17:58:15
 *  Author: Marius
 */ 

// Includes
//---------------------------------
#include "../inc/adc.h"

// Defines
//---------------------------------

// Function Definitions
//---------------------------------
void adc_init()
{
	// Select Vref=AVcc
	ADMUX |= (1<<REFS0);
	//set prescaller to 128 and enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

uint16_t adc_read(uint8_t channel)
{
	//select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	
	//single conversion mode
	ADCSRA |= (1<<ADSC);
	
	// wait until ADC conversion is complete
	while( ADCSRA & (1<<ADSC) );
	return ADC;
}