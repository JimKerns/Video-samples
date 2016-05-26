/* Interface with USART for serial communication. ASCII data is recieved and stored in a character array in an interrupt
driven process. Up to 20 characters may be stored before they are retrieved by another function. After 20 characters, any additional
characters are lost.

usage:

USART_vInit(); // initialize / enable USART - set up baud rate, set for 8 bits, 1 stop bit, no parity

char mystring[20];  // string for data returned.

num_char = GetSerialString(mystring);  //return number of characters read, Character String in mystring
// if the number of characters = 0, not serial data was received since the last call to GetSerialString

for (ii = 0; ii < num_char; ii++)  
{
	code to parse string here
}	

*/

#ifndef Serial_LIB_H_
#define Serial_LIB_H_


#define F_CPU  8000000ul
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>


// Define baud rate for serial communication
#define USART_BAUD 115200ul

#define USART_UBBR_VALUE 51ul
//51ul 9600 baud at 8mhz, 3ul 115.2K at 8 mhz clock, 8ul with U2X = 1 for 115.2 baud at 8 MHz

//prototypes for serial communication
static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

extern void USART_vInit();

extern uint8_t GetSerialString(char* StringArray);  //return number of characters read, Character String in StringArray

#endif