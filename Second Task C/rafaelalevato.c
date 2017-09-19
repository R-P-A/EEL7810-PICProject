/** 
 *	@author  Rafael Pintar Alevato
 *	@date    18/09/2017
 *	
 *	@brief Main file for the Task 2 of EEL7810.
 *	
 *	The code does two main functions:
 *	- Blinks a led in a 1 second interval dictated by the timer 1.
 *	- Display a counter on a LCD with the number of times any button was pressed.
 */

#include <stdio.h>
#include "pic_config.h"
#include "lcd.h"

// Buttons for the inputs which trigger the interruptions
#define button_1 RB4
#define button_2 RB5
#define button_3 RB6
#define button_4 RB7

// Led blinked by the timer1 interruption
#define blink_led RB1

// Flags used in the interruptions
bit interrupt_portb_flag = false;
bit interrupt_timer1_flag = false;
bit second_timer1_pass = false;

void main() {

	// Ins and Outs of ports A and B. 0 => output / 1 => input
	TRISA = 0b00000000;
	TRISB = 0b11110000;

	// Make sure no other pin from PORTB or PORTA is set.
	PORTB = 0x00;
	PORTA = 0x00;

	// Interrupt Configuration
	GIE = true;			// Global Interrupt Enable
	PEIE = true;		// Peripherals Interrupt Enable
	RBIE = true;		// Interrupt on Change of PORTB (RB<7:4>)
	TMR1IE = true;		// Timer 1 Interrupt Enable
	TMR1ON = true;		// Timer 1 ON
	TMR1CS = false;		// Timer 1 set as timer
	T1CKPS0 = 1;		// T1CKPS = 0b11 => Prescaler 8
	T1CKPS1 = 1;

	initialize_lcd();
	clear_lcd();

	int int_counter_rb = 0;
	char lcd_string[18];
	write_string_lcd("Interrupt PORTB");
	start_character(2,1);
	sprintf(lcd_string, "Counter: %d", int_counter_rb);
	write_string_lcd(lcd_string);

	while(true) {
		if (interrupt_portb_flag) {
			interrupt_portb_flag = false;
			int_counter_rb++;
			clear_lcd();
			write_string_lcd("Interrupt PORTB");
			start_character(2,1);
			sprintf(lcd_string, "Counter: %d", int_counter_rb);
			write_string_lcd(lcd_string);
		}

		if (interrupt_timer1_flag) {
			interrupt_timer1_flag = false;
			// Passing two times to give 1 second of delay
			if (second_timer1_pass) {
				second_timer1_pass = false;
				blink_led = ~blink_led;
			} else {
				second_timer1_pass = true;
			}
		}
	}
}


void interrupt interrupt_service_routine(void) {
	// If interrupt from buttons
	if (RBIE && RBIF) {
		// Need to read or write PORTB to be able to reset this interrupt flag
		int read_portb = button_1;
		RBIF = false;
		interrupt_portb_flag = true;
		return;
	}

	// If interrupt from timer 1
	if (TMR1IE && TMR1IF) {
		TMR1IF = false;
		TMR1 = 0x0BE0;
		interrupt_timer1_flag = true;
		return;
	}
	return;
}