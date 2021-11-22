#include "ADC.h"

/**
 * @brief Pointer to the array of all addresses we will write to. ADC starting at 0x1400
 * 
 */
volatile char* ext_adc = ADC_ADDRESS;

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
	
	uint8_t value = 0;
	
	// Setting ADC mode for multiplexer configuration (page 8 of ADC datasheet)
	// setting channels
	// for channel 0 uint8_t adc_mode = 0b1000 0001;
	uint8_t adc_mode = (1 << SINGLE_CHANNEL_SAMPLE) | (channel);
	
	ext_adc[offset_adc] = adc_mode;

	// Wait for conversion
	_delay_us(5000);
	
	// Getting value from ADC
	value = ext_adc[offset_adc];
	
	// Overflow detection
	if(value > 255)
		value = 255;
	else if(value <= 0)
		value = 1;
	
	// Returns the value inside the ADC
	return value;
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