 /******************************************************************************
 *
 * Module: Timer
 *
 * File Name: TIMER.c
 *
 * Description: Source file for the AVR Timer Driver
 *
 * Author: Hossam Mahmoud
 *
 *******************************************************************************/

/*******************************************************************************
 *                              					 Application Libraries                                				  *
 *******************************************************************************/

#include "TIMER.h"

#include "avr/io.h" /* To use the IO Ports Registers */
//#include <util/delay.h>
#include <math.h>


/*******************************************************************************
 *                              					Module Implementation                           					  *
 *******************************************************************************/

void Timer0_setPrescaler(void) {
#if (PRESCALER_VALUE == PRESCALER_1024)
	TCCR0 = (1<<CS02) | (1<<CS00);
#elif (PRESCALER_VALUE == PRESCALER_256)
	SET_BIT(TCCR0, CS02);
#elif (PRESCALER_VALUE == PRESCALER_64)
	TCCR0 = (1<<CS01) | (1<<CS00);
#elif (PRESCALER_VALUE == PRESCALER_8)
	SET_BIT(TCCR0, CS01);
#elif (PRESCALER_VALUE == PRESCALER_0)
	SET_BIT(TCCR0, CS00);
#elif (PRESCALER_VALUE == NO_CLOCK)
	CLR_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	CLR_BIT(TCCR0, CS02);
#else
	TCCR0 = (1<<CS02) | (1<<CS00);
#endif
}

void Timer0_setMode(void) {
#if (TIMER_MODE == NORMAL_MODE)
	Timer0_normalMode();
#elif (TIMER_MODE == COMPARE_MODE)
	Timer0_compareMode();
#elif (TIMER_MODE == PWM_MODE)
	Timer0_fastPWMMode();
#else
	Timer0_normalMode();
#endif
}

void Timer0_normalMode(void) {
	SET_BIT(TCCR0, FOC0);
	CLR_BIT(TCCR0, WGM00);
	CLR_BIT(TCCR0, WGM01);
	CLR_BIT(TCCR0, COM01);
	CLR_BIT(TCCR0, COM00);
#if (INTERRUPT_MODE == INTERRUPT_ENABLE)
	SET_BIT(TIMSK, TOIE0);
#elif (INTERRUPT_MODE == INTERRUPT_DISABLE)
	CLR_BIT(TIMSK, TOIE0);
#endif
}

void Timer0_compareMode(void) {
	//GPIO_setupPinDirection(PORT_B, PIN_3, PIN_OUTPUT);
	SET_BIT(TCCR0, FOC0);
	CLR_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);
#if (INTERRUPT_MODE == INTERRUPT_ENABLE)
	SET_BIT(TIMSK, OCIE0);
	SET_BIT(SREG, 7); // Bit 7 – i bit: Global Interrupt Enable
#elif (INTERRUPT_MODE == INTERRUPT_DISABLE)
	CLR_BIT(TIMSK, OCIE0);
#endif

#if (CTC_MODE == CTC_NORMAL)
	CLR_BIT(TCCR0, COM01);
	CLR_BIT(TCCR0, COM00);
#elif (CTC_MODE == CTC_TOGGLE)
	CLR_BIT(TCCR0, COM01);
	SET_BIT(TCCR0, COM00);
#elif (CTC_MODE == CTC_CLEAR)
	SET_BIT(TCCR0, COM01);
	CLR_BIT(TCCR0, COM00);
#elif (CTC_MODE == CTC_SET)
	SET_BIT(TCCR0, COM01);
	SET_BIT(TCCR0, COM00);
#endif
}

void Timer0_fastPWMMode(void) {
	CLR_BIT(TCCR0, FOC0);
	SET_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);
#if (FASTPWM_MODE == FASTPWM_NORMAL)
	CLR_BIT(TCCR0, COM01);
	CLR_BIT(TCCR0, COM00);
