#ifndef MOTOR_H
#define MOTOR_H

#define LEFT 0
#define RIGHT 1
#define NONE 2

#include "sam.h"
#include "delay.h"
#include "PI.h"

pidData_t pid;

void motor_init();

void motor_set_direction(uint8_t direction);

void motor_set_speed(uint8_t speed);

void motor_set_direction_speed(uint8_t direction, uint16_t speed);

int16_t motor_encoder_read();

void motor_set_with_PI(uint16_t desired_value);

void motor_center();

#endif