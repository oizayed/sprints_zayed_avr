/*
 * pushButton.c
 *
 *  Created on: Dec 7, 2019
 *      Author: Omar Zayed
 */

#include "../../mcal/gpio/gpio.h"
#include "pushButton.h"

static buttons avrbuttons[BTN_MAX_NUM];
static uint8 buttonNo = 0;

/**
 * Description: Initialize the BTN_x Pin state (where x 0, 1, 2, 3) to Input
 * @param btn_id: The btn to be initialized and it takes
 * 				  one of the enum (En_buttonId) parameters
 *
 */

void pushButton_Init(En_buttonId btn_id)
{
	avrbuttons[buttonNo].buttonID = btn_id;
	switch(btn_id)
	{
	case BTN_0:
		gpioPinDirection(BTN_0_GPIO, BTN_0_BIT, INPUT);
		avrbuttons[buttonNo].GPIOPort = BTN_0_GPIO;
		avrbuttons[buttonNo].buttonBit = BTN_0_BIT;
		break;
	case BTN_1:
		gpioPinDirection(BTN_1_GPIO, BTN_1_BIT, INPUT);
		avrbuttons[buttonNo].GPIOPort = BTN_1_GPIO;
		avrbuttons[buttonNo].buttonBit = BTN_1_BIT;
		break;
	case BTN_2:
		gpioPinDirection(BTN_2_GPIO, BTN_2_BIT, INPUT);
		avrbuttons[buttonNo].GPIOPort = BTN_2_GPIO;
		avrbuttons[buttonNo].buttonBit = BTN_2_BIT;

		break;
	case BTN_3:
		gpioPinDirection(BTN_3_GPIO, BTN_3_BIT, INPUT);
		avrbuttons[buttonNo].GPIOPort = BTN_3_GPIO;
		avrbuttons[buttonNo].buttonBit = BTN_3_BIT;
		break;
	default:
		break;
	}
	buttonNo++;

}

/**
 * Description: read all BTN_x (where x 0, 1, 2, 3) states and store it in the program
 *
 * @note : this function must be called in the system tick hundler or in the super loop hundler
 */
void pushButton_Update(void)
{
	for(uint8 i = 0; i < buttonNo; i++)
	{
		if(gpioPinRead(avrbuttons[i].GPIOPort,avrbuttons[i].buttonBit) == HIGH)
		{
			if(avrbuttons[i].buttonStatus == Released)
			{
				avrbuttons[i].buttonStatus = Prepressed;
			}
			else if(avrbuttons[i].buttonStatus == Prepressed)
			{
				avrbuttons[i].buttonStatus = Pressed;
			}
		} else
		{
			if(avrbuttons[i].buttonStatus == Pressed)
			{
				avrbuttons[i].buttonStatus = Prereleased;
			}
			else if(avrbuttons[i].buttonStatus == Prereleased)
			{
				avrbuttons[i].buttonStatus = Released;
			}
		}
	}
}
/**
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 */
En_buttonStatus_t pushButton_GetStatus(En_buttonId btn_id)
{
	En_buttonStatus_t outStatus;
	for(uint8 i = 0; i < buttonNo; i++)
	{
		if(btn_id == avrbuttons[i].buttonID)
		{
			outStatus = avrbuttons[i].buttonStatus;
		}
	}

	return outStatus;

}


