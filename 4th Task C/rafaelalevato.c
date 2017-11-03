/** 
 *	@author  Rafael Pintar Alevato
 *	@date    02/11/2017
 *	
 *	@brief Main file for the Task 4 of EEL7810.
 *	
 *	The code does these main functions:
 *		- Read an input voltage set by a potenciometer placed on port A0 pin through ADC.
 *		- There are 2 potenciometers with a switch to select one of them:
 *			> One varying the voltage from 0 to 5 V with an increment of 0,5 V
 *			> Other varying the voltage from 0 to 5 V with an increment of 0,05 V
 *		- The voltage read by the ADC is used to control a PWM on port B3. There is a yellow led on that port.
 *		- If the voltage is less than 1 V, turn on the red led on port B0
 *		- If the voltage is greater or equal than 1 V and less than 2 V, turn on the green led on port B1
 *		- If the voltage is greater or equal than 2 V and less than 3 V, turn on the yellow led on port B2
 *		- If the voltage is greater or equal than 3 V and less than 4 V, turn on the blue led on port B4
 *		- If the voltage is greater or equal than 4 V, turn on all the leds on ports B0, B1, B2, B4
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

	// Timer 2 configuration for PWM. This configurations sets the period high to be able to see the led blinking.
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

		if (input_voltage < 1) {
			PORTB |= 0b00000001;
			PORTB &= 0b11101001;
		} else if (input_voltage < 2) {
			PORTB |= 0b00000010;
			PORTB &= 0b11101010;
		} else if (input_voltage < 3) {
			PORTB |= 0b00000100;
			PORTB &= 0b11101100;
		} else if (input_voltage < 4) {
			PORTB |= 0b00010000;
			PORTB &= 0b11111000;
		} else {
			PORTB |= 0b00010111;
		}
	}
}