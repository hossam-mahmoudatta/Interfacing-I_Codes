/*
 * main.c
 *
 *  Created on: May 2, 2023
 *      Author: Administrator
 */
#include <util/delay.h>
#include "../MCAL/GPIO_DRIVER/GPIO.h"
#include <stdio.h>

int main(void) {
	// Setups the Switch I/O
	GPIO_setupPinDirection(PORT_D, PIN_2, PIN_INPUT);
	// Setups the LED I/O
	GPIO_setupPinDirection(PORT_C, PIN_1, PIN_OUTPUT);

	while (1) {
		// Here it checks if the switch is pressed
		// If pressed, it will put voltage on the LED pin
		if (GPIO_readPin(PORT_D, PIN_2) == LOGIC_LOW) {
			GPIO_writePin(PORT_C, PIN_1, LOGIC_HIGH);
		}
		// Here it checks if the switch is not pressed
		// If not pressed, it will remove voltage on the LED pin
		else if (GPIO_readPin(PORT_D, PIN_2) == LOGIC_HIGH) {
		    GPIO_writePin(PORT_C, PIN_1, LOGIC_LOW);
		}
	}
}



