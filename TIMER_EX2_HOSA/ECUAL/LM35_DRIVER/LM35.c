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

#include "LM35.h"
#include "../../MCAL/ADC_DRIVER/ADC.h"

#include "avr/io.h" /* To use the IO Ports Registers */
#include <util/delay.h>


// Initializes and enables the ADC Module to start functionality
uint8 LM35_getTemperature(void) {
	uint8 temperature = 0;
	uint8 ADC_Value = 0;
	ADC_Value = ADC_readChannel(LM35_CH_ID);

	temperature = (uint8) ( ( (uint32)ADC_Value * LM35_MAX_TEMP * ADC_REFERENCE_VOLT_VALUE) / (ADC_MAX_VALUE * LM35_MAX_VOLT) );

	return temperature;

}
