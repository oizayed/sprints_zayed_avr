/*
 * SwICU.c
 *
 *  Created on: Dec 15, 2019
 *      Author: Omar Zayed
 */


#include "SwICU.h"

uint32 T2_counter = 0;

void SwICU_Init(SwICU_Edge_TypeDef inputCaptureEdge)
{
	// INT2
	if(inputCaptureEdge == SwICU_EdgeFalling)
	{
		CLR_BIT(MCUCSR, BIT6);
	}
	else if(inputCaptureEdge == SwICU_EdgeRisiging)
	{
		SET_BIT(MCUCSR, BIT6);
	}
	timer2Init(T2_NORMAL_MODE, T2_OC0_DIS, T2_PRESCALER_8, 0, 0, 0, T2_INTERRUPT_NORMAL);
}



SwICU_Edge_TypeDef SwICU_GetCfgEdge(void)
{
	if(GET_BIT(MCUCSR, BIT6))
	{
		return SwICU_EdgeRisiging;
	}

	return SwICU_EdgeFalling;

}



void SwICU_SetCfgEdge(SwICU_Edge_TypeDef edge)
{
	if(edge == SwICU_EdgeFalling)
	{
		CLR_BIT(MCUCSR, BIT6);
	}
	else if(edge == SwICU_EdgeRisiging)
	{
		SET_BIT(MCUCSR, BIT6);
	}
}



void SwICU_Read(volatile uint8 * capt)
{
	*capt = T2_counter;
}


void SwICU_Stop(void)
{
	timer2Stop();
}



void SwICU_Start(void)
{
	timer2Start();
	T2_counter = 0;
}



void SwICU_Enable(void)
{
	SET_BIT(GICR, BIT5);
}



void SwICU_Disable(void)
{
	CLR_BIT(GICR, BIT5);
}



ISR(TIMER2_OVF_vect)
{
	T2_counter++;
}
