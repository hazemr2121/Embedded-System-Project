/*
 * Clock.h
 *
 * Created: 5/26/2023 11:59:02 PM
 *  Author: haahm
 */ 


#ifndef CLOCK_H_
#define CLOCK_H_

#include <avr/interrupt.h>
#include "LCD.h"
#include "Keypad.h"
#include "std_types.h"
#define NUMER_OF_OVERFLOWS 62
#define I_BIT (7)
uint8 is_alarm_on = 0;
int hours = 0;   // Global variables to store the time
int minutes = 0;
int seconds = 0;
int is_pm = 0;
uint8 timeStr[9];
int A_hours = 0;
int A_minutes = 0;
int A_seconds = 0;
int A_is_pm = 0;
uint8 A_TimeStr[9];

    // Array to hold the formatted time string

void (*g_callbackPtr)(void) = NULL_PTR;





ISR(TIMER0_OVF_vect)
{
	if(g_callbackPtr != NULL_PTR)
	{
		(*g_callbackPtr)();
	}
}
void timer0_callbackPtr(void(*a_ptr)(void)){
	g_callbackPtr = a_ptr;
}
void timer0_init(void)
{
	TCNT0 = 0;
	SET_BIT(TIMSK,TOIE0);
	TCCR0 = (1 << FOC0) | (1 << CS02) | (1<<CS00);
	SET_BIT(SREG,I_BIT);
}

void displayTime() {
	sprintf(timeStr, "%02d:%02d:%02d", hours, minutes, seconds);
	
	LCD_goToRowColumn(0, 0);  // Set the cursor position on the LCD
	LCD_string(timeStr); // Display the time string
	LCD_string(is_pm ? "PM" : "AM"); // Display PM/AM indicator
	LCD_goToRowColumn(1,0);
	LCD_string("Alarm: ");
	LCD_goToRowColumn(2,0);
	sprintf(A_TimeStr, "%02d:%02d:%02d", A_hours, A_minutes, A_seconds);
	LCD_string(A_TimeStr);
	LCD_string(A_is_pm ? "PM" : "AM"); // Display PM/AM indicator
	
	
}


adjustingTime(){
	clear();
	LCD_string("Adjust Time:");
	LCD_goToRowColumn(1,0);
	LCD_string("Time: ");
	uint8 key = INVALID_KEYPAD_PRESS;
	uint8 index = 0;
	while(1)
	{
		key = keypad_Get_Value();
		if(key != INVALID_KEYPAD_PRESS)
		{
			if(key != INVALID_KEYPAD_PRESS)
			{
				if(key >= '0' && key <= '9')
				{
					if(index == 2 || index == 5)
					{
						timeStr[index] = ':';
						LCD_Char(':');
						index++;
						
					}
					else if(index == 8){
						LCD_goToRowColumn(2,0);
						LCD_string("is_pm:");
						is_pm = key;
						LCD_Char(key);
						index++;
						
					}
					else{
						timeStr[index] = key;
						LCD_Char(key);
						index++;
					}

				}
				if(key == '*')
				{
					sscanf(timeStr, "%02d:%02d:%02d", &hours, &minutes, &seconds);
					clear();
					break;
				}
			}
		}
		
	}
	clear();
	displayTime();
}


adjustingAlarm(){
	clear();
	LCD_string("Adjust Alarm:");
	LCD_goToRowColumn(1,0);
	LCD_string("Alarm: ");
	uint8 key = INVALID_KEYPAD_PRESS;
	uint8 index = 0;
	while(1)
	{
		key = keypad_Get_Value();
		if(key != INVALID_KEYPAD_PRESS)
		{
			if(key != INVALID_KEYPAD_PRESS)
			{
				if(key >= '0' && key <= '9')
				{
					if(index == 2 || index == 5)
					{
						A_TimeStr[index] = ':';
						LCD_Char(':');
						index++;
						
					}
					else if(index == 8){
						LCD_goToRowColumn(2,0);
						LCD_string("is_pm:");
						A_TimeStr[index] = key;
						LCD_Char(key);
						index++;
						
					}
					else{
						A_TimeStr[index] = key;
						LCD_Char(key);
						index++;
					}

				}
				if(key == '+')
				{
					sscanf(A_TimeStr, "%02d:%02d:%02d", &A_hours, &A_minutes, &A_seconds);
					clear();
					break;
				}
			}
		}
		
	}
	is_alarm_on = 1;
	clear();
	displayTime();
}
#endif /* CLOCK_H_ */