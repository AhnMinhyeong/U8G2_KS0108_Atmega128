/*
 * KS0108.c
 *
 * Created: 2018-11-01 오전 12:00:18
 * Author : minhy
 */ 
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include "u8g2.h"
#define RS_H PORTA|=(1<<1)
#define RS_L PORTA&=~(1<<1)
#define EN_H PORTA|=(1<<0)
#define EN_L PORTA&=~(1<<0)
#define CS0_H PORTA|=(1<<2)
#define CS0_L PORTA&=~(1<<2)
#define CS1_H PORTA|=(1<<3)
#define CS1_L PORTA&=~(1<<3)
#define DB0_H PORTC|=(1<<0)
#define DB0_L PORTC&=~(1<<0)
#define DB1_H PORTC|=(1<<1)
#define DB1_L PORTC&=~(1<<1)
#define DB2_H PORTC|=(1<<2)
#define DB2_L PORTC&=~(1<<2)
#define DB3_H PORTC|=(1<<3)
#define DB3_L PORTC&=~(1<<3)
#define DB4_H PORTC|=(1<<4)
#define DB4_L PORTC&=~(1<<4)
#define DB5_H PORTC|=(1<<5)
#define DB5_L PORTC&=~(1<<5)
#define DB6_H PORTC|=(1<<6)
#define DB6_L PORTC&=~(1<<6)
#define DB7_H PORTC|=(1<<7)
#define DB7_L PORTC&=~(1<<7)
#define DB0 0
#define DB1 1
#define DB2 2
#define DB3 3
#define DB4 4
#define DB5 5
#define DB6 6
#define DB7 7
#define PORT_DB PORTC
#define PORT_COM PORTA

u8g2_t u8g2_ks0108;
u8g2_t u8g2_ssd1306;

void ks0108_on(void)
{
	RS_L;
	EN_L;
	CS0_L;
	CS1_L;
	PORT_DB=(1<<DB5)|(1<<DB4)|(1<<DB3)|(1<<DB2)|(1<<DB1)|(1<<DB0);
	EN_H;
	_delay_us(5);
	EN_L;
	_delay_us(5);
}

uint8_t ks0108_GPIO(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	switch(msg)
	{						// can be used to setup pins
    case U8X8_MSG_DELAY_NANO:			// delay arg_int * 1 nano second
		_delay_us(0.001);
      break;    
    case U8X8_MSG_DELAY_100NANO:		// delay arg_int * 100 nano seconds
		_delay_us(0.1);
      break;
    case U8X8_MSG_DELAY_10MICRO:		// delay arg_int * 10 micro seconds
		_delay_us(10);
      break;
    case U8X8_MSG_DELAY_MILLI:			// delay arg_int * 1 milli second
		_delay_ms(arg_int);
      break;
    case U8X8_MSG_GPIO_D0:				// D0 or SPI clock pin: Output level in arg_int
		if(arg_int) DB0_H;
		else DB0_L;
    //case U8X8_MSG_GPIO_SPI_CLOCK:
      break;
    case U8X8_MSG_GPIO_D1:				// D1 or SPI data pin: Output level in arg_int
		if(arg_int) DB1_H;
		else DB1_L;
    //case U8X8_MSG_GPIO_SPI_DATA:
      break;
    case U8X8_MSG_GPIO_D2:				// D2 pin: Output level in arg_int
		if(arg_int) DB2_H;
		else DB2_L;
      break;
    case U8X8_MSG_GPIO_D3:				// D3 pin: Output level in arg_int
		if(arg_int)DB3_H;
		else DB3_L;
      break;
    case U8X8_MSG_GPIO_D4:				// D4 pin: Output level in arg_int
		if(arg_int) DB4_H;
		else DB4_L;
      break;
    case U8X8_MSG_GPIO_D5:				// D5 pin: Output level in arg_int
		if(arg_int) DB5_H;
		else DB5_L;
      break;
    case U8X8_MSG_GPIO_D6:				// D6 pin: Output level in arg_int
		if(arg_int) DB6_H;
		else DB6_L;
      break;
    case U8X8_MSG_GPIO_D7:				// D7 pin: Output level in arg_int
		if(arg_int) DB7_H;
		else DB7_L;
      break;
    case U8X8_MSG_GPIO_E:				// E/WR pin: Output level in arg_int
		if(arg_int) EN_H;
		else EN_L;
      break;
    case U8X8_MSG_GPIO_CS:				// CS (chip select) pin: Output level in arg_int
		if(arg_int) CS0_H;
		else CS0_L;
      break;
    case U8X8_MSG_GPIO_DC:				// DC (data/cmd, A0, register select) pin: Output level in arg_int
		if(arg_int) RS_H;
		else RS_L;
      break;
    case U8X8_MSG_GPIO_RESET:			// Reset pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_CS1:				// CS1 (chip select) pin: Output level in arg_int
		if(arg_int) CS1_H;
		else CS1_L;
      break;
    case U8X8_MSG_GPIO_CS2:				// CS2 (chip select) pin: Output level in arg_int

      break;

    default:
      u8x8_SetGPIOResult(u8x8, 1);			// default return value
      break;
	}

	return 1;
 }
 
int main(void)
{
	PORT_DB=0xff;
	PORT_COM=0x0f;
	DDRD=0x88;
	PORTD=0x70;
	ks0108_on();
	u8g2_Setup_ks0108_128x64_f(&u8g2_ks0108, U8G2_R0, u8x8_byte_ks0108, ks0108_GPIO);
	u8g2_SetFont(&u8g2_ks0108,u8g2_font_ncenB08_tf);
	u8g2_ClearBuffer(&u8g2_ks0108);
	u8g2_DrawStr(&u8g2_ks0108, 0, 20, "Hello");
	u8g2_SendBuffer(&u8g2_ks0108);
    /* Replace with your application code */
    while (1) 
    {
	    switch(PIND&0x70)
	    {
		    case 0x60:
		    PORTD|=(1<<7);
			u8g2_ClearBuffer(&u8g2_ks0108);
			u8g2_DrawStr(&u8g2_ks0108, 0, 20, "Hello");
			u8g2_DrawFrame(&u8g2_ks0108,0,10,50,50);
			u8g2_SendBuffer(&u8g2_ks0108);
		    _delay_ms(100);
		    break;
		    
		    case 0x50:
		    PORTD|=(1<<7);
			u8g2_ClearBuffer(&u8g2_ks0108);
			u8g2_DrawStr(&u8g2_ks0108, 0, 50, "Hello");
			u8g2_SendBuffer(&u8g2_ks0108);
		    _delay_ms(100);
			break;
			
		    default:
		    PORTD&=~(1<<7);
		    //_delay_ms(300);
		    break;
	    }
    }
}

