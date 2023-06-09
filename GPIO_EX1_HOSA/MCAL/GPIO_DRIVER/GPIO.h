 /******************************************************************************
 *
 * Module: GPIO (General Purpose I/O
 *
 * File Name: GPIO.h
 *
 * Description: Header file for the AVR GPIO Driver
 *
 * Author: Hossam Mahmoud
 *
 *******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"


/*******************************************************************************
 *                                									Definitions                                  					           		  *
 *******************************************************************************/
#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

#define PORT_A		     0
#define PORT_B			 1
#define PORT_C            2
#define PORT_D            3

#define PIN_0                0
#define PIN_1                	1
#define PIN_2                2
#define PIN_3                3
#define PIN_4                4
#define PIN_5                5
#define PIN_6                6
#define PIN_7                7

/*******************************************************************************
 *                               							Types Declaration                            									  *
 *******************************************************************************/

typedef enum {
	PIN_INPUT, PIN_OUTPUT
} GPIO_PinDirectionType;

typedef enum {
	PORT_INPUT, PORT_OUTPUT = 0xFF
} GPIO_PortDirectionType;

typedef enum GPIO_Error_t {
	GPIO_OK,
	GPIO_WRONG_PIN_NUMBER,
	GPIO_WRONG_PORT_NUMBER,
	GPIO_WRONG_DIRECTION
} GPIO_Error_t;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
GPIO_Error_t GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
GPIO_Error_t GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
GPIO_Error_t GPIO_togglePin(uint8 port_num, uint8 pin_num);

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
GPIO_Error_t GPIO_setupPortDirection(uint8 port_num, uint8 direction);

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
GPIO_Error_t GPIO_writePort(uint8 port_num, uint8 value);

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num);

#endif /* GPIO_H_ */
