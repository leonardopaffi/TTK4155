#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <avr/io.h>
#include <avr/interrupt.h>

/*
	INT2 -> RIGHT BUTTON
	INT1 -> LEFT BUTTON
	INT0 -> CAN INTERRUPT
*/

volatile uint8_t RIGHT_BUTTON_PRESSED;
volatile uint8_t LEFT_BUTTON_PRESSED;
volatile uint8_t JOYSTICK_BUTTON_PRESSED;

/**
 * @brief initialization function for the interrupt
 * 
 */
void interrupt_init();

/**
 * @brief Resets variables and prints in the console if a button is pressed
 * 
 */
void interrupt_polling();

ISR(INT2_vect)
{
	// Wakes the MCU up when right button is pressed
	RIGHT_BUTTON_PRESSED = 1;
}

ISR(INT1_vect)
{
	// Wakes the MCU up when left button is pressed
	LEFT_BUTTON_PRESSED = 1;
}

#endif