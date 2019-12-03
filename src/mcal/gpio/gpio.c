/*
 * gpio.c
 *
 *  Created on: Dec 3, 2019
 *      Author: Omar Zayed
 */

#include "gpio.h"
#include "../registers.h"

/*===========================PORT Control===============================*/
/**
 * Description: set port direction (which is DDR register)
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 * @param direction: set the port direction and takes the following values
 * 				- 0x00 -> Input
 * 				- 0xff -> Output
 */
void gpioPortDirection(uint8 port, uint8 direction)
{
	switch(port)
	{
	case GPIOA :
		PORTA_DIR = direction;
		break;
	case GPIOB :
		PORTB_DIR = direction;
		break;
	case GPIOC :
		PORTC_DIR = direction;
		break;
	case GPIOD :
		PORTD_DIR = direction;
		break;
	default : // Handle this case
		break;
	}
}

/**
 * Description: set the port value (which is PORT register)
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param value: set the port value and takes the following values
 * 				- 0x00 -> Low
 * 				- 0xff -> High
 */
void gpioPortWrite(uint8 port, uint8 value)
{
	switch(port)
	{
	case GPIOA :
		PORTA_DATA = value;
		break;
	case GPIOB :
		PORTB_DATA = value;
		break;
	case GPIOC :
		PORTC_DATA = value;
		break;
	case GPIOD :
		PORTD_DATA = value;
		break;
	default : // Handle this case
		break;
	}
}

/**
 * Description: toggle the port value (which is PORT register)
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 */
void gpioPortToggle(uint8 port)
{
	switch(port)
	{
	case GPIOA :
		PORTA_DATA = ~PORTA_DATA;
		break;
	case GPIOB :
		PORTB_DATA = ~PORTB_DATA;
		break;
	case GPIOC :
		PORTC_DATA = ~PORTC_DATA;
		break;
	case GPIOD :
		PORTD_DATA = ~PORTD_DATA;
		break;
	default : // Handle this case
		break;
	}
}

/**
 * Description: read the current port value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @return
 */
uint8 gpioPortRead(uint8 port)
{
	uint8 out;
	switch(port)
	{
	case GPIOA :
		out = PORTA_PIN;
		break;
	case GPIOB :
		out = PORTB_PIN;
		break;
	case GPIOC :
		out = PORTC_PIN;
		break;
	case GPIOD :
		out = PORTD_PIN;
		break;
	default : // Handle this case
		break;
	}
	return out;
}

/*===========================PIN Control===============================*/
/**
 * Description: set selected pins (more than one pin [ORed]) direction
 *
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pins the user need to set its direction and takes
 * 				any member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 *
 * @param direction: set the pins direction and takes the following values
 * 				- 0x00 -> Input
 * 				- 0xff -> Output
 */
void gpioPinDirection(uint8 port, uint8 pins, uint8 direction)
{
	switch(port)
	{
	case GPIOA :
		ASSIGN_BIT(PORTA_DIR, pins, direction);
		break;
	case GPIOB :
		ASSIGN_BIT(PORTB_DIR, pins, direction);
		break;
	case GPIOC :
		ASSIGN_BIT(PORTC_DIR, pins, direction);
		break;
	case GPIOD :
		ASSIGN_BIT(PORTD_DIR, pins, direction);
		break;
	default : // Handle this case
		break;
	}


}

/**
 * Description: set selected pins (more than one pin [ORed]) values
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pins the user need to write its values and takes
 * 				any member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 * @param value
 */
void gpioPinWrite(uint8 port, uint8 pins, uint8 value)
{
	switch(port)
	{
	case GPIOA :
		ASSIGN_BIT(PORTA_DATA, pins, value);
		break;
	case GPIOB :
		ASSIGN_BIT(PORTB_DATA, pins, value);
		break;
	case GPIOC :
		ASSIGN_BIT(PORTC_DATA, pins, value);
		break;
	case GPIOD :
		ASSIGN_BIT(PORTD_DATA, pins, value);
		break;
	default : // Handle this case
		break;
	}
}

