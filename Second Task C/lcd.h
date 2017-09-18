/** 
 *	@author  Rafael Pintar Alevato
 *	@date    17/09/2017
 *	@version 0.9 
 *	
 *	@brief Functions to use LCD for PIC16F628A
 */

int16 lcd_d4;
int16 lcd_d5;
int16 lcd_d6;
int16 lcd_d7;
int16 lcd_enable;
int16 lcd_rs;

/**
 *	Read the least significant Nibble from a Byte and send it to the LCD.
 *	@param Data to be sent
 */
void send_nibble_lcd(int data) {
	// Load the nibble from the data to the LCD pins
	output_bit(lcd_d4, bit_test(data,0));
	output_bit(lcd_d5, bit_test(data,1));
	output_bit(lcd_d6, bit_test(data,2));
	output_bit(lcd_d7, bit_test(data,3));

	// Generates an enable pulse
	output_high(lcd_enable);
	delay_us(1);  // Delay to stabilize the LCD
	output_low(lcd_enable);
	return;
}

/**
 *	Send a byte to the LCD.
 *	@param data_type Type of the data to be sent. 0 => Instruction. 1 => Character
 *	@param data Data to be sent
 */
void send_byte_lcd(boolean data_type, int data) {
	output_bit(lcd_rs,data_type);	// Instruction or Character
	delay_us(100);					// Stabilize LCD pin
	output_low(lcd_enable);			// Clean ENABLE just to be sure
	send_nibble_lcd(data>>4);		// Send most significant nibble of data
	send_nibble_lcd(data & 0x0f);	// Send least significant nibble of data
	delay_us(40);					// Stabilize LCD
	return;
}

/**
 *	Send a character to the LCD.
 *	@param c Character to be written on LCD
 */
void write_lcd(char c) {
	send_byte_lcd(1,c);
}

void clean_lcd() {
	send_byte_lcd(0,0x01);	// Instruction to clean the LCD display
	delay_ms(2);			// Stabilize the LCD
	return;
}

/**	Initialize LCD with cursor ready to write a character.
 *	The parameters are the pins for data. Always call this first.
 */
void initialize_lcd(int16 enable_pin, int16 register_select, int16 d4, int16 d5, int16 d6, int16 d7) {
	// Make sure the pins are at 0
	lcd_d4 = d4;
	lcd_d5 = d5;
	lcd_d6 = d6;
	lcd_d7 = d7;
	lcd_enable = enable_pin;
	lcd_rs = register_select;

	output_low(lcd_d4);
	output_low(lcd_d5);
	output_low(lcd_d6);
	output_low(lcd_d7);
	output_low(lcd_rs);
	output_low(lcd_enable);
	delay_ms(15);				// Stabilize the LCD
	send_nibble_lcd(0x03);		// Command to initialize the display
	delay_ms(5);				// Stabilize the LCD
	send_nibble_lcd(0x02);		// Command to send cursor to home and clean the characters counter
	delay_ms(1);				// Stabilize the LCD
	send_byte_lcd(0,0x28);		// Command to configure the LCD to receive 4 bits, 2 lines and font 5x7
	send_byte_lcd(0,0x0c);		// Command to display control
	clean_lcd();
	send_byte_lcd(0,0x06);		// Command to move cursor to the right and wait a character
	return;
}

/**
 *	Defines the position of the next character to be written.
 *	@param c Character to be written on LCD
 */
void start_character(int line, int column) {
	int16 position=0;
	// Choose the correct line
	if (line == 1)
		position=0x80;
	if(line == 2)
		position=0xc0;

	// Sum the column to the line position. Subtract 1 to write on the right place.
	position=position+column;
	position--;

	send_byte_lcd(0,position);
	return;
}