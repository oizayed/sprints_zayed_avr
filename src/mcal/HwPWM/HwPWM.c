/*
 * HwPWM.c
 *
 *  Created on: Dec 16, 2019
 *      Author: Omar Zayed
 */
#define Timer1_CLR_Mask					0b0000000000000000
#define Timer1_COM_Mask					0b1111000000000000
#define Timer1_WGN_Mask					0b0000000000010000
#define Timer1_PRE_Mask					T1_PRESCALER_NO

#include "HwPWM.h"

void HwPWM_Init(void)
{
	// clear the TCCR1 Regs

	TCCR1 &= Timer1_CLR_Mask;

	// First Setting if inverting or non-inverting

	TCCR1 |= Timer1_COM_Mask;

	// Then Setting the Mode

	TCCR1 |= Timer1_WGN_Mask;

	// Setting the Prescaler

	TCCR1 |= Timer1_PRE_Mask;

	// Setting the Initial Value

	TCNT1 = 0;

	// Setting the Compare Value A

	OCR1A = 0;

	// Setting the Compare Value B

	OCR1B = 0;

	// Setting Input Capture

	ICR1 = 0xFFFF;


}


void HwPWM_ChangeWidth(uint8 duty, uint32 frequency)
{
	ICR1 = 8000000 / frequency;
	OCR1A = duty * 80000 / frequency;
}
