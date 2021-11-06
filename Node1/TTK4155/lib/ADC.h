#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

#define ADC_ADDRESS 0x1400

#define SINGLE_CHANNEL_SAMPLE 7

volatile char* ext_adc = ADC_ADDRESS;	//Create a pointer to the array of all addresses we will write to. ADC starting at 0x1400.
volatile char ADC_data;

// Initializes the ADC and its clock signal
void adc_init(void);
// Reads a certain analog channel of the ADC
uint8_t adc_read(uint8_t channel);

void adc_init()
{
	SFIOR = 0x01;
	// PB0 as OUTPUT
	DDRB = 0x01;
	// PORTB = 0x01;
	
	// CTC, Toggle OC0 on compare match, no pre-scaler
	TCCR0 |= (1<<WGM01) | (1<<COM00) | (1<<CS00);
	
	// Setting Output Compare Register to force the oscillator to 500kHz
	// Pin n.1 (OC0) is used
	OCR0 = 0x04;
}

uint8_t adc_read(uint8_t channel)
{
	// 0x1400 -> 0001 0100 0000 0000
	volatile char *ext_adc = (char *)0x1400; // Start address for the ADC
	uint8_t offset_adc= 0x01;
	
	// Setting ADC mode for multiplexer configuration (page 8 of ADC datasheet)
	// setting channels
	// for channel 0 uint8_t adc_mode = 0b1000 0001;
	uint8_t adc_mode = (1 << SINGLE_CHANNEL_SAMPLE) | (channel);
	
	ext_adc[offset_adc] = adc_mode;

	// Wait for conversion
	_delay_us(2000);
	
	// Returns the value inside the ADC
	return ext_adc[offset_adc];
}

void adc_read_all_channels()
{
	for(int i = 0; i < 4; i++)
	{
		printf("Channel %d: %d \n\r", i, adc_read(i));
	}
	printf("\n\r");
	_delay_ms(5000);
}

#endif