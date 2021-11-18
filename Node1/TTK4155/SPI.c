#include "SPI.h"

void SPI_slave_enable()
{
	// Set SS-pin LOW
	PORTB &= ~(1 << PB4);
}

void SPI_slave_disable()
{
	// Set SS-pin HIGH
	PORTB |= (1 << PB4);
}

void SPI_master_init()
{
	// Code adapted from datasheet
	// Set SS (PB4), MOSI (PB5) and SCK (PB7) as output
	DDRB = (1<<PB4)|(1<<PB5)|(1<<PB7);
	DDRB &= ~(1 << PB6);
	
	// Enable SPI, Master, set clock rate fck/16
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	// Starting with slave disabled
	SPI_slave_disable();
}

void SPI_master_transmit(char cData)
{
	// Start transmission
	SPDR = cData;
	// Wait for transmission complete
	while(!(SPSR & (1 << SPIF)))
		;
}

char SPI_master_read()
{
	// Shifting the register by 8bit 
	SPDR = 0x00;
	// Wait for complete reception
	while(!(SPSR & (1 << SPIF)))
		;
		
	return SPDR;
}