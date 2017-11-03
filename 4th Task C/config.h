/** 
 *	@author  Rafael Pintar Alevato
 *	@date    18/09/2017
 *	
 *	@brief Configuration for PIC16F819. Always include this file.
 */

#ifndef _CONFIG_
#define _CONFIG_

// Define the frequency of the internal clock
#define _XTAL_FREQ 4000000

// PIC16F819 Configuration Bit Settings
#pragma config FOSC = HS		// Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF		// Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON		// Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF		// RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = ON		// Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF		// Low-Voltage Programming Enable bit (RB3/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF		// Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF		// Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB3		// CCP1 Pin Selection bit (CCP1 function on RB3)
#pragma config CP = OFF			// Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

#define true 1
#define false 0

/**
 *	Test a single bit of an int in position pos.
 *	@param value Value of the input to be tested
 *	@param pos Position of the bit to be tested
 *	@return Wheter the bit is 1 or 0.
 */
bit_test_int(int value, unsigned int pos);

/**
 *	Test a single bit of an unsigned int in position pos.
 *	@param value Value of the input to be tested
 *	@param pos Position of the bit to be tested
 *	@return Wheter the bit is 1 or 0.
 */
bit_test_uint(unsigned int value, unsigned int pos);

#endif	// _CONFIG_