/* Functions to read all 8 A/D inputs on the LTU ERE controller board as fast as possible -
As soon as one value is read, the next A/D input is triggered. 

Usage: 

AD_init(); // Set up parameters for A/D inputs

sei();  // enable global interrupts.

getADval(channel);  // returns latest A/D values for pin channel


JMK 2/8/2013
*/


#ifndef AD_H_
#define AD_H_

extern uint8_t ADComplete;  // set when all 8 A/D channels have been read. 

extern void AD_init(void);
//extern void processAD(void);  

extern uint16_t getADval(uint8_t channel);  // returns latest A/D values. 

#endif /* AD_H_ */