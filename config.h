#ifndef __CONFIG_H
#define __CONFIG_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>


#if 0
#define WIFI_AP_NAME "PW55"
#define WIFI_AP_PWD  "097103603"
#else
#define WIFI_AP_NAME "TP-LINK1215"
#define WIFI_AP_PWD  "88888888"
#endif

#define REFRESH_LOOP_INTERVAL 1
#define REFRESH_TIME_INTERVAL 60 // s
#define REFRESH_HEADER_INTERVAL 10 // s
#define REFRESH_WEATHER_INTERVAL 10*60 // s
#define REFRESH_ALL_INTERVAL 10*60 // 强制全部刷新

#define TIMER_INTERVAL 30 // s


//#define URL_WEATHER "https://e.weather.com.cn/mweather/101210101.shtml"
#define WEATHER_URL_TODAY 		"https://api.seniverse.com/v3/weather/now.json"
#define WEATHER_URL_FORECAST 	"https://api.seniverse.com/v3/weather/daily.json"
#define WEATHER_URL_KEY 		"SqBLO65wX1XTKUfUN"
#define WEATHER_URL_LANGUAGE_EN "en"
#define WEATHER_URL_LANGUAGE_CN "zh-Hans"


// NTP配置参数, 使用阿里云的NTP服务器
static const char *ntpServerUrl1 = "ntp1.aliyun.com";
static const char *ntpServerUrl2 = "ntp2.aliyun.com";
static const char *ntpServerUrl3 = "ntp3.aliyun.com";




#endif

