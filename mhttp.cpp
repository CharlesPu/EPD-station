#include "mhttp.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <string.h>
#include "config.h"

WiFiMulti mwifiMulti;

void wifiInit(void){
	
	WiFi.mode(WIFI_STA);
	mwifiMulti.addAP(WIFI_AP_NAME, WIFI_AP_PWD); 
	
	// wait for WiFi connection
	Serial.print("Waiting for WiFi to connect...");
	while ((mwifiMulti.run() != WL_CONNECTED)) {
	  Serial.print(".");
	}
	Serial.println(" connected");
}

weather_info_t getTodayWeather(String city){
	String url_xinzhi = WEATHER_URL_TODAY;
	url_xinzhi = url_xinzhi + "?key=" + WEATHER_URL_KEY;
	url_xinzhi = url_xinzhi + "&location=" + city;
	url_xinzhi = url_xinzhi + "&language=" + WEATHER_URL_LANGUAGE_CN;
	url_xinzhi = url_xinzhi + "&unit=c";

	DynamicJsonDocument doc(2048); //分配内存,动态

	HTTPClient http;
	weather_info_t r;

	http.begin(url_xinzhi);

	int httpGet = http.GET();

	if (httpGet > 0)
	{
		if (httpGet == HTTP_CODE_OK)
		{
			String json = http.getString();
			Serial.println(json);  //打印接受到的消息

			deserializeJson(doc, json);

			JsonObject root = doc.as<JsonObject>();
			JsonArray results = root["results"];

			r.weathers[0].date = results[0]["last_update"];
//			strncpy(r.weathers[0].date, results[0]["last_update"], 0, 10);
			r.weathers[0].text = results[0]["now"]["text"];
			r.weathers[0].temp = results[0]["now"]["temperature"];
		}
	}
	http.end();

	return r;
}

weather_info_t getForecastWeather(String city){
	String url_xinzhi = WEATHER_URL_FORECAST;
	url_xinzhi = url_xinzhi + "?key=" + WEATHER_URL_KEY;
	url_xinzhi = url_xinzhi + "&location=" + city;
	url_xinzhi = url_xinzhi + "&language=" + WEATHER_URL_LANGUAGE_CN;
	url_xinzhi = url_xinzhi + "&unit=c&start=0&days=3"; // 非vip最多三天

	DynamicJsonDocument doc(2048); //分配内存,动态

	HTTPClient http;
	weather_info_t r;

	http.begin(url_xinzhi);

	int httpGet = http.GET();

	if (httpGet > 0)
	{
		if (httpGet == HTTP_CODE_OK)
		{
			String json = http.getString();
			Serial.println(json);  //打印接受到的消息

			deserializeJson(doc, json);
//			Serial.println(doc);  

			JsonObject root = doc.as<JsonObject>();
			JsonArray results = root["results"];

			for (int i = 0; i < 3; ++i)
			{
				r.weathers[i].date = results[0]["daily"][i]["date"];
				r.weathers[i].text = results[0]["daily"][i]["text_day"];
				r.weathers[i].code = results[0]["daily"][i]["code_day"];
				r.weathers[i].temp = results[0]["daily"][i]["high"];
        r.weathers[i].temp_low = results[0]["daily"][i]["low"];
        r.weathers[i].temp_high = results[0]["daily"][i]["high"];
        r.weathers[i].humidity = results[0]["daily"][i]["humidity"];
			}
		}
	}
	http.end();

	return r;
}

void httpTest(void) {
//    HTTPClient http;
//
//    Serial.print("[HTTP] begin...\n");
//    // configure traged server and url
//	http.begin(URL_WEATHER);
//
//
//    Serial.print("[HTTP] GET...\n");
//    // start connection and send HTTP header
//    int httpCode = http.GET();
//
//    // httpCode will be negative on error
//    if(httpCode > 0) {
//        // HTTP header has been send and Server response header has been handled
//        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
//
//        // file found at server
//        if(httpCode == HTTP_CODE_OK) {
//            String payload = http.getString();
//            Serial.println(payload);
//        }
//    } else {
//        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
//    }
//
//    http.end();
}

