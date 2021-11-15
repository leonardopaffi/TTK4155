/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include "sam.h"
#include "uart.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "PWM.h"
#include "ADC.h"
#include "Motor.h"

uint8_t score = 0;
uint8_t game_pause = 0;

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	SystemInit();
	configure_uart();
	
	PWM_init();
	
	ADC_init();
	
	motor_init();
	
	int d = can_init_def_tx_rx_mb(0x00290561);
	printf("Node 2\n\r");
	
	WDT -> WDT_MR |= WDT_MR_WDDIS;
	
	CAN_MESSAGE msg;
	msg.id = 12;
	msg.data_length = 2;
	msg.data[0] = 'c';
	msg.data[1] = 'f';
	
	while(1){
		// GOAL logic
		if (ADC_check_goal() && !game_pause)
		{
			score++;
			printf("score: %d \n\r", score);
			game_pause = 1;
		}
		
		// TODO: Need to implement something to un-pause game
		
		
		
			// Set data in the DAC
			uint16_t data1 = 0xAAAA;
			uint16_t data2 = 0xFFFF;
			REG_DACC_CDR = ((data1 << 16) | data2);
		
	}
}