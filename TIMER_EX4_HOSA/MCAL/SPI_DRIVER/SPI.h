 /******************************************************************************
 *
 * Module: SPI (Serial Peripheral Interface)
 *
 * File Name: SPI.h
 *
 * Description: Header file for the AVR SPI Driver
 *
 * Author: Hossam Mahmoud
 *
 *******************************************************************************/

#ifndef SPI_H_
#define SPI_H_

#include "../GPIO_DRIVER/GPIO.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"

// A better naming for the SPI Connection pins
#define SS 		PIN_4
#define MOSI 	PIN_5
#define MISO 	PIN_6
#define SCK 		PIN_7
#define SPI_DEF_DATA_VAL 0xFF // The default data value in the SPDR

/*******************************************************************************
 *                              						Functions Prototypes                           					  *
 *******************************************************************************/

// Initializes and enables the SPI Module to start functionality
void SPI_initMaster(void);
void SPI_initSlave(void);

// Responsible for the SPI to send & receive a byte
uint8 SPI_sendReceiveByte(uint8 data);

// Responsible for the SPI to send an array of bytes, a string
void SPI_sendString(const uint8 *str);

// Responsible for the SPI to receive an array of bytes, a string
void SPI_receiveString(uint8 *str);

#endif /* USART_H_ */
