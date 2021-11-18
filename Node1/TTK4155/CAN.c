#include "CAN.h"

void CAN_init(uint8_t mode)
{
	MCP2515_reset();
	
	printf("%x", MCP2515_read(MCP_CANSTAT));
	
	MCP2515_write(MCP_CNF3, 0b00000001);
	MCP2515_write(MCP_CNF2, 0b10110101);
	MCP2515_write(MCP_CNF1, 0b00000011);
	
	MCP2515_set_mode(mode);
	
	// Enables output interrupt
	MCP2515_write(MCP_CANINTE, 0X03);	
}

void CAN_send(CAN_message message)
{
	// Writing ID registers
	MCP2515_write(MCP_TXB0SIDH, message.id >> 3);
	MCP2515_write(MCP_TXB0SIDL, message.id << 5);
	// Setting message length
	MCP2515_write(MCP_TXB0DLC, message.length);
	
	// Sending message
	for(uint8_t i = 0; i < (message.length); i++){
		MCP2515_write(MCP_TXB0D0 + i, message.data[i]);
		//printf("\r\nSENDING MESSAGE: \r\n data: %d\r\n", message.data[i]);
	}
	//printf("\r\n");
	// Enables sending
	MCP2515_RTS(MCP_RTS_TX0);
}


void CAN_receive(void){
	CAN_message msg;

	// Checks buffer0 
	if(MCP2515_read_status() & 0x01){
		// Reading ID
		msg.id = (MCP2515_read(MCP_RXB0SIDH) << 3)|(MCP2515_read(MCP_RXB0SIDL) >> 5);
		// Reading message length
		msg.length = MCP2515_read(MCP_RXB0DLC);
		// Reading message
		for(uint8_t i = 0; i < (msg.length); i++){
			msg.data[i] = MCP2515_read(MCP_RXB0D0 + i);
			//CAN_debug_print(msg.id, msg.data[i], i);
		}
		// Clearing CANINTF to allow new message to be received
		MCP2515_bit_modify(MCP_CANINTF, 0x01, 0x00);
	}
	
	// Checks buffer1
	if(MCP2515_read_status() & 0x02){
		// Reading ID
		msg.id = (MCP2515_read(MCP_RXB1SIDH) << 3)|(MCP2515_read(MCP_RXB1SIDL) >> 5);
		// Reading message length
		msg.length = MCP2515_read(MCP_RXB1DLC);
		// Reading message
		for(uint8_t i = 0; i < (msg.length); i++){
			msg.data[i] = MCP2515_read(MCP_RXB1D0 + i);
			//CAN_debug_print(msg.id, msg.data[i], i);
		}
		// Clearing CANINTF to allow new message to be received
		MCP2515_bit_modify(MCP_CANINTF,0x02, 0x00);
	}
}

void CAN_debug_print(uint8_t id, char data, uint8_t position)
{
	printf("INCOMING DATA BYTE: \r\n data[%d]: %c \r\n id: %d\r\n", position, data, id);
}