/**
 * Description: toggle selected pin (only one pin) direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pin the user need to toggle it's value and takes
 * 				only one member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 */
void gpioPinToggle(uint8 port, uint8 pins)
{

	switch(port)
	{
	case GPIOA :
		TOGGLE_BIT(PORTA_DATA, pins);
		break;
	case GPIOB :
		TOGGLE_BIT(PORTB_DATA, pins);
		break;
	case GPIOC :
		TOGGLE_BIT(PORTC_DATA, pins);
		break;
	case GPIOD :
		TOGGLE_BIT(PORTD_DATA, pins);
		break;
	default : // Handle this case
		break;
	}
}

/**
 * Description: read selected pin (only one pin) direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 * @param pin: the selected pin the user need to read it's value and takes
 * 				only one member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 * @return
 */
uint8 gpioPinRead(uint8 port, uint8 pin)
{
	uint8 out;
	switch(port)
	{
	case GPIOA :
		out = GET_BIT(PORTA_PIN, pin);
		break;
	case GPIOB :
		out = GET_BIT(PORTB_PIN, pin);
		break;
	case GPIOC :
		out = GET_BIT(PORTC_PIN, pin);
		break;
	case GPIOD :
		out = GET_BIT(PORTD_PIN, pin);
		break;
	default : // Handle this case
		break;
	}
	return out;
}

/*===========================Upper Nibble Control===============================*/
/**
 * Description: set the upper nibble direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param direction
 */
void gpioUpperNibbleDirection(uint8 port, uint8 direction)
{
	direction &= 0b11110000;
	switch(port)
	{
	case GPIOA :
		PORTA_DIR &= 0b00001111;
		PORTA_DIR |= direction;
		break;
	case GPIOB :
		PORTB_DIR &= 0b00001111;
		PORTB_DIR |= direction;
		break;
	case GPIOC :
		PORTC_DIR &= 0b00001111;
		PORTC_DIR |= direction;
		break;
	case GPIOD :
		PORTD_DIR &= 0b00001111;
		PORTD_DIR |= direction;
		break;
	default : // Handle this case
		break;
	}

}

/**
 * Description: write the upper nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param value
 */
void gpioUpperNibbleWrite(uint8 port, uint8 value)
{
	value &= 0b11110000;
	switch(port)
	{
	case GPIOA :
		PORTA_DATA &= 0b00001111;
		PORTA_DATA |= value;
		break;
	case GPIOB :
		PORTB_DATA &= 0b00001111;
		PORTB_DATA |= value;
		break;
	case GPIOC :
		PORTC_DATA &= 0b00001111;
		PORTC_DATA |= value;
		break;
	case GPIOD :
		PORTD_DATA &= 0b00001111;
		PORTD_DATA |= value;
		break;
	default : // Handle this case
		break;
	}

}

/**
 * Description: toggle the upper nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 */
void gpioUpperNibbleToggle(uint8 port)
{
	switch(port)
	{
	case GPIOA :
		TOGGLE_BIT(PORTA_DATA,BIT7);
		TOGGLE_BIT(PORTA_DATA,BIT6);
		TOGGLE_BIT(PORTA_DATA,BIT5);
		TOGGLE_BIT(PORTA_DATA,BIT4);
		break;
	case GPIOB :
		TOGGLE_BIT(PORTB_DATA,BIT7);
		TOGGLE_BIT(PORTB_DATA,BIT6);
		TOGGLE_BIT(PORTB_DATA,BIT5);
		TOGGLE_BIT(PORTB_DATA,BIT4);
		break;
	case GPIOC :
		TOGGLE_BIT(PORTC_DATA,BIT7);
		TOGGLE_BIT(PORTC_DATA,BIT6);
		TOGGLE_BIT(PORTC_DATA,BIT5);
		TOGGLE_BIT(PORTC_DATA,BIT4);
		break;
	case GPIOD :
		TOGGLE_BIT(PORTD_DATA,BIT7);
		TOGGLE_BIT(PORTD_DATA,BIT6);
		TOGGLE_BIT(PORTD_DATA,BIT5);
		TOGGLE_BIT(PORTD_DATA,BIT4);
		break;
	default : // Handle this case
		break;
	}

}

