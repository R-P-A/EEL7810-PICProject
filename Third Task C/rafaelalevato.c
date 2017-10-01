/** 
 *	@author  Rafael Pintar Alevato
 *	@date    01/10/2017
 *	
 *	@brief Main file for the Task 3 of EEL7810.
 *	
 *	The code does two main functions:
 *	- A counter of 1 second interval dictated by the timer 1.
 *	- The counter needs to be displayed in decimal and hexadecimal.
 *	- The value of the counter needs to be saved on EEPROM memory and it needs to restart from last value.
 */

#include <stdio.h>
#include "pic_config.h"
#include "lcd.h"

// Led blinked by the timer1 interruption
#define blink_led RB0

// Flags used in the interruptions
bit interrupt_portb_flag = false;
bit interrupt_timer1_flag = false;
bit second_timer1_pass = false;

void main() {

	// Ins and Outs of ports A and B. 0 => output / 1 => input
	TRISA = 0b00000000;
	TRISB = 0b00000000;

	// Make sure no other pin from PORTB or PORTA is set.
	PORTB = 0x00;
	PORTA = 0x00;

	// Interrupt Configuration
	GIE = true;			// Global Interrupt Enable
	PEIE = true;		// Peripherals Interrupt Enable
	TMR1IE = true;		// Timer 1 Interrupt Enable
	TMR1ON = true;		// Timer 1 ON
	TMR1CS = false;		// Timer 1 set as timer
	T1CKPS0 = 1;		// T1CKPS = 0b11 => Prescaler 8
	T1CKPS1 = 1;

	initialize_lcd();
	clear_lcd();

	int int_counter_rb = 0;
	char lcd_string[18];
	write_string_lcd("Counter");
	start_character(2,1);
	sprintf(lcd_string, "Dec: %d Hex: %X", int_counter_rb, int_counter_rb);
	write_string_lcd(lcd_string);

	while(true) {
		if (interrupt_timer1_flag) {
			interrupt_timer1_flag = false;
			// Passing two times to give 1 second of delay
			if (second_timer1_pass) {
				second_timer1_pass = false;
				blink_led = ~blink_led;
				int_counter_rb++;
				clear_lcd();
				write_string_lcd("Counter");
				start_character(2,1);
				sprintf(lcd_string, "Dec: %d Hex: %X", int_counter_rb, int_counter_rb);
				write_string_lcd(lcd_string);
			} else {
				second_timer1_pass = true;
			}
		}
	}
}


void interrupt interrupt_service_routine(void) {
	// If interrupt from timer 1
	if (TMR1IE && TMR1IF) {
		TMR1IF = false;
		TMR1 = 0x0BE0;
		interrupt_timer1_flag = true;
		return;
	}
	return;
}