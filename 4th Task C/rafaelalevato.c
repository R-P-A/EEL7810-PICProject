/** 
 *	@author  Rafael Pintar Alevato
 *	@date    01/10/2017
 *	
 *	@brief Main file for the Task 4 of EEL7810.
 *	
 *	The code does two main functions:
 */

#include <stdio.h>
#include "config.h"
#include "adc.h"

// Led blinked by the timer1 interruption
#define blink_led RB0

void main() {

	adc_init();

	// Ins and Outs of ports A and B. 0 => output / 1 => input
	TRISA = 0b00000001;
	TRISB = 0b00000000;

	// Timer 2 configuration for PWM
	TMR2ON = 1;
	T2CKPS1 = 1;
	T2CKPS0 = 1;
	PR2 = 0xFF;

	// PWM Configuration on port RB3
	CCP1M3 = 1;
	CCP1M2 = 1;
	CCP1M1 = 0;
	CCP1M0 = 0;

	// Make sure no other pin from PORTB is set.
	PORTB = 0b00000000;

	unsigned int input_pot;
	float input_voltage;

	while(true) {
		input_pot = adc_read(0);
		CCP1Y = bit_test_uint(input_pot, 0);
		CCP1X = bit_test_uint(input_pot, 1);
		CCPR1L = input_pot >> 2;

		input_voltage = (float) input_pot * 0.00491;	// Constant to convert the value read to 0-5 V (5/1024 plus adjustments)

		if (input_voltage <= 1) {
			PORTB = 0b00000001;
		} else if (input_voltage <= 2) {
			PORTB = 0b00000010;
		} else if (input_voltage <= 3) {
			PORTB = 0b00000100;
		} else if (input_voltage <= 4) {
			PORTB = 0b00010000;
		} else {
			PORTB = 0b00010111;
		}
	}
}