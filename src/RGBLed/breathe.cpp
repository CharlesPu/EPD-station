#include "rgbled.h"

#include <FastLED.h>



//LED参数
 float r1=200,g1=200,b1=200;
 float r2=r1,g2=g1,b2=b1;
 int ledBkTime=30;//led呼吸时长


void LED_breathe(){
	for(int i=0;i<ledBkTime;i++)
	{
		LEDLI();
		RGBDOW();
	}
	for(int i=0;i<ledBkTime;i++)
	{
		LEDLI();
		RGBUP();
	}
}

void LEDLI()
{
  
   for(int i=0;i<NUM_LEDS;i++)
    {
     leds[i]=CRGB(g2,r2,b2);
    }
   FastLED.show();
   delay(50);
  
}
 
void RGBDOW()
{
  r2=r2-r1/ledBkTime;
  g2=g2-g1/ledBkTime;
  b2=b2-b1/ledBkTime;
}

void RGBUP()
{
 r2=r2+r1/ledBkTime;
 g2=g2+g1/ledBkTime;
 b2=b2+b1/ledBkTime; 
}


