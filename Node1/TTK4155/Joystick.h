#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "ADC.h"
#include "OLED.h"

// Joystick channel addresses
#define J_X_ADDRESS 0x01
#define J_Y_ADDRESS 0x00

// Idle values limit interval
#define IDLE_X_MIN 20
#define IDLE_X_MAX 80
#define IDLE_Y_MIN 20
#define IDLE_Y_MAX 80

// Position structure for x,y values
// 8-bit each value
typedef struct
{
	uint8_t x;
	uint8_t y;
} pos_t;

typedef enum
{
	X_IDLE,
	LEFT,
	RIGHT
} x_direction;

typedef enum
{
	Y_IDLE,
	UP,
	DOWN
} y_direction;

typedef struct
{
	char x_dir;
	char y_dir;
} direction;

// Prevents the joystick to get more than one input
uint8_t stop;
uint8_t button;

/**
 * @brief Reads position of the joystick
 * 
 * @return pos_t 
 */
pos_t pos_read(void);

/**
 * @brief Initialization function for the joystick
 * 
 */
void joystick_init();

/**
 * @brief Read the position of the joystick axes X,Y
 * 
 * @return pos_t 
 */
pos_t joystick_pos_read();

/**
 * @brief Debug function for checking the position of the axes X,Y
 * 
 */
void print_joystick_position();

/**
 * @brief Read the position of the joystick and converts to LEFT,RIGHT,UP,DOWN or IDLE if the joystick is untouched
 * 
 * @return direction 
 */
direction joystick_dir_read();

/**
 * @brief Updates the menu on the OLED when something happens with the joystick
 * 
 */
void joystick_menu_navigation();

/**
 * @brief Debug function for checking the directoin of the joystick
 * 
 */
void print_joystick_direction();

/**
 * @brief Function to remap values in a certain range
 * 
 * @param x The value to remap
 * @param in_min Input range minumum value
 * @param in_max Input range maximum value
 * @param out_min Output range minumum value
 * @param out_max Output range maximum value
 * @return long 
 */
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif