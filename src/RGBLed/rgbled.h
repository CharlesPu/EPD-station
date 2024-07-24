#ifndef __RGBLED_H__
#define __RGBLED_H__

#include <FastLED.h>


#define LED2812_PIN 48
#define NUM_LEDS 1
extern CRGB leds[NUM_LEDS];



void RGBLED_init(uint8_t b);



void RGBDOW();
void RGBUP();
void LEDLI();
void LED_breathe();

void LED_blink();
void LED_red(void);
void LED_black(void);







#endif

