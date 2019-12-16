/*
 * Ch2_REQ3.c
 *
 *  Created on: Dec 16, 2019
 *      Author: Omar Zayed
 */




#include "../../mcal/gpio/gpio.h"
#include "../../mcal/HwPWM/HwPWM.h"









void Ch2_REQ3(void)
{
	gpioPinDirection(GPIOD, BIT5, OUTPUT);
	HwPWM_Init();
	HwPWM_ChangeWidth(50, 1000000);


	while(1)
	{


	}
}
