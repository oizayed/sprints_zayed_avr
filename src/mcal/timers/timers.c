/*
 * timers.c
 *
 *  Created on: Dec 8, 2019
 *      Author: Omar Zayed
 */

#define Timer0_Mode_CLR_Mask			0b10110111
#define Timer0_OCM_CLR_Mask				0b11001111
#define Timer0_PRESC_CLR_Mask			0b11111000
#define Timer0_Int_CLR_Mask				0b11111100
#define Timer0_Delay_Begin_Value		0b00000000
#define Timer0_Delay_End_Value			0b11111010
#define Timer0_PWM_End_Value			0b11001000

#define Timer1_Mode_CLR_Mask			0b1111111111100111
#define Timer1_OCM_CLR_Mask				0b0000111111111111
#define Timer1_PRESC_CLR_Mask			0b1111111111111000
#define Timer1_Int_CLR_Mask				0b11000011
#define Timer1_Delay_Begin_Value		0b0000000000000000
#define Timer1_Delay_End_Value			0b0000000011111010

#define Timer2_Mode_CLR_Mask			0b10110111
#define Timer2_OCM_CLR_Mask				0b11001111
#define Timer2_PRESC_CLR_Mask			0b11111000
#define Timer2_Int_CLR_Mask				0b00111111
#define Timer2_Delay_Begin_Value		0b00000000
#define Timer2_Delay_End_us				0b00011001
#define Timer2_Delay_End_Value			0b11111010



#include "timers.h"

En_timer0perscaler_t Timer0Prescaler;
En_timer1perscaler_t Timer1Prescaler;
En_timer2perscaler_t Timer2Prescaler;

uint8 T1DC;
uint8 T2DC;



/*===========================Timer0 Control===============================*/
/**
 * Description: Initiates the timer with the required working values by setting the TCCR, OCR and TIMSK registers.
 * @param control : the output compare mode and takes the following values :
 * 					T0_OC0_DIS=0
 * 					T0_OC0_TOGGLE=0x10
 * 					T0_OC0_CLEAR=0x20
 * 					T0_OC0_SET=0x30
 * @param initialValue : the beginning value of the timer.
 * @param outputCompare : the value which the timer will compare at.
 * @param interruptMask : the interrupt mode and takes the following values :
 * 							T0_POLLING=0
 * 							T0_INTERRUPT_NORMAL=0x01
 * 							T0_INTERRUPT_CMP=0x02
 */
void timer0Init(En_timer0Mode_t mode,En_timer0OC_t OC0,En_timer0perscaler_t prescal, uint8 initialValue, uint8 outputCompare, En_timer0Interrupt_t interruptMask)
{

	// First Setting the Mode

	TCCR0 &= Timer0_Mode_CLR_Mask;
	TCCR0 |= mode;

	// Then Setting the Output Compare Mode

	TCCR0 &= Timer0_OCM_CLR_Mask;
	TCCR0 |= OC0;

	// Setting the Prescaler

	Timer0Prescaler = prescal;

	// Setting the Initial Value

	TCNT0 = initialValue;

	// Setting the Compare Value

	OCR0 = outputCompare;

	// Setting Interrupt

	TIMSK &= Timer0_Int_CLR_Mask;
	TIMSK |= interruptMask;


}

/**
 * Description: sets the beginning value of the timer to the TCNT register.
 * @param value : the beginning value.
 */
void timer0Set(uint8 value)
{
	TCNT0 = value;
}

/**
 * Description: reads the TCNT register.
 * @return : the value of the timer.
 */
uint8 timer0Read(void)
{
	return TCNT0;
}

/**
 * Description: assigns the prescaler to the TCCR which makes the timer start working
 */
void timer0Start(void)
{
	TCCR0 &= Timer0_PRESC_CLR_Mask;
	TCCR0 |= Timer0Prescaler;
}

/**
 * Description: clears the prescaler part in the TCCR which makes the timer stop working
 */
void timer0Stop(void)
{
	TCCR0 &= Timer0_PRESC_CLR_Mask;
}

/**
 * Description: a function to make delay in the code.
 * @param delay : the time of the delay required.
 */
void timer0Delay_ms(uint16 delay)
{
	timer0Init(T0_COMP_MODE, T0_OC0_DIS, T0_PRESCALER_64, Timer0_Delay_Begin_Value, Timer0_Delay_End_Value, T0_POLLING);
	timer0Start();
	while(delay)
	{
		while(!(GET_BIT(TIFR,BIT1)))
		{

		}
		SET_BIT(TIFR,BIT1);
		timer0Set(Timer0_Delay_Begin_Value);
		delay--;
	}
}

/**
 * Description: this function forms the required PWM output.
 * @param dutyCycle : a uint8 number which shows the time-on relative to the total time of the PWM
 * @param freq : a uint8 number (range between 5 to 255) which will lead to 500Hz if 5 and 145Hz if 255
 */
void timer0SwPWM(uint8 dutyCycle,uint8 freq)
{
	float DC = dutyCycle / 255.00;
	gpioPinWrite(GPIOB, BIT4, HIGH);
	timer0Delay_ms(DC * 10);
	gpioPinWrite(GPIOB, BIT4, LOW);
	timer0Delay_ms((1.00 - DC) * 10);
}



