/* Includes ------------------------------------------------------------------*/
#include <Arduino.h>
#include <Ticker.h>

#include "epaper.h"
#include "mhttp.h"
#include "mtime.h"
#include "config.h"

#include "src/RGBLed/rgbled.h"

Ticker ticker1;

void timer_cb(){
	LED_blink();
}

/* Entry point ----------------------------------------------------------------*/
void setup()
{
  srand(time(NULL));
	Serial.begin(115200);

	RGBLED_init(10);
	LED_red();
	
	wifiInit();
	syncSysTime();
	ticker1.attach_ms(TIMER_INTERVAL * 1000, timer_cb);

	LED_black();
}

/* The main loop -------------------------------------------------------------*/
void loop()
{	
	if((mwifiMulti.run() != WL_CONNECTED)) {
    printf("wifi is not connected!!\r\n");
    delay(500);
    return;
  }
  // weather_info_t w = getTodayWeather("hangzhou");
  // Serial.printf("%s %s %s\r\n", w.weathers[0].date, w.weathers[0].text, w.weathers[0].temp);
#if 0
  weather_info_t w = getForecastWeather("hangzhou");
  EPD_4in2bc_weather(&w);
#endif
#if 1
  EPD_2in9_station();
#endif
}

