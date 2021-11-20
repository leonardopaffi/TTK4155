#ifndef CAN_H
#define CAN_H

#include "CAN_Controller.h"
#include "avr/interrupt.h"

/*
	"Buttons" variable:
	Joystick button << 0
	Right button << 1
*/

typedef struct{
	uint16_t length;
	uint16_t id;
	uint8_t data[8];
} CAN_message;

/**
 * @brief Initialization function for the CAN bus
 * 
 * @param mode 
 */
void CAN_init(uint8_t mode);

/**
 * @brief Send data though the CAN bus
 * 
 * @param message 
 */
void CAN_send(CAN_message message);

/**
 * @brief Checks registers for received messages
 * 
 */
void CAN_receive();

/**
 * @brief Debug function for printing incoming messages
 * 
 * @param id 
 * @param data 
 * @param position 
 */
void CAN_debug_print(uint8_t id, char data, uint8_t position);

#endif