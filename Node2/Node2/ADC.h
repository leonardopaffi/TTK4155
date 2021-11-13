#include <stdio.h>
#include "sam.h"

#define PASSWD_PIO_ADC 0x41444300
#define ADC_LIMIT 2000

void ADC_init()
{
	PMC->PMC_PCER1 |= PMC_PCER1_PID37; //ADC CLK ON
	ADC->ADC_MR |= ADC_MR_FREERUN_ON;
	ADC->ADC_CHER |= ADC_CHER_CH0; // CH0 ON
	ADC->ADC_CR |= ADC_CR_START; //starts analog-to-digital conversion
}

int ADC_read()
{
	// Getting data in the register
	return ADC->ADC_CDR[0];
}

int ADC_check_goal()
{
	if(ADC_read() < ADC_LIMIT){
		// A GOAL is detected
		return 1;
	}
	
	return 0;
}

void ADC_print()
{
	printf("adc: %d\n\r", (int)ADC->ADC_CDR[0]);
}