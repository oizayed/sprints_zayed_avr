/*
 * REQ86.c
 *
 *  Created on: Dec 8, 2019
 *      Author: Omar Zayed
 */

#include "../../mcal/gpio/gpio.h"
#include "../../firmware/led/led.h"
#include "../../utils/softwareDelay/softwareDelay.h"
#include "../../firmware/pushButton/pushButton.h"
#include "../../mcal/timers/timers.h"


void REQ86(void)
{
	Led_Init(LED_0);
	Led_Init(LED_1);
	pushButton_Init(BTN_0);
	pushButton_Init(BTN_1);
	uint32 counter = 0;
	uint8 BTNCounter = 0;


	while(1)
	{
		timer0Delay_ms(30);
		pushButton_Update();

		if(pushButton_GetStatus(BTN_0) == Pressed)
		{
			Led_On(LED_0);
			counter = 0;
		}

		if(pushButton_GetStatus(BTN_0) == Released)
		{
			counter++;
		}
		if(counter == 1)
		{
			BTNCounter++;
		}

		if(counter > (16 * BTNCounter))
		{

			Led_Off(LED_0);
			counter = 0;
			BTNCounter = 0;
		}
	}
}


