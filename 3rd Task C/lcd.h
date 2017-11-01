/** 
 *	@author  Rafael Pintar Alevato
 *	@date    18/09/2017
 *	
 *	@brief Functions to use LCD for PIC16F628A.
 *	You can change the PINs for enable, register_select and the 4 data pins
 *	in the defines inside lcd.h.
 */
#ifndef _LCD_
#define _LCD_

#include <stdio.h>
#include "pic_config.h"

#define lcd_enable RB1
#define lcd_rs     RB2
#define lcd_data_4 RB4
#define lcd_data_5 RB5
#define lcd_data_6 RB6
#define lcd_data_7 RB7

/**
 *	Read the least significant Nibble from a Byte and send it to the LCD.
 *	@param Data to be sent
 */
void send_nibble_lcd(int data);

/**
 *	Send a byte to the LCD.
 *	@param data_type Type of the data to be sent. 0 => Instruction. 1 => Character
 *	@param data Data to be sent
 */
void send_byte_lcd(int data_type, int data);

/**
 *	Send a character to the LCD.
 *	@param c Character to be written on LCD
 */
void write_char_lcd(char c);

/**
 *	Send a string to the LCD.
 *	@param string String pointer to be written on LCD
 */
void write_string_lcd(char* string);

/**	Clear LCD screen and set cursor to 1,1. */
void clear_lcd();

/**	Initialize LCD with cursor ready to write a character. */
void initialize_lcd();

/**
 *	Defines the position of the next character to be written.
 *	@param line Line 1 or 2 of the LCD
 *	@param column Column of the LCD 1-16
 */
void start_character(int line, int column);

#endif