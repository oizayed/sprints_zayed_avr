/*
 * REQ1412.c
 *
 *  Created on: Dec 14, 2019
 *      Author: Omar Zayed
 */


#include "../../firmware/MotorDC/MotorDC.h"
#include "../../firmware/pushButton/pushButton.h"

uint8 Timer0PWM;


void REQ1412(void)
{
	MotorDC_Init(MOT_1);
	MotorDC_Init(MOT_2);
	pushButton_Init(BTN_0);
	MotorDC_Dir(MOT_1, FORWARD);
	MotorDC_Dir(MOT_2, FORWARD);
	//gpioPinDirection(GPIOB, BIT7, OUTPUT);
	//gpioPinDirection(GPIOD, BIT7, OUTPUT);
	Timer0PWM = 0; //range from 1 to 200
	timer0Init(T0_NORMAL_MODE,T0_OC0_DIS, T0_PRESCALER_8, 0, 0, T0_INTERRUPT_NORMAL);
	//timer1Init(T1_COMP_MODE_OCR1A_TOP,T1_OC0_DIS,T1_PRESCALER_8, 0, 2000, 0,0, T1_INTERRUPT_CMP_1A);
	sei();
	timer0Start();
	//timer1Start();
	while (1)
	{

	}
}
/*
ISR(TIMER1_COMPA_vect)
{
	static uint32 T1ISRcounter = 0;
	static uint8 pushButtonFlag = 0;
	static uint8 seq = 0;
	static uint8 PWM = 80;
	static uint8 DirectionFlag = 0;

	if(T1ISRcounter % 1000 == 0)
	{
		pushButton_Update();
		Timer0PWM++;
		if(pushButtonFlag == 2)
		{
			if(seq == 0)
			{
				MotorDC_Speed_PollingWithT0(PWM);
				if(PWM == 255)
				{
					DirectionFlag = 1;
				}
				if(PWM == 80)
				{
					DirectionFlag = 0;
				}
				if(DirectionFlag == 0)
				{
					PWM++;
				}
				if(DirectionFlag == 1)
				{
					PWM--;
				}
				if((DirectionFlag == 1) && (PWM == 81))
				{
					seq = 1;
					T1ISRcounter = 0;
				}
			}
		}

		if(pushButton_GetStatus(BTN_0) == Pressed)
		{
			pushButtonFlag = 1;
		}

		if((pushButton_GetStatus(BTN_0) == Released) && (pushButtonFlag == 1))
		{
			pushButtonFlag = 2;
		}
		if(pushButtonFlag == 2)
		{
			gpioPinToggle(GPIOB, BIT7);
			pushButtonFlag = 0;
		}
	}
	timer1Set(0);

}

 */

ISR(TIMER0_OVF_vect)
{
	static volatile uint8 Timer0CompCount = 0;
	if(Timer0CompCount == Timer0PWM)
	{
		gpioPinWrite(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, LOW);
		gpioPinWrite(MOTOR_EN_2_GPIO, MOTOR_EN_2_BIT, LOW);
	}
	else if(Timer0CompCount == 1)
	{
		gpioPinWrite(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, HIGH);
		gpioPinWrite(MOTOR_EN_2_GPIO, MOTOR_EN_2_BIT, HIGH);
	}

	Timer0CompCount++;
}




