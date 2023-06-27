 /******************************************************************************
 *
 * Module: ADC (Analog to Digital Converter)
 *
 * File Name: ADC.h
 *
 * Description: Header file for the AVR ADC Driver
 *
 * Author: Hossam Mahmoud
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "../GPIO_DRIVER/GPIO.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"


/*******************************************************************************
 *                                								Definitions                                  					      *
 *******************************************************************************/

typedef enum {
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
} ICU_Clock;

typedef enum {
	FALLING, RISING
} ICU_EdgeType;

typedef struct {
	ICU_Clock clock;
	ICU_EdgeType edge;
} ICU_ConfigType;


/*******************************************************************************
 *                              						Functions Prototypes                           					  *
 *******************************************************************************/

// Initializes and enables the ADC Module to start functionality
void ICU_Init(void);

void ICU_setCallBack(void(*a_ptr)(void));

void ICU_setEdgeDetection(const ICU_EdgeType edgeType);

// Description: Function to get the Timer1 Value when the input is captured The value stored at Input Capture Register ICR1
uint16 ICU_getInputCaptureValue(void);

 // clear the Timer1 Value to start count from ZERO
void ICU_clearTimerValue(void);

// disable the Timer1 to stop the ICU Driver
void ICU_DeInit(void);


#endif /* ADC_H_ */
