/*
 * TTK4155.c
 *
 * Created: 07.09.2021 10:44:28
 * Author : Leonardo Paffi
 */

#include <avr/io.h>
#include "USART.h"
#include "SRAM.h"
#include "ADC.h"
#include "Joystick.h"
#include "Interrupt.h"
#include "Slider.h"
#include "OLED.h"
#include "CAN.h"
#include "mcp2515.h"

#define FOSC 4915200 // Clock speed
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

#include <stdlib.h>

uint8_t playing = 0;

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
	a.length = 4;
	
	pos_t j_pos;
	sliderpos_t slider_pos;
	
	printf("I'm NODE 1\r\n");
	
	// Re-initializing Node 2
	CAN_message msgs;
	msgs.id = 1;
	msgs.length = 1;
	msgs.data[0] = 0x01;
			
	CAN_send(msgs);
	
	/* MAIN LOOP */
	while (1)
	{
		j_pos = joystick_pos_read();
		slider_pos = slider_pos_read();
		
		joystick_menu_navigation(&playing);	
		
		interrupt_polling();
		
		if(playing)
		{
			a.data[0] = j_pos.x;
			a.data[1] = j_pos.y;
			a.data[2] = button;
			a.data[3] = slider_pos.R;
			
			CAN_send(a);	
			
			//print_joystick_position();
			
			printf("%d \r\n", adc_read(0x01));
			
			if(you_lose)
			{
				OLED_print_string("You lose", 8, 3);
			}
		}
	}
}