/**
 * Description: read the upper nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @return
 */
uint8 gpioUpperNibbleRead(uint8 port)
{
	uint8 out;
	switch(port)
	{
	case GPIOA :
		out = PORTA_PIN & 0b11110000;
		break;
	case GPIOB :
		out = PORTB_PIN & 0b11110000;
		break;
	case GPIOC :
		out = PORTC_PIN & 0b11110000;
		break;
	case GPIOD :
		out = PORTD_PIN & 0b11110000;
		break;
	default : // Handle this case
		break;
	}
	return out;

}

/*===========================Lower Nibble Control===============================*/
/**
 * Description: set the lower nibble direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 * @param direction
 */
void gpioLowerNibbleDirection(uint8 port, uint8 direction)
{
	direction &= 0b00001111;
	switch(port)
	{
	case GPIOA :
		PORTA_DIR &= 0b11110000;
		PORTA_DIR |= direction;
		break;
	case GPIOB :
		PORTB_DIR &= 0b11110000;
		PORTB_DIR |= direction;
		break;
	case GPIOC :
		PORTC_DIR &= 0b11110000;
		PORTC_DIR |= direction;
		break;
	case GPIOD :
		PORTD_DIR &= 0b11110000;
		PORTD_DIR |= direction;
		break;
	default : // Handle this case
		break;
	}

}

/**
 * Description: write the lower nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param value
 */
void gpioLowerNibbleWrite(uint8 port, uint8 value)
{
	value &= 0b00001111;
	switch(port)
	{
	case GPIOA :
		PORTA_DATA &= 0b11110000;
		PORTA_DATA |= value;
		break;
	case GPIOB :
		PORTB_DATA &= 0b11110000;
		PORTB_DATA |= value;
		break;
	case GPIOC :
		PORTC_DATA &= 0b11110000;
		PORTC_DATA |= value;
		break;
	case GPIOD :
		PORTD_DATA &= 0b11110000;
		PORTD_DATA |= value;
		break;
	default : // Handle this case
		break;
	}

}

/**
 * Description: toggle the lower nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 */
void gpioLowerNibbleToggle(uint8 port)
{
	switch(port)
	{
	case GPIOA :
		TOGGLE_BIT(PORTA_DATA,BIT3);
		TOGGLE_BIT(PORTA_DATA,BIT2);
		TOGGLE_BIT(PORTA_DATA,BIT1);
		TOGGLE_BIT(PORTA_DATA,BIT0);
		break;
	case GPIOB :
		TOGGLE_BIT(PORTB_DATA,BIT3);
		TOGGLE_BIT(PORTB_DATA,BIT2);
		TOGGLE_BIT(PORTB_DATA,BIT1);
		TOGGLE_BIT(PORTB_DATA,BIT0);
		break;
	case GPIOC :
		TOGGLE_BIT(PORTC_DATA,BIT3);
		TOGGLE_BIT(PORTC_DATA,BIT2);
		TOGGLE_BIT(PORTC_DATA,BIT1);
		TOGGLE_BIT(PORTC_DATA,BIT0);
		break;
	case GPIOD :
		TOGGLE_BIT(PORTD_DATA,BIT3);
		TOGGLE_BIT(PORTD_DATA,BIT2);
		TOGGLE_BIT(PORTD_DATA,BIT1);
		TOGGLE_BIT(PORTD_DATA,BIT0);
		break;
	default : // Handle this case
		break;
	}

}

/**
 * Description: read the lower nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @return
 */
uint8 gpioLowerNibbleRead(uint8 port)
{
	uint8 out;
	switch(port)
	{
	case GPIOA :
		out = PORTA_PIN & 0b00001111;
		break;
	case GPIOB :
		out = PORTB_PIN & 0b00001111;
		break;
	case GPIOC :
		out = PORTC_PIN & 0b00001111;
		break;
	case GPIOD :
		out = PORTD_PIN & 0b00001111;
		break;
	default : // Handle this case
	break;
	}
	return out;


}


