#ifndef __EPEPAR_H
#define __EPEPAR_H

#include "mhttp.h"
#include "src/EPD/EPD.h"

#define REFRESH_TIME_INTERVAL 5 // s
#define REFRESH_WEATHER_INTERVAL 30 // s
#define REFRESH_ALL_INTERVAL 5*60 // 强制全部刷新

void EPD_4in2bc_demo(void);
void EPD_4in2bc_weather(weather_info_t*);
void EPD_4in2bc_weather_draw_w(weather_info_t*, uint8_t *BlackImage, uint8_t *RYImage);



void EPD_2in9_demo();
void EPD_2in9_station();
void EPD_2in9_draw_time_once();
void EPD_2in9_draw_header(int x);
void EPD_2in9_draw_weather(weather_info_t *w);


#endif


/////////////////////////////////////////////////////////////////////////////////
