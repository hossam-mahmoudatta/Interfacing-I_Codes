 /******************************************************************************
 *
 * Module: LCD Display
 *
 * File Name: LCD.h
 *
 * Description: Header file for the AVR LCD Driver
 *
 * Author: Hossam Mahmoud
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "../../MCAL/GPIO_DRIVER/GPIO.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"


/*******************************************************************************
 *                                								Definitions                                  					      *
 *******************************************************************************/

#define LCD_DATA_PORT								PORT_A
#define LCD_INIT_PORT									PORT_A

#define LCD_RS												PIN_1
#define LCD_ENABLE										PIN_2

#define LCD_BIT_MODE									4			// if '4', then its 4 BIT Mode, if '8' then its 8 BIT Mode

#if((LCD_BIT_MODE != 4) && (LCD_BIT_MODE != 8))
	#error "Number of Data bits should be equal to 4 or 8"
#endif

#define LCD_FOUR_BIT_DATAPIN					PIN_3

#define LCD_CLEAR_DISPLAY						0x01
#define LCD_TWO_LINE_FOUR_BIT				0x28
#define LCD_TWO_LINE_FOUR_BIT_INIT1   	0x33
#define LCD_TWO_LINE_FOUR_BIT_INIT2		0x32
#define LCD_TWO_LINE_EIGHT_BIT				0x38
#define LCD_CURSOR_OFF          					0x0C
#define LCD_CURSOR_ON          					0x0E
#define LCD_CURSOR_BLINKING          			0x0F
#define LCD_CURSOR_LOCATION        			0x80


/*******************************************************************************
 *                              						Functions Prototypes                           					  *
 *******************************************************************************/

// Initializes and enables the LCD Module to start functionality
void LCD_Init(void);


 // Sends a command to the LCD
void LCD_sendCommand(uint8 command);


 // Displays a character on the LCD
void LCD_displayCharacter(uint8 data);


// Displays a string on the LCD
void LCD_displayString(const char *Str);


// Chooses where the cursor would stand on the LCD to type from it
void LCD_moveCursor(uint8 row,uint8 col);


// Displays a string on the LCD at a chosen cursor and row
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *Str);


// LCD only understands ASCII, so this converts Int to a string
void LCD_intgerToString(int data);


// Clears the LCD from any garbage
void LCD_clearScreen(void);


#endif /* LCD_H_ */
