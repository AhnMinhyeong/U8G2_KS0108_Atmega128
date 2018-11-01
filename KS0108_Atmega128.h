/*
 * KS0108_Atmega128.h
 *
 * Created: 2018-11-02 오전 3:38:58
 *  Author: minhy
 */ 


#ifndef KS0108_ATMEGA128_H_
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "u8g2.h"
#define KS0108_ATMEGA128_H_

void port_init(void);
void ks0108_on(void);
void ks0108_off(void);
uint8_t ks0108_GPIO(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);



#endif /* KS0108_ATMEGA128_H_ */
