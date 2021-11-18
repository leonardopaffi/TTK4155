#ifndef ADC_H
#define ADC_H

#include <stdio.h>
#include "sam.h"

#define ADC_LIMIT 2000

/**
 * @brief Initialization function for the ADC
 * 
 */
void ADC_init();

/**
 * @brief Read data for the ADC
 * 
 * @return int 
 */
int ADC_read();

/**
 * @brief Check if the user has scored a goal
 * 
 * @return int Return 1 if the goal has been scored
 */
int ADC_check_goal();

/**
 * @brief Debug function that prints ADC data
 * 
 */
void ADC_print();

#endif