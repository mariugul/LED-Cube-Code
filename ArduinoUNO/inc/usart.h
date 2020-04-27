/*
 * usart.h
 *
 * Created: 10.12.2019 17:32:59
 *  Author: Mariu
 */ 

// Header Guard
//---------------------------------
#ifndef __USART_H__
#define __USART_H__

// Includes
//---------------------------------
#include <avr/io.h>
#include <stdio.h>

// Defines
//---------------------------------

// Function Prototypes
//---------------------------------
void usart_init(uint32_t clock, uint32_t baudrate);
int usart_send_byte(char u8Data, FILE *stream);

#endif