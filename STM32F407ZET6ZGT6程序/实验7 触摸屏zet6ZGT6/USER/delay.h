#ifndef __delay_H
#define	__delay_H

#include "stm32f4xx.h"

void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

void Delay(unsigned int nCount);

#endif /*__delay_H*/