/*===========================Timer1 Control===============================*/
/**
 * Description:
 * @param controlA
 * @param controlB
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void timer1Init(En_timer1Mode_t mode,En_timer1OC_t OC1,En_timer1perscaler_t prescal, uint16 initialValue, uint16 outputCompareA, uint16 outputCompareB,uint16 inputCapture, En_timer1Interrupt_t interruptMask)
{
	// First Setting the Mode

	TCCR1 &= Timer1_Mode_CLR_Mask;
	TCCR1 |= mode;

	// Then Setting the Output Compare Mode

	TCCR1 &= Timer1_OCM_CLR_Mask;
	TCCR1 |= OC1;

	// Setting the Prescaler

	Timer1Prescaler = prescal;

	// Setting the Initial Value

	TCNT1 = initialValue;

	// Setting the Compare Value A

	OCR1A = outputCompareA;

	// Setting the Compare Value B

	OCR1B = outputCompareB;

	// Setting Input Capture

	ICR1 = inputCapture;

	// Setting Interrupt

	TIMSK &= Timer1_Int_CLR_Mask;
	TIMSK |= interruptMask;

}

/**
 * Description:
 * @param value
 */
void timer1Set(uint16 value)
{
	TCNT1 = value;
}


/**
 * Description:
 * @return
 */
uint16 timer1Read(void)
{
	return TCNT1;
}


/**
 * Description:
 */
void timer1Start(void){

	TCCR1 &= Timer1_PRESC_CLR_Mask;
	TCCR1 |= Timer1Prescaler;

}
/**
 * Description:
 */
void timer1Stop(void)
{
	TCCR1 &= Timer1_PRESC_CLR_Mask;
}

/**
 * Description:
 * @param delay
 */
void timer1Delay_ms(uint16 delay)
{
	timer1Init(T1_COMP_MODE_ICR1_TOP, T1_OC0_DIS, T1_PRESCALER_64, Timer1_Delay_Begin_Value, Timer1_Delay_Begin_Value, Timer1_Delay_Begin_Value, Timer1_Delay_End_Value, T1_POLLING);
	timer1Start();
	while(delay)
	{
		while(!(GET_BIT(TIFR,BIT5)))
		{

		}
		SET_BIT(TIFR,BIT5);
		timer1Set(Timer1_Delay_Begin_Value);
		delay--;
	}
}

/**
 * Description:
 * @param dutyCycle
 */
void timer1SwPWM(uint8 dutyCycle,uint8 freq)
{
	float DC = dutyCycle / 255.00;
	gpioPinWrite(GPIOB, BIT4, HIGH);
	timer1Delay_ms(DC * 10);
	gpioPinWrite(GPIOB, BIT4, LOW);
	timer1Delay_ms((1.00 - DC) * 10);

}




/*===========================Timer2 Control===============================*/
/**
 * Description:
 * @param control
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void timer2Init(En_timer2Mode_t mode,En_timer2OC_t OC2,En_timer2perscaler_t prescal, uint8 initialValue, uint8 outputCompare, uint8 assynchronous, En_timer2Interrupt_t interruptMask)
{
	// First Setting the Mode

	TCCR2 &= Timer2_Mode_CLR_Mask;
	TCCR2 |= mode;

	// Then Setting the Output Compare Mode

	TCCR2 &= Timer2_OCM_CLR_Mask;
	TCCR2 |= OC2;

	// Setting the Prescaler

	Timer2Prescaler = prescal;

	// Setting the Initial Value

	TCNT2 = initialValue;

	// Setting the Compare Value

	OCR2 = outputCompare;

	// Setting Interrupt

	TIMSK &= Timer2_Int_CLR_Mask;
	TIMSK |= interruptMask;


}
/**
 * Description:
 * @param value
 */
void timer2Set(uint8 value)
{
	TCNT2 = value;
}

/**
 * Description:
 * @return
 */
uint8 timer2Read(void)
{
	return TCNT2;
}

/**
 * Description:
 */
void timer2Start(void)
{
	TCCR2 &= Timer2_PRESC_CLR_Mask;
	TCCR2 |= Timer2Prescaler;
}

/**
 * Description:
 */
void timer2Stop(void)
{
	TCCR2 &= Timer2_PRESC_CLR_Mask;
}

/**
 * Description:
 * @param delay
 */
void timer2Delay_ms(uint16 delay)
{
	timer2Init(T2_COMP_MODE, T2_OC0_DIS, T2_PRESCALER_64, Timer2_Delay_Begin_Value, Timer2_Delay_End_Value, Timer2_Delay_Begin_Value, T2_POLLING);
	timer2Start();
	while(delay)
	{
		while(!(GET_BIT(TIFR,BIT7)))
		{

		}
		SET_BIT(TIFR,BIT7);
		timer2Set(Timer2_Delay_Begin_Value);
		delay--;
	}

}

/**
 * Description:
 * @param dutyCycle
 */
void timer2SwPWM(uint8 dutyCycle,uint8 freq)
{
	float DC = dutyCycle / 255.00;
	gpioPinWrite(GPIOB, BIT4, HIGH);
	timer2Delay_ms(DC * 10);
	gpioPinWrite(GPIOB, BIT4, LOW);
	timer2Delay_ms((1.00 - DC) * 10);

}

/*
 * user defined
 * This is delay 100us
 */
void timer2Delay_us(uint32 delay)
{
	timer2Init(T2_COMP_MODE, T2_OC0_DIS, T2_PRESCALER_64, Timer2_Delay_Begin_Value, Timer2_Delay_End_us, Timer2_Delay_Begin_Value, T2_POLLING);
	timer2Start();
	while(delay)
	{
		timer2Set(Timer2_Delay_Begin_Value);
		while(!(GET_BIT(TIFR,BIT7)))
		{

		}
		SET_BIT(TIFR,BIT7);
		delay--;
	}
}












