 /******************************************************************************
 *
 * Module: LCD Display
 *
 * File Name: LCD.c
 *
 * Description: Source file for the AVR LCD Driver
 *
 * Author: Hossam Mahmoud
 *
 *******************************************************************************/

#include "LCD.h"
#include "avr/io.h" /* To use the IO Ports Registers */
#include <util/delay.h>


// Initializes and enables the LCD Module to start functionality
void LCD_Init(void) {
	// Initialize RS Pin
	GPIO_setupPinDirection(LCD_INIT_PORT, LCD_RS, PIN_OUTPUT);

	// Initialize Enable Pin
	GPIO_setupPinDirection(LCD_INIT_PORT, LCD_ENABLE, PIN_OUTPUT);

	// LCD Power On Internal Delay is 15 mS
	_delay_ms(20);

	// Initializing Sending Commands
	// Checks which BIT Mode, 4 or 8 line bit
	if (LCD_BIT_MODE == 4) {
		GPIO_setupPinDirection(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 0), PIN_OUTPUT);
		GPIO_setupPinDirection(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 1), PIN_OUTPUT);
		GPIO_setupPinDirection(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 2), PIN_OUTPUT);
		GPIO_setupPinDirection(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 3), PIN_OUTPUT);

		LCD_sendCommand(LCD_TWO_LINE_FOUR_BIT_INIT1);
		LCD_sendCommand(LCD_TWO_LINE_FOUR_BIT_INIT2);
		LCD_sendCommand(LCD_TWO_LINE_FOUR_BIT);
	}
	else if (LCD_BIT_MODE == 8) {
		// Setup the port and pins for the data pins inside the LCD
		GPIO_setupPortDirection(LCD_DATA_PORT, PORT_OUTPUT);

		LCD_sendCommand(LCD_TWO_LINE_EIGHT_BIT);
	}
	else {
		// Default value in case user entered something wrong
		// Setup the port and pins for the data pins inside the LCD
		GPIO_setupPortDirection(LCD_DATA_PORT, PORT_OUTPUT);

		LCD_sendCommand(LCD_TWO_LINE_EIGHT_BIT);
	}

	// Makes the cursor off
	LCD_sendCommand(LCD_CURSOR_OFF);
	// Clears Display
	LCD_sendCommand(LCD_CLEAR_DISPLAY);
}


// Sends a command to the LCD
void LCD_sendCommand(uint8 command) {
	// Set RS Pin to '0'
	GPIO_writePin(LCD_INIT_PORT, LCD_RS, LOGIC_LOW);
	_delay_ms(1);

	// Set Enable Pin to '1'
	GPIO_writePin(LCD_INIT_PORT, LCD_ENABLE, LOGIC_HIGH);
	_delay_ms(1);

	// Inserts the command in the assigned PORT to be sent to the LCD
	// uint8 BIT_MODE;
	if (LCD_BIT_MODE == 4) {
		GPIO_writePin(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 0), GET_BIT( command, 4 ));
		GPIO_writePin(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 1), GET_BIT( command, 5 ));
		GPIO_writePin(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 2), GET_BIT( command, 6 ));
		GPIO_writePin(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 3), GET_BIT( command, 7 ));
		_delay_ms(1);

		// Clear Enable Pin to '0'
		GPIO_writePin(LCD_INIT_PORT, LCD_ENABLE, LOGIC_LOW);
		_delay_ms(1); /* delay for processing Th = 13ns */

		// Set Enable Pin to '1'
		GPIO_writePin(LCD_INIT_PORT, LCD_ENABLE, LOGIC_HIGH);
		_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

		GPIO_writePin(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 0), GET_BIT( command, 0 ));
		GPIO_writePin(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 1), GET_BIT( command, 1 ));
		GPIO_writePin(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 2), GET_BIT( command, 2 ));
		GPIO_writePin(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 3), GET_BIT( command, 3 ));
		_delay_ms(1); /* delay for processing Tdsw = 100ns */

		// Clear Enable Pin to '0'
		GPIO_writePin(LCD_INIT_PORT, LCD_ENABLE, LOGIC_LOW);
		_delay_ms(1); /* delay for processing Th = 13ns */
	}
	else if (LCD_BIT_MODE == 8) {
		GPIO_writePort(LCD_DATA_PORT, command);
		_delay_ms(1);

		// Clear Enable Pin to '0'
		GPIO_writePin(LCD_INIT_PORT, LCD_ENABLE, LOGIC_LOW);
		_delay_ms(1); /* delay for processing Th = 13ns */
	}
	else {
		// Default value in case user entered something wrong
		GPIO_writePort(LCD_DATA_PORT, command);
		_delay_ms(1);

		// Clear Enable Pin to '0'
		GPIO_writePin(LCD_INIT_PORT, LCD_ENABLE, LOGIC_LOW);
		_delay_ms(1); /* delay for processing Th = 13ns */
	}
}