#elif (FASTPWM_MODE == FASTPWM_NOINVERT)
	SET_BIT(TCCR0, COM01);
	CLR_BIT(TCCR0, COM00);
#elif (FASTPWM_MODE == FASTPWM_INVERT)
	SET_BIT(TCCR0, COM01);
	SET_BIT(TCCR0, COM00);
#endif
}



void Timer1_setPrescaler(void) {
	switch(PRESCALER_VALUE) {
		case PRESCALER_1024:
			SET_BIT(TCCR1B, CS10);
			CLR_BIT(TCCR1B, CS11);
			SET_BIT(TCCR1B, CS12);
		break;

		case PRESCALER_256:
			CLR_BIT(TCCR1B, CS10);
			CLR_BIT(TCCR1B, CS11);
			SET_BIT(TCCR1B, CS12);
		break;

		case PRESCALER_64:
			SET_BIT(TCCR1B, CS10);
			SET_BIT(TCCR1B, CS11);
			CLR_BIT(TCCR1B, CS12);
		break;

		case PRESCALER_8:
			CLR_BIT(TCCR1B, CS10);
			SET_BIT(TCCR1B, CS11);
			CLR_BIT(TCCR1B, CS12);
		break;

		case PRESCALER_0:
			SET_BIT(TCCR1B, CS10);
			CLR_BIT(TCCR1B, CS11);
			CLR_BIT(TCCR1B, CS12);
		break;

		case NO_CLOCK:
			CLR_BIT(TCCR1B, CS10);
			CLR_BIT(TCCR1B, CS11);
			CLR_BIT(TCCR1B, CS12);
		break;

		default:
			SET_BIT(TCCR1B, CS10);
			CLR_BIT(TCCR1B, CS11);
			CLR_BIT(TCCR1B, CS12);
		break;
	}
}

void Timer1_setMode(void) {
	/*switch(TIMER_MODE) {
		case NORMAL_MODE:
			Timer1_normalMode();
		break;

		case COMPARE_MODE:
			Timer1_compareMode();
		break;

		case PWM_MODE:
			Timer1_fastPWMMode();
		break;

		default:
			Timer1_normalMode();
		break;
	}*/
}
/*
void Timer1_normalMode(void) {
	CLR_BIT(TCCR1A, COM1A1);
	CLR_BIT(TCCR1A, COM1A0);
	CLR_BIT(TCCR1A, COM1B1);
	CLR_BIT(TCCR1A, COM1B0);
	SET_BIT(TCCR1A, FOC1A);
	SET_BIT(TCCR1A, FOC1B);
	CLR_BIT(TCCR1B, WGM13);
	CLR_BIT(TCCR1B, WGM12);
	CLR_BIT(TCCR1A, WGM11);
	CLR_BIT(TCCR1A, WGM10);
}

void Timer1_compareMode(void) {
	SET_BIT(TCCR1A, FOC1A);
	SET_BIT(TCCR1A, FOC1B);
	CLR_BIT(TCCR1B, WGM13);
	SET_BIT(TCCR1B, WGM12);
	CLR_BIT(TCCR1A, WGM11);
	CLR_BIT(TCCR1A, WGM10);
#if (CTC_MODE == CTC_NORMAL)
	CLR_BIT(TCCR1A, COM1A1);
	CLR_BIT(TCCR1A, COM1A0);
	CLR_BIT(TCCR1A, COM1B1);
	CLR_BIT(TCCR1A, COM1B0);
#elif (CTC_MODE == CTC_TOGGLE)
	CLR_BIT(TCCR1A, COM1A1);
	SET_BIT(TCCR1A, COM1A0);
	CLR_BIT(TCCR1A, COM1B1);
	SET_BIT(TCCR1A, COM1B0);
#elif (CTC_MODE == CTC_CLEAR)
	SET_BIT(TCCR1A, COM1A1);
	CLR_BIT(TCCR1A, COM1A0);
	SET_BIT(TCCR1A, COM1B1);
	CLR_BIT(TCCR1A, COM1B0);
#elif (CTC_MODE == CTC_SET)
	SET_BIT(TCCR1A, COM1A1);
	SET_BIT(TCCR1A, COM1A0);
	SET_BIT(TCCR1A, COM1B1);
	SET_BIT(TCCR1A, COM1B0);
#endif
}

void Timer1_fastPWMMode(void) {
	SET_BIT(TCCR1B, WGM13);
	SET_BIT(TCCR1B, WGM12);
	SET_BIT(TCCR1A, WGM11);
	SET_BIT(TCCR1A, WGM10);
#if (FASTPWM_MODE == FASTPWM_NORMAL)
	CLR_BIT(TCCR1A, COM1A1);
	CLR_BIT(TCCR1A, COM1A0);
	CLR_BIT(TCCR1A, COM1B1);
	CLR_BIT(TCCR1A, COM1B0);
#elif (FASTPWM_MODE == FASTPWM_NOINVERT)
	SET_BIT(TCCR1A, COM1A1);
	CLR_BIT(TCCR1A, COM1A0);
	SET_BIT(TCCR1A, COM1B1);
	CLR_BIT(TCCR1A, COM1B0);
#elif (FASTPWM_MODE == FASTPWM_INVERT)
	SET_BIT(TCCR1A, COM1A1);
	SET_BIT(TCCR1A, COM1A0);
	SET_BIT(TCCR1A, COM1B1);
	SET_BIT(TCCR1A, COM1B0);
#endif
}
*/


