/*
 * Ch2_REQ2.c
 *
 *  Created on: Dec 16, 2019
 *      Author: Omar Zayed
 */
/*
#include "../../firmware/led/led.h"
#include "../../mcal/SwICU/SwICU.h"
#include "../../mcal/gpio/gpio.h"
#include "../../utils/softwareDelay/softwareDelay.h"
#include <avr/delay.h>
#include "../../firmware/lcd/char_lcd.h"


uint16 CMdistance;
char str[5];





void Ch2_REQ2(void)
{
	gpioPinDirection(GPIOB, BIT1, OUTPUT); //Trig
	gpioPinDirection(GPIOB, BIT2, INPUT);
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);
	LCD_init();
	SwICU_Init(SwICU_EdgeRisiging);
	sei();
	SwICU_Enable();
	while(1)
	{
		gpioPinWrite(GPIOB, BIT1, HIGH);
		_delay_us(10);
		gpioPinWrite(GPIOB, BIT1, LOW);
		_delay_ms(200);
		itoa(CMdistance,str, 10);
		LCD_clear();
		LCD_send_string(str);

	}
}

ISR(INT2_vect)
{
	static volatile uint8 TimerOutput;
	static volatile uint8 LedsBits;
	if(gpioPinRead(GPIOB, BIT2) == HIGH)
	{
		SwICU_SetCfgEdge(SwICU_EdgeFalling);
		SwICU_Start();
	} else
	{
		SwICU_SetCfgEdge(SwICU_EdgeRisiging);
		SwICU_Stop();
		SwICU_Read(&TimerOutput);
		CMdistance = (2 * TimerOutput);
		LedsBits = CMdistance / 7;
		if(CMdistance < 106)
		{

			if(GET_BIT(LedsBits, BIT0) == 1)
			{
				Led_On(LED_0);
			}
			else
			{
				Led_Off(LED_0);
			}

			if(GET_BIT(LedsBits, BIT1) == 1)
			{
				Led_On(LED_1);
			}
			else
			{
				Led_Off(LED_1);
			}

			if(GET_BIT(LedsBits, BIT2) == 1)
			{
				Led_On(LED_2);
			}
			else
			{
				Led_Off(LED_2);
			}

			if(GET_BIT(LedsBits, BIT3) == 1)
			{
				Led_On(LED_3);
			}
			else
			{
				Led_Off(LED_3);
			}
		}
		else
		{
			Led_On(LED_0);
			Led_On(LED_1);
			Led_On(LED_2);
			Led_On(LED_3);
		}



	}
}

*/
