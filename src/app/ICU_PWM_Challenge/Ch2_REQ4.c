/*
 * Ch2_REQ4.c
 *
 *  Created on: Dec 16, 2019
 *      Author: Omar Zayed
 */


#include "../../firmware/MotorDC/MotorDC.h"
#include "../../firmware/led/led.h"
#include "../../mcal/SwICU/SwICU.h"
#include "../../mcal/gpio/gpio.h"
#include "../../utils/softwareDelay/softwareDelay.h"
#include <avr/delay.h>
#include "../../firmware/lcd/char_lcd.h"



uint8 flag = 1;
uint16 CMdistance;
uint8 seq = 0;
char str[5];





void Ch2_REQ4(void)
{
	gpioPinDirection(GPIOB, BIT1, OUTPUT); //Trig
	gpioPinDirection(GPIOB, BIT2, INPUT);
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);
	MotorDC_Init(MOT_1);
	MotorDC_Init(MOT_2);
	//LCD_init();
	SwICU_Init(SwICU_EdgeRisiging);
	sei();
	SwICU_Enable();
	while(1)
	{


		gpioPinWrite(GPIOB, BIT1, HIGH);
		_delay_us(10);
		gpioPinWrite(GPIOB, BIT1, LOW);

		//itoa(CMdistance,str, 10);
		//LCD_clear();
		//LCD_send_string(str);

		if(CMdistance >= 50)
		{
			seq = 1;
		}
		else if((CMdistance < 50) && (CMdistance >= 35))
		{
			seq = 2;
		}
		else if((CMdistance < 35) && (CMdistance >= 25))
		{
			seq = 3;
		}
		else
		{
			seq = 4;
		}

		switch(seq)
		{
		case 1 :
			/////////
			gpioPinWrite(GPIOB, BIT1, HIGH);
			_delay_us(10);
			gpioPinWrite(GPIOB, BIT1, LOW);
			///////
			MotorDC_Dir(MOT_1, FORWARD);
			MotorDC_Dir(MOT_2, FORWARD);
			MotorDC_Speed_HwPWM(30);
			break;

		case 2 :

			//////
			gpioPinWrite(GPIOB, BIT1, HIGH);
			_delay_us(10);
			gpioPinWrite(GPIOB, BIT1, LOW);
			//////
			MotorDC_Dir(MOT_1, FORWARD);
			MotorDC_Dir(MOT_2, FORWARD);
			MotorDC_Speed_HwPWM(28);
			break;

		case 3 :

			//////
			gpioPinWrite(GPIOB, BIT1, HIGH);
			_delay_us(10);
			gpioPinWrite(GPIOB, BIT1, LOW);
			//////
			MotorDC_Dir(MOT_1, BACKWARD);
			MotorDC_Dir(MOT_2, FORWARD);
			MotorDC_Speed_HwPWM(28);
			_delay_ms(500);
			break;

		case 4 :

			//////
			gpioPinWrite(GPIOB, BIT1, HIGH);
			_delay_us(10);
			gpioPinWrite(GPIOB, BIT1, LOW);
			//////
			MotorDC_Dir(MOT_1, BACKWARD);
			MotorDC_Dir(MOT_2, BACKWARD);
			MotorDC_Speed_HwPWM(27);
			break;

		default :
			break;
		}
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
		flag = 0;
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
		flag = 1;
	}
}



