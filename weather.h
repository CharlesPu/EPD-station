#ifndef __WEATHER_H
#define __WEATHER_H


#include <Arduino.h>


#define CODE_MAP_MAX 10

typedef struct{
	int code[CODE_MAP_MAX];
	unsigned char code_pic_48[288];
	unsigned char code_pic_128[2048];
}weather_code_t;


extern weather_code_t w_codes[];
extern int w_codes_len; 






#endif


