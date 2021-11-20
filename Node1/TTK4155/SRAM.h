#ifndef SRAM_H
#define SRAM_H

/**
 * @brief Initialization function for the SRAM
 * 
 */
void SRAM_init(void)
{
	/*Enabling memory reading*/
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM2);
}

#endif