#include "adc.h"

void adc_init() {
	ADON = true;		// Turn the ADC on
	ADCS0 = false;		// Set the Clock Select bits
	ADCS1 = true;
	ADCON1 = 0b10001110;
}

unsigned int adc_read(unsigned char channel) {
	if(channel > 7)								//Channel range is 0 ~ 7
	  return false;

	ADCON0 &= 0b11000101;						//Clearing channel selection bits
	ADCON0 |= channel << 3;						//Setting channel selection bits
	__delay_ms(2);								//Acquisition time to charge hold capacitor
	GO_nDONE = true;							//Initializes A/D conversion
	while(GO_nDONE);							//Waiting for conversion to complete
	return ((ADRESH << 8) + ADRESL); 	//Return result which is saved in these registers as high and low part
}