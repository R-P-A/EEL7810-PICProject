/** 
 *	@author  Rafael Pintar Alevato
 *	@date    17/09/2017
 *	@version 0.9 
 *	
 *	@brief Functions to use LCD for PIC16F628A.
 */

#define lcd_enable RB2
#define lcd_rs RB3
#define lcd_data_4 RA0
#define lcd_data_5 RA1
#define lcd_data_6 RA2
#define lcd_data_7 RA3

void send_nibble_lcd(int data);
void send_byte_lcd(int data_type, int data);
void write_char_lcd(char c);
void write_string_lcd(char* string);
void clear_lcd();
void initialize_lcd();
void start_character(int line, int column);

/**
 *	Read the least significant Nibble from a Byte and send it to the LCD.
 *	@param Data to be sent
 */
void send_nibble_lcd(int data) {
	// Load the nibble from the data to the LCD pins
	lcd_data_4 = int_bit_test(data,0);
	lcd_data_5 = int_bit_test(data,1);
	lcd_data_6 = int_bit_test(data,2);
	lcd_data_7 = int_bit_test(data,3);

	// Generates an enable pulse
	lcd_enable = 1;
	__delay_us(10);  // Delay to stabilize the LCD
	lcd_enable = 0;
	return;
}

/**
 *	Send a byte to the LCD.
 *	@param data_type Type of the data to be sent. 0 => Instruction. 1 => Character
 *	@param data Data to be sent
 */
void send_byte_lcd(int data_type, int data) {
	lcd_rs = data_type;					// Instruction or Character
	__delay_us(100);					// Stabilize LCD pin
	lcd_enable = 0;						// Clean ENABLE just to be sure
	send_nibble_lcd(data>>4);			// Send most significant nibble of data
	send_nibble_lcd(data & 0x0f);		// Send least significant nibble of data
	__delay_us(40);						// Stabilize LCD
	return;
}

/**
 *	Send a character to the LCD.
 *	@param c Character to be written on LCD
 */
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

/**	Initialize LCD with cursor ready to write a character.
 *	The parameters are the pins for data. Always call this first.
 */
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

/**
 *	Defines the position of the next character to be written.
 *	@param c Character to be written on LCD
 */
void start_character(int line, int column) {
	int position = 0;
	// Choose the correct line
	if (line == 1)
		position=0x80;
	if(line == 2)
		position=0xc0;

	// Sum the column to the line position. Subtract 1 to write on the right place.
	position = position + column;
	position--;

	send_byte_lcd(0,position);
	return;
}