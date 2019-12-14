/*
 * REQ1411.c
 *
 *  Created on: Dec 14, 2019
 *      Author: Omar Zayed
 */




#include "../../mcal/gpio/gpio.h"
#include "../../mcal/timers/timers.h"

void REQ1411(void)
{
	gpioPinDirection(GPIOD, BIT7, OUTPUT);
	gpioPinDirection(GPIOD, BIT6, OUTPUT);
	timer0SwPWM(125,78);
	while (1)
	{
		timer2Delay_ms(50);
		gpioPinToggle(GPIOD, BIT6);



	}
}
