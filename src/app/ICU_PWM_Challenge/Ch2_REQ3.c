/*
 * Ch2_REQ3.c
 *
 *  Created on: Dec 17, 2019
 *      Author: Omar Zayed
 */

/*

#include "../../firmware/MotorDC/MotorDC.h"
#include "../../firmware/led/led.h"
#include "../../mcal/SwICU/SwICU.h"
#include "../../mcal/gpio/gpio.h"
#include <avr/delay.h>
#include "../../firmware/lcd/char_lcd.h"


uint32 T0counter = 0;
static volatile uint16 CMdistance = 50;
static volatile uint8 LedsBits = 0;
uint8 seq = 0;
char str[5];


void Ch2_REQ3(void)
{
	gpioPinDirection(GPIOB, BIT1, OUTPUT); 	//Trigger
	gpioPinDirection(GPIOB, BIT2, INPUT);	//Echo

	timer0Init(T0_COMP_MODE, T0_OC0_DIS, T0_PRESCALER_64, 0, 250, T0_INTERRUPT_CMP);
	timer0Start();

	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);

	MotorDC_Init(MOT_1);
	MotorDC_Init(MOT_2);

	SwICU_Init(SwICU_EdgeRisiging);
	SwICU_Enable();

	sei();



	while(1)
	{
		gpioPinWrite(GPIOB, BIT1, HIGH);
		_delay_us(10);
		gpioPinWrite(GPIOB, BIT1, LOW);
		_delay_ms(200);

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



/*

ISR(TIMER0_COMP_vect)
{

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

		MotorDC_Dir(MOT_1, FORWARD);
		MotorDC_Dir(MOT_2, FORWARD);
		MotorDC_Speed_HwPWM(50);
		break;

	case 2 :

		MotorDC_Dir(MOT_1, FORWARD);
		MotorDC_Dir(MOT_2, FORWARD);
		MotorDC_Speed_HwPWM(40);
		break;

	case 3 :

		MotorDC_Speed_HwPWM(0);
		MotorDC_Dir(MOT_1, BACKWARD);
		MotorDC_Dir(MOT_2, FORWARD);
		_delay_ms(1000);
		MotorDC_Speed_HwPWM(20);
		_delay_ms(1000);
		MotorDC_Speed_HwPWM(0);
		_delay_ms(1000);
		break;

	case 4 :

		MotorDC_Speed_HwPWM(0);
		MotorDC_Dir(MOT_1, BACKWARD);
		MotorDC_Dir(MOT_2, BACKWARD);
		_delay_ms(1000);
		MotorDC_Speed_HwPWM(40);
		break;

	default :
		break;
	}
}
 */
