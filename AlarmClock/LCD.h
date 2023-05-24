/*
 * LCD.h
 *
 * Created: 4/10/2023 10:39:29 PM
 *  Author: haahm
 */ 


#ifndef LCD_H_
#define LCD_H_
#define  F_CPU 16000000
#include "ATmega32_Rrgiosters.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#define LCD_DATA_PORT PORTB
#define LCD_DATA_Dir DDRB
#define LCD_Command_Port PORTA
#define LCD_Command_Dir DDRA
#define RS PIN3
#define EN PIN2
#define SET_CURSOR_LOCATION (0x80)

void LCD_Init(void)
{
	LCD_DATA_Dir |= 0b00010111;
	LCD_Command_Dir |= (1<<RS) | (1<<EN);
	_delay_ms(15);
	LCD_Command(0x02);
	LCD_Command(0x28);
	LCD_Command(0x0C);
	LCD_Command(0x06);
	LCD_Command(0x01);
	LCD_Command(0x80);
}
void LCD_Command(unsigned char cmd)
{
	PORTB &= 0b11101000;
	PORTB |= (((((cmd&0xF0)>>4) &0b00001000) << 1)|(((cmd&0xF0)>>4)&0b00000111));
	CLR_BIT(LCD_Command_Port,RS);
	SET_BIT(LCD_Command_Port,EN);
	_delay_ms(1);
	CLR_BIT(LCD_Command_Port,EN);
	_delay_ms(2);
	PORTB &= 0b11101000;
	PORTB |= ((((cmd&0x0F) &0b00001000) << 1)|(((cmd&0x0F))&0b00000111));
	SET_BIT(LCD_Command_Port,EN);
	_delay_ms(1);
	CLR_BIT(LCD_Command_Port,EN);
	_delay_ms(2);
}

void LCD_Char(unsigned char char_data)
{
	PORTB &= 0b11101000;
	PORTB |= (((((char_data&0xF0)>>4) &0b00001000) << 1)|(((char_data&0xF0)>>4)&0b00000111));
	SET_BIT(LCD_Command_Port, RS);
	SET_BIT(LCD_Command_Port,EN);
	_delay_ms(1);
	CLR_BIT(LCD_Command_Port,EN);
	_delay_ms(100);
	
	PORTB &= 0b11101000;
	PORTB |= (((((char_data&0x0F)) &0b00001000) << 1)|(((char_data&0x0F))&0b00000111));
	SET_BIT(LCD_Command_Port,EN);
	_delay_ms(1);
	CLR_BIT(LCD_Command_Port,EN);
	_delay_ms(100);
}
void LCD_string(unsigned char* str)
{
	for(int i=0; str[i] != '\0';i++)
	{
		LCD_Char(str[i]);
	}
}
void clear(void)
{
	LCD_Command(0x01);
}
#endif /* LCD_H_ */