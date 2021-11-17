#ifndef mPWM
#define mPWM_H



void mPWM_init()
{
	REG_PMC_PCER1 |= PMC_PCER1_PID36;                     // Enable PWM
	REG_PIOC_ABSR |= PIO_ABSR_P20;                        // Set PWM pin 20 peripheral C 
	REG_PIOC_PDR |= PIO_PDR_P20;                          // Set PWM pin 20 to an output
	REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(42);     // Set the PWM clock rate to 2MHz (84MHz/42)
	REG_PWM_CMR5 = PWM_CMR_CALG | PWM_CMR_CPRE_CLKA;      // Enable dual slope PWM and set the clock source as CLKA
	REG_PWM_CPRD5 = 20000;                                // Set the PWM frequency 2MHz/(2 * 20000) = 50Hz = 20ms
	REG_PWM_CDTY5 = 20000-STEP_CENTER;                    // Set the PWM duty cycle to 1500 - centre the servo
	REG_PWM_ENA = PWM_ENA_CHID5;                          // Enable the PWM channel
}


