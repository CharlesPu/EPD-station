#ifndef __MHTTP_H
#define __MHTTP_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>


#define WIFI_AP_NAME "PW55"
#define WIFI_AP_PWD  "097103603"
// #define WIFI_AP_NAME "TP-LINK1215"
// #define WIFI_AP_PWD  "88888888"


//#define URL_WEATHER "https://e.weather.com.cn/mweather/101210101.shtml"
#define WEATHER_URL_TODAY 		"https://api.seniverse.com/v3/weather/now.json"
#define WEATHER_URL_FORECAST 	"https://api.seniverse.com/v3/weather/daily.json"
#define WEATHER_URL_KEY 		"SqBLO65wX1XTKUfUN"
#define WEATHER_URL_LANGUAGE_EN "en"
#define WEATHER_URL_LANGUAGE_CN "zh-Hans"

typedef struct{
	const char* date;
	const char* text;
	int code;
	const char* temp;
}weather_t;

typedef struct{
	weather_t weathers[3];
}weather_info_t;

extern WiFiMulti mwifiMulti;

void wifiInit(void);
weather_info_t getTodayWeather(String city);
weather_info_t getForecastWeather(String city);




#endif

