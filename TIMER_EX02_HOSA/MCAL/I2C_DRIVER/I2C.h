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

#ifndef I2C_H_
#define I2C_H_

#include "../GPIO_DRIVER/GPIO.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"

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
 *                              						 Predecessor Macros                           					  *
 *******************************************************************************/

// A better naming for the I2C Connection pins
#define SCL 								PIN_0
#define SDA 								PIN_1
#define I2C_SLAVE_ADDR 		0x02	// Slave Address = 0b00000010
#define I2C_INITIALSTATUS 	0xF8	// Masking to eliminate 1st 3 bits & get last 5 bits 0b11111000

// I2C Status Bits in the TWSR Register, found in tables 74 & 75 in the Data sheet
#define I2C_START         				0x08 	// start has been sent
#define I2C_REP_START     			0x10 	// repeated start
#define I2C_MT_SLA_W_ACK 	0x18 	// Master transmit ( slave address + Write request ) to slave + ACK received from slave.
#define I2C_MT_SLA_W_NACK 	0x20 	// Master transmit ( slave address + Write request ) to slave + Not ACK received from slave.
#define I2C_MT_DATA_ACK		0x28 	// Master transmit data + ACK has been received from Slave.
#define I2C_MT_DATA_NACK   	0x30 	// Master transmit data + Not ACK has been received from Slave.
#define I2C_ARBIT_LOST   			0x38 	// Arbitration lost in (Slave + Write) or Data bytes
#define I2C_MT_SLA_R_ACK  	0x40 	// Master transmit ( slave address + Read request ) to slave + ACK received from slave.
#define I2C_MT_SLA_R_NACK  	0x48 	// Master transmit ( slave address + Read request ) to slave + Not ACK received from slave.
#define I2C_MR_DATA_ACK   		0x50 	// Master received data + received ACK from slave.
#define I2C_MR_DATA_NACK 	0x58 	// Master received data + received Not ACK from slave.


/*******************************************************************************
 *                              						Functions Prototypes                           					  *
 *******************************************************************************/

// Initializes and enables the SPI Module to start functionality
void I2C_init(void);

// Responsible for the SPI to send an array of bytes, a string
void I2C_start(void);

// Responsible for the SPI to receive an array of bytes, a string
void I2C_stop(void);

// Responsible for the SPI to receive an array of bytes, a string
void I2C_writeByte(uint8 data);

// Responsible for the SPI to receive an array of bytes, a string
uint8 I2C_readByteWithACK(void);

// Responsible for the SPI to receive an array of bytes, a string
uint8 I2C_readByteWithNACK(void);

// Responsible for the SPI to receive an array of bytes, a string
uint8 I2C_getStatus(void);

#endif /* I2C_H_ */
