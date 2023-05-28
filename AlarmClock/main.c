/*
 * AlarmClock.c
 *
 * Created: 5/15/2023 4:14:04 PM
 * Author : haahm
 */ 

#include <avr/io.h>
#include "Keypad.h"
#include "LCD.h"
#include "Clock.h"
#include "std_types.h"
uint8 timerRunning = 1;
uint8 ticks =0;
void TheTime()
{
	if(timerRunning == 1)
	{
	ticks++;
		if(ticks == NUMER_OF_OVERFLOWS)
		{
			seconds++;
			// Check if seconds reached 60
			if (seconds >= 60) {
				seconds = 0;
				minutes++;
				
				// Check if minutes reached 60
				if (minutes >= 60) {
					minutes = 0;
					hours++;
					
					// Check if hours reached 12 or 24 (based on time format)
					if (hours >= 12) {
						hours = 0;  // Reset hours to 0 for 12-hour format
						// Alternatively, you can implement 24-hour format by resetting hours to 0 after 24
					}
				}
			}
			
			displayTime();
			ticks = 0;
		}
		
		}

}
void handleAlarm()
{
	if(seconds == A_seconds && minutes == A_minutes && hours == A_hours && is_pm == A_is_pm && is_alarm_on == 1)
	{
		SET_BIT(DDRB,7);
		SET_BIT(DDRC,6);
		SET_BIT(PORTB,PINB7);
		SET_BIT(PORTC,6);
	}
}
int main(void)
{
	LCD_Init();
	keypad_init();
	
	timer0_init();
	timer0_callbackPtr(TheTime);
    while (1) 
    {
	uint8 key = keypad_Get_Value();
		if(key == '*')
		{
			timerRunning = 0;
			adjustingTime();
			timerRunning = 1;
		}
		else if (key == '+')
		{
			timerRunning = 0;
			adjustingAlarm();
			timerRunning = 1;
		}
		else if (key == '0')
		{
		CLR_BIT(PORTB,7);
		CLR_BIT(PORTC,6);
		}
		handleAlarm();
		
    }
}

