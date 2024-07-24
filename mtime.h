#ifndef __MTIME_H
#define __MTIME_H

// NTP配置参数, 使用阿里云的NTP服务器
static const char *ntpServerUrl1 = "ntp1.aliyun.com";
static const char *ntpServerUrl2 = "ntp2.aliyun.com";
static const char *ntpServerUrl3 = "ntp3.aliyun.com";

static const long gmtOffset_sec = 8 * 3600;    // 时区偏移量，北京是GMT+8
static const int daylightOffset_sec = 0;       // 夏令时偏移量，中国无夏令时


void syncSysTime(void);
void printLocalTime(void);




#endif

