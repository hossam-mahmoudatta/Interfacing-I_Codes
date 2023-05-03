/*
 * main.c
 *
 *  Created on: May 2, 2023
 *      Author: Administrator
 */
#include <util/delay.h>
#include <avr/io.h>
#include "../MCAL/LED_DRIVER/LED.h"
#include "../MCAL/BUTTON_DRIVER/BUTTON.h"

int main(void) {
	// Initializes the LED I/O
	LED_Init(PORT_C, PIN_0);

	// Initializes the Buttons
	BUTTON_Init(PORT_B, PIN_0);

	while (1) {
		if ( (BUTTON_Read(PORT_B, PIN_0) == LOGIC_HIGH) ) {
			LED_Toggle(PORT_C, PIN_0);
		} // If both buttons are pressed, then both LEDs should work

		else if ( (BUTTON_Read(PORT_B, PIN_0) == LOGIC_HIGH) ) {
			LED_On(PORT_C, PIN_0);
		} // If both buttons are pressed, then both LEDs should work
	}
}



