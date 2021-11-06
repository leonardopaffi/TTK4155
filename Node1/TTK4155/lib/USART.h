#ifndef USART_H
#define USART_H

#include <stdio.h>

int USART_Transmit(unsigned char data);
int USART_Receive(void);

void USART_Init(unsigned int ubrr)
{
	/*Adapted from the datasheet*/
	/*Set baud rate*/
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter*/
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	/*Set frame format: 8data*/
	UCSR0C = (1 << URSEL0) | (3 << UCSZ00);
	fdevopen(USART_Transmit, USART_Receive);
}

int USART_Transmit(unsigned char data)
{
	/*Adapted from the datasheet*/
	/*Wait for empty transmit buffer*/
	while (!(UCSR0A & (1 << UDRE0)))
		;
	/*Put data into buffer, sends the data*/
	UDR0 = data;

	return 0;
}

int USART_Receive(void)
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1 << RXC0)))
		;
	/* Get and return received data from buffer */
	return UDR0;
}

#endif