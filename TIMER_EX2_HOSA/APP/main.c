/******************************************************************************
 *
 * Application
 *
 * File Name: main.c
 *
 * Description: Application file for this exercise
 *
 * Author: Hossam Mahmoud
 *
 *******************************************************************************/


/*******************************************************************************
 *                              					 Application Libraries                                					  *
 *******************************************************************************/

//#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                              						  Modules Drivers                                  					  *
 *******************************************************************************/

//#include "../MCAL/ADC_DRIVER/ADC.h"
//#include "../MCAL/EXT_INTERRUPT_DRIVER/EXT_INTERRUPT.h"
//#include "../MCAL/I2C_DRIVER/I2C.h"
//#include "../MCAL/ICU_DRIVER/ICU.h"
//#include "../MCAL/SPI_DRIVER/SPI.h"
#include "../MCAL/TIMER_DRIVER/TIMER.h"
//#include "../MCAL/USART_DRIVER/USART.h"
//#include "../MCAL/EXT_INTERRUPT_DRIVER/EXT_INTERRUPT.h"

//#include "../ECUAL/EEPROM_DRIVER/EEPROM.h"
//#include "../ECUAL/KEYPAD_DRIVER/KEYPAD.h"
//#include "../ECUAL/LCD_DRIVER/LCD.h"
//#include "../ECUAL/LM35_DRIVER/LM35.h"
//#include "../ECUAL/SEVEN-SEGMENT_DRIVER/SEGMENT.h"
//#include "../ECUAL/BUTTON_DRIVER/BUTTON.h"
#include "../ECUAL/LED_DRIVER/LED.h"

/*******************************************************************************
 *                              						Application Execution                              					  *
 *******************************************************************************/

float32 delay = 3;
char tick = 0;

#define NUM_OF_OVERFLOWS_PER_SECOND 4


ISR(TIMER0_OVF_vect) {
	TCNT0 = 6;
	tick++;
	if(tick == NUM_OF_OVERFLOWS_PER_SECOND) {
		LED_Toggle(PORT_C, PIN_0);   //toggle led every 1 second
		tick = 0;                 //clear the tick counter again to count a new 0.5 second
	}
}

int main(void) {
	LED_Init(PORT_C, PIN_0); // Initializes LED Driver
	SET_BIT(SREG, 7); // Sets the I bit in the Status register
	Timer0_Init(); // Initializes Timer 0
	TCNT0 = 6; // Initializes the starting point of the counter in Timer0

	while (1) {

	}
}



