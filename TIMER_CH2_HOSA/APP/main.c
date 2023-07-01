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

volatile char compareMatches = 0;
volatile uint8 OCRValue = 0;
// How to do different frequencies using OCR0 only?
// I will calculate the OCR0 of the largest frequency i have
// Then calculate the ticks for different other frequencies

/*
ISR(TIMER0_COMP_vect) {
	compareMatches++;
	LED_Toggle(PORT_C, PIN_0);

	if(compareMatches == 2) {
		LED_Toggle(PORT_C, PIN_1);
	}
	else if(compareMatches == 4) {
		LED_Toggle(PORT_C, PIN_1);
		LED_Toggle(PORT_C, PIN_2);
		compareMatches = 0;
	}
}
*/

ISR(TIMER0_COMP_vect) {
	LED_Toggle(PORT_C, PIN_0
			);
	if(OCR0 ==OCRValue) {
		LED_Toggle(PORT_C, PIN_1);
	}
}

int main(void) {

	float requiredFrequency1		= 		10		; 	// Required Frequency in KHz
	float requiredFrequency2 	= 		5		; 	// Required Frequency in KHz
	float requiredFrequency3 	= 		2.5	; 	// Required Frequency in KHz

	GPIO_setupPinDirection(PORT_C, PIN_0, PIN_OUTPUT);
	GPIO_setupPinDirection(PORT_C, PIN_1, PIN_OUTPUT);
	GPIO_setupPinDirection(PORT_C, PIN_2, PIN_OUTPUT);

	//Timer_setCTCMode_interruptFreq(requiredFrequency1);

	OCRValue = Timer_setCTCMode_interruptFreq(requiredFrequency1);

	while (1) {

	}
}

