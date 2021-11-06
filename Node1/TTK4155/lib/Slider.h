#ifndef SLIDER_H
#define SLIDER_H

#include "ADC.h"

// Joystick channel addresses
#define S_L_ADDRESS 0x03
#define S_R_ADDRESS 0x02

typedef struct {
	uint8_t L;
	uint8_t R;	
} sliderpos_t;

sliderpos_t slider_pos_read()
{
	sliderpos_t pos = {adc_read(S_L_ADDRESS), adc_read(S_R_ADDRESS)};
	
	return pos;
}

void print_slider_position()
{
	sliderpos_t slider_position = slider_pos_read();
	
	printf("L: %d " , slider_position.L);
	printf("R: %d\n\r", slider_position.R);
}

#endif