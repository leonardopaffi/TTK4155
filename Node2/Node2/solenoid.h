#ifndef SOLENOID_H_
#define SOLENOID_H_

#include "sam.h"

/**
 * @brief Initalization function for the solenoid
 * 
 */
void solenoid_init();

/**
 * @brief Send impulse to the solenoid
 * 
 * @param in_state 
 */
void solenoid_routine(uint8_t in_state);

#endif 