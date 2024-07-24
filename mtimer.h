#ifndef __MTIMER_H
#define __MTIMER_H


#include <Arduino.h>


void TIM_ISR(void);
void timer_init(uint32_t arr, void (*f)());






#endif

