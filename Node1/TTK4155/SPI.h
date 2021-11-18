#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

/**
 * @brief Enable the SPI slave
 * 
 */
void SPI_slave_enable();

/**
 * @brief Disable the SPI slave
 * 
 */
void SPI_slave_disable();

/**
 * @brief Initialize the SPI master
 * 
 */
void SPI_master_init();

/**
 * @brief Transmit data with SPI
 * 
 * @param cData 
 */
void SPI_master_transmit(char cData);

/**
 * @brief Read data with SPI
 * 
 * @return char 
 */
char SPI_master_read();

#endif
