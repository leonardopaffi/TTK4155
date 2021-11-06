#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "ADC.h"
#include "OLED.h"

// Joystick channel addresses
#define J_X_ADDRESS 0x01
#define J_Y_ADDRESS 0x00

// Joystick offset
#define J_X_OFFSET 164
#define J_Y_OFFSET 164

// Idle values limit interval
#define IDLE_X_MIN -40
#define IDLE_X_MAX 40
#define IDLE_Y_MIN -40
#define IDLE_Y_MAX 40

// Position structure for x,y values
// 8-bit each value
typedef struct
{
	int16_t x;
	int16_t y;
} pos_t;

typedef enum {
	X_IDLE,
	LEFT,
	RIGHT
} x_direction;

typedef enum {
	Y_IDLE,
	UP,
	DOWN
} y_direction;

typedef struct{
	char x_dir;
	char y_dir;	
} direction;

// Calibrates the ADC
void joystick_calibrate();
// Reads position of the joystick
pos_t pos_read(void);

// Prevents the joystick to get more than one input
uint8_t stop = 0;
uint8_t button = 0;

void joystick_init()
{
	PORTB |= (1 << PB2);
	DDRB |= (1 << DDB2);
}

pos_t joystick_pos_read()
{
	pos_t pos = {adc_read(J_X_ADDRESS)- J_X_OFFSET, adc_read(J_Y_ADDRESS)- J_Y_OFFSET};
	
	return pos;
}

void print_joystick_position()
{
	pos_t joystick_position = joystick_pos_read();
	
	printf("x: %d " , joystick_position.x);
	printf("y: %d\n\r", joystick_position.y);
}

direction joystick_dir_read()
{
	pos_t joystick_position = joystick_pos_read();
	direction dir = {X_IDLE, Y_IDLE};
	
	if(joystick_position.x > IDLE_X_MAX)
		dir.x_dir = RIGHT;
	else if(joystick_position.x < IDLE_X_MIN)
		dir.x_dir = LEFT;
	else
		dir.x_dir = X_IDLE;
	
	if(joystick_position.y > IDLE_Y_MAX)
		dir.y_dir = UP;
	else if(joystick_position.y < IDLE_Y_MIN)
		dir.y_dir = DOWN;
	else
		dir.y_dir = Y_IDLE;
		
	return dir;
	
}

void joystick_menu_navigation()
{
	// Updating the button state
	button = !((PINB & (1<<PB2))/4);
	
	// Getting the position
	pos_t joystick_position = joystick_pos_read();


	if(button == 1 && stop == 0)
	{	
		// Button on menu is pressed
		printf("%d\r\n", menu_pos);
		stop = 1;
	}
	
	// Navigating when button is NOT pressed
	if (button == 0)
	{
		// Going UP
		if(joystick_position.y > IDLE_Y_MAX)
		{
			if(stop == 0 && button == 0){
				OLED_update_menu(menu_pos-1);
				stop = 1;
			}
		}
		// Going DOWN
		else if(joystick_position.y < IDLE_Y_MIN)
		{
			if(stop == 0 && button == 0){
				OLED_update_menu(menu_pos+1);
				stop = 1;
			}
		}
		// Position: IDLE
		else {
			if (button == 0)
			{
				stop = 0;
			}
		}
	}
}

void print_joystick_direction()
{
	direction dir = joystick_dir_read();
	
	switch(dir.x_dir){
		case X_IDLE:
			printf("IDLE ");
			break;
			
		case LEFT:
			printf("LEFT ");
			break;
			
		case RIGHT:
			printf("RIGHT ");
			break;
	}
	
	switch(dir.y_dir){
		case Y_IDLE:
			printf("IDLE\r\n");
			break;
		
		case DOWN:
			printf("DOWN\r\n");
			break;
			
		case UP:
			printf("UP\r\n");
			break;
	}
}

#endif