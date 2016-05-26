#include "Motor_PWM_lib.h"

// Port definitions for H-driver chip. use port C except for PC0, PC1 which are reserved for I2C
// put the enable connections on Port D OC1A and OC1B pins (4,5) for PWM outputs
#define HBridgeDirPort PORTC
#define HBridgeDirDataDirPort DDRC
#define HBridgeR_FWD 4
#define HBridgeL_FWD 6
#define HBridgeR_REV 7
#define HBridgeL_REV 5
#define HBridgePWMPort PORTD
#define HBridgePWMDataDirPort DDRD
#define HBridgeR_ENA 4
#define HBridgeL_ENA 5
#define PWM_Period_1 4000  // period for PWM output in counter 1 ticks.

// set up PWM
HBridgeInit()
{
	// set up port for motor control - set pins as outputs.
	HBridgeDirDataDirPort |= 1 << HBridgeR_FWD | 1 << HBridgeL_FWD
	| 1 << HBridgeR_REV | 1 << HBridgeL_REV;
	HBridgePWMDataDirPort |= 1 << HBridgeR_ENA | 1 << HBridgeL_ENA;




	// set up for fast PWM, mode 14 using ICR1 on the OC1A and OC1B ports for HBridge, prescale = 8
	// non-inverting
	TCCR1A |= 1 << WGM11 | 1 << COM1A1 | 1 << COM1B1;
	TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1 << CS11;
	//WGM10 = 0
	//TIMSK |= 1<< TOIE1 ;  // interrupt on timer/counter 1 overflow
	
	ICR1 = PWM_Period_1; // trigger for end of PWM
	OCR1A = 0; // turn off PWM for now
	OCR1B = 0;


}


// H-Bridge control.

HBridgeCommand(uint8_t side, uint8_t speed, uint8_t direction)
{
	// command direction (forward / reverse) for each motor.
	
	double junkx = 0;
	uint16_t junki = 0;
	
	if (side == 0) // 0 = left
	{
		if (speed != 0)
		{
			HBridgePWMDataDirPort |= (1 << HBridgeL_ENA);  // turn enable back on if necessary
			junkx = speed; // cast to float. Left motor
			junki = ICR1*(junkx/100);
			OCR1A = junki;
		}
		else
		{
			HBridgePWMDataDirPort &= ~(1 << HBridgeL_ENA);  // turn enable off
		}
		
		
		if (direction == 0) //forward
		{
			HBridgeDirPort |= (1 << HBridgeL_FWD); // set forward / reverse ports
			HBridgeDirPort &= ~(1 << HBridgeL_REV); // forward = on, reverse = off
			//HBridgeDC(0) = speed[side]; // speed value from 1 to 100
		} else if (direction == 1)			// reverse
		{
			HBridgeDirPort &= ~(1 << HBridgeL_FWD); // set forward / reverse ports
			HBridgeDirPort |= (1 << HBridgeL_REV); // forward = off, reverse = on
			//HBridgeDC(0) = -1*speed[side]; // speed value from -1 to -100
		}
		
	} else // right motor
	{
		if (speed != 0)
		{
			HBridgePWMDataDirPort |= (1 << HBridgeR_ENA);  // turn enable back on if necessary
			junkx = speed; // cast to float. Left motor
			junki = ICR1*(junkx/100);
			OCR1B = junki;
		}
		else
		{
			HBridgePWMDataDirPort &= ~(1 << HBridgeR_ENA);  // turn enable off
		}
		
		if (direction == 0) //forward
		{
			HBridgeDirPort |= (1 << HBridgeR_FWD); // set forward / reverse ports
			HBridgeDirPort &= ~(1 << HBridgeR_REV); // forward = on, reverse = off
			//HBridgeDC(1) = speed[side]; // speed value from 1 to 100
		} else if (direction == 1)			// reverse
		{
			HBridgeDirPort &= ~(1 << HBridgeR_FWD); // set forward / reverse ports
			HBridgeDirPort |= (1 << HBridgeR_REV); // forward = off, reverse = on
			//HBridgeDC(1) = -1*speed[side]; // speed value from -1 to -100
		}
	}
}
