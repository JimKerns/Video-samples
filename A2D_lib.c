/*
 * AD.c
 *
 * Created: 12/26/2012 6:50:44 PM
 *  Author: Rizzo
 *  Revised JMK - allow A/D to free run. Returned value will be latest value input. 
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "A2D_lib.h"


uint16_t AD_vals[8];
extern uint8_t ADComplete = 0;

uint8_t ADC_Mux_Array[8];  //array of active A/D pins
uint8_t ADC_Num_Mux = 0;   // number of active A/D pins

void AD_init(void)
{
	
	// set up A/D inputs
	ADCSRA |= 1<<ADPS1 | 1<<ADPS2;  // prescale to get A/d frequency between 50Hkz and 200Khz
	// a/d frequency = F_CPU/prescale = 8mhz/64=125Khz
	ADMUX |= (1<<REFS0); // select AVCC for analog reference voltage.
	ADCSRA |= 1<<ADIE;  // enable interrupt at end of A/D conversion
	ADCSRA |= 1<<ADEN; // enables the A/D input after setup is done
	ADCSRA |= 1<<ADSC; // kick off first A/D conversion
}	
	

/*void processAD(void)
{
	uint8_t ADCLowBit = ADCL; // read low bit from ADC - locks register so high bit can be red
	uint16_t ADCHiBit = ADCH<<8 | ADCLowBit;
		
	AD_vals[ADMUX & 0x07] = ADCHiBit;
		
	if(ADMUX == 0x47)    // looped through all 8 A/D inputs
	{
		ADMUX = 0x40;
		ADComplete = 1;
		return;
	}
	else
	{
		ADMUX++;
		
	}
	ADCSRA |= 1<<ADSC; // trigger next A/D
} */

uint16_t getADval(uint8_t channel)
{
	return(AD_vals[channel]);
}

ISR(ADC_vect)
{
		uint8_t ADCLowBit = ADCL; // read low bit from ADC - locks register so high bit can be red
		uint16_t ADCHiBit = ADCH<<8 | ADCLowBit;
		
		AD_vals[ADMUX & 0x07] = ADCHiBit;   // mask higher bits in ADMUX - result of and is A/D pin
				
		
		if(ADMUX == 0x47)    // looped through all 8 A/D inputs
		{
			ADMUX = 0x40;
			ADComplete = 1;
		}
		else
		{
			ADMUX++;
			
		}
		ADCSRA |= 1<<ADSC; // trigger next A/D
}
