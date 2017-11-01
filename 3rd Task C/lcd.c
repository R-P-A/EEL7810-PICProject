#include "lcd.h"

void send_nibble_lcd(int data) {
	// Load the nibble from the data to the LCD pins
	lcd_data_4 = bit_test_int(data,0);
	lcd_data_5 = bit_test_int(data,1);
	lcd_data_6 = bit_test_int(data,2);
	lcd_data_7 = bit_test_int(data,3);

	// Generates an enable pulse
	lcd_enable = 1;
	__delay_us(10);  // Delay to stabilize the LCD
	lcd_enable = 0;
	return;
}

void send_byte_lcd(int data_type, int data) {
	lcd_rs = data_type;					// Instruction or Character
	__delay_us(100);					// Stabilize LCD pin
	lcd_enable = 0;						// Clean ENABLE just to be sure
	send_nibble_lcd(data>>4);			// Send most significant nibble of data
	send_nibble_lcd(data & 0x0f);		// Send least significant nibble of data
	__delay_us(40);						// Stabilize LCD
	return;
}

void write_char_lcd(char c) {
	send_byte_lcd(1,c);
}


void write_string_lcd(char* string) {
	for (int i = 0; string[i] != '\0'; i++ ) {
		write_char_lcd(string[i]);
	}
}

void clear_lcd() {
	send_byte_lcd(0,0x01);	// Instruction to clean the LCD display
	__delay_ms(2);			// Stabilize the LCD
	return;
}

void initialize_lcd() {
	lcd_data_4 = 0;
	lcd_data_5 = 0;
	lcd_data_6 = 0;
	lcd_data_7 = 0;
	lcd_rs = 0;
	lcd_enable = 0;
	__delay_ms(15);				// Stabilize the LCD
	send_nibble_lcd(0x03);		// Command to initialize the display
	__delay_ms(5);				// Stabilize the LCD
	send_nibble_lcd(0x02);		// Command to send cursor to home and clean the characters counter
	__delay_ms(1);				// Stabilize the LCD
	send_byte_lcd(0,0x28);		// Command to configure the LCD to receive 4 bits, 2 lines and font 5x7
	send_byte_lcd(0,0x0c);		// Command to display control
	clear_lcd();
	send_byte_lcd(0,0x06);		// Command to move cursor to the right and wait a character
	return;
}

void start_character(int line, int column) {
	int position = 0;
	// Choose the correct line
	if (line == 1)
		position = 0x80;
	if(line == 2)
		position = 0xc0;

	// Sum the column to the line position. Subtract 1 to write on the right place.
	position = position + column;
	position--;

	send_byte_lcd(0,position);
	return;
}