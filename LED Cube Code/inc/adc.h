/*
 * adc.h
 *
 * Created: 10.12.2019 17:57:59
 *  Author: Marius
 */ 

// Header Guard
//---------------------------------
#ifndef __ADC_H__
#define __ADC_H__

// Includes
//---------------------------------
#include <avr/io.h>
#include <stdint.h>

// Defines
//---------------------------------

// Function Prototypes
//---------------------------------
void adc_init();
uint16_t adc_read(uint8_t channel);

#endif