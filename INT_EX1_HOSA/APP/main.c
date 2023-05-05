/*
 * main.c
 *
 *  Created on: May 2, 2023
 *      Author: Administrator
 */
#include <util/delay.h>
#include <avr/io.h>
//#include "../MCAL/LED_DRIVER/LED.h"
#include "../MCAL/BUTTON_DRIVER/BUTTON.h"
#include "../MCAL/SEVEN-SEGMENT_DRIVER/SEGMENT.h"

int main(void) {

	// Initializes the Buttons
	BUTTON_Init(PORT_D, PIN_4);
	SEGMENT_Init(PORT_C);
	uint8 counter = 0;

	while (1) {

		if ( (BUTTON_Read(PORT_D, PIN_4) == LOGIC_HIGH) ) {
			_delay_ms(30);
			if ( (BUTTON_Read(PORT_D, PIN_4) == LOGIC_HIGH) ) {
				if (counter > 9) {
					counter = 0;
					continue;
				}
				else if ( (counter >= 0) && (counter <= 9) ) {
					SEGMENT_DISPLAY(PORT_C, counter);
				}
				counter++;
			}
			while ( (BUTTON_Read(PORT_D, PIN_4) == LOGIC_HIGH) ) { };
		}
	}
}



