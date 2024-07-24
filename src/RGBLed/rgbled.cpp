#include "rgbled.h"
#include <FastLED.h>


CRGB leds[NUM_LEDS];


void RGBLED_init(uint8_t b){
	FastLED.addLeds<WS2811, LED2812_PIN, RGB>(leds, NUM_LEDS);
	FastLED.setBrightness(b);
}

void LED_blink(void){
	for(int i=0;i<NUM_LEDS;i++)
    {
     leds[i]=CRGB::LightPink;
    }
   FastLED.show();
	delay(100);
	for(int i=0;i<NUM_LEDS;i++)
    {
     leds[i]= CRGB::Black;
    }
   FastLED.show();
	delay(100);
}

void LED_red(void){
	for(int i=0;i<NUM_LEDS;i++)
    {
     leds[i]=CRGB::Red;
    }
   FastLED.show();
}

void LED_black(void){
	for(int i=0;i<NUM_LEDS;i++)
    {
     leds[i]=CRGB::Black;
    }
   FastLED.show();
}




