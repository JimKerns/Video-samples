#include "Serial_lib.h"




/* 
ATmega32           ATmega1284P
USART_RXC_vect         USART0_RX_vect
UDR                     UDR0
UCSRA                UCSR0A
RXC                     RXC0
TXC                      TXC0
UDRE                  UDRE0
U2X                     U2X0 (I don't think we use this one)
UCSRB                UCSR0B
RXCIE                 RXCIE0
TXCIE                  TXCIE0  (I would have to check to see if we use this)
RXEN                  RXEN0
TXEN                  TXEN0
UCSRC               UCSR0C
UMSEL               UMSEL01 UMSEL00 (both set = 0 for asynchronous operation)
UPM0, UPM1     UPM00,UPM01 (we don't set these)
USBS                 USBS0
UBRRL, UBRRH  UBRR0L, UBRR0H   Baud rate calculation is the same.
URSEL               not used.
*/

char PCData[20];	// characters received from PC via serial port
uint8_t PCData_index = 0; // new data recieved from serial port


uint8_t serialCheckRxComplete(void);

// UART Rx Interrupt
ISR( USART0_RX_vect ) {
	if(PCData_index <= 20)
	{
		PCData[PCData_index] = UDR0;
		++ PCData_index;
		// store character in PCData and update index.
	}
	
	 
}


void USART_vInit(void) {
	stdout = &mystdout;
	
	// Set baud rate
	UBRR0H = (unsigned char) (USART_UBBR_VALUE >> 8);
	UBRR0L = (unsigned char) USART_UBBR_VALUE;

	// set double speed on UART to improve baud rate error
	//UCSR0A = (1 << U2X0);
	/* Enable receiver and transmitter */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C |=  (3 << UCSZ00);
	// Set frame format to 8 data bits, no parity UPM01 UPM00 = 0, 1 stop bit USBSn = 0
}

uint8_t USART_vReceiveByte(void) {
	// Wait until a byte has been received
	while ((UCSR0A & (1 << RXC0)) == 0)
	;
	// Return received data
	return UDR0;
}


static int uart_putchar(char c, FILE *stream)
{
	if (c == '\n')
	uart_putchar('\r', stream);

	//insert code cut / pasted from data sheet.
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
	return 0;
}

uint8_t serialCheckRxComplete(void)
{
	return ((UCSR0A & (1 << RXC0))); // nonzero if serial data is available to read.
}

uint8_t GetSerialString(char* StringArray)  //return number of characters read, Character String in StringArray
{
	uint8_t tmpnum;
	cli();  // shut down interrupts for the next  statements in case a character is received in between...
	tmpnum = PCData_index;
	StringArray = PCData;
	PCData_index = 0;  // reset counter and empty char array
	//PCData = "";  
	sei(); // re-enable interrupts
	return(tmpnum);
}