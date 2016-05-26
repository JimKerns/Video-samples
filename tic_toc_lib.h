/* Implementation of tic and toc functions using 8 bit timer TCNT0
Usage: 

uint16_t  value = 0;  / declare returned value as unsigned, 16 bit

tic_toc_init; // enable tic toc timer

sei();  // enable global interrupts.

	tic; // reset timer = 0

	value = toc; // return unsigned integer value of time since tic
	in milliseconds

Notes: Timer will overflow after 65.535 seconds without warning or error
*/

#ifndef _TIC_TOC_H_
#define _TIC_TOC_H_

#include <avr/io.h>
#include <avr/interrupt.h>

// Registers for ATMEGA128
//#define TIC_CONTROL_A TCCR0A  // control register A
//#define TIC_CONTROL_B TCCR0B  // control register B
//#define TIC_OCROA_REG OCR0A   
//#define TIC_TIMSK0 TIMSK0  // timer mask - enable interrupt
//#define tic_OCIE0A OCIE0A   // enable interrupt on OCR0A match.
//#define TIC_TIMER0_COMPA_vect TIMER0_COMPA_vect  // interrupt vector

// Registers for ATMEGA32

#define TIC_CONTROL_A TCCR0  // control register 
#define TIC_CONTROL_B TCCR0  // same register used in ATMEGA32
#define TIC_OCROA_REG OCR0
#define TIC_TIMSK0 TIMSK  // timer mask - enable interrupt
#define tic_OCIE0A OCIE0   // enable interrupt on OCR0A match.
#define TIC_TIMER0_COMPA_vect TIMER0_COMP_vect 


// prescale bits are identical in atmega128 and atmega32
// prescale / timer values for F_CPU = 11.05 MHz
 #define tic_prescale_bits 0b011   // prescale 64
 #define tic_OCR0A_VAL 171

// prescale / timer_values for F_CPU = 8 MHz
// #define tic_prescale_bits 0b011   // prescale 64
// #define tic_OCR0A_VAL  124

// prescale / timer_values for F_CPU = 1 MHz
//#define tic_prescale_bits  0b010   // prescale = 8
//#define tic_OCR0A_VAL 124

//uint16_t tic_toc_count = 0;

extern void tic_toc_init(void);  // enable timer, set pre-scale values. 

extern void tic(void); // reset timer = 0

extern uint16_t toc(void); // return unsigned integer value of time since tic
                    //in milliseconds
					
#endif
