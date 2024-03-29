/*
 * MotorDC.c
 *
 *  Created on: Dec 9, 2019
 *      Author: Omar Zayed
 */

#include "MotorDC.h"
#include "MotorDC_CFG.h"
#include "../../mcal/gpio/gpio.h"
#include "../../mcal/timers/timers.h"
#include "../../mcal/HwPWM/HwPWM.h"



/**
 * Description:
 * @param
 */
void MotorDC_Init(En_motorType_t MOT_x)
{
	switch(MOT_x)
	{
	case MOT_1:
		gpioPinDirection(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, OUTPUT);
		gpioPinDirection(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, OUTPUT);
		gpioPinDirection(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, OUTPUT);
		break;
	case MOT_2:
		gpioPinDirection(MOTOR_EN_2_GPIO, MOTOR_EN_2_BIT, OUTPUT);
		gpioPinDirection(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, OUTPUT);
		gpioPinDirection(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, OUTPUT);
		break;
	default:
		break;
	}
	HwPWM_Init();

}

/**
 * Description:
 * @param
 * @param
 */
void MotorDC_Dir(En_motorType_t MOT_x, En_motorDir_t dir)
{
	switch(MOT_x)
	{
	case MOT_1:
		switch(dir)
		{
		case STOP:
			gpioPinWrite(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, LOW);
			gpioPinWrite(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, LOW);
			break;
		case FORWARD:
			gpioPinWrite(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, HIGH);
			gpioPinWrite(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, LOW);
			break;
		case BACKWARD:
			gpioPinWrite(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, LOW);
			gpioPinWrite(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, HIGH);
			break;
		default:
			break;
		}
		break;
		case MOT_2:
			switch(dir)
			{
			case STOP:
				gpioPinWrite(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, LOW);
				gpioPinWrite(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, LOW);
				break;
			case FORWARD:
				gpioPinWrite(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, HIGH);
				gpioPinWrite(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, LOW);
				break;
			case BACKWARD:
				gpioPinWrite(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, LOW);
				gpioPinWrite(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, HIGH);
				break;
			default:
				break;
			}
			break;
			default:
				break;
	}
}

/**
 * Description:
 * @param
 */
void MotorDC_Speed_PollingWithT0(uint8 speed)
{
	float DC = speed / 255.00;
	gpioPinWrite(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, HIGH);
	gpioPinWrite(MOTOR_EN_2_GPIO, MOTOR_EN_2_BIT, HIGH);
	timer0Delay_ms(DC * 29);
	gpioPinWrite(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, LOW);
	gpioPinWrite(MOTOR_EN_2_GPIO, MOTOR_EN_2_BIT, LOW);
	timer0Delay_ms((1.00 - DC) * 29);

}

/**
 * Description: set the port value (which is PORT register)
 * @param
 */
void MotorDC_Speed_HwPWM(uint8 speed)
{
	HwPWM_ChangeWidth(speed, 400);
}
