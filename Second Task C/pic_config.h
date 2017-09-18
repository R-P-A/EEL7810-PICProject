#include <16F628A.h>	// Include microcontroller PIC16F628A library

// Fuses configuration
#FUSES NOWDT			// Watch Dog Timer Off
#FUSES HS				// Crystal Oscillator 4 MHz to 20 MHZ
#FUSES PUT				// Power Up Timer Enabled (Wait some time in Reset before initiating)
#FUSES NOPROTECT		// No protection for code memory from reading
#FUSES BROWNOUT			// Reset when source voltage falls under a limit
#FUSES NOMCLR			// Master Clear Pin disabled
#FUSES NOLVP			// Low voltage programming disabled
#FUSES NOCPD			// No protection for EEPROM from read/write
#FUSES INTRC_IO			// Internal Oscillator

#use delay(clock=4000000)	  // Define which clock we will utilize