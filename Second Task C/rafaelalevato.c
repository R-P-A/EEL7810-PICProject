#include "pic_config.h"

#include <lcd.h>		// LCD library

// Definition of ins and outs of ports A and B
// 0 => output / 1 => input
#define trisa 0b00000000
#define trisb 0b00000000

// enable_interrupts(GLOBAL);
// enable_interrupts(INT_RB);

void main() {

	set_tris_a(trisa);
	set_tris_b(trisb);

	initialize_lcd(pin_b1, pin_b2, pin_a0, pin_a1, pin_a2, pin_a3);

	clean_lcd();

	start_character(1,1);
	
	printf(write_lcd,"Hello World");
}