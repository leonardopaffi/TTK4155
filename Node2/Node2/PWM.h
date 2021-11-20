#ifndef PWM_H
#define PWM_H

#include "sam.h"

#define STEP_CENTER 1320
#define STEP_RIGHT_MAX 1740
#define STEP_LEFT_MAX 900

/**
 * @brief Initialization function for the PWM
 * 
 */
void PWM_init();

/**
 * @brief Function to map a value in a certain range
 * 
 * @param x Value to be mapped
 * @param in_min 
 * @param in_max 
 * @param out_min 
 * @param out_max 
 * @return long 
 */
long map(long x, long in_min, long in_max, long out_min, long out_max);

/**
 * @brief Set value to PWM
 * 
 * @param value 
 * @return int 
 */
int PWM_set_value(uint8_t value);

#endif PWM_H