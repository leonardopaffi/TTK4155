#ifndef PI_H
#define PI_H

#include <stdint.h>

typedef struct PID_DATA{
	// Structure adapted from example code
	// To calculate Error
	int16_t error;
	//! Summation of errors, used for integrate calculations
	int32_t integral;
	//! The Proportional tuning constant, multiplied with SCALING_FACTOR
	int16_t P_Factor;
	//! The Integral tuning constant, multiplied with SCALING_FACTOR
	int32_t I_Factor;
} pidData_t;

void PI_init(int16_t P_factor, int16_t I_factor, pidData_t* pid_st);

int16_t PI_controller(int16_t set_point, int16_t process_value, pidData_t  *pid_st);

#endif