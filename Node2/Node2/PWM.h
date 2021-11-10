#define STEP_CENTER 1320
#define STEP_RIGHT_MAX 1740
#define STEP_LEFT_MAX 900

void PWM_init()
{
	REG_PMC_PCER1 |= PMC_PCER1_PID36;                     // Enable PWM
	REG_PIOC_ABSR |= PIO_ABSR_P19;                        // Set PWM pin perhipheral type A or B, in this case B
	REG_PIOC_PDR |= PIO_PDR_P19;                          // Set PWM pin to an output
	REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(42);     // Set the PWM clock rate to 2MHz (84MHz/42)
	REG_PWM_CMR5 = PWM_CMR_CALG | PWM_CMR_CPRE_CLKA;      // Enable dual slope PWM and set the clock source as CLKA
	REG_PWM_CPRD5 = 20000;                                // Set the PWM frequency 2MHz/(2 * 20000) = 50Hz = 20ms
	REG_PWM_CDTY5 = 20000-STEP_CENTER;                           // Set the PWM duty cycle to 1500 - centre the servo
	REG_PWM_ENA = PWM_ENA_CHID5;                          // Enable the PWM channel
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int PWM_set_value(int8_t value)
{
	int16_t step_value = STEP_CENTER;
	
	// Value between 0 and 100
	
	step_value = map(value, 0, 100, STEP_LEFT_MAX, STEP_RIGHT_MAX);
	//printf("%d", step_value);
	
	if(step_value < STEP_LEFT_MAX || step_value > STEP_RIGHT_MAX)
	{
		// Error: Value is outside range
		return 1;
	} else {
		REG_PWM_CDTY5 = 20000-step_value;
	}
}