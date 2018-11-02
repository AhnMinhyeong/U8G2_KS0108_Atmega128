/*
 * KS0108_Atmega128_Func.c
 *
 * Created: 2018-11-02 오전 3:37:32
 *  Author: minhy
 */ 
#include "KS0108_Atmega128.h"

#define PORT_DB PORTC
#define PORT_COM PORTA
#define DDR_DB DDRC
#define DDR_COM DDRA

#define RS_H PORT_COM|=(1<<1)
#define RS_L PORT_COM&=~(1<<1)
#define EN_H PORT_COM|=(1<<0)
#define EN_L PORT_COM&=~(1<<0)
#define CS0_H PORT_COM|=(1<<2)
#define CS0_L PORT_COM&=~(1<<2)
#define CS1_H PORT_COM|=(1<<3)
#define CS1_L PORT_COM&=~(1<<3)
#define DB0_H PORT_DB|=(1<<0)
#define DB0_L PORT_DB&=~(1<<0)
#define DB1_H PORT_DB|=(1<<1)
#define DB1_L PORT_DB&=~(1<<1)
#define DB2_H PORT_DB|=(1<<2)
#define DB2_L PORT_DB&=~(1<<2)
#define DB3_H PORT_DB|=(1<<3)
#define DB3_L PORT_DB&=~(1<<3)
#define DB4_H PORT_DB|=(1<<4)
#define DB4_L PORT_DB&=~(1<<4)
#define DB5_H PORT_DB|=(1<<5)
#define DB5_L PORT_DB&=~(1<<5)
#define DB6_H PORT_DB|=(1<<6)
#define DB6_L PORT_DB&=~(1<<6)
#define DB7_H PORT_DB|=(1<<7)
#define DB7_L PORT_DB&=~(1<<7)
#define DB0 0
#define DB1 1
#define DB2 2
#define DB3 3
#define DB4 4
#define DB5 5
#define DB6 6
#define DB7 7

void port_init(void)
{
	DDR_DB=0xff;
	DDR_COM=0x0f;
}

void ks0108_on(void)
{
	RS_L;
	EN_L;
	CS0_L;
	CS1_L;
	PORT_DB=(1<<DB6);
	EN_H;
	_delay_us(5);
	EN_L;
	_delay_us(5);
//////////////Set Address Y to 0
	RS_L;
	EN_L;
	CS0_L;
	CS1_L;
	PORT_DB=(1<<DB7)|(1<<DB6);
	EN_H;
	_delay_us(5);
	EN_L;
	_delay_us(5);
//////////////Set Address X to 0
	RS_L;
	EN_L;
	CS0_L;
	CS1_L;
	PORT_DB=(1<<DB5)|(1<<DB4)|(1<<DB3)|(1<<DB2)|(1<<DB1)|(1<<DB0);
	EN_H;
	_delay_us(5);
	EN_L;
	_delay_us(5);
/////////////Turn on Display
}

void ks0108_off(void)
{
	RS_L;
	EN_L;
	CS0_L;
	CS1_L;
	PORT_DB=(1<<DB5)|(1<<DB4)|(1<<DB3)|(1<<DB2)|(1<<DB1);
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
		break;
		case U8X8_MSG_GPIO_D1:				// D1 or SPI data pin: Output level in arg_int
		if(arg_int) DB1_H;
		else DB1_L;
		break;
		case U8X8_MSG_GPIO_D2:				// D2 pin: Output level in arg_int
		if(arg_int) DB2_H;
		else DB2_L;
		break;
		case U8X8_MSG_GPIO_D3:				// D3 pin: Output level in arg_int
		if(arg_int) DB3_H;
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
