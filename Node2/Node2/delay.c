#include "delay.h"

void test_delay_us(int16_t value)
{
	SysTick -> LOAD = 0x00FFFFFF;
	SysTick -> CTRL = 0x00000005;
	
	
	SysTick -> LOAD = value-1;
	SysTick -> VAL = 0;
	
	while((SysTick->CTRL&0x00010000) == 0) {};
	
	printf("delayed");
}

void delay_us(uint16_t value)
{
	for(int i = value; i > 0; i--)
		asm("NOP");
}