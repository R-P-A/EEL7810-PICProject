#include "pic_config.h"

#include <lcd.h>		// LCD library
#include <math.h>

// Definition of ins and outs of ports A and B
// 0 => output / 1 => input
#define trisa 0b00000000
#define trisb 0b11110001

int16 countB = 0;

void interrupt_portb();

char* intToChar(int16 number);

void main() {

	enable_interrupts(global);
	enable_interrupts(int_rb);

	set_tris_a(trisa);
	set_tris_b(trisb);

	initialize_lcd(pin_b1, pin_b2, pin_a0, pin_a1, pin_a2, pin_a3);

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
		clean_lcd();
		printf(write_lcd, "Porta B: ");
		char* number;
		number = intToChar(countB);
		char lsdNumber = number[1];
		char msdNumber = number[0];
		write_lcd(msdNumber);
		write_lcd(lsdNumber);
		clear_interrupt(int_rb);
		delay_us(10);
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