/*
 * Motor_PWM_lib.h
 *
 * Created: 2/11/2013 10:32:44 AM
 *  Author: jkerns
 */ 


#ifndef MOTOR_PWM_H_
#define MOTOR_PWM_H_

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>


// prototype for PWM initialize
void HBridgeInit(); 
// prototype for H-Bridge control.
void HBridgeCommand(uint8_t side, int speed, uint8_t direction);


#endif /* MOTOR_PWM_H_ */