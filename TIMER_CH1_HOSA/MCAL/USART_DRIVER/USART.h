 /******************************************************************************
 *
 * Module: USART (Universal Synchronous Asynchronous Receiver Transmitter)
 *
 * File Name: USART.h
 *
 * Description: Header file for the AVR USART Driver
 *
 * Author: Hossam Mahmoud
 *
 *******************************************************************************/

#ifndef USART_H_
#define USART_H_

#include "../GPIO_DRIVER/GPIO.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"


/*******************************************************************************
 *                              						Functions Prototypes                           					  *
 *******************************************************************************/

// Initializes and enables the USART Module to start functionality
void USART_Init(uint32 baudRate);

// Responsible for the USART to send a byte
void USART_sendByte(const uint8 data);

// Responsible for the USART to receive a byte
uint8 USART_receiveByte(void);

// Responsible for the USART to send an array of bytes, a string
void USART_sendString(const uint8 *str);

// Responsible for the USART to receive an array of bytes, a string
void USART_receiveString(uint8 *str);

#endif /* USART_H_ */
