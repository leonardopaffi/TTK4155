#include "Joystick.h"

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
    pos_t pos = {map(adc_read(J_X_ADDRESS), 0, 255, 0, 100), map(adc_read(J_Y_ADDRESS), 0, 255, 0, 100)};
    //pos_t pos = {adc_read(J_X_ADDRESS), adc_read(J_Y_ADDRESS)};
    return pos;
}

void print_joystick_position()
{
    pos_t joystick_position = joystick_pos_read();

    printf("x: %d ", joystick_position.x);
    printf("y: %d\n\r", joystick_position.y);
}

direction joystick_dir_read()
{
    pos_t joystick_position = joystick_pos_read();
    direction dir = {X_IDLE, Y_IDLE};

    if (joystick_position.x > IDLE_X_MAX)
        dir.x_dir = RIGHT;
    else if (joystick_position.x < IDLE_X_MIN)
        dir.x_dir = LEFT;
    else
        dir.x_dir = X_IDLE;

    if (joystick_position.y > IDLE_Y_MAX)
        dir.y_dir = UP;
    else if (joystick_position.y < IDLE_Y_MIN)
        dir.y_dir = DOWN;
    else
        dir.y_dir = Y_IDLE;

    return dir;
}

void joystick_menu_navigation(uint8_t* playing)
{
    // Updating the button state
    button = !((PINB & (1 << PB2)) / 4);

    // Getting the position
    pos_t joystick_position = joystick_pos_read();

    if (button == 1 && stop == 0 && *playing == 0 && is_main_menu)
    {
        // Button on menu is pressed
        printf("%d\r\n", menu_pos);
		
		switch(menu_pos)
		{
			case PLAYMENU:
				*playing = 1;
				OLED_print_menu(PLAYMENU);
				is_main_menu = 1; 
				break;
			
			case CREDITS:
				OLED_print_menu(CREDITS);
				is_main_menu = 0;
				break;
			
			case ABOUT:
				OLED_print_menu(ABOUT);
				is_main_menu = 0;
				break;
			
			default:
				break;
		}
		
        stop = 1;
    }

    // Navigating when button is NOT pressed
    if (button == 0 && *playing == 0 && is_main_menu)
    {
        // Going UP
        if (joystick_position.y > IDLE_Y_MAX)
        {
            if (stop == 0 && button == 0)
            {
                OLED_update_menu(menu_pos - 1);
                stop = 1;
            }
        }
        // Going DOWN
        else if (joystick_position.y < IDLE_Y_MIN)
        {
            if (stop == 0 && button == 0)
            {
                OLED_update_menu(menu_pos + 1);
                stop = 1;
            }
        }
        // Position: IDLE
        else
        {
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

    switch (dir.x_dir)
    {
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

    switch (dir.y_dir)
    {
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

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}