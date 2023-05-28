/*
 * LCD.h
 *
 * Created: 4/10/2023 10:39:29 PM
 *  Author: haahm
 */ 


#ifndef LCD_H_
#define LCD_H_
#define F_CPU 16000000UL
#include "ATmega32_Rrgiosters.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#define SET_CURSOR_LOCATION (0x80)

void LCD_Init(void)
{
	// Set RS and EN as output
	SET_BIT(DDRA, 3);
	SET_BIT(DDRA, 2);
		
	// Set D4, D5, D6, D7 as output
	SET_BIT(DDRB, 0);
	SET_BIT(DDRB, 1);
	SET_BIT(DDRB, 2);
	SET_BIT(DDRB, 4);
	
	
	_delay_ms(15);
		
	// Set LCD to 4 bit mode
	LCD_Command(0x02);
	LCD_Command(0x28);
		
	// Set display on and cursor off
	LCD_Command(0x0C);
	
	LCD_Command(0x06);
		
	// Clear LCD
	clear();
		
	// Force cursor to the beginning of 1st line
	LCD_Command(0x80);
}

void LCD_Command(unsigned char command)
{
	// Set RS = 0 to receive commands
	CLR_BIT(PORTA, 3);
		
	// Clear the pins on which we will receive commands (D4, D5, D6, D7)
	PORTB &= 0b11101000;
	
	// Get the 4 high bits from command then shift to right to eliminate low bits -> // 0000 1011
	unsigned char high = (command & 0xf0) >> 4;
	
	// Shift the leftmost 1 to the left by 1 to accommodate the pin places (0, 1, 2, 4)
	unsigned char temp = ((high & 0b00001000) << 1) | (high & 0b00000111); // 0001 0011
	
	// Set the pins to the high bits we obtained in temp
	PORTB |= temp;
	
	// Set EN = 1 (latch). Set EN to high then to low
	CLR_BIT(PORTA, 2);
	SET_BIT(PORTA, 2);
	_delay_ms(1);
	CLR_BIT(PORTA, 2);
	
	// Clear the pins on which we will receive commands (D4, D5, D6, D7)
	PORTB &= 0b11101000;
	
	// Get the 4 low bits from command
	unsigned char low = (command & 0x0f);
	
	// Shift the leftmost 1 to the left by 1 to accommodate the pin places (0, 1, 2, 4)
	unsigned char temp2 = ((low & 0b00001000) << 1) | (low & 0b00000111); // 0001 0011
	
	// Set the pins to the low bits we obtained in temp
	PORTB |= temp2;
	
	// Set EN = 1 (latch). Set EN to high then to low
	CLR_BIT(PORTA, 2);
	SET_BIT(PORTA, 2);
	_delay_ms(1);
	CLR_BIT(PORTA, 2);
	
	_delay_ms(40);
}

void LCD_Char(unsigned char character)
{
	// Set RS = 1 to receive data
	SET_BIT(PORTA, 3);
		
	// Clear the pins on which we will receive data (D4, D5, D6, D7)
	PORTB &= 0b11101000;
		
	// Get the 4 high bits from character then shift to right to eliminate low bits -> // 0000 1011
	unsigned char high = (character & 0xf0) >> 4;
		
	// Shift the leftmost 1 to the left by 1 to accommodate the pin places (0, 1, 2, 4)
	unsigned char temp = ((high & 0b00001000) << 1) | (high & 0b00000111); // 0001 0011
		
	// Set the pins to the high bits we obtained in temp
	PORTB |= temp;
		
	// Set EN = 1 (latch). Set EN to high then to low
	CLR_BIT(PORTA, 2);
	SET_BIT(PORTA, 2);
	_delay_ms(1);
	CLR_BIT(PORTA, 2);
		
	// Clear the pins on which we will receive commands (D4, D5, D6, D7)
	PORTB &= 0b11101000;
		
	// Get the 4 low bits from command
	unsigned char low = (character & 0x0f);
		
	// Shift the leftmost 1 to the left by 1 to accommodate the pin places (0, 1, 2, 4)
	unsigned char temp2 = ((low & 0b00001000) << 1) | (low & 0b00000111); // 0001 0011
		
	// Set the pins to the low bits we obtained in temp
	PORTB |= temp2;
		
	// Set EN = 1 (latch). Set EN to high then to low
	CLR_BIT(PORTA, 2);
	SET_BIT(PORTA, 2);
	_delay_ms(1);
	CLR_BIT(PORTA, 2);
		
	_delay_ms(5);
}
void LCD_string(unsigned char* str)
{
	for(int i=0; str[i] != '\0';i++)
	{
		LCD_Char(str[i]);
	}
}

void LCD_goToRowColumn(unsigned char row, unsigned char col)
{
	unsigned char Address = 0;
	
	switch(row) // 2, 4
	{
		case 0:
		Address = col;
		break;
		case 1:
		Address = col+0x40;
		break;
		case 2:
		Address = col+0x14;
		break;
		case 3:
		Address = col+0x54;
		break;
	}
	
	LCD_Command(Address | SET_CURSOR_LOCATION);
}

void clear(void)
{
	LCD_Command(0x01);
}
#endif /* LCD_H_ */