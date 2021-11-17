#ifndef PWM_H
#define PWM_H

#include "sam.h"

#define STEP_CENTER 1320
#define STEP_RIGHT_MAX 1740
#define STEP_LEFT_MAX 900

void PWM_init();

long map(long x, long in_min, long in_max, long out_min, long out_max);

int PWM_set_value(int8_t value);

#endif PWM_H