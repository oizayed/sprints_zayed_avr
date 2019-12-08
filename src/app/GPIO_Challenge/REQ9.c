/*
 * REQ9.c
 *
 *  Created on: Dec 8, 2019
 *      Author: Omar Zayed
 */

#include "../../mcal/gpio/gpio.h"
#include "../../firmware/led/led.h"
#include "../../firmware/pushButton/pushButton.h"
#include "../../mcal/timers/timers.h"

static En_LedNumber_t WhichLedOn;


void REQ9(void)
{
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_On(LED_0);
	pushButton_Init(BTN_0);
	pushButton_Init(BTN_1);
	WhichLedOn = LED_0;
	uint8 flag = 0;


	while(1)
	{

		switch(WhichLedOn)
		{
		case LED_0 :
			while(flag != 2)
			{
				timer0Delay_ms(30);
				pushButton_Update();

				if(pushButton_GetStatus(BTN_0) == Pressed)
				{
					flag = 1;
					Led_Off(LED_0);
					Led_On(LED_1);
				}

				if((pushButton_GetStatus(BTN_0) == Released) && (flag == 1))
				{
					flag = 2;
				}
			}
			WhichLedOn = LED_1;
			timer2Delay_ms(1000);
			flag = 0;
			break;
		case LED_1 :
			Led_Off(LED_1);
			Led_On(LED_2);
			WhichLedOn = LED_2;
			timer2Delay_ms(1000);
			break;
		case LED_2 :
			Led_Off(LED_2);
			Led_On(LED_0);
			WhichLedOn = LED_0;
			timer2Delay_ms(1000);
			break;
		default : // default case
			break;
		}
	}
}



