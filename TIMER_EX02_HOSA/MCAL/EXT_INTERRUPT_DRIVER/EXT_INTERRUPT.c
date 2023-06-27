 /******************************************************************************
 *
 * Module: External Interrupt
 *
 * File Name: EXT_INTERRUPT.c
 *
 * Description: Source file for the AVR External Interrupt Driver
 *
 * Author: Hossam Mahmoud
 *
 *******************************************************************************/

#include "EXT_INTERRUPT.h"

#include "avr/io.h" /* To use the IO Ports Registers */
#include <util/delay.h>

// Initialize External Interrupt
void EXT_INTERRUPT_Init(void) {

	/* MCU Control Register – MCUCR  Register Bits Description:
	 * Bit 3, 2 – ISC11, ISC10: Interrupt Sense Control 1 Bit 1 and Bit 0
	 * Bit 1, 0 – ISC01, ISC00: Interrupt Sense Control 0 Bit 1 and Bit 0
	 */

	/* General Interrupt Control Register – GICR Register Bits Description:
	 * Bit 7 – INT1: External Interrupt Request 1 Enable
	 * Bit 6 – INT0: External Interrupt Request 0 Enable
	 * Bit 5 – INT2: External Interrupt Request 2 Enable
	 */

	// Checking if INT0 is enabled or disabled
	#if (EXT_INTERRUPT_INT0_INIT_STATE == EXT_INTERRUPT_Enable_State)
		// Enabling the INT0 bit inside GICR
		SET_BIT(GICR, INT0);

		// Setup Pin PD2 "INT0" to Input
		GPIO_setupPinDirection(PORT_D, PIN_2, PIN_INPUT);

		// Initializing the ISC0X bits
		#if (EXT_INTERRUPT_0_MODE == EXT_INTERRUPT_Low_Level)
			CLR_BIT(MCUCR, ISC01);
			CLR_BIT(MCUCR, ISC00);
		#elif (EXT_INTERRUPT_0_MODE == EXT_INTERRUPT_Logical_Change)
			CLR_BIT(MCUCR, ISC01);
			SET_BIT(MCUCR, ISC00);
		#elif (EXT_INTERRUPT_0_MODE == EXT_INTERRUPT_Falling_Edge)
			SET_BIT(MCUCR, ISC01);
			CLR_BIT(MCUCR, ISC00);
		#elif (EXT_INTERRUPT_0_MODE == EXT_INTERRUPT_Rising_Edge)
			SET_BIT(MCUCR, ISC01);
			SET_BIT(MCUCR, ISC00);
		#endif
	#elif (EXT_INTERRUPT_INT0_INIT_STATE == EXT_INTERRUPT_Disable_State)
			CLR_BIT(GICR, INT0);
	#endif

	// Checking if INT1 is enabled or disabled
	#if (EXT_INTERRUPT_INT1_INIT_STATE == EXT_INTERRUPT_Enable_State)
		// Enabling the INT0 bit inside GICR
		SET_BIT(GICR, INT1);

		// Setup Pin PD3 "INT1" to Input
		GPIO_setupPinDirection(PORT_D, PIN_3, PIN_INPUT);

		// Initializing the ISC0X bits
		#if (EXT_INTERRUPT_1_MODE == EXT_INTERRUPT_Low_Level)
			CLR_BIT(MCUCR, ISC11);
			CLR_BIT(MCUCR, ISC10);
		#elif (EXT_INTERRUPT_1_MODE == EXT_INTERRUPT_Logical_Change)
			CLR_BIT(MCUCR, ISC11);
			SET_BIT(MCUCR, ISC10);
		#elif (EXT_INTERRUPT_1_MODE == EXT_INTERRUPT_Falling_Edge)
			SET_BIT(MCUCR, ISC11);
			CLR_BIT(MCUCR, ISC10);
		#elif (EXT_INTERRUPT_1_MODE == EXT_INTERRUPT_Rising_Edge)
			SET_BIT(MCUCR, ISC11);
			SET_BIT(MCUCR, ISC10);
		#endif
	#elif (EXT_INTERRUPT_INT1_INIT_STATE == EXT_INTERRUPT_Disable_State)
			CLR_BIT(GICR, INT1);
	#endif

	// Checking if INT2 is enabled or disabled
	#if (EXT_INTERRUPT_INT2_INIT_STATE == EXT_INTERRUPT_Enable_State)
		// Enabling the INT0 bit inside GICR
		SET_BIT(GICR, INT2);

		// Setup Pin PB2 "INT2" to Input
		GPIO_setupPinDirection(PORT_B, PIN_2, PIN_INPUT);

		// Initializing the ISC0X bits
		#if (EXT_INTERRUPT_2_MODE == EXT_INTERRUPT_INT2_Falling_Edge)
			CLR_BIT(MCUCSR, ISC2);
		#elif (EXT_INTERRUPT_2_MODE == EXT_INTERRUPT_INT2_Rising_Edge)
			SET_BIT(MCUCSR, ISC2);
		#endif
	#elif (EXT_INTERRUPT_INT2_INIT_STATE == EXT_INTERRUPT_Disable_State)
			CLR_BIT(GICR, INT2);
	#endif

	/* Status Register – SREG Register Bits Description:
	 * Bit 7 – I: Global Interrupt Enable
	 */
	// Enabling the I-Bit
	SET_BIT(SREG, SREG_I_BIT);
}

// Disable External Interrupt ISR
void EXT_INTERRUPT_DeInit(void) {

	#if (EXT_INTERRUPT_INT0_INIT_STATE == EXT_INTERRUPT_Enable_State)
		CLR_BIT(GICR, INT0);
	#endif

	#if (EXT_INTERRUPT_INT1_INIT_STATE == EXT_INTERRUPT_Enable_State)
		CLR_BIT(GICR, INT1);
	#endif

	#if (EXT_INTERRUPT_INT2_INIT_STATE == EXT_INTERRUPT_Enable_State)
		CLR_BIT(GICR, INT2);
	#endif

	CLR_BIT(SREG, SREG_I_BIT);
}

//The function that will be called in the EXT INT
void (*CallBackPtr) (void) = NULL;

// External Interrupt Call Back Function
void EXT_INTERRUPT_SetCallBack(void (*CopyFuncPtr) (void)) {
	CallBackPtr = CopyFuncPtr;
}



// void __vector_1(void) __attribute__((signal, used));
// Previous prototype __attribute__((signal, used));
// is to tell the compiler that I will use this function
// but not now, so don't optimize and delete it.

/*
void __vector_1(void) {
	if(CallBackPtr != NULL) {
		CallBackPtr();
	}
}
*/

