/*
 * LCD.c
 *
 * Created: 1/24/2013 11:08:10 AM
 *  Author: cchung
 */ 

// Define  CPU clock rate - used by some of the include files (delay.h) so it goes up front.
#define F_CPU 11059200ul

#include <avr/io.h>
#include <util/delay.h>
#include "LCD_lib.h"

// port definitions for LCD display
#define LCDPort PORTB
#define LCDDataDirPort DDRB
#define LCDControlPort PORTD
#define LCDDataDirControl DDRD

// *********** add these lines for new controller board ***************
#define LCDEnablePort PORTC  // change to PORTD for original board
#define LCDEnableDataDir DDRC  // change to DDRD for original board
//******************
//#define LCDReadWrite 7  // original board
#define LCDReadWrite 3    // new board
//*************************************************
//
#define LCDENA 3     
#define LCDCRSSel 2

void LCDEnableOnOff(void);
void LCDSendCommand(unsigned char command);
void LCDSendCharacter(unsigned char character);
void LCDCheckIfBusy(void);

#define LCDnumberOfColumns 20
uint8_t LCD1stCharacterPos[4] = {0, 64, 20, 84};
int LCDCol = 1; // global variables for setting row/column for LCD display
int LCDRow = 1; 

void LCDSendCommand(unsigned char command)
{
	LCDCheckIfBusy();
	LCDPort = command;
	LCDControlPort &= ~((1<<LCDCRSSel)|(1<<LCDReadWrite)); //turn off RS (command mode) and RW (write mode)
	LCDEnableOnOff();
	LCDDataDirPort = 0;
	LCDPort = 0; // turn off pullups if any.
}

void LCDSendCharacter(unsigned char character)
{
	LCDCheckIfBusy();
	LCDPort = character;
	LCDControlPort &= ~(1<<LCDReadWrite); //turn off RW (write mode)
	LCDControlPort |= (1<<LCDCRSSel); //turn on RS (character display mode)
	LCDEnableOnOff(); // set enable to allow ports to be read by LCD, wait, clear enable to allow LCD to process.
	LCDDataDirPort = 0; //reset LCD port
	LCDPort = 0; // turn off pullups if any.
}

void LCDCheckIfBusy()
{
	LCDDataDirPort = 0b00000000; //Put PortB in Input (read) Mode
	LCDControlPort &= ~(1<<LCDCRSSel); //Turn on Mr. LCD's Command Mode (RS off)
	LCDControlPort |= (1<<LCDReadWrite); //Set Mr. LCD to Read (RW on)
	while (LCDPort >= 0x80); //D7 pin will be a "1" with any number above 0x80 if busy
	{
		LCDEnableOnOff(); // this is just another routine to turn the enable on and off
	}
	LCDDataDirPort = 0xFF; //Set portB as output
}

void LCDEnableOnOff()
{
	LCDEnablePort |= (1<<LCDENA); //Turn Enable on so Mr. LCD can function
	_delay_us(50); // 400 is too long, 10 was too short Original code just had a couple no-ops
	LCDEnablePort &= ~(1<<LCDENA); //turn off Enable so Mr. LCD can Concentrate
}

void LCDSendString(char *StringOfCharacters)
{
	while(*StringOfCharacters > 0)
	{
		LCDSendCharacter(*StringOfCharacters++);
	}
}

void LCDGoToPosition(uint8_t x, uint8_t y) // unit8_t: unsigned integer with 8 bits
{
	int junk = 0;
	junk = (0x80 + LCD1stCharacterPos[y-1] + (x-1));
	LCDSendCommand(junk);
}

void LCD_init(void)
{
	//LCD stuff
		LCDDataDirControl  |= 1<<LCDReadWrite | 1<<LCDCRSSel;
		LCDEnableDataDir |= 1<<LCDENA;
	_delay_ms(15);

	// initialize LCD
	LCDSendCommand(0x01); //Clear Screen 0x01 = 00000001
	_delay_ms(2);  // msec
	LCDSendCommand(0x38); // 8 bit mode
	_delay_us(50);  // micro seconds
	LCDSendCommand(0b00001100); // 1, display on, cursor off, not blink
	_delay_us(50);
	LCDSendCommand(0x01); //Clear Screen 0x01 = 00000001
	_delay_ms(10); // let things settle.
}