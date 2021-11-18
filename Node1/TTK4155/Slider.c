#include "Slider.h"

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
