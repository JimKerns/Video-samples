/*
 * LEDBlink.c
 *
 * Created: 1/17/2013 9:42:31 AM
 *  Author: jkerns
 */ 

#define F_CPU 1000000 // factory default clock rate for this chip = 1 MHz. 
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB = 0b00000001; // set port B pin 0 as output, pins 1-7 as inputs. 
	//DDRB |= (1 << DDRB0) |(1 << DDRB1) |(1 << DDRB2) |(1 << DDRB3) ; // set DDRB for Pin0 to 3 as outputs - a better way using "|=" for or equals and "<<" as shift left
	PORTB = 0b00000000; // set all low
	
	while (1)  // run forever. Or, at least until shut off. 
	{		   
				
		PORTB ^= 1 << PINB0;  // change state of port B pin 0 using an exclusive or with a 1 shifted left by PINB0

		_delay_ms(500);  // delay in milliseconds 1000 = 1 second. 
	}
}