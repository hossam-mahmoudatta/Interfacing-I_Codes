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
	LED_Init(PORT_C, PIN_1);

	// Initializes the Buttons
	BUTTON_Init(PORT_B, PIN_0);
	BUTTON_Init(PORT_B, PIN_1);

	while (1) {
		if ( (BUTTON_Read(PORT_B, PIN_0) == LOGIC_HIGH) && (BUTTON_Read(PORT_B, PIN_1) == LOGIC_HIGH) ) {
			LED_Off(PORT_C, PIN_0);
			LED_Off(PORT_C, PIN_1);
		} // If both buttons are pressed, then both LEDs should work

		else if ( (BUTTON_Read(PORT_B, PIN_0) == LOGIC_LOW) && (BUTTON_Read(PORT_B, PIN_1) == LOGIC_LOW) ) {
			LED_On(PORT_C, PIN_0);
			LED_On(PORT_C, PIN_1);
		} // If both buttons are NOT pressed, then both LEDs SHOULDN'T work

		else if ( (BUTTON_Read(PORT_B, PIN_0) == LOGIC_HIGH) && (BUTTON_Read(PORT_B, PIN_1) == LOGIC_LOW) ) {
			LED_Off(PORT_C, PIN_0);
			LED_On(PORT_C, PIN_1);
		} // If button0 is pressed, then only LED0 should work

		else if ( (BUTTON_Read(PORT_B, PIN_0) == LOGIC_LOW) && (BUTTON_Read(PORT_B, PIN_1) == LOGIC_HIGH) ) {
			LED_On(PORT_C, PIN_0);
			LED_Off(PORT_C, PIN_1);
		} // If button1 is pressed, then only LED1 should work
	}
}



