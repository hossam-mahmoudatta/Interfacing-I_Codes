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
#include <util/delay.h>
#include <math.h>


/*******************************************************************************
 *                              					Module Implementation                           					  *
 *******************************************************************************/

void Timer0_setPrescaler(void) {
	switch(PRESCALER_VALUE) {
		case PRESCALER_1024:
			SET_BIT(TCCR0, CS00);
			CLR_BIT(TCCR0, CS01);
			SET_BIT(TCCR0, CS02);
		break;

		case PRESCALER_256:
			CLR_BIT(TCCR0, CS00);
			CLR_BIT(TCCR0, CS01);
			SET_BIT(TCCR0, CS02);
		break;

		case PRESCALER_64:
			SET_BIT(TCCR0, CS00);
			SET_BIT(TCCR0, CS01);
			CLR_BIT(TCCR0, CS02);
		break;

		case PRESCALER_8:
			CLR_BIT(TCCR0, CS00);
			SET_BIT(TCCR0, CS01);
			CLR_BIT(TCCR0, CS02);
		break;

		case PRESCALER_0:
			SET_BIT(TCCR0, CS00);
			CLR_BIT(TCCR0, CS01);
			CLR_BIT(TCCR0, CS02);
		break;

		case NO_CLOCK:
			CLR_BIT(TCCR0, CS00);
			CLR_BIT(TCCR0, CS01);
			CLR_BIT(TCCR0, CS02);
		break;

		default:
			SET_BIT(TCCR0, CS00);
			CLR_BIT(TCCR0, CS01);
			CLR_BIT(TCCR0, CS02);
		break;
	}
}

void Timer0_setMode(void) {
	switch(TIMER_MODE) {
		case NORMAL_MODE:
			Timer0_normalMode();
		break;

		case COMPARE_MODE:
			Timer0_compareMode();
		break;

		case PWM_MODE:
			Timer0_fastPWMMode();
		break;

		default:
			Timer0_normalMode();
		break;
	}
}

void Timer0_normalMode(void) {
	SET_BIT(TCCR0, FOC0);
	CLR_BIT(TCCR0, WGM00);
	CLR_BIT(TCCR0, WGM01);
	CLR_BIT(TCCR0, COM01);
	CLR_BIT(TCCR0, COM00);
}

void Timer0_compareMode(void) {
	SET_BIT(TCCR0, FOC0);
	CLR_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);
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
	switch(TIMER_MODE) {
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
	}
}

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
	switch(TIMER_MODE) {
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
	}
}

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


void Timer_setDelay(float32 timeDelay) {
	// Sets the delay for Timer of your choice
	// Calculates the overflow amount
	// Sets TCNTx to 0
	// Sets overflow counter to 0
	// Compares overflow counter with overflow amount in a loop
	// Executes a busy wait function
	// Then clears the TIFR by setting it
	// Iterates Overflow Counter

	float32 Tick_Time = 0;
	float32 MaxDelay_Time = 0;
	float32 overflowAmount = 0;
	uint8 overFlowCounter = 0;

	Tick_Time = PRESCALER_VALUE / (float)F_CPU;
	MaxDelay_Time = Tick_Time * 256; 		// 2^n = 256
	overflowAmount = ceil((timeDelay) / (MaxDelay_Time));
	//overflowAmount = floor((timeDelay) / (MaxDelay_Time));

#if (TIMER_SELECT == TIMER0)
	// Using the Timer Overflow Flag TOV
	TCNT0 = 0x00;
	while (overFlowCounter < overflowAmount) {
		while (BIT_IS_CLR(TIFR, TOV0)) {
			// This function is a Busy Wait
		}
		overFlowCounter++;
		SET_BIT(TIFR, TOV0);
	}
	overFlowCounter = 0;
	TCCR0 = 0x00;

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
