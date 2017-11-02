/** 
 *	@author  Rafael Pintar Alevato
 *	@date    18/09/2017
 *	
 *	@brief A/D Module configuration for PIC16F819.
 */

#ifndef _ADC_
#define _ADC_

#include <stdio.h>
#include "config.h"

/**
 *	Initiate the ADC module.
 */
void adc_init();

/**
 *	Read a analog input from a channel (PORTA).
 *	@param Channel to read (RA0-RA7)
 *	@return Value read by the ADC
 */
unsigned int adc_read(unsigned char channel);

#endif	// _ADC_