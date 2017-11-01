/** 
 *	@author  Rafael Pintar Alevato
 *	@date    18/09/2017
 *	
 *	@brief Configuration for PIC16F628A. Always include this file.
 */

#define _XTAL_FREQ 4000000

#include <xc.h>

// PIC16F628A Configuration Bit Settings
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define true 1
#define false 0

/**
 *	Test a single bit of an int in position pos.
 *	@param value Value of the input to be tested
 *	@param pos Position of the bit to be tested
 *	@return Wheter the bit is 1 or 0.
 */
int_bit_test(int value, int pos) {
	return (value >> pos) & 1;
}