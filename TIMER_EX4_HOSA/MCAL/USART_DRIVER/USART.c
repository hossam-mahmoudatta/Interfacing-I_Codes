 /******************************************************************************
 *
 * Module: USART (Universal Synchronous Asynchronous Receiver Transmitter)
 *
 * File Name: USART.c
 *
 * Description: Source file for the AVR USART Driver
 *
 * Author: Hossam Mahmoud
 *
 *******************************************************************************/

#include "USART.h"

#include "avr/io.h" /* To use the IO Ports Registers */
#include <util/delay.h>


// Initializes and enables the USART Module to start functionality
void USART_Init(uint32 baudRate) {
	// why uint32? to support the largest baud rate
	// to create a UART driver, I have 4 main parameters
	// Parity, Stop Bit, Data size, Baud Rate

	/* UDR: USART I/O Data Register
	  * BITS 7:0: RXB7:0, UDR (Read)
	  * BITS 7:0: TXB7:0, UDR (Write)
	  */
	// Why same bits, because they are mapped into the same place in mEMORY, but they are 2 different registers

	/* UCSRA - USART Control and Status Register A
	  *  Bit 7 – RXC: USART Receive Complete, when it receives data, the flag = 0
	  *  Bit 6 – TXC: USART Transmit Complete
	  *  Bit 5 – UDRE: USART Data Register Empty, when the register is empty, the flag will be set to '1'
	  *  Bit 4 – FE: Frame Error
	  *  Bit 3 – DOR: Data OverRun
	  *  Bit 2 – PE: Parity Error
	  *  Bit 1 – U2X: Double the USART Transmission Speed
	  *  Bit 0 – MPCM: Multi-processor Communication Mode
	  */

	/* UCSRB - USART Control and Status Register B
	  *  Bit 7 – RXCIE: RX Complete Interrupt Enable, how to make using interrupt?
	  *  Bit 6 – TXCIE: TX Complete Interrupt Enable
	  *  Bit 5 – UDRIE: USART Data Register Empty Interrupt Enable, when the register is empty, the flag will be set to '1'
	  *  Bit 4 – RXEN: Receiver Enable, set to 1
	  *  Bit 3 – TXEN: Transmitter Enable, set to 1
	  *  Bit 2 – UCSZ2: Character Size, it controls the data size of the data frame
	  *  Bit 1 – RXB8: Receive Data Bit 8, Enables the ninth bit of data, but remember that the UDR is 8 bits
	  *  Bit 0 – TXB8: Transmit Data Bit 8, Enables the ninth bit of data, but remember that the UDR is 8 bits
	  */

	// UCSRC - USART Control and Status Register C
	// Bit 7 – URSEL: Register Select, i must set it to '1'
	// Bit 6 – UMSEL: USART Mode Select, '0' for Asynchronous
	// BIT 5:4: UPM1:0, Parity Mode, I will use it as disable parity, so '00'
	// BIT 3: TXEN, Trans Enable, set to 1
	// BIT 2:1: UCSZ1:0, Character Size, I will choose '011' to be 8 bits
	// BIT 0: UCPOL, clock polarity, chooses if I choose on rising or falling edge, but since
	// Im using asynchronous mode, so i dont need this bit

	// All serial peripherals are very slow compared to the processor,
	// for ex. we will use the baudrate 9600, which is approx 9.6 KHz
	// while the processor is 16 MHz, so the risk is that while im looping on the data
	// the looping of the processor will eventually outrace the uart sending time,
	// so u might overwrite on nits inside the UART
	// so we must make polling functions and then set flags to know if i received or sent the data successfully on the uart

	// UBRRL & UBRRH, BaudRate Registers
	// From the datasheet, I need to calculate the UBBR by using this equation:
	// UBBR = ( ((Fcpu) / (8 * Baud)) - 1 )
	// When will this eqn be in -Ve? if the Fcpu is less than '1'
	// What does the -Ve UBBR mean? it means i can't use this baud rate @ this Fcpu
	// The Fcpu must be atleast 8 times larger than the Baud Rate!!!
	// So if my Fcpu = 16Mhz & Baud = 9600, then the UBBR = 207.

	// To initialize this Init Function, i need to:
	// Tweak the Frame
	// Set the baud rate

	uint16 UBBR_Value = 0;

	SET_BIT(UCSRA, U2X);

	SET_BIT(UCSRB, TXEN);
	SET_BIT(UCSRB, RXEN);

	SET_BIT(UCSRC, URSEL);
	CLR_BIT(UCSRC, UMSEL);
	SET_BIT(UCSRC, TXEN);

	CLR_BIT(UCSRC, UCSZ2);
	SET_BIT(UCSRC, UCSZ1);
	SET_BIT(UCSRC, UCSZ0);

	// UBBRH = 0;
	// UBBRL = 207;
	// (0000) (1100 1111) 12 bits, (0000) is for UBBRH, (1100 1111) if for UBBRL

	UBBR_Value = (uint16) ( ( (F_CPU) / (8 * baudRate * 8UL) ) - 1 );
	UBRRH = UBBR_Value >> 8;
	// Because I want the 4 Zeroes in it

	UBRRL = UBBR_Value;
	// Because I want the actual value

}


// Responsible for the USART to send a byte
void USART_sendByte(const uint8 data) {
	/* UCSRA - USART Control and Status Register A
	  *  Bit 6 – TXC: USART Transmit Complete
	  *  Bit 5 – UDRE: USART Data Register Empty
	  *
	  *  UDRE flag is set when the TX Buffer (UDR) is empty and ready
	  *  for transmitting a new byte waiting untill this flag is set to '1'
	  */
	while(BIT_IS_CLR(UCSRA,UDRE)) {
		// Polling (Busy Wait)
	}

	/*
	 * Put the required data in the UDR register and also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;

	/************************* Another Method *************************
	UDR = data;
	while( BIT_IS_CLR(UCSRA, TXC) ){

	} // Wait until the transmission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	// This is waiting for the flag to be set to '0' to know that I received data
	*******************************************************************/
}


// Responsible for the USART to receive a byte
uint8 USART_receiveByte(void) {
	/* UCSRA - USART Control and Status Register A
	  *  Bit 7 – RXC: USART Receive Complete, when it receives data, the flag = 0
	  */

	while ( BIT_IS_CLR(UCSRA, RXC) );
	// This is waiting for the flag to be set to '0' to know that I received data

	// When reading
	return UDR;
}


// Responsible for the USART to send an array of bytes, a string
void USART_sendString(const uint8 *str) {
	uint8 i = 0;
	while (str[i] != '\0') {
		USART_sendByte(str[i]);
		i++;
	}
}


// Responsible for the USART to receive an array of bytes, a string
void USART_receiveString(uint8 *str) {
	uint8 i = 0;
	str[i] = USART_receiveByte();

	while (str[i] != '#') {
		i++;
		str[i] = USART_receiveByte();
	}
	str[i] = '\0'; // replacing the '#' with '\0'
}


