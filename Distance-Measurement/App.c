/*
 * App.c
 *
 *  Created on: Jul 13, 2024
 *      Author: DELL
 */

#include "lcd.h"
#include "ultrasonic.h"
#include <util/delay.h>
int main(void)
{
	uint16 distance = 0;
	LCD_init();

	Ultrasonic_init();
	LCD_displayString("Distance = ");
    while(1)
    {

    	distance = Ultrasonic_readDistance();
    	LCD_moveCursor(0, 11);
    	LCD_intgerToString(distance);
    	LCD_displayString("cm ");
    	_delay_ms(10);


    }
}

