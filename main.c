/*
 * KS0108.c
 *
 * Created: 2018-11-01 오전 12:00:18
 * Author : minhy
 */ 

#include "KS0108_Atmega128.h"

u8g2_t u8g2_ks0108;
u8g2_t u8g2_ssd1306;

int main(void)
{
	int i=0,j=0;
	
	DDRD=0x88;
	PORTD=0x70;
	//ks0108_off();
	init_ks0108();
	u8g2_Setup_ks0108_128x64_f(&u8g2_ks0108, U8G2_R0, u8x8_byte_ks0108, ks0108_GPIO);
	u8g2_SetFont(&u8g2_ks0108,u8g2_font_ncenB08_tf);
	u8g2_ClearBuffer(&u8g2_ks0108);
	u8g2_DrawFrame(&u8g2_ks0108,0,0,128,64);
	u8g2_DrawStr(&u8g2_ks0108, 1, 10, "Ready To Go!!");
	u8g2_SendBuffer(&u8g2_ks0108);

    while (1) 
    {
	    switch(PIND&0x70)
	    {
		    case 0x60:
		    PORTD|=(1<<7);
			if(i<64) i+=2;
			else i=0;
			u8g2_ClearBuffer(&u8g2_ks0108);
			u8g2_DrawStr(&u8g2_ks0108, j, i, "Hello");
			//u8g2_DrawFrame(&u8g2_ks0108,0,20,50,50);
			u8g2_SendBuffer(&u8g2_ks0108);
		    _delay_ms(50);
		    break;
		    
		    case 0x50:
		    PORTD|=(1<<7);
			if(j<128) j+=2;
			else j=0;
			u8g2_ClearBuffer(&u8g2_ks0108);
			u8g2_DrawStr(&u8g2_ks0108, j, i, "Hello");
			u8g2_SendBuffer(&u8g2_ks0108);			
		    _delay_ms(50);
			break;
			
		    default:
		    PORTD&=~(1<<7);
		    _delay_ms(50);
		    break;
	    }
    }
}

