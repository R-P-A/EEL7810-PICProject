/** 
 *	@author  Rafael Pintar Alevato
 *	@date    02/11/2017
 *	
 *	@brief A/D Module configuration for PIC16F819.
 */

#ifndef _ADC_
#define _ADC_

#include <stdio.h>
#include "config.h"

/**
 *	Initiate the ADC module.
 *	@param port_config Analogic input port configurations (PCFG), see datasheet for the table. Values can be 0-15
 */
void adc_init(unsigned int port_config);

/**
 *	Read a analog input from a channel (PORTA).
 *	@param channel Channel to read (range is 0-7)
 *	@return value Value read by the ADC
 */
unsigned int adc_read(unsigned char channel);

#endif	// _ADC_