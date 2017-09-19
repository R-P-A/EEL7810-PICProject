#include <stdio.h>
#include "pic_config.h"
#include "lcd.h"


#define button_1 RB4
#define button_2 RB5
#define button_3 RB6
#define button_4 RB7

#define blink_led RB1
#define test_led RB0

// Global variables used in interruptions
bit interrupt_portb_flag = false;
bit interrupt_timer1_flag = false;
bit second_timer1_pass = false;

void main() {

	test_led = 0;

	// Ins and Outs of ports A and B. 0 => output / 1 => input
	TRISA = 0b00000000;
	TRISB = 0b11110000;

	RBIE = true;
	GIE = true;
	PEIE = true;
	TMR1IE = true;
	TMR1ON = true;
	TMR1CS = false;
	T1CKPS0 = 1;
	T1CKPS1 = 1;

	initialize_lcd();
	clear_lcd();
	start_character(1,1);

	int count_int_portb = 0;
	char lcd_string[17];
	sprintf(lcd_string, "Int B: %d", count_int_portb);
	write_string_lcd(lcd_string);

	while(true) {
		if (interrupt_portb_flag) {
			interrupt_portb_flag = false;
			// This interruption is on button change, so we check if button is pressed to count only once.
			if (button_1 == 0 || button_2 == 0  || button_3 == 0  || button_4 == 0 ) {
				count_int_portb++;
				clear_lcd();
				sprintf(lcd_string, "Int B: %d", count_int_portb);
				write_string_lcd(lcd_string);
			}
		}

		if (interrupt_timer1_flag) {
			interrupt_timer1_flag = false;
			if (second_timer1_pass) {
				second_timer1_pass = false;
				blink_led = ~blink_led;
			} else {
				second_timer1_pass = true;
			}
		}
	}
}

void __interrupt ISR(void) {
	if (RBIE && RBIF) {
		RBIF = false;
		interrupt_portb_flag = true;
		int read_portb = button_1;
		return;
	}
	if (TMR1IE && TMR1IF) {
		TMR1IF = false;
		TMR1 = 0x0BE0;
		interrupt_timer1_flag = true;
		return;
	}
	return;
}