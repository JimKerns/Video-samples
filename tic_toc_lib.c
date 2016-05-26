#include "tic_toc_lib.h"

uint16_t tic_toc_count = 0;

// enable timer, set pre-scale values.
// initialize registers to set up tic toc timers
void tic_toc_init(void) 
{  

TIC_CONTROL_A |= 1<<WGM01;  // enable CTC Clear on Compare mode
TIC_CONTROL_B |= tic_prescale_bits<<(CS00);  // set up prescale
TIC_OCROA_REG = tic_OCR0A_VAL; // set "top" of TCNT0
TIC_TIMSK0 |= (1<<tic_OCIE0A);  // enable interrupt vector
}

void tic(void) // reset timer = 0
{
	TCNT0 = 0;   // reset timer
	tic_toc_count = 0; // reset millisecond counter

}

uint16_t toc(void){ // return unsigned integer value of time since tic
//in milliseconds
uint16_t tmp;
tmp = tic_toc_count;
return(tmp);

}


// tic_toc updtate - interrupt at the end of each PWM period...
ISR(TIC_TIMER0_COMPA_vect)
{
	// count up one millisecond each interrupt
	
	tic_toc_count++;
	
}