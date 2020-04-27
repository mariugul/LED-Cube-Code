/*
 * usart.c
 *
 * Created: 10.12.2019 17:33:20
 *  Author: Mariu
 */ 

// Includes
//---------------------------------
#include "../inc/usart.h"

// Defines
//---------------------------------
#define F_CPU 16000000UL
#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


// Function Definitions
//---------------------------------
void usart_init(uint32_t clock, uint32_t baudrate)
{
	//uint32_t ubbr_value = (((clock / (baudrate * 16UL))) - 1);
	
	// Set baud rate
	UBRR0H = (uint8_t)(UBRR_VALUE>>8);
	UBRR0L = (uint8_t)UBRR_VALUE;

	// Set frame format to 8 data bits, no parity, 1 stop bit
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);

	//enable transmission and reception
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	
	//set stream pointer
	FILE usart_str = FDEV_SETUP_STREAM(usart_send_byte, NULL, _FDEV_SETUP_WRITE);
}

int usart_send_byte(char u8Data, FILE *stream)
{
	if(u8Data == '\n')
	{
		usart_send_byte('\r', stream);
	}
	//wait while previous byte is completed
	while(!(UCSR0A&(1<<UDRE0))){};

	// Transmit data
	UDR0 = u8Data;
	return 0;
}