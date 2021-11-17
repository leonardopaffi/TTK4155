#include "PI.h"

void PI_init(int16_t P_factor, int16_t I_factor, pidData_t* pid_st)
{
	// Initializing data for the PI structure
	pid_st -> P_Factor = P_factor;
	pid_st -> I_Factor = I_factor;
	pid_st -> error = 0;
	pid_st -> integral = 0;
}

int16_t PI_controller(int16_t set_point, int16_t process_value, pidData_t  *pid_st)
{
	// Adds previous error
	pid_st->integral = pid_st->integral +  (pid_st->error * pid_st->I_Factor);
	// Calculates new error
	pid_st->error = set_point - process_value;
	// Adds new error
	pid_st->integral = pid_st->integral +  (pid_st->error * pid_st->I_Factor);

	return (uint16_t)(((pid_st->error * pid_st->P_Factor) + pid_st->integral) / 128);
}