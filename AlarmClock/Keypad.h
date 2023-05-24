/*
 * Keypad.h
 *
 * Created: 4/10/2023 11:55:27 PM
 *  Author: haahm
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "BIT_MATH.h"
#include "ATmega32_Rrgiosters.h"
#include <util/delay.h>
#define INVALID_KEYPAD_PRESS (0xFF)
const unsigned char arr[4][4]={{0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15}};
								
void keypad_init()
{
	CLR_BIT(DDRD,7);
	CLR_BIT(DDRD,6);
	CLR_BIT(DDRD,5);
	CLR_BIT(DDRD,3);
	
	SET_BIT(DDRC,5);
	SET_BIT(DDRC,4);
	SET_BIT(DDRC,3);
	SET_BIT(DDRC,2);
	
	SET_BIT(PORTD,7);
	SET_BIT(PORTD,6);
	SET_BIT(PORTD,5);
	SET_BIT(PORTD,3);
	
}

unsigned char keypad_Get_Value(void)
{
	unsigned char col,row,ans = INVALID_KEYPAD_PRESS;
	char key = 0;
	for(row=5;row>=2;row--)
	{
		PORTC |= 0b00111100;
		CLR_BIT(PORTC,row);
		for(col = 7;col>=3;col--)
		{
			if(col == 4)
			{
				col--;
			}
			if(GET_BIT(PIND,col)==0)
			{
				_delay_ms(120);
				if(GET_BIT(PIND,col)==0)
				{
					if(col == 3)
					{
						ans = arr[5-row][7-col-1];
						break;
					}
					else
					{
						ans = arr[5-row][7-col];
					}
				}
			}

		}
		
	}
	if(ans==0){
		key = '7';
	}
	else if(ans == 1){
		key = '8';
	}
	else if(ans == 2){
		key = '9';
	}
	else if(ans == 3){
		key = '/';
	}
	else if(ans == 4){
		key = '4';
	}
	else if(ans == 5){
		key = '5';
	}
	else if(ans == 6){
		key = '6';
	}
	else if(ans == 7){
		key = '*';
	}
	else if(ans == 8){
		key = '1';
	}
	else if(ans == 9){
		key = '2';
	}
	else if(ans == 10){
		key = '3';
	}
	else if(ans == 11){
		key = '-';
	}
	else if(ans == 12){
		key = 'C';
	}
	else if(ans == 13){
		key = '0';
	}
	else if(ans == 14){
		key = '=';
	}
	else if(ans == 15){
		key = '+';
	}
	return key;
}


#endif /* KEYPAD_H_ */