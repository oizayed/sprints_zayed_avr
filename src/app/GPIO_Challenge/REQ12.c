/*
 * REQ12.c
 *
 *  Created on: Dec 9, 2019
 *      Author: Omar Zayed
 */


#include "../../firmware/MotorDC/MotorDC.h"
#include "../../firmware/pushButton/pushButton.h"



void REQ12(void)
{
	MotorDC_Init(MOT_1);
	MotorDC_Init(MOT_2);
	pushButton_Init(BTN_0);
	MotorDC_Dir(MOT_1, FORWARD);
	MotorDC_Dir(MOT_2, FORWARD);
	uint32 counter = 0;
	uint8 PWM = 80;
	uint8 flag = 0;
	uint8 seq = 0;
	uint32 seq2 = 0;
	while (1)
	{

		SwDelay_ms(30);
		pushButton_Update();

		if(pushButton_GetStatus(BTN_0) == Pressed)
		{
			counter = 1;
		}

		if((pushButton_GetStatus(BTN_0) == Released) && (counter == 1))
		{
			counter = 2;
		}


		if(counter == 2)
		{
			while(seq == 0)
			{
				MotorDC_Speed_PollingWithT0(PWM);
				if(PWM == 255)
				{
					flag = 1;
				}
				if(PWM == 80)
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
				if((flag == 1) && (PWM == 81))
				{
					seq = 1;
				}
			}
			MotorDC_Dir(MOT_2, BACKWARD);
			while(seq == 1)
			{
				MotorDC_Speed_PollingWithT0(100);
				seq2++;
				if(seq2 == 100)
				{
					seq = 0;
				}
			}
			counter = 0;
		}
	}
}
