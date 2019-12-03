/*
 * softwareDelay.c
 *
 *  Created on: Dec 3, 2019
 *      Author: Omar Zayed
 */

#include "softwareDelay.h"

void SwDelay_ms(uint32 n)
{
	sint16 x = n / 1000;
	n = n / x;
	for(sint16 k = 0; k < x; k++)
	{
		for(sint16 i = 0; i < 3; i++)
		{
			for(sint16 j = 0; j < (n * 1000); j++)
			{

			}

		}
	}

}


