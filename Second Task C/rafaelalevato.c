#include "pic_config.h"

#include <lcd.h>		// LCD library

// Definition of ins and outs of ports A and B
// 0 => output / 1 => input
#define trisa 0b00000000
#define trisb 0b11110001

#define button_1 pin_b4
#define button_2 pin_b5
#define button_3 pin_b6
#define button_4 pin_b7

#define blink_led pin_b1

#define enbale_lcd pin_b2
#define rs_lcd pin_b3
#define data_1 pin_a0
#define data_2 pin_a1
#define data_3 pin_a2
#define data_4 pin_a3

// Global variables used in interruptions
int1 interrupt_portb_flag = false;
int1 interrupt_timer1_flag = false;

void interrupt_portb();

char* intToChar(int16 number);

int1 is_button_pressed(int16 button);

void main() {

	enable_interrupts(global);
	enable_interrupts(int_rb);
	enable_interrupts(int_timer1);

	set_tris_a(trisa);
	set_tris_b(trisb);

	setup_timer_1(t1_internal | t1_div_by_8);

	initialize_lcd(pin_b2, pin_b3, pin_a0, pin_a1, pin_a2, pin_a3);

	clean_lcd();

	start_character(1,1);
	
	printf(write_lcd,"Int B(4-7): 0000");

	int16 countB = 0;
	int1 ledWasOut = false;
	int1 secondTimer1Pass = false;

	while(true) {
		if (interrupt_portb_flag) {
			interrupt_portb_flag = false;
			// This interruption is on button change, so we check if button is pressed to count only once.
			if (!input(pin_b7) || !input(pin_b6) || !input(pin_b5) || !input(pin_b4)) {
				countB = countB + 1;
				start_character(1, 13);
				char* number = intToChar(countB);
				for (int i = 0; i < 4; i++) {
					write_lcd(number[i]);
				}
			}
		}

		if (interrupt_timer1_flag) {
			interrupt_timer1_flag = false;
			if (secondTimer1Pass) {
				secondTimer1Pass = false;
				if (ledWasOut) {
					output_bit(pin_b1, 0);
					ledWasOut = false;
				} else {
					output_bit(pin_b1, 1);
					ledWasOut = true;
				}
			} else {
				secondTimer1Pass = true;
			}
		}
	}
}

#int_rb
void interrupt_portb() {
	clear_interrupt(int_rb);
	interrupt_portb_flag = true;
}

#int_timer1
void interrupt_timer1() {
	clear_interrupt(int_timer1);
	set_timer1(3030);
	interrupt_timer1_flag = true;
}

int1 is_button_pressed(int16 button) {
	return !input(button);
}

char* intToChar(int16 number) {
	char result[4];
	if (number < 10) {
		result[0] = '0';
		result[1] = '0';
		result[2] = '0';
		result[3] = number + '0';
	} else if (number < 100) {
		result[0] = '0';
		result[1] = '0';
		result[2] = (number / 10) + '0';
		result[3] = (number % 10) + '0';
	} else if (number < 1000) {
		result[0] = '0';
		result[1] = (number / 100) + '0';
		result[2] = ((number % 100) / 10) + '0';
		result[3] = ((number % 100) % 10) + '0';
	} else if (number < 10000) {
		result[0] = (number / 1000) + '0';
		result[1] = ((number % 1000) / 100) + '0';
		result[2] = (((number % 1000) % 100) / 10) + '0';
		result[3] = (((number % 1000) % 100) % 10) + '0';
	} else {
		result[0] = ' ';
		result[1] = 'O';
		result[2] = 'V';
		result[3] = 'F';
	}
	return result;
}