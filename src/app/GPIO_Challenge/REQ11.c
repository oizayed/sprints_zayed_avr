/*
 * REQ11.c
 *
 *  Created on: Dec 8, 2019
 *      Author: Omar Zayed
 */

#include "../../mcal/gpio/gpio.h"
#include "../../firmware/led/led.h"
#include "../../mcal/timers/timers.h"

void REQ11(void)
{
	Led_Init(LED_0);
	uint8 PWM = 0;
	uint8 flag = 0;
	while (1)
	{

		timer2SwPWM(PWM,0);
		if(PWM == 255)
		{
			flag = 1;
		}
		if(PWM == 0)
		{
			flag = 0;
		}
		if(flag == 0)
		{
			PWM++;
		}
		if(flag == 1)
		{
			PWM--;
		}
	}
}


