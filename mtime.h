#ifndef __MTIME_H
#define __MTIME_H



static const long gmtOffset_sec = 8 * 3600;    // 时区偏移量，北京是GMT+8
static const int daylightOffset_sec = 0;       // 夏令时偏移量，中国无夏令时


void syncSysTime(void);
void printLocalTime(void);




#endif

