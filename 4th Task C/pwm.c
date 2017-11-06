#include "pwm.h"

void pwm_init(float period) {
	period /= 4;
	period *= _XTAL_FREQ;
	// Timer 2 configuration for PWM.
	if ((period / 256) >= 16) {
		T2CKPS1 = 1;
		T2CKPS0 = 1;
		PR2 = 0xFF;
		TMR2ON = 1;
	} else if ((period / 256) >= 4) {
		T2CKPS1 = 1;
		T2CKPS0 = 1;
		period /= 16;
		PR2 = (int) period;
		TMR2ON = 1;
	} else if ((period / 256) >= 1) {
		T2CKPS1 = 0;
		T2CKPS0 = 1;
		period /= 4;
		PR2 = (int) period;
		TMR2ON = 1;
	} else if ((period / 256) >= 0) {
		T2CKPS1 = 0;
		T2CKPS0 = 0;
		PR2 = (int) period;
		TMR2ON = 1;
	} else {
		T2CKPS1 = 1;
		T2CKPS0 = 1;
		PR2 = 0xFF;
		TMR2ON = 1;
	}

	// PWM Configuration of Capture/Compare/PWM Module
	CCP1M3 = 1;
	CCP1M2 = 1;
	CCP1M1 = 0;
	CCP1M0 = 0;
}