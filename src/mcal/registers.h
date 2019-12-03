/*
 * registers.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_
#include "std_types.h"

/*
 * General Registers
 */
#define MCUCR		
#define MCUCSR		
#define GICR		
#define GIFR		

/*
 * PORTx registers
 */

#define PORTA_DATA 	
#define PORTA_DIR  	
#define PORTA_PIN	

#define PORTB_DATA 	
#define PORTB_DIR  	
#define PORTB_PIN	

#define PORTC_DATA 	
#define PORTC_DIR  	
#define PORTC_PIN	


#define PORTD_DATA 	
#define PORTD_DIR  	
#define PORTD_PIN	


/*
 * General Timer registers
 */
#define TIMSK		
#define TIFR		


/*
 * Timer 0 Registers
 */

#define TCCR0		
#define TCNT0		
#define OCR0		


/*
 * Timer 1 Registers
 */

#define TCCR1A		
#define TCCR1B		
#define TCCR1		
#define TCNT1H		
#define TCNT1L		
#define TCNT1		
#define OCR1AH		
#define OCR1AL		
#define OCR1A		
#define OCR1BH		
#define OCR1BL		
#define OCR1B		
#define ICR1H		
#define ICR1L		
#define ICR1		


/*
 * Timer 2 Registers
 */
#define TCCR2		
#define TCNT2		
#define OCR2		








#endif /* REGISTERS_H_ */
