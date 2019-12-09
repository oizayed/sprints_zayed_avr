/*
 * app1.c
 *
 *  Created on: Dec 3, 2019
 *      Author: Omar Zayed
 */

#include "../../mcal/gpio/gpio.h"
#include "../../firmware/led/led.h"
#include "../../utils/softwareDelay/softwareDelay.h"
#include "../../utils/std_types.h"

void app1(void)
{
	gpioPortDirection(GPIOB, OUTPUT);
	gpioPortDirection(GPIOC, INPUT);




	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);



	while(1)
	{

		Led_On(LED_0);
		Led_On(LED_1);
		Led_Toggle(LED_2);
		Led_Toggle(LED_3);
		gpioPinWrite(GPIOB,BIT3,HIGH);



		SwDelay_ms(5000);

		Led_Off(LED_0);
		Led_Off(LED_1);
		Led_Toggle(LED_2);
		Led_Toggle(LED_3);
		gpioPinWrite(GPIOB,BIT3,LOW);




		SwDelay_ms(5000);


		gpioPortToggle(GPIOB);


		SwDelay_ms(1000);


		gpioPortToggle(GPIOB);


		SwDelay_ms(1000);


		gpioPortWrite(GPIOB, HIGH);


		SwDelay_ms(1000);


		gpioPortWrite(GPIOB, LOW);


		SwDelay_ms(1000);


	}
}


