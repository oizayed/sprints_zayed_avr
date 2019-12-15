/*
 * Ch2_REQ1.c
 *
 *  Created on: Dec 15, 2019
 *      Author: Omar Zayed
 */

#include "../../firmware/led/led.h"
#include "../../mcal/SwICU/SwICU.h"
#include "../../mcal/gpio/gpio.h"
#include "../../utils/softwareDelay/softwareDelay.h"
#include <avr/delay.h>



void Ch2_REQ1(void)
{
	gpioPinDirection(GPIOA, BIT7, OUTPUT); //Trig
	gpioPinDirection(GPIOB, BIT2, INPUT);
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);
	SwICU_Init(SwICU_EdgeRisiging);
	sei();
	SwICU_Enable();
	while(1)
	{
		gpioPinWrite(GPIOA, BIT7, HIGH);
		_delay_us(10);
		gpioPinWrite(GPIOA, BIT7, LOW);
		_delay_ms(10);

	}
}

ISR(INT2_vect)
{
	static volatile uint8 TimerOutput;
	static volatile uint16 CMdistance;
	if(gpioPinRead(GPIOB, BIT2) == HIGH)
	{
		SwICU_SetCfgEdge(SwICU_EdgeFalling);
		SwICU_Start();
	} else
	{
		SwICU_SetCfgEdge(SwICU_EdgeRisiging);
		SwICU_Stop();
		SwICU_Read(&TimerOutput);
		CMdistance = (4 * TimerOutput) / 2;

		if(CMdistance < 20)
		{
			Led_On(LED_0);
			Led_Off(LED_1);
			Led_Off(LED_2);
			Led_Off(LED_3);
		}
		else if ((CMdistance > 20) && (CMdistance < 100))
		{
			Led_Off(LED_0);
			Led_On(LED_1);
			Led_Off(LED_2);
			Led_Off(LED_3);
		}
		else if ((CMdistance > 100) && (CMdistance < 150))
		{
			Led_Off(LED_0);
			Led_Off(LED_1);
			Led_On(LED_2);
			Led_Off(LED_3);
		}
		else if (CMdistance > 150)
		{
			Led_Off(LED_0);
			Led_Off(LED_1);
			Led_Off(LED_2);
			Led_On(LED_3);
		}
	}
}



