#ifndef MOTOR_H
#define MOTOR_H

#define LEFT 0
#define RIGHT 1

#include "delay.h"

void motor_init()
{
	// Set EN pin for motor (PD9)
	PIOD -> PIO_PER |= PIO_PER_P9;
	PIOD -> PIO_OER |= PIO_OER_P9;
	PIOD -> PIO_SODR |= PIO_SODR_P9;

	// DIR
	PIOD -> PIO_PER = PIO_PD10;
	PIOD -> PIO_OER = PIO_PD10;
	
	// !OE
	PIOD -> PIO_PER = PIO_PD0;
	PIOD -> PIO_OER = PIO_PD0;
	PIOD -> PIO_CODR = PIO_CODR_P0;
	
	// SEL
	PIOD -> PIO_PER = PIO_PD2;
	PIOD -> PIO_OER = PIO_PD2;
	
	// !RES
	PIOD -> PIO_PER = PIO_PD1;
	PIOD -> PIO_OER = PIO_PD1;
	PIOD -> PIO_CODR = PIO_CODR_P1;
	
	// Initialize DAC
	PMC->PMC_PCER1 = PMC_PCER1_PID38;     // DACC power ON
	DACC->DACC_CR = DACC_CR_SWRST ;       // Reset DACC

	DACC->DACC_MR = DACC_MR_TRGEN_DIS                    // Free running mode
	| DACC_MR_USER_SEL_CHANNEL1          // select channel 1
	| DACC_MR_REFRESH (10);

	DACC->DACC_IER |= DACC_IER_EOC;

	DACC->DACC_CHER = DACC_CHER_CH1;      // enable channel 1 = DAC1
	//DACC->DACC_ISR;  // Read and clear status register
	
	// Setting encoder pins as input
	PIOC -> PIO_IFER = PIO_PC8;
	PIOC -> PIO_IFER = PIO_PC7;
	PIOC -> PIO_IFER = PIO_PC6;
	PIOC -> PIO_IFER = PIO_PC5;
	PIOC -> PIO_IFER = PIO_PC4;
	PIOC -> PIO_IFER = PIO_PC3;
	PIOC -> PIO_IFER = PIO_PC2;
	PIOC -> PIO_IFER = PIO_PC1;
}

void motor_set_direction(uint8_t direction)
{
	if(direction == LEFT){
		// Set LEFT direction (PD10)
		PIOD -> PIO_CODR |= PIO_CODR_P10;
			
	} else {
		// Set RIGHT direction (PD10)
		PIOD -> PIO_SODR |= PIO_SODR_P10;
			
	}
}

void motor_set_speed(uint8_t speed)
{
	// Exit if speed is too high or negative
	if(speed > 100 || speed < 0)
	{
		return;
	}
	
	// Speed should be between 0 and 100
	uint16_t speed_voltage = speed * 30;
	
	// Set speed value
	DACC -> DACC_CDR = speed_voltage;
}
void motor_set_direction_speed(uint8_t direction, uint16_t speed)
{
	motor_set_direction(direction);
	motor_set_speed(speed);
}

void motor_encoder_read()
{
	// !RST HIGH
	//PIOD -> PIO_SODR = PIO_SODR_P1;
	// !OE LOW
	PIOD -> PIO_CODR = PIO_CODR_P0;
	// SEL LOW
	PIOD -> PIO_CODR = PIO_CODR_P2;
	
	delay_us(48*30);
	
	// Read MSB from pins: 40,39,38,37,36,35,34,33 (DO7-DO0)
// 	PIOC->PIO_I
// 	PIOC->PIO_PER

	
	PIOC -> PIO_PER = PIO_PC8;
	PIOC -> PIO_PER = PIO_PC7;
	PIOC -> PIO_PER = PIO_PC6;
	PIOC -> PIO_PER = PIO_PC5;
	PIOC -> PIO_PER = PIO_PC4;
	PIOC -> PIO_PER = PIO_PC3;
	PIOC -> PIO_PER = PIO_PC2;
	PIOC -> PIO_PER = PIO_PC1;

	uint32_t pin_status;
	pin_status = PIOC->PIO_PDSR & PIO_PDSR_P8;
	printf("%d",pin_status);
	pin_status = PIOC->PIO_PDSR & PIO_PDSR_P7;
	printf("%d",pin_status);
	pin_status = PIOC->PIO_PDSR & PIO_PDSR_P6;
	printf("%d",pin_status);
	pin_status = PIOC->PIO_PDSR & PIO_PDSR_P5;
	printf("%d",pin_status);
	pin_status = PIOC->PIO_PDSR & PIO_PDSR_P4;
	printf("%d",pin_status);
	pin_status = PIOC->PIO_PDSR & PIO_PDSR_P3;
	printf("%d",pin_status);
	pin_status = PIOC->PIO_PDSR & PIO_PDSR_P2;
	printf("%d",pin_status);
	pin_status = PIOC->PIO_PDSR & PIO_PDSR_P1;
	printf("%d",pin_status);

	// SEL HI
	PIOD -> PIO_SODR = PIO_SODR_P2;
	
	delay_us(48*30);
	
	pin_status = PIOC->PIO_PDSR & PIO_PDSR_P8;
	printf("%d",pin_status);
	pin_status = PIOC->PIO_PDSR & PIO_PDSR_P7;
	printf("%d",pin_status);
	pin_status = PIOC->PIO_PDSR & PIO_PDSR_P6;
	printf("%d",pin_status);
	pin_status = PIOC->PIO_PDSR & PIO_PDSR_P5;
	printf("%d",pin_status);
	pin_status = PIOC->PIO_PDSR & PIO_PDSR_P4;
	printf("%d",pin_status);
	pin_status = PIOC->PIO_PDSR & PIO_PDSR_P3;
	printf("%d",pin_status);
	pin_status = PIOC->PIO_PDSR & PIO_PDSR_P2;
	printf("%d",pin_status);
	pin_status = PIOC->PIO_PDSR & PIO_PDSR_P1;
	printf("%d",pin_status);
	
	// !RST LOW
	//PIOD -> PIO_CODR = PIO_CODR_P1;
	// !OE HIGH
	PIOD -> PIO_SODR = PIO_SODR_P0;
	
}


#endif