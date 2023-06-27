/******************************************************************************
 *
 * Module: EEPROM
 *
 * File Name: EEPROM.h
 *
 * Description: Header file for the AVR EEPROM driver
 *
 * Author: Hossam Mahmoud
 *
 *******************************************************************************/

#ifndef EEPROM_H_
#define EEPROM_H_

#include "../../MCAL/GPIO_DRIVER/GPIO.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"

#define ERROR 			0
#define SUCCESS 	1

/*******************************************************************************
 *                              						Functions Prototypes                           					  *
 *******************************************************************************/

uint8 EEPROM_writeByte(uint16 u16Address, uint8 u8Data);


uint8 EEPROM_readByte(uint16 u16Address, uint8 *u8Data);


#endif /* EEPROM_H_ */