// Displays a character on the LCD
void LCD_displayCharacter(uint8 data) {
	// Set RS Pin to '1'
	GPIO_writePin(LCD_INIT_PORT, LCD_RS, LOGIC_HIGH);
	_delay_ms(1);

	// Set Enable Pin to '1'
	GPIO_writePin(LCD_INIT_PORT, LCD_ENABLE, LOGIC_HIGH);
	_delay_ms(1);

	// Inserts the data in the assigned PORT to be sent to the LCD
	// Inserts the data in the assigned PORT to be sent to the LCD
	if (LCD_BIT_MODE == 4) {
		GPIO_writePin(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 0), GET_BIT( data, 4 ));
		GPIO_writePin(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 1), GET_BIT( data, 5 ));
		GPIO_writePin(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 2), GET_BIT( data, 6 ));
		GPIO_writePin(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 3), GET_BIT( data, 7 ));
		_delay_ms(1);

		// Clear Enable Pin to '0'
		GPIO_writePin(LCD_INIT_PORT, LCD_ENABLE, LOGIC_LOW);
		_delay_ms(1); /* delay for processing Th = 13ns */

		// Set Enable Pin to '1'
		GPIO_writePin(LCD_INIT_PORT, LCD_ENABLE, LOGIC_HIGH);
		_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

		GPIO_writePin(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 0), GET_BIT( data, 0 ));
		GPIO_writePin(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 1), GET_BIT( data, 1 ));
		GPIO_writePin(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 2), GET_BIT( data, 2 ));
		GPIO_writePin(LCD_DATA_PORT, (LCD_FOUR_BIT_DATAPIN + 3), GET_BIT( data, 3 ));
		_delay_ms(1); /* delay for processing Tdsw = 100ns */

		// Clear Enable Pin to '0'
		GPIO_writePin(LCD_INIT_PORT, LCD_ENABLE, LOGIC_LOW);
		_delay_ms(1); /* delay for processing Th = 13ns */
	}
	else if (LCD_BIT_MODE == 8) {
		GPIO_writePort(LCD_DATA_PORT, data);
		_delay_ms(1);

		// Clear Enable Pin to '0'
		GPIO_writePin(LCD_INIT_PORT, LCD_ENABLE, LOGIC_LOW);
		_delay_ms(1); /* delay for processing Th = 13ns */
	}
	else {
		// Default value in case user entered something wrong
		GPIO_writePort(LCD_DATA_PORT, data);
		_delay_ms(1);

		// Clear Enable Pin to '0'
		GPIO_writePin(LCD_INIT_PORT, LCD_ENABLE, LOGIC_LOW);
		_delay_ms(1); /* delay for processing Th = 13ns */
	}
}


// Displays a string on the LCD
void LCD_displayString(const char *str) {
	uint8 i = 0;
	while(str[i] != '\0') {
		LCD_displayCharacter(str[i]);
		i++;
	}
	/*
	for (int i = 0 ; i < strlen(str) ; i++) {
		LCD_displayCharacters(str[i]);
	}*/
}


// Chooses where the cursor would stand on the LCD to type from it
void LCD_moveCursor(uint8 row, uint8 col) {
	uint8 LCD_MEMORY_ADDRESS;

	// Calculate the required address in the LCD DDRAM checking
	// The location of the cursor originally on which line
	switch(row) {
		case 0:
			LCD_MEMORY_ADDRESS = col;
				break;
		case 1:
			LCD_MEMORY_ADDRESS = col + 0x40;
				break;
		case 2:
			LCD_MEMORY_ADDRESS = col + 0x10;
				break;
		case 3:
			LCD_MEMORY_ADDRESS = col + 0x50;
				break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(LCD_MEMORY_ADDRESS | LCD_CURSOR_LOCATION);
}


// Displays a string on the LCD at a chosen cursor and row
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *Str) {
	// Go to to the required LCD position
	LCD_moveCursor(row, col);

	// Display the string from the cursor
	LCD_displayString(Str);
}

// LCD only understands ASCII, so this converts Int to a string
void LCD_intgerToString(int data) {
	// A string to hold the ASCII values
	char buffer[16];

	// Converts data to its ASCII
	itoa(data, buffer, 10);

	// Display string with the results in the buffer
	LCD_displayString(buffer);
}

// Clears the LCD from any garbage
void LCD_clearScreen(void) {
	// Clears the LCD Display
	LCD_sendCommand(LCD_CLEAR_DISPLAY);
}