void Timer2_setPrescaler(void) {
	switch(PRESCALER_VALUE) {
		case PRESCALER_1024:
			SET_BIT(TCCR2, CS20);
			CLR_BIT(TCCR2, CS21);
			SET_BIT(TCCR2, CS22);
		break;

		case PRESCALER_256:
			CLR_BIT(TCCR2, CS20);
			CLR_BIT(TCCR2, CS21);
			SET_BIT(TCCR2, CS22);
		break;

		case PRESCALER_64:
			SET_BIT(TCCR2, CS20);
			SET_BIT(TCCR2, CS21);
			CLR_BIT(TCCR2, CS22);
		break;

		case PRESCALER_8:
			CLR_BIT(TCCR2, CS20);
			SET_BIT(TCCR2, CS21);
			CLR_BIT(TCCR2, CS22);
		break;

		case PRESCALER_0:
			SET_BIT(TCCR2, CS20);
			CLR_BIT(TCCR2, CS21);
			CLR_BIT(TCCR2, CS22);
		break;

		case NO_CLOCK:
			CLR_BIT(TCCR2, CS20);
			CLR_BIT(TCCR2, CS21);
			CLR_BIT(TCCR2, CS22);
		break;

		default:
			SET_BIT(TCCR2, CS20);
			CLR_BIT(TCCR2, CS21);
			CLR_BIT(TCCR2, CS22);
		break;
	}
}

