 /******************************************************************************
 *
 * Module: GPIO (General Purpose I/O
 *
 * File Name: GPIO.h
 *
 * Description: Header file for the AVR GPIO Driver
 *
 * Author: Hossam Mahmoud
 *
 *******************************************************************************/

#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../MCAL/GPIO_DRIVER/GPIO.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"


/*******************************************************************************
 *                                									Definitions                                  					           		  *
 *******************************************************************************/


/*******************************************************************************
 *                               							Types Declaration                            									  *
 *******************************************************************************/

typedef enum BUTTON_Error_t {
	BUTTON_OK,
	BUTTON_WRONG_PIN_NUMBER,
	BUTTON_WRONG_PORT_NUMBER
} BUTTON_Error_t;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
BUTTON_Error_t BUTTON_Init(uint8 port_num, uint8 pin_num);

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
uint8 BUTTON_Read(uint8 port_num, uint8 pin_num);

#endif
