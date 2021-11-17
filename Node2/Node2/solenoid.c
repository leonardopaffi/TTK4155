#include "solenoid.h"

void solenoid_init(){
	/* Disable pull-up on bit PC2(D0) */
	PIOC->PIO_PUDR |= PIO_PC9;
	/* Enable PIO controller on bit PC2(D0) */
	PIOC->PIO_PER |= PIO_PC9;
	/* Set output enable on PC2(D0) */
	PIOC->PIO_OER |= PIO_PC9;
}

void solenoid_routine(uint8_t pressed){

	if (pressed == 1){
		PIOC->PIO_CODR |= PIO_PC9;
		} else {
		PIOC->PIO_SODR |= PIO_PC9;
	}
}
