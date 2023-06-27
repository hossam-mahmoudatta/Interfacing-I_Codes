 /******************************************************************************
 *
 * Module: I2C (Inter Integrated Circuit)
 *
 * File Name: I2C.h
 *
 * Description: Header file for the AVR I2C Driver
 *
 * Author: Hossam Mahmoud
 *
 *******************************************************************************/

/*******************************************************************************
 *                              					 Application Libraries                                					  *
 *******************************************************************************/

#include "I2C.h"

#include "avr/io.h" /* To use the IO Ports Registers */
#include <util/delay.h>

/* TWBR - TWI Bit Rate Register
  *  Bit 7..0 – TWBR: TWI Bit Rate Register
  */

/* TWCR - TWI Control Register
  *  Bit 7 – TWINT: TWI Interrupt Flag
  *  Bit 6 – TWEA: TWI Enable Acknowledge Bit
  *  Bit 5 – TWSTA: TWI Start Condition Bit
  *  Bit 4 – TWSTO: TWI Stop Condition Bit
  *  Bit 3 – TWWC: TWI Write Collision Flag
  *  Bit 2 – TWEN: TWI Enable Bit
  *  Bit 1 – RES: Reserved Bit
  *  Bit 0 – TWIE: TWI Interrupt Enable
  */

/* TWSR - TWI Status Register
  *  Bit 7..3 – TWS: TWI Status
  *  Bit 2 – Res: Reserved Bit
  *  Bit 1..0 – TWPS: TWI Prescaler Bits
  */

/* TWDR - TWI Data Register
  *  Bit 7..0 – TWDR: TWI Data Register
  */

/* TWAR - TWI (Slave) Address Register
  *  Bit 7..1 – TWA: TWI (Slave) Address Register
  *  Bit 0 – TWGCE: TWI General Call Recognition Enable Bit
  */

/*******************************************************************************
 *                              					Module Implementation                              					  *
 *******************************************************************************/

// Initializes and enables the Master mode for the TWI Module to start functionality
void I2C_init(void) {
	/* For TWBR
	 * SCL Freq = (F_CPU) / (16 + 2 * TWBR * 4^TWPS)
	 * In the previous equation, I have two unknowns, the TWBR & TWPS
	 * Its the prescaler bits.. so what to choose?
	 * I know that the SCL is 400 KHz, & F_CPU is 8 MHz
	 * I can control TWPS & let it, TWPS = 0, so TWBR = 2
	 */
	TWSR = 0x00;
	TWBR = 0x02;
	TWAR = I2C_SLAVE_ADDR; // Slave Address
	TWCR = (1 << TWEN); // Enabling the I2C Module

}

// Responsible for the SPI to send an array of bytes, a string
void I2C_start(void) {
	// Again enabling the I2C Module, Set the Start Condition, Clearing the TWINT Flag
	/* But why I'm not using the normal set bit technique?
	 * Because I don't want to keep old data, & I want the information always set by me
	 */
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTA);

	while(BIT_IS_CLR(TWCR, TWINT)) {
		// Busy Wait for TWINT set in TWCR Register
		// to ensure that start bit is send successfully
	}
}

// Responsible for the SPI to receive an array of bytes, a string
void I2C_stop(void) {
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTO);
}

// Responsible for the SPI to receive an array of bytes, a string
void I2C_writeByte(uint8 data) {
	TWCR = (1 << TWEN) | (1 << TWINT);
	TWDR = data;

	while(BIT_IS_CLR(TWCR, TWINT)) {
		// Busy Wait for TWINT set in TWCR Register
		// to ensure that data is sent successfully
	}
}

// Responsible for the SPI to receive an array of bytes, a string
uint8 I2C_readByteWithACK(void) {
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);

	while(BIT_IS_CLR(TWCR, TWINT)) {
		// Busy Wait for TWINT set in TWCR Register
		// to ensure that data is sent successfully
	}
	return TWDR;
}

// Responsible for the SPI to receive an array of bytes, a string
uint8 I2C_readByteWithNACK(void) {
	TWCR = (1 << TWEN) | (1 << TWINT);

	while(BIT_IS_CLR(TWCR, TWINT)) {
		// Busy Wait for TWINT set in TWCR Register
		// to ensure that data is sent successfully
	}
	return TWDR;
}

// Responsible for the SPI to receive an array of bytes, a string
uint8 I2C_getStatus(void) {
	uint8 I2CStatus;
	I2CStatus = TWSR & I2C_INITIALSTATUS;
	return I2CStatus;
}
