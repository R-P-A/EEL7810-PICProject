#include "adc.h"

void adc_init(unsigned int port_config) {
	ADCON1 = port_config;
	ADFM = 1;
	if (_XTAL_FREQ < 1250000) {
		ADCS2 = 0;
		ADCS1 = 0;
		ADCS0 = 0;
	} else if (_XTAL_FREQ < 2500000) {
		ADCS2 = 1;
		ADCS1 = 0;
		ADCS0 = 0;
	} else if (_XTAL_FREQ < 5000000) {
		ADCS2 = 0;
		ADCS1 = 0;
		ADCS0 = 1;
	} else if (_XTAL_FREQ < 10000000) {
		ADCS2 = 1;
		ADCS1 = 0;
		ADCS0 = 1;
	} else if (_XTAL_FREQ < 20000000) {
		ADCS2 = 0;
		ADCS1 = 1;
		ADCS0 = 0;
	}
	ADON = 1;		// Turn the ADC on
}

unsigned int adc_read(unsigned char channel) {
	if(channel > 7)								// Channel range is 0-7
	  return false;

	ADCON0 &= 0b11000101;						// Clearing channel selection bits
	ADCON0 |= channel << 3;						// Setting channel selection bits
	__delay_ms(1);								// Acquisition time to charge hold capacitor
	GO_nDONE = 1;								// Initializes A/D conversion
	while(GO_nDONE);							// Waiting for conversion to complete
	return ((ADRESH << 8) + ADRESL); 			// Return result which is saved in these registers as high and low part
}