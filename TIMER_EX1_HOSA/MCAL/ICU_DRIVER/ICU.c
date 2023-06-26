 /******************************************************************************
 *
 * Module: ADC (Analog to Digital Converter)
 *
 * File Name: ADC.c
 *
 * Description: Source file for the AVR ADC Driver
 *
 * Author: Hossam Mahmoud
 *
 *******************************************************************************/

#include "ICU.h"

#include "avr/io.h" /* To use the IO Ports Registers */
#include <util/delay.h>
//#include <avr/interrupt.h>


// Initializes and enables the ADC Module to start functionality
void ICU_Init(void) {

	/* TCCR1A Register Bits Description:
	 * 7:6 - COM1A1:0: Compare Output Mode for Compare Unit A
	 * 5:4 – COM1B1:0: Compare Output Mode for Compare Unit B
	 * 3 – FOC1A: Force Output Compare for Compare unit A
	 * 2 – FOC1B: Force Output Compare for Compare unit B
	 * 1:0 – WGM11:0: Waveform Generation Mode
	 */

	// Clears COM1A1:0 to '00', I want normal mode
	CLR_BIT(TCCR1A, COM1A1);
	CLR_BIT(TCCR1A, COM1A0);

	// Clears COM1B1:0 to '00', I want normal mode
	CLR_BIT(TCCR1A, COM1B1);
	CLR_BIT(TCCR1A, COM1B0);

	// Sets FOC1A to '1', I'm in normal mode
	SET_BIT(TCCR1A, FOC1A);

	// Sets FOC1A to '1', I'm in normal mode
	SET_BIT(TCCR1A, FOC1B);

	// Clears COM1B1:0 to '00', I want normal mode
	CLR_BIT(TCCR1A, WGM11);
	CLR_BIT(TCCR1A, WGM10);


	/* TCCR1B Register Bits Description:
	 * Bit 7 – ICNC1: Input Capture Noise Canceler
	 * Bit 6 – ICES1: Input Capture Edge Select
	 * Bit 5 – Reserved Bit
	 * Bit 4:3 – WGM13:2: Waveform Generation Mode
	 * Bit 2:0 – CS12:0: Clock Select
	 */

	// Clears ICNC1 to '0', I DONT want the noise canceling
	CLR_BIT(TCCR1B, ICNC1);

	// Sets ICES1 to '1', I want the rising edge
	SET_BIT(TCCR1B, ICES1);

	// Sets CS12:0 to '001', nO PRESCALING
	CLR_BIT(TCCR1B, CS12);
	CLR_BIT(TCCR1B, CS11);
	SET_BIT(TCCR1B, CS10);

	// Clears TCNT1 to '0', Initialize to '0'
	TCNT1 = 0;

	// Clears ICR1 to '0', Initialize to '0'
	ICR1 = 0;

	/* TIMSK Register Bits Description:
	 * Bit 5 – TICIE1: Timer/Counter1, Input Capture Interrupt Enable
	 * Bit 4 – OCIE1A: Timer/Counter1, Output Compare A Match Interrupt Enable
	 * Bit 3 – OCIE1B: Timer/Counter1, Output Compare B Match Interrupt Enable
	 * Bit 2 – TOIE1: Timer/Counter1, Overflow Interrupt Enable
	 */

	// TIMSK1 |= (1 << TICIE1);
	// SREG |= (1 << 7);

}

void ICU_setCallBack(void(*a_ptr)(void));

void ICU_setEdgeDetection(const ICU_EdgeType edgeType);

// Description: Function to get the Timer1 Value when the input is captured The value stored at Input Capture Register ICR1
uint16 ICU_getInputCaptureValue(void);

 // clear the Timer1 Value to start count from ZERO
void ICU_clearTimerValue(void);

// disable the Timer1 to stop the ICU Driver
void ICU_DeInit(void);
