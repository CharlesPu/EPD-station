#include <Arduino.h>
#include "mtime.h"


void syncSysTime() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServerUrl3,ntpServerUrl2,ntpServerUrl1);

  Serial.print(F("Waiting for NTP time sync: "));
  time_t nowSecs = time(nullptr);
  while (nowSecs < 8 * 3600 * 2) {
    delay(500);
    Serial.print(F("."));
    yield();
    nowSecs = time(nullptr);
  }

  Serial.println();
  printLocalTime();
  
//  struct tm timeinfo;
//  gmtime_r(&nowSecs, &timeinfo);
//  Serial.print(F("Current Sync time: "));
//  Serial.print(asctime(&timeinfo));
}

void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.print(F("Current Local time: "));
//  Serial.println(&timeinfo, "%F %T %A");
  Serial.print(asctime(&timeinfo));
}


