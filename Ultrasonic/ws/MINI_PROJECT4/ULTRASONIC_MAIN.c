/*
 * ULTRASONIC_MAIN.c
 *
 *  Created on: Oct 18, 2023
 *      Author: Ahmedmohamed
 */
#include "LCD.h"
#include "ULTRASONIC.h"
#include <avr/io.h>
int main()
{
	uint16 distance=0;
	SREG |= (1<<7);
	Ultrasonic_init();
	LCD_INIT();
	LCD_MoveCursor(0,4);
	LCD_Displaystring("UT sensor");
	LCD_MoveCursor(2,0);
	LCD_Displaystring("distance =    cm");
	while(1)
	{
		LCD_MoveCursor(2,11);

			distance = Ultrasonic_readDistance();
			if(distance>=100)
			{
				LCD_IntegerToString(distance);
			}
			else
			{
				LCD_IntegerToString(distance);
				LCD_DisplayCharacter(' ');
			}
	}

}

