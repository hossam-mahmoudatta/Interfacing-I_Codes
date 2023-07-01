/******************************************************************************
 *
 * Module: EEPROM
 *
 * File Name: EEPROM.c
 *
 * Description: Source file for the AVR EEPROM driver
 *
 * Author: Hossam Mahmoud
 *
 *******************************************************************************/

#include "EEPROM.h"
#include "../../MCAL/I2C_DRIVER/I2C.h"

#include "avr/io.h" /* To use the IO Ports Registers */
#include <util/delay.h>



uint8 EEPROM_writeByte(uint16 u16Address, uint8 u8Data) {
	I2C_start();
	if (I2C_getStatus() != I2C_START) {
	        return ERROR;
	}

	/*
	 * EEPROM address is 11 bits, the 3 MSB is the device address
	 * The other bits are the word address
	 * but the device address is again shifted to another 8 bit frame:
	 * the 4 MSB is 1010, then the Device Address, then R/W
	 */
	uint8 EEPROM_ADDRESS_EQN = (uint8) (0xA0 | ( (u16Address & 0x0700) >> 7) );
	// 0xA0 = 1010, 0x0700 = 0b111 0000 000
	I2C_writeByte(EEPROM_ADDRESS_EQN);
	if (I2C_getStatus() != I2C_MT_SLA_W_ACK) {
		return ERROR;
	}

	I2C_writeByte((uint8) (u16Address));
	if (I2C_getStatus() != I2C_MT_DATA_ACK) {
		return ERROR;
	}

	I2C_writeByte(u8Data);
	if (I2C_getStatus() != I2C_MT_DATA_ACK) {
		return ERROR;
	}

	I2C_stop();

	return SUCCESS;
}


uint8 EEPROM_readByte(uint16 u16Address, uint8 *u8Data) {
	I2C_start();
	if (I2C_getStatus() != I2C_START) {
			return ERROR;
	}

	/*
	 * EEPROM address is 11 bits, the 3 MSB is the device address
	 * The other bits are the word address
	 * but the device address is again shifted to another 8 bit frame:
	 * the 4 MSB is 1010, then the Device Address, then R/W
	 */
	uint8 EEPROM_ADDRESS_EQN = (uint8) (0xA0 | ( (u16Address & 0x0700) >> 7) );
	// 0xA0 = 1010, 0x0700 = 0b111 0000 000
	I2C_writeByte(EEPROM_ADDRESS_EQN);
	if (I2C_getStatus() != I2C_MT_SLA_W_ACK) {
		return ERROR;
	}

	I2C_writeByte((uint8) (u16Address));
	if (I2C_getStatus() != I2C_MT_DATA_ACK) {
		return ERROR;
	}

	I2C_start();
	if (I2C_getStatus() != I2C_REP_START) {
		return ERROR;
	}

	I2C_writeByte(EEPROM_ADDRESS_EQN | 1); // For Reading
	if (I2C_getStatus() != I2C_MT_SLA_R_ACK) {
		return ERROR;
	}

	*u8Data = I2C_readByteWithNACK();
	if (I2C_getStatus() != I2C_MR_DATA_NACK) {
		return ERROR;
	}

	I2C_stop();

	return SUCCESS;
}
