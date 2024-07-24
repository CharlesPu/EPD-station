/* Includes ------------------------------------------------------------------*/
#include <Arduino.h>
#include <Ticker.h>


#include "epaper.h"
#include "mhttp.h"
#include "mtime.h"
#include "mtimer.h"

#include "src/RGBLed/rgbled.h"

Ticker ticker1;
#define REFRESH_INTERVAL 60 * 10 // s


void timer_cb(){
	LED_blink();
}

/* Entry point ----------------------------------------------------------------*/
void setup()
{
	Serial.begin(115200);

	RGBLED_init(10);
	LED_red();
	
	wifiInit();
	syncSysTime();
//	timer_init(5000, timer_cb); // ms
	ticker1.attach_ms(5000, timer_cb);

	LED_black();
}

/* The main loop -------------------------------------------------------------*/
void loop()
{	
	if((mwifiMulti.run() == WL_CONNECTED)) {
//		weather_info_t w = getTodayWeather("hangzhou");
//		Serial.printf("%s %s %s\r\n", w.weathers[0].date, w.weathers[0].text, w.weathers[0].temp);

		weather_info_t w = getForecastWeather("hangzhou");

		EPD_4in2bc_weather(&w);
    }
  
	delay(REFRESH_INTERVAL * 1000);
}

