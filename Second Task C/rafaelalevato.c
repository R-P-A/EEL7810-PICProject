#include "pic_config.h"

#include <lcd.h>		// LCD library

// Definition of ins and outs of ports A and B
// 0 => output / 1 => input
#define trisa 0b00000000
#define trisb 0b00000000

enable_interrupts(GLOBAL);
enable_interrupts(INT_RB);



// // Pins which the LCD utilizes
// #define lcd_enable	pin_b1		// LCD enable pin
// #define lcd_rs		pin_b2		// LCD register select pin 0 => commands / 1 => data

// // LCD data pins
// #define lcd_db4		pin_b4
// #define lcd_db5		pin_b5
// #define lcd_db6		pin_b6
// #define lcd_db7		pin_b7

void main() {

	initialize_lcd(pin_b4, pin_b5, pin_b6, pin_b7, pin_b1, pin_b2);

	clean_lcd();

	start_character(1,1);
	
	printf(write_lcd,"Hello World");
}