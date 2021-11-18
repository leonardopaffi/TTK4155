#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

#define ADC_ADDRESS 0x1400

#define SINGLE_CHANNEL_SAMPLE 7

/**
 * @brief Pointer to the array of all addresses we will write to. ADC starting at 0x1400
 * 
 */
volatile char* ext_adc;

/**
 * @brief Data retrieved from the ADC
 * 
 */
volatile char ADC_data;

/**
 * @brief Initializes the ADC and its clock signal
 * 
 */
void adc_init(void);

/**
 * @brief Reads a certain analog channel of the ADC
 * 
 * @param channel 
 * @return uint8_t 
 */
uint8_t adc_read(uint8_t channel);

/**
 * @brief Initialization function of the ADC
 * 
 */
void adc_init();

/**
 * @brief Reading data from the ADC
 * 
 * @param channel 
 * @return uint8_t 
 */
uint8_t adc_read(uint8_t channel);

/**
 * @brief Debug function to read all the channels from the ADC
 * 
 */
void adc_read_all_channels();

#endif