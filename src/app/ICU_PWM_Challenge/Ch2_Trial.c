/*
 * Ch2_Trial.c
 *
 *  Created on: Dec 17, 2019
 *      Author: Omar Zayed
 */

#include "../../firmware/MotorDC/MotorDC.h"
#include "../../firmware/led/led.h"
#include "../../mcal/SwICU/SwICU.h"
#include "../../mcal/gpio/gpio.h"
#include <avr/delay.h>
#include "../../firmware/lcd/char_lcd.h"
/*
uint32 T0counter = 0;
uint16 CMdistance = 0;
uint8 LedsBits = 0;
uint8 seq = 0;
char str[5];
*/
void Ch2_Trial(void)
{
	gpioPinDirection(GPIOB, BIT1, OUTPUT); 	//Trigger
	gpioPinDirection(GPIOB, BIT2, INPUT);	//Echo

	timer0Init(T0_COMP_MODE, T0_OC0_DIS, T0_PRESCALER_64, 0, 250, T0_INTERRUPT_CMP);
	timer0Start();
	Led_Init(LED_0);

	MotorDC_Init(MOT_1);
	MotorDC_Init(MOT_2);
	//LCD_init();

	SwICU_Init(SwICU_EdgeRisiging);
	SwICU_Enable();

	sei();

	while(1)
	{
		Led_On(LED_0);
	}

}

