#include "CAN_Controller.h"

uint8_t MCP2515_read(uint8_t address)
{
	uint8_t value;
	SPI_slave_enable();
	SPI_master_transmit(MCP_READ);
	SPI_master_transmit(address);
	value = SPI_master_read();
	SPI_slave_disable();
	
	return value;
}

void MCP2515_write(uint8_t address, uint8_t data)
{
	SPI_slave_enable();
	SPI_master_transmit(MCP_WRITE);
	SPI_master_transmit(address);
	SPI_master_transmit(data);
	SPI_slave_disable();
}

void MCP2515_RTS(uint8_t buffer)
{
	if(buffer==MCP_RTS_TX0 || buffer==MCP_RTS_TX1 || buffer==MCP_RTS_TX2 || buffer==MCP_RTS_ALL)
	{
		SPI_slave_enable();
		SPI_master_transmit(buffer);
		SPI_slave_disable();
	} else {
		printf("%d is not a Buffer. RTS function error", buffer);
	}
}

uint8_t MCP2515_read_status()
{
	uint8_t value;
	SPI_slave_enable();
	SPI_master_transmit(MCP_READ_STATUS);
	value = SPI_master_read();
	SPI_slave_disable();
	
	return value;
}

void MCP2515_bit_modify(uint8_t address, uint8_t byte_mask, uint8_t data)
{
	SPI_slave_enable();
	SPI_master_transmit(MCP_BITMOD);
	SPI_master_transmit(address);
	SPI_master_transmit(byte_mask);
	SPI_master_transmit(data);
	SPI_slave_disable();
}

void MCP2515_reset()
{
	SPI_slave_enable();
	SPI_master_transmit(MCP_RESET);
	SPI_slave_disable();
}

void MCP2515_set_mode(uint8_t mode)
{
	MCP2515_bit_modify(MCP_CANCTRL, 0xE0, mode);
}