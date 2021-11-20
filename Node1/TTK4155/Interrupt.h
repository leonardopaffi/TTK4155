#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <avr/io.h>
#include <avr/interrupt.h>

/*
	INT2 -> RIGHT BUTTON
	INT1 -> LEFT BUTTON
	INT0 -> CAN INTERRUPT
*/

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

#endif