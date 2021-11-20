#ifndef MOTOR_H
#define MOTOR_H

#define LEFT 0
#define RIGHT 1
#define NONE 2

#include "sam.h"
#include "delay.h"
#include "PI.h"

pidData_t pid;

/**
 * @brief Initialization function for the motor
 * 
 */
void motor_init();

/**
 * @brief Set direction of the motor LEFT/RIGHT
 * 
 * @param direction 
 */
void motor_set_direction(uint8_t direction);

/**
 * @brief Set speed of the motor, normalized to 0-100
 * 
 * @param speed 
 */
void motor_set_speed(uint8_t speed);

/**
 * @brief Set both speed and direction for the motor
 * 
 * @param direction 
 * @param speed 
 */
void motor_set_direction_speed(uint8_t direction, uint16_t speed);

/**
 * @brief Read data from the encoder
 * 
 * @return int16_t 
 */
int16_t motor_encoder_read();

/**
 * @brief Set the position of the motor with PI
 * 
 * @param desired_value 
 */
void motor_set_with_PI(uint16_t desired_value);

/**
 * @brief Center motor
 * 
 */
void motor_center();

#endif