/*
 * main.c
 *
 *  Created on: May 2, 2023
 *      Author: Administrator
 */
#include <util/delay.h>
#include <avr/io.h>
#include "../MCAL/LED_DRIVER/LED.h"

int main(void) {
	// Initializes the LED I/O
	LED_Init(PORT_C, PIN_2);

	while (1) {
		LED_Off(PORT_C, PIN_2);
		_delay_ms(2000);
		LED_On(PORT_C, PIN_2);
		_delay_ms(2000);
	}
}