void Timer2_setMode(void) {
	/*switch(TIMER_MODE) {
		case NORMAL_MODE:
			Timer2_normalMode();
		break;

		case COMPARE_MODE:
			Timer2_compareMode();
		break;

		case PWM_MODE:
			Timer2_fastPWMMode();
		break;

		default:
			Timer2_normalMode();
		break;
	}*/
}
/*
void Timer2_normalMode(void) {
	SET_BIT(TCCR2, FOC2);
	CLR_BIT(TCCR2, WGM20);
	CLR_BIT(TCCR2, WGM21);
	CLR_BIT(TCCR2, COM21);
	CLR_BIT(TCCR2, COM20);
}

void Timer2_compareMode(void) {
	SET_BIT(TCCR2, FOC2);
	CLR_BIT(TCCR2, WGM20);
	SET_BIT(TCCR2, WGM21);
#if (CTC_MODE == CTC_NORMAL)
	CLR_BIT(TCCR2, COM21);
	CLR_BIT(TCCR2, COM20);
#elif (CTC_MODE == CTC_TOGGLE)
	CLR_BIT(TCCR2, COM21);
	SET_BIT(TCCR2, COM20);
#elif (CTC_MODE == CTC_CLEAR)
	SET_BIT(TCCR2, COM21);
	CLR_BIT(TCCR2, COM20);
#elif (CTC_MODE == CTC_SET)
	SET_BIT(TCCR2, COM21);
	SET_BIT(TCCR2, COM20);
#endif
}

void Timer2_fastPWMMode(void) {
	SET_BIT(TCCR2, WGM20);
	SET_BIT(TCCR2, WGM21);
#if (FASTPWM_MODE == FASTPWM_NORMAL)
	CLR_BIT(TCCR2, COM21);
	CLR_BIT(TCCR2, COM20);
#elif (FASTPWM_MODE == FASTPWM_NOINVERT)
	SET_BIT(TCCR2, COM21);
	CLR_BIT(TCCR2, COM20);
#elif (FASTPWM_MODE == FASTPWM_INVERT)
	SET_BIT(TCCR2, COM21);
	SET_BIT(TCCR2, COM20);
#endif
}
*/

// Initializes and enables the Master mode for the TWI Module to start functionality
#if (TIMER_SELECT == TIMER0)
	void Timer0_Init() {
		Timer0_setPrescaler();
		Timer0_setMode();
	}
#elif (TIMER_SELECT == TIMER1)
	void Timer1_Init(void) {
		Timer1_setPrescaler();
		Timer1_setMode();
	}
#elif (TIMER_SELECT == TIMER2)
	void Timer2_Init(void) {
		Timer2_setPrescaler();
		Timer2_setMode();
	}
#endif


void Timer_setNormalDelay(float32 timeDelay) {
	// Sets the delay for Timer of your choice
	// Calculates the overflow amount
	// Sets TCNTx to 0
	// Sets overflow counter to 0
	// Compares overflow counter with overflow amount in a loop
	// Executes a busy wait function
	// Then clears the TIFR by setting it
	// Iterates Overflow Counter

	float32 	tickTime 					= 0;
	float32 	maxDelayTime 		= 0;
	float32 	overflowAmount 	= 0;
	uint8 		overFlowCounter 	= 0;

	tickTime = PRESCALER_VALUE / (float)F_CPU;
	maxDelayTime = tickTime * 256; 		// 2^n = 256
	overflowAmount = ceil((timeDelay) / (maxDelayTime));
	//overflowAmount = floor((timeDelay) / (MaxDelay_Time));

#if (TIMER_SELECT == TIMER0)
	// Using the Timer Overflow Flag TOV
	Timer0_Init();
	while (overFlowCounter < overflowAmount) {
		while (BIT_IS_CLR(TIFR, TOV0)) {
			// This function is a Busy Wait
		}
		overFlowCounter++;
		SET_BIT(TIFR, TOV0);
	}
	overFlowCounter = 0;
	Timer0_Init();
	//TCCR0 = 0;

// Using the Timer Output Compare Flag OCF0
//	TCNT0 = 0x00;
//	while (overFlowCounter < overflowAmount) {
//		while (BIT_IS_CLR(TIFR, OCF0)) {
//			// This function is a Busy Wait
//		}
//		// Clear the overflow flag
//		CLR_BIT(TIFR, OCF0);
//		overFlowCounter++;
//	}
//	overFlowCounter = 0;
//	TCNT0 = 0x00;

#elif (TIMER_SELECT == TIMER1)
	TCNT1 = 0x00;
	while (overFlowCounter < overflowAmount) {
		while (BIT_IS_CLR(TIFR, OCF1A)) {
			// This function is a Busy Wait
		}
		// Clear the overflow flag
		CLR_BIT(TIFR, OCF1A);
		overFlowCounter++;
	}
	overFlowCounter = 0;
	TCNT1 = 0x00;

#elif (TIMER_SELECT == TIMER2)
	TCNT2 = 0x00;
	while (overFlowCounter < overflowAmount) {
		while (BIT_IS_CLR(TIFR, OCF2)) {
			// This function is a Busy Wait
		}
		// Clear the overflow flag
		CLR_BIT(TIFR, OCF2);
		overFlowCounter++;
	}
	overFlowCounter = 0;
	TCNT2 = 0x00;

#endif
}

