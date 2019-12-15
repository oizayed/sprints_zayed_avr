/*
 * SwICU.h
 *
 *  Created on: Oct 27, 2019
 *      Author: Sprints
 */

#ifndef SWICU_H_
#define SWICU_H_

#include "../../utils/interrupts.h"
#include "../timers/timers.h"
#include "../registers.h"

typedef enum {
	SwICU_EdgeFalling = 2,
	SwICU_EdgeRisiging = 3
}SwICU_Edge_TypeDef;

void SwICU_Init(SwICU_Edge_TypeDef inputCaptureEdge);
SwICU_Edge_TypeDef SwICU_GetCfgEdge(void);
void SwICU_SetCfgEdge(SwICU_Edge_TypeDef edge);
void SwICU_Read(volatile uint8 * capt);
void SwICU_Stop(void);
void SwICU_Start(void);
void SwICU_Enable(void);
void SwICU_Disable(void);

#endif /* SWICU_H_ */
