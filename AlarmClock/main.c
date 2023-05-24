/*
 * AlarmClock.c
 *
 * Created: 5/15/2023 4:14:04 PM
 * Author : haahm
 */ 

#include <avr/io.h>
#include "Keypad.h"
#include "LCD.h"
#include "std_types.h"
int main(void)
{
	LCD_Init();
	keypad_init();
	
    while (1) 
    {
		uint8 key;
		key = keypad_Get_Value();
		LCD_Char(key);
    }
}

