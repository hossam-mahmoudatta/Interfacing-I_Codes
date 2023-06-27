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

#include "BUTTON.h"

#include "avr/io.h" /* To use the IO Ports Registers */

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
BUTTON_Error_t BUTTON_Init(uint8 port_num, uint8 pin_num) {
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	uint8_t BUTTON_Driver_Checker = NULL;
	if((pin_num >= NUM_OF_PINS_PER_PORT)) {
		BUTTON_Driver_Checker = BUTTON_WRONG_PIN_NUMBER;
	}
	else if((port_num >= NUM_OF_PORTS)) {
		BUTTON_Driver_Checker = BUTTON_WRONG_PORT_NUMBER;
	}
	else {
		/* Setup the pin direction as required */
		GPIO_setupPinDirection(port_num, pin_num, PIN_INPUT);
		BUTTON_Driver_Checker = BUTTON_OK;
	}
	return BUTTON_Driver_Checker;
}

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
uint8 BUTTON_Read(uint8 port_num, uint8 pin_num) {

	uint8_t BUTTON_Driver_Checker = NULL;
		if((pin_num >= NUM_OF_PINS_PER_PORT)) {
			BUTTON_Driver_Checker = BUTTON_WRONG_PIN_NUMBER;
		}
		else if((port_num >= NUM_OF_PORTS)) {
			BUTTON_Driver_Checker = BUTTON_WRONG_PORT_NUMBER;
		}
		else {
			/* Setup the pin direction as required */
			GPIO_readPin(port_num, pin_num);
			BUTTON_Driver_Checker = BUTTON_OK;
		}
		return GPIO_readPin(port_num, pin_num);
}

