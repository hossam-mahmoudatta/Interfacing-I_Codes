/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: GPIO.c
 *
 * Description: Source file for the AVR GPIO driver
 *
 * Author: Hossam Mahmoud
 *
 *******************************************************************************/

#include "SEGMENT.h"

#include "avr/io.h" /* To use the IO Ports Registers */

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
SEGMENT_Error_t SEGMENT_Init(uint8 port_num) {
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	uint8_t SEGMENT_Driver_Checker = NULL;

	if((port_num >= NUM_OF_PORTS)) {
		SEGMENT_Driver_Checker = SEGMENT_WRONG_PORT_NUMBER;
	}
	else {
		/* Setup the pin direction as required */
		GPIO_setupPinDirection(port_num, PIN_0, PIN_OUTPUT);
		GPIO_setupPinDirection(port_num, PIN_1, PIN_OUTPUT);
		GPIO_setupPinDirection(port_num, PIN_2, PIN_OUTPUT);
		GPIO_setupPinDirection(port_num, PIN_3, PIN_OUTPUT);
		SEGMENT_Driver_Checker = SEGMENT_OK;
	}
	return SEGMENT_Driver_Checker;
}

SEGMENT_Error_t SEGMENT_DISPLAY(uint8 port_num, uint8 value) {
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	uint8_t SEGMENT_Driver_Checker = NULL;

	if((port_num >= NUM_OF_PORTS)) {
		SEGMENT_Driver_Checker = SEGMENT_WRONG_PORT_NUMBER;
	}
	else if((value < 0 && value > 9)) {
		SEGMENT_Driver_Checker = SEGMENT_WRONG_VALUE;
	}
	else {
		switch(value) {
			case 0:
				GPIO_writePin(port_num, PIN_0, LOGIC_LOW);
				GPIO_writePin(port_num, PIN_1, LOGIC_LOW);
				GPIO_writePin(port_num, PIN_2, LOGIC_LOW);
				GPIO_writePin(port_num, PIN_3, LOGIC_LOW);
				break;
			case 1:
				GPIO_writePin(port_num, PIN_0, LOGIC_HIGH);
				GPIO_writePin(port_num, PIN_1, LOGIC_LOW);
				GPIO_writePin(port_num, PIN_2, LOGIC_LOW);
				GPIO_writePin(port_num, PIN_3, LOGIC_LOW);
				break;
			case 2:
				GPIO_writePin(port_num, PIN_0, LOGIC_LOW);
				GPIO_writePin(port_num, PIN_1, LOGIC_HIGH);
				GPIO_writePin(port_num, PIN_2, LOGIC_LOW);
				GPIO_writePin(port_num, PIN_3, LOGIC_LOW);
				break;
			case 3:
				GPIO_writePin(port_num, PIN_0, LOGIC_HIGH);
				GPIO_writePin(port_num, PIN_1, LOGIC_HIGH);
				GPIO_writePin(port_num, PIN_2, LOGIC_LOW);
				GPIO_writePin(port_num, PIN_3, LOGIC_LOW);
				break;
			case 4:
				GPIO_writePin(port_num, PIN_0, LOGIC_LOW);
				GPIO_writePin(port_num, PIN_1, LOGIC_LOW);
				GPIO_writePin(port_num, PIN_2, LOGIC_HIGH);
				GPIO_writePin(port_num, PIN_3, LOGIC_LOW);
				break;
			case 5:
				GPIO_writePin(port_num, PIN_0, LOGIC_HIGH);
				GPIO_writePin(port_num, PIN_1, LOGIC_LOW);
				GPIO_writePin(port_num, PIN_2, LOGIC_HIGH);
				GPIO_writePin(port_num, PIN_3, LOGIC_LOW);
				break;
			case 6:
				GPIO_writePin(port_num, PIN_0, LOGIC_LOW);
				GPIO_writePin(port_num, PIN_1, LOGIC_HIGH);
				GPIO_writePin(port_num, PIN_2, LOGIC_HIGH);
				GPIO_writePin(port_num, PIN_3, LOGIC_LOW);
				break;
			case 7:
				GPIO_writePin(port_num, PIN_0, LOGIC_HIGH);
				GPIO_writePin(port_num, PIN_1, LOGIC_HIGH);
				GPIO_writePin(port_num, PIN_2, LOGIC_HIGH);
				GPIO_writePin(port_num, PIN_3, LOGIC_LOW);
				break;
			case 8:
				GPIO_writePin(port_num, PIN_0, LOGIC_LOW);
				GPIO_writePin(port_num, PIN_1, LOGIC_LOW);
				GPIO_writePin(port_num, PIN_2, LOGIC_LOW);
				GPIO_writePin(port_num, PIN_3, LOGIC_HIGH);
				break;
			case 9:
				GPIO_writePin(port_num, PIN_0, LOGIC_HIGH);
				GPIO_writePin(port_num, PIN_1, LOGIC_LOW);
				GPIO_writePin(port_num, PIN_2, LOGIC_LOW);
				GPIO_writePin(port_num, PIN_3, LOGIC_HIGH);
				break;
		}
		SEGMENT_Driver_Checker = SEGMENT_OK;
	}
	return SEGMENT_Driver_Checker;
}
