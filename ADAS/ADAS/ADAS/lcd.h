/*
 * lcd.h
 *
 * Created: 7/8/2024 7:29:53 PM
 *  Author: john
 */ 

#ifndef LCD_H_
#define LCD_H_
#define lcd_data PORTA
#define lcd_ctrl PORTC
#define rs	PC0
#define rw	PC1
#define e	PC2
#include <avr/delay.h>
#include <avr/io.h>

typedef unsigned char u8;

void lcd_cmd(u8 cmd)
{
	lcd_ctrl&=~(1<<rw);
	lcd_ctrl&=~(1<<rs);
	lcd_data=cmd;
	lcd_ctrl|=(1<<e);
	_delay_ms(1);
	lcd_ctrl&=~(1<<e);
}

void lcd_char(u8 ch)
{
	lcd_ctrl&=~(1<<rw);
	lcd_ctrl|=(1<<rs);
	lcd_data=ch;
	lcd_ctrl|=(1<<e);
	_delay_ms(1);
	lcd_ctrl&=~(1<<e);
}

void lcd_str(const char* str)
{
	for (int i=0;str[i] !='\0';i++)
	{
		lcd_char(str[i]);
		_delay_ms(2);
	}
}

void lcd_init ()
{
	DDRA=255;//data
	DDRC|=(1<<rs)|(1<<e)|(1<<rw);
	_delay_ms(20);
lcd_cmd(0x38);//1 char 1 digit
lcd_cmd(0x0E);// display & cursor ON
lcd_cmd(0x01);//clear
_delay_ms(1);

}

#endif /* LCD_H_ */