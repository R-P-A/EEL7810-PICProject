#ifndef _PWM_
#define _PWM_

#include <stdio.h>
#include "config.h"

/**
 *	Read a analog input from a channel (PORTA).
 *	@param period Period of the PWM. Value must be > 0.
 */
void pwm_init(float period);

#endif	// _PWM_