#ifndef __MHTTP_H
#define __MHTTP_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>


typedef struct{
	const char* date;
	const char* text;
	int code;
	const char* temp;
  const char* temp_low;
  const char* temp_high;
  const char* humidity;
}weather_t;

typedef struct{
	weather_t weathers[3];
}weather_info_t;

extern WiFiMulti mwifiMulti;

void wifiInit(void);
weather_info_t getTodayWeather(String city);
weather_info_t getForecastWeather(String city);




#endif

