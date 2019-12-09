/*
 * REQ14.c
 *
 *  Created on: Dec 9, 2019
 *      Author: Omar Zayed
 */

#include "../../mcal/gpio/gpio.h"
#include "../../mcal/timers/timers.h"

void REQ14(void)
{
	gpioPinDirection(GPIOC, BIT4, OUTPUT);
	while (1)
	{

		timer2Delay_us(1);
		gpioPinToggle(GPIOC, BIT4);
	}
}


