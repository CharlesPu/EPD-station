#ifndef __EPEPAR_H
#define __EPEPAR_H

#include "mhttp.h"
#include "src/EPD/EPD.h"
#include "src/EPD/GUI_Paint.h"



typedef struct{
  unsigned char *image;
  int image_width,image_height;

  int start_image_x, start_image_y;
  int start_temp_high_x, start_temp_high_y;
  int start_humidity_x, start_humidity_y;
  sFONT ff;
  sFONT ff_temp;
}weather_paint_t;

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
