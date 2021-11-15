#ifndef MOTOR_H
#define MOTOR_H

#define LEFT 0
#define RIGHT 1

void motor_init()
{
	// Set EN pin for motor (PD9)
	PIOD -> PIO_PER = PIO_PD9;
	PIOD -> PIO_OER = PIO_PD9;
	PIOD -> PIO_SODR = PIO_SODR_P9;

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
	
	// Initialize DAC, set to half word
	REG_DACC_MR = DACC_MR_REFRESH(10) | DACC_MR_USER_SEL_CHANNEL1;
	REG_DACC_CHER = DACC_CHER_CH1;
	
}

void motor_set_direction(uint8_t direction)
{
	if(LEFT){
		// Set LEFT direction (PD10)
		REG_PIOD_OER |= PIO_OER_P10;
		REG_PIOD_CODR |= PIO_CODR_P10;
			
	} else {
		// Set RIGHT direction (PD10)
		REG_PIOD_OER |= PIO_OER_P10;
		REG_PIOD_SODR |= PIO_SODR_P10;
			
	}
}

#endif