void Timer_setInterruptDelay(float32 timeDelay) {
	// Sets the delay for Timer of your choice
	// Calculates the overflow amount
	// Sets TCNTx to 0
	// Sets overflow counter to 0
	// Compares overflow counter with overflow amount in a loop
	// Executes a busy wait function
	// Then clears the TIFR by setting it
	// Iterates Overflow Counter

	float32 	tickTime 					= 0;
	float32 	maxDelayTime 		= 0;
	float32 	overflowAmount 	= 0;
	uint8 		overFlowCounter 	= 0;

	tickTime = PRESCALER_VALUE / (float)F_CPU;
	maxDelayTime = tickTime * 256; 		// 2^n = 256
	overflowAmount = ceil((timeDelay) / (maxDelayTime));
	//overflowAmount = floor((timeDelay) / (MaxDelay_Time));

#if (TIMER_SELECT == TIMER0)
	//Timer0_Init();
	overFlowCounter++;
	if (overFlowCounter == overflowAmount) {
		overFlowCounter = 0;
	}

#elif (TIMER_SELECT == TIMER1)
	TCNT1 = 0x00;
	while (overFlowCounter < overflowAmount) {
		while (BIT_IS_CLR(TIFR, OCF1A)) {
			// This function is a Busy Wait
		}
		// Clear the overflow flag
		CLR_BIT(TIFR, OCF1A);
		overFlowCounter++;
	}
	overFlowCounter = 0;
	TCNT1 = 0x00;

#elif (TIMER_SELECT == TIMER2)
	TCNT2 = 0x00;
	while (overFlowCounter < overflowAmount) {
		while (BIT_IS_CLR(TIFR, OCF2)) {
			// This function is a Busy Wait
		}
		// Clear the overflow flag
		CLR_BIT(TIFR, OCF2);
		overFlowCounter++;
	}
	overFlowCounter = 0;
	TCNT2 = 0x00;

#endif
}

void Timer_setCTCMode_normalFreq(float freqKHZ, uint8 port_num, uint8 pin_num) {
	// CTC: Clear Timer on Compare Match
	// Our equation for the CTC Mode
	// Focn = F_CPU / (2N*(1 + OCRn))
	// For i.e: Focn = 2 KHz, what are my knowns?
	// Focn, FCPU, N,,, so i will calculate the OCRn
	// Thus solving my problem.

	GPIO_setupPinDirection(port_num, pin_num, PIN_OUTPUT);
	GPIO_writePin(port_num, pin_num, LOGIC_LOW);

#if (TIMER_SELECT == TIMER0)
	// Using the Timer CTC Mode
	Timer0_Init();
	TCNT0 	= 0;
	OCR0 		= 0;
	OCR0 		= ceil( (float32)F_CPU / (2 * PRESCALER_VALUE * freqKHZ * 1000) ) - 1;

	if (BIT_IS_SET(TIFR, OCF0)) {
		GPIO_togglePin(port_num, pin_num);
		SET_BIT(TIFR, OCF0);
	}


#elif (TIMER_SELECT == TIMER1)
	TCNT1 = 0x00;
	while (overFlowCounter < overflowAmount) {
		while (BIT_IS_CLR(TIFR, OCF1A)) {
			// This function is a Busy Wait
		}
		// Clear the overflow flag
		CLR_BIT(TIFR, OCF1A);
		overFlowCounter++;
	}
	overFlowCounter = 0;
	TCNT1 = 0x00;


#elif (TIMER_SELECT == TIMER2)
	TCNT2 = 0x00;
	while (overFlowCounter < overflowAmount) {
		while (BIT_IS_CLR(TIFR, OCF2)) {
			// This function is a Busy Wait
		}
		// Clear the overflow flag
		CLR_BIT(TIFR, OCF2);
		overFlowCounter++;
	}
	overFlowCounter = 0;
	TCNT2 = 0x00;
#endif
}


