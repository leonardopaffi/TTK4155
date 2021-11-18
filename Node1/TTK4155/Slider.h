#ifndef SLIDER_H
#define SLIDER_H

#include "ADC.h"

// Joystick channel addresses
#define S_L_ADDRESS 0x03
#define S_R_ADDRESS 0x02

/**
 * @brief Data type for sliders position L (left), R (right)
 * 
 */
typedef struct
{
	uint8_t L;
	uint8_t R;
} sliderpos_t;

/**
 * @brief Read the position of both sliders
 * 
 * @return sliderpos_t 
 */
sliderpos_t slider_pos_read();

/**
 * @brief Print position of both sliders L.R
 * 
 */
void print_slider_position();

#endif