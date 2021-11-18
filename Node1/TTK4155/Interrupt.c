#include "Interrupt.h"

RIGHT_BUTTON_PRESSED = 0;
LEFT_BUTTON_PRESSED = 0;
JOYSTICK_BUTTON_PRESSED = 0;

void interrupt_init()
{
	cli();
	
	//DDRE &= ~(1 << PE0);
	
	// Enable interrupt 0 on falling edge
	MCUCR |= (1 << ISC01);
	
	// Enable interrupt 1 on rising edge
	MCUCR |= (1 << ISC11) | (1 << ISC10);
	
	// Enable interrupt 2 on rising edge
	EMCUCR |= (1 << ISC2);
	
	// Enable interrupts on MCU
	GICR |= (1 << INT2) | (1 << INT1) | (1 << INT0);
	
	sei();
}

void interrupt_polling()
{
	if(RIGHT_BUTTON_PRESSED)
	{
		// Do stuff
		printf("RIGHT B\n\r");
		//Reset button variable
		RIGHT_BUTTON_PRESSED = 0;
	}
	
	if(LEFT_BUTTON_PRESSED)
	{
		// Do stuff
		printf("LEFT B\n\r");
		//Reset button variable
		LEFT_BUTTON_PRESSED = 0;
	}
	
}
