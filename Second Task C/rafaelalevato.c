#include "pic_config.h"

#include <lcd.h>		// LCD library
#include <math.h>

// Definition of ins and outs of ports A and B
// 0 => output / 1 => input
#define trisa 0b00000000
#define trisb 0b11110001

int16 countB = 0;

int1 ledWasOut = false;
int1 secondTimer1Pass = false;

void interrupt_portb();

char* intToChar(int16 number);

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
	
	printf(write_lcd,"Porta B: 00");

	while(true) {
	}
}

#int_rb
void interrupt_portb() {
	if (!input(pin_b7) || !input(pin_b6) || !input(pin_b5) || !input(pin_b4)) {
		countB = countB + 1;
		start_character(1, 10);
		char* number = intToChar(countB);
		char lsdNumber = number[1];
		char msdNumber = number[0];
		write_lcd(msdNumber);
		write_lcd(lsdNumber);
		clear_interrupt(int_rb);
		delay_us(10);
	}
}

#int_timer1
void interrupt_timer1() {
	set_timer1(3030);
	if (secondTimer1Pass) {
		if (ledWasOut) {
			output_bit(pin_b1, 0);
			ledWasOut = false;
		} else {
			output_bit(pin_b1, 1);
			ledWasOut = true;
		}
		secondTimer1Pass = false;
	} else {
		secondTimer1Pass = true;
	}
	
}

char* intToChar(int16 number) {
	char result[2];
	if (number < 10) {
		result[0] = '0';
		result[1] = number + '0';
	} else if (number < 100) {
		result[0] = (number / 10) + '0';
		result[1] = (number % 10) + '0';
	} else {
		result[0] = '*';
		result[1] = '*';
	}
	return result;
}