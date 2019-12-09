/*
 * REQ1311.c
 *
 *  Created on: Dec 9, 2019
 *      Author: Omar Zayed
 */




#include "../../mcal/gpio/gpio.h"
#include "../../firmware/led/led.h"
#include "../../mcal/timers/timers.h"
#include "../../utils/interrupts.h"

uint32 counter = 0;

void REQ1311(void)
{
	Led_Init(LED_0);
	timer0Init(T0_COMP_MODE, T0_OC0_DIS, T0_PRESCALER_64, 0b00000000, 0b11111010, T0_INTERRUPT_CMP);
	sei();
	timer0Start();
	Led_Toggle(LED_0);
	while (1)
	{

	}
}

ISR(TIMER0_COMP_vect)
{
	timer0Set(0);
	counter++;
	if(counter == 1000)
	{
		Led_Toggle(LED_0);
		counter = 0;

	}
	sei();
}
