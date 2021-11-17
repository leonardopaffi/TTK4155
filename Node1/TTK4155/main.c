/*
 * TTK4155.c
 *
 * Created: 07.09.2021 10:44:28
 * Author : Leonardo Paffi
 */

#include <avr/io.h>
#include "lib/USART.h"
#include "lib/SRAM.h"
#include "lib/ADC.h"
#include "lib/Joystick.h"
#include "lib/Interrupt.h"
#include "lib/Slider.h"
#include "lib/OLED.h"
#include "lib/CAN.h"
#include "lib/mcp2515.h"

#define FOSC 4915200 // Clock speed
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

#include <stdlib.h>

int main(void)
{
	USART_Init(MYUBRR);

	SRAM_init();

	OLED_init();
	
	interrupt_init();

	adc_init();
		
	joystick_init();
		
	SPI_master_init();
		
	OLED_print_menu(MAIN);
	
	CAN_init(MODE_NORMAL);
	
	CAN_message a;
	a.id = 2;
	a.length = 3;
	
	pos_t j_pos;
	
	printf("I'm NODE 1\r\n");
	
	/* MAIN LOOP */
	while (1)
	{
		j_pos = joystick_pos_read();
		joystick_menu_navigation();
		
		interrupt_polling();
		a.data[0] = j_pos.x;
		a.data[1] = j_pos.y;
		a.data[2] = button;
		
		CAN_send(a);	
		
		//print_joystick_direction();	
	}
}
