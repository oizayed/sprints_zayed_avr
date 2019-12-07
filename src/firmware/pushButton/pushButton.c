/*
 * pushButton.c
 *
 *  Created on: Dec 7, 2019
 *      Author: Omar Zayed
 */

#include "../../mcal/gpio/gpio.h"
#include "pushButton.h"

//static buttons avrbuttons[BTN_MAX_NUM];

/**
 * Description: Initialize the BTN_x Pin state (where x 0, 1, 2, 3) to Input
 * @param btn_id: The btn to be initialized and it takes
 * 				  one of the enum (En_buttonId) parameters
 *
 */
/*
void pushButton_Init(En_buttonId btn_id)
{
	static uint8 buttonNo = 0;
	avrbuttons[buttonNo].buttonID = btn_id;
	buttonNo++;
	switch(btn_id)
	{
	case BTN_0:
		gpioPinDirection(BTN_0_GPIO, BTN_0_BIT, OUTPUT);
		break;
	case BTN_1:
		gpioPinDirection(BTN_1_GPIO, BTN_1_BIT, OUTPUT);
		break;
	case BTN_2:
		gpioPinDirection(BTN_2_GPIO, BTN_2_BIT, OUTPUT);
		break;
	case BTN_3:
		gpioPinDirection(BTN_3_GPIO, BTN_3_BIT, OUTPUT);
		break;
	default:
		break;
	}

}
*/
/**
 * Description: read all BTN_x (where x 0, 1, 2, 3) states and store it in the program
 *
 * @note : this function must be called in the system tick hundler or in the super loop hundler
 */
/*
void pushButton_Update(void)
{
	for(int i = 0; i < BTN_MAX_NUM; i++)
	{
		switch(avrbuttons[i].En_buttonId)
			{
			case BTN_0:
				if(gpioPinRead(BTN_0_GPIO, BTN_0_BIT))
				{

				}
				break;
			case BTN_1:
				gpioPinDirection(BTN_1_GPIO, BTN_1_BIT, OUTPUT);
				break;
			case BTN_2:
				gpioPinDirection(BTN_2_GPIO, BTN_2_BIT, OUTPUT);
				break;
			case BTN_3:
				gpioPinDirection(BTN_3_GPIO, BTN_3_BIT, OUTPUT);
				break;
			default:
				break;
			}
	}

}
*/
/**
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 */
/*
En_buttonStatus_t pushButton_GetStatus(En_buttonId btn_id)
{

}
*/

