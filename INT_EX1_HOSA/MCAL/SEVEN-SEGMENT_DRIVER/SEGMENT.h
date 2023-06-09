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

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "../GPIO_DRIVER/GPIO.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"


/*******************************************************************************
 *                                									Definitions                                  					           		  *
 *******************************************************************************/


/*******************************************************************************
 *                               							Types Declaration                            									  *
 *******************************************************************************/

typedef enum SEGMENT_Error_t {
	SEGMENT_OK,
	SEGMENT_WRONG_VALUE,
	SEGMENT_WRONG_PORT_NUMBER
} SEGMENT_Error_t;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
SEGMENT_Error_t SEGMENT_Init(uint8 port_num);

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
SEGMENT_Error_t SEGMENT_DISPLAY(uint8 port_num, uint8 value);

#endif /* SEVEN-SEGMENT_H_ */
