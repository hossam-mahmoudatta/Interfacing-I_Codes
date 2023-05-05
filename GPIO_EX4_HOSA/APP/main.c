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
	LED_On(PORT_C, PIN_0);
	uint8 flag = 0;
	while (1) {
		// So how to think about it?
		// There must be a flag or a counter, I guess i can do it by
		// if the counter is odd, then the led must be on
		// if the counter is even, then the led must be off
		// i guess i will make a nested if cond that checks if the button is pressed. so lets try this algo!

		if ( (BUTTON_Read(PORT_B, PIN_0) == LOGIC_LOW) ) {
			_delay_ms(20);
			flag++;
			if (flag % 2 != 0 ) {
				LED_Off(PORT_C, PIN_0);
			}
			else if (flag % 2 == 0 ) {
				LED_On(PORT_C, PIN_0);
			}
		} // If both buttons are pressed, then both LEDs should work
	}
}