uint8 Timer_setCTCMode_interruptFreq(float freqKHZ) {
	// CTC: Clear Timer on Compare Match
	// Our equation for the CTC Mode
	// Focn = F_CPU / (2N*(1 + OCRn))
	// For i.e: Focn = 2 KHz, what are my knowns?
	// Focn, FCPU, N,,, so i will calculate the OCRn
	// Thus solving my problem.

#if (TIMER_SELECT == TIMER0)
	// Using the Timer CTC Mode
	Timer0_Init();
	TCNT0 	= 0;
	OCR0 		= 0;
	OCR0 		= ceil( (float32)F_CPU / (2 * PRESCALER_VALUE * freqKHZ * 1000) ) - 1;

	return OCR0;

#elif (TIMER_SELECT == TIMER1)
	TCNT1 = 0x00;
	while (overFlowCounter < overflowAmount) {
		while (BIT_IS_CLR(TIFR, OCF1A)) {
			// This function is a Busy Wait
		}
		// Clear the overflow flag
		CLR_BIT(TIFR, OCF1A);
		overFlowCounter++;
	}
	overFlowCounter = 0;
	TCNT1 = 0x00;


#elif (TIMER_SELECT == TIMER2)
	TCNT2 = 0x00;
	while (overFlowCounter < overflowAmount) {
		while (BIT_IS_CLR(TIFR, OCF2)) {
			// This function is a Busy Wait
		}
		// Clear the overflow flag
		CLR_BIT(TIFR, OCF2);
		overFlowCounter++;
	}
	overFlowCounter = 0;
	TCNT2 = 0x00;
#endif
}


/*
void Timer_setCTCMode_interruptFreq(float freqKHZ, uint8 port_num, uint8 pin_num) {
	// CTC: Clear Timer on Compare Match
	// Our equation for the CTC Mode
	// Focn = F_CPU / (2N*(1 + OCRn))
	// For i.e: Focn = 2 KHz, what are my knowns?
	// Focn, FCPU, N,,, so i will calculate the OCRn
	// Thus solving my problem.

	GPIO_setupPinDirection(port_num, pin_num, PIN_OUTPUT);
	GPIO_writePin(port_num, pin_num, LOGIC_LOW);

#if (TIMER_SELECT == TIMER0)
	// Using the Timer CTC Mode
	Timer0_Init();
	TCNT0 	= 0;
	OCR0 		= 0;
	OCR0 		= ceil( (float32)F_CPU / (2 * PRESCALER_VALUE * freqKHZ * 1000) ) - 1;

	if (BIT_IS_SET(TIFR, OCF0)) {
		GPIO_togglePin(port_num, pin_num);
		SET_BIT(TIFR, OCF0);
	}


#elif (TIMER_SELECT == TIMER1)
	TCNT1 = 0x00;
	while (overFlowCounter < overflowAmount) {
		while (BIT_IS_CLR(TIFR, OCF1A)) {
			// This function is a Busy Wait
		}
		// Clear the overflow flag
		CLR_BIT(TIFR, OCF1A);
		overFlowCounter++;
	}
	overFlowCounter = 0;
	TCNT1 = 0x00;


#elif (TIMER_SELECT == TIMER2)
	TCNT2 = 0x00;
	while (overFlowCounter < overflowAmount) {
		while (BIT_IS_CLR(TIFR, OCF2)) {
			// This function is a Busy Wait
		}
		// Clear the overflow flag
		CLR_BIT(TIFR, OCF2);
		overFlowCounter++;
	}
	overFlowCounter = 0;
	TCNT2 = 0x00;
#endif
}
*/
