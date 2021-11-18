#ifndef USART_H
#define USART_H

#include <stdio.h>

/**
 * @brief Initialization function for the USART
 * 
 * @param ubrr USART bitrate
 */
void USART_Init(unsigned int ubrr);

/**
 * @brief Transmit data over the USART
 * 
 * @param data 
 * @return int 
 */
int USART_Transmit(unsigned char data);

/**
 * @brief Receives data over the USART
 * 
 * @return int Received data
 */
int USART_Receive();

#endif