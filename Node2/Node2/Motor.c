#include "motor.h"

void motor_init()
{
	PIOC -> PIO_WPMR = (0x50494F << 8);
	PMC->PMC_PCER0 |= (1 << ID_PIOC);
	//PMC->PMC_PCER0 |= (1 << ID_PIOD);
	
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
	
	
	// Initialize DAC
	PMC->PMC_PCER1 = PMC_PCER1_PID38;     // DACC power ON
	DACC->DACC_CR = DACC_CR_SWRST ;       // Reset DACC

	DACC->DACC_MR = DACC_MR_TRGEN_DIS                    // Free running mode
	| DACC_MR_USER_SEL_CHANNEL1          // select channel 1
	| DACC_MR_REFRESH (10);

	DACC->DACC_IER |= DACC_IER_EOC;
	// Enable channel 1 = DAC1
	DACC->DACC_CHER = DACC_CHER_CH1;
	
	//DACC->DACC_ISR;  // Read and clear status register
	
	// Setting encoder pins as input
	PIOC -> PIO_IFER = (0xFF << 1);
	PIOC -> PIO_PUDR = (0xFF << 1);
	// !RES to low
	PIOD -> PIO_CODR = PIO_PD1;
	// !RES to high
	PIOD -> PIO_SODR = PIO_PD1;
	
	// Initialize PI controller
	PI_init(20,1,&pid);
	
	// Set motor at center
	

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
	if(speed > 100)
	{
		speed = 100;
	}
	
	else if(speed < 0)
	{
		speed = 0;
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

int16_t motor_encoder_read()
{
	// !RST HIGH
	//PIOD -> PIO_SODR = PIO_SODR_P1;
	
	PIOC -> PIO_PER = PIO_PC8;
	PIOC -> PIO_PER = PIO_PC7;
	PIOC -> PIO_PER = PIO_PC6;
	PIOC -> PIO_PER = PIO_PC5;
	PIOC -> PIO_PER = PIO_PC4;
	PIOC -> PIO_PER = PIO_PC3;
	PIOC -> PIO_PER = PIO_PC2;
	PIOC -> PIO_PER = PIO_PC1;
	
	int16_t data;
	// !OE LOW
	PIOD -> PIO_CODR = PIO_PD0;
	// SEL LOW
	PIOD -> PIO_CODR = PIO_PD2;
	
	delay_us(1000);
	
	// Read MSB
	data |= ((PIOC->PIO_PDSR >> 1) & 0xFF) << 8;
	// SEL HIGH
	PIOD -> PIO_SODR = PIO_PD2;
	
	delay_us(1000);
	
	// Read LSB
	data |= (PIOC->PIO_PDSR >> 1) & 0xFF;
	// !OE HIGH
	PIOD -> PIO_SODR = PIO_PD0;
	
	return data;
	
}

void motor_set_with_PI(uint16_t desired_value)
{
	int16_t value = motor_encoder_read();
	
	while(value != desired_value)
	{
		value = motor_encoder_read();
		int16_t speed  = PI_controller(desired_value, value, &pid);
		
		//printf("READ VALUE %d \r\n", value);
		
		if(speed > 100 | speed < 0)
		{
			speed = 30;
		}
		
		if(desired_value-value > 0)
		{
			motor_set_direction_speed(LEFT, speed);
		}
		
		else if (desired_value-value < 0)
		{
			motor_set_direction_speed(RIGHT, speed);
		}
	}
	
}
