#ifndef PI_H
#define PI_H

#include <stdint.h>

typedef struct PID_DATA{
	// Structure adapted from example code
	// To calculate Error
	int16_t error;
	// Summation of errors, used for integrate calculations
	int32_t integral;
	// The Proportional tuning constant, multiplied with SCALING_FACTOR
	int16_t P_Factor;
	// The Integral tuning constant, multiplied with SCALING_FACTOR
	int32_t I_Factor;
} pidData_t;

/**
 * @brief Initialization function for the PI controller
 * 
 * @param P_factor 
 * @param I_factor 
 * @param pid_st 
 */
void PI_init(int16_t P_factor, int16_t I_factor, pidData_t* pid_st);

/**
 * @brief Updates the value with the PI controller
 * 
 * @param set_point 
 * @param process_value 
 * @param pid_st 
 * @return int16_t 
 */
int16_t PI_controller(int16_t set_point, int16_t process_value, pidData_t  *pid_st);

#endif