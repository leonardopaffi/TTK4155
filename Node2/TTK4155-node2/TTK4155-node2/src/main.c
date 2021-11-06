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
#include <asf.h>
#include "uart.h"
#include "can_controller.h"

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	configure_uart();
	
	int d = can_init_def_tx_rx_mb(0x00290561);
	uart_putchar(d);
	uart_putchar('\r');
	uart_putchar('\n');
	
	PIOA -> PIO_PER |= PIO_PER_P19;	//enable pin
	PIOA -> PIO_OER |= PIO_OER_P19; // set as output
	PIOA -> PIO_SODR |= PIO_SODR_P19; // set high
	
	CAN_MESSAGE msg;
	msg.id = 12;
	msg.data_length = 2;
	msg.data[0] = 'c';
	msg.data[1] = 'f';
	
	
	while(1){
		char c = can_send(&msg, 0);
		uart_putchar(c+0x30);
		uart_putchar('\r');
		uart_putchar('\n');
		
		
		
		delay_ms(1000);
	}
}
