/*
 * REQ7.c
 *
 *  Created on: Dec 7, 2019
 *      Author: Omar Zayed
 */

#include "../../mcal/gpio/gpio.h"
#include "../../firmware/led/led.h"
#include "../../utils/softwareDelay/softwareDelay.h"

static En_LedNumber_t WhichLedOn;

void REQ7(void)
{
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_On(LED_0);
	WhichLedOn = LED_0;

	while(1)
	{
		SwDelay_ms(1000);
		switch(WhichLedOn)
		{
		case LED_0 :
			Led_Off(LED_0);
			Led_On(LED_1);
			WhichLedOn = LED_1;
			break;
		case LED_1 :
			Led_Off(LED_1);
			Led_On(LED_2);
			WhichLedOn = LED_2;
			break;
		case LED_2 :
			Led_Off(LED_2);
			Led_On(LED_0);
			WhichLedOn = LED_0;
			break;
		default : // default case
			break;
		}
	}
}


