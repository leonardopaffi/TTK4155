#ifndef CAN_CONTROLLER_H
#define CAN_CONTROLLER_H

#include "SPI.h"
#include "mcp2515.h"

// From the Register Map table 11.1 page 63 of MCP2515 datasheet
#define MCP_TXB0SIDH	0x31
#define MCP_TXB0SIDL	0x32
#define MCP_TXB0DLC		0x35
#define MCP_TXB0D0		0x36
#define MCP_RXB0SIDL	0X62
#define MCP_RXB0DLC		0x65
#define MCP_RXB0D0		0x66
#define MCP_RXB1SIDL	0X72
#define MCP_RXB1DLC		0X75
#define MCP_RXB1D0		0x76

/**
 * @brief Reading instruction for the MCP2515
 * 
 * @param address Address of the register to read
 * @return uint8_t 
 */
uint8_t MCP2515_read(uint8_t address);

/**
 * @brief Writing data to a register of the MCP2515
 * 
 * @param address 
 * @param data 
 */
void MCP2515_write(uint8_t address, uint8_t data);

/**
 * @brief Ready To Send instruction for the MCP2515
 * 
 * @param buffer 
 */
void MCP2515_RTS(uint8_t buffer);

/**
 * @brief Read status instruction for the MCP2515
 * 
 * @return uint8_t 
 */
uint8_t MCP2515_read_status();

/**
 * @brief Modify bit/bits of a register providing a mask and the new data 
 * 
 * @param address 
 * @param byte_mask 
 * @param data 
 */
void MCP2515_bit_modify(uint8_t address, uint8_t byte_mask, uint8_t data);

/**
 * @brief Reset the MCP2515
 * 
 */
void MCP2515_reset();

/**
 * @brief Set mode for the MCP2515
 * 
 * @param mode 
 */
void MCP2515_set_mode(uint8_t mode);

#endif