#include "epaper.h"
#include "src/EPD/DEV_Config.h"
#include "src/EPD/GUI_Paint.h"
#include "ImageData.h"
#include "weather.h"

#include <stdlib.h>

epd_gpio_t epd_gpio_1 = {
    .BUSY_Pin = 14,
    .RES_Pin = 15,
    .DC_Pin = 16,
    .CS_Pin = 17,
    .SCL_Pin = 18,
    .SDI_Pin = 19,
};

epd_gpio_t epd_gpio_2 = {
    .BUSY_Pin = 42,
    .RES_Pin = 39,
    .DC_Pin = 40,
    .CS_Pin = 41,
    .SCL_Pin = 37,
    .SDI_Pin = 38,
};

void EPD_4in2bc_weather(weather_info_t *w)
{
  printf("EPD_4IN2BC_test weather\r\n");

  printf("e-Paper Init and Clear...\r\n");
  EPD_4IN2BC_Init(&epd_gpio_1);
  //	EPD_4IN2BC_Clear();
  DEV_Delay_ms(10);

  // Create a new image cache named IMAGE_BW and f ill it with white
  UBYTE *BlackImage, *RYImage; // Red or Yellow
  UWORD Imagesize = ((EPD_4IN2BC_WIDTH % 8 == 0) ? (EPD_4IN2BC_WIDTH / 8) : (EPD_4IN2BC_WIDTH / 8 + 1)) * EPD_4IN2BC_HEIGHT;
  if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL)
  {
    printf("Failed to apply for black memory...\r\n");
    while (1);
  }
  if ((RYImage = (UBYTE *)malloc(Imagesize)) == NULL)
  {
    printf("Failed to apply for red memory...\r\n");
    while (1);
  }
  printf("NewImage:BlackImage and RYImage\r\n");
  Paint_NewImage(BlackImage, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, 0, WHITE);
  Paint_NewImage(RYImage, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, 0, WHITE);

  // Select Image
  for (int i = 0; i < 3; ++i)
    printf("----%s %s %d %s\r\n", w->weathers[i].date, w->weathers[i].text, w->weathers[i].code, w->weathers[i].temp);

  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);
  Paint_SelectImage(RYImage);
  Paint_Clear(WHITE);
  // draw back
  Paint_SelectImage(RYImage);
  Paint_DrawLine(10, 200, 390, 200, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
  Paint_DrawLine(200, 10, 200, 190, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
  Paint_DrawLine(210, 100, 390, 100, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

  EPD_4in2bc_weather_draw_w(w, BlackImage, RYImage);

  printf("EPD_Display\r\n");
  EPD_4IN2BC_Display(BlackImage, RYImage);
  //	DEV_Delay_ms(20000);

#if 0 // show image for array    
	printf("show image for array\r\n");
	EPD_4IN2BC_Display(gImage_pu_wang_1, gImage_pu_wang_2);
	DEV_Delay_ms(2000);
#endif

#if 0 // Drawing on the image
	/*Horizontal screen*/
	//1.Draw black image
	printf("Draw black image\r\n");
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
	Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
	Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
	Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
	Paint_DrawPoint(10, 110, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
	Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
	Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	Paint_DrawString_EN(10, 0, "waveshare", &Font16, WHITE, BLACK);
	Paint_DrawString_CN(130, 20, "微雪电子", &Font24CN, BLACK, WHITE);
	Paint_DrawNum(10, 50, 987654321, &Font16, BLACK, WHITE);

	//2.Draw red image
	printf("Draw red image\r\n");
	Paint_SelectImage(RYImage);
	Paint_Clear(WHITE);
	Paint_DrawCircle(160, 95, 20, RED, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
	Paint_DrawCircle(210, 95, 20, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	Paint_DrawLine(85, 95, 125, 95, RED, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	Paint_DrawLine(105, 75, 105, 115, RED, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	Paint_DrawString_CN(130, 0, "你好abc", &Font12CN, RED, WHITE);
	Paint_DrawString_EN(10, 20, "hello world", &Font12, RED, WHITE);
	Paint_DrawNum(10, 33, 123456789, &Font12, WHITE, RED);

	printf("EPD_Display\r\n");
	EPD_4IN2BC_Display(BlackImage, RYImage);
	DEV_Delay_ms(5000);
#endif

  //	printf("Clear...\r\n");
  //	EPD_4IN2BC_Clear();

  printf("Goto Sleep...\r\n");
  EPD_4IN2BC_Sleep();
  free(BlackImage);
  free(RYImage);
  BlackImage = NULL;
  RYImage = NULL;
}

void EPD_4in2bc_demo(void)
{
  printf("EPD_4IN2BC_test Demo\r\n");

  printf("e-Paper Init and Clear...\r\n");
  EPD_4IN2BC_Init(&epd_gpio_1);
  EPD_4IN2BC_Clear();
  DEV_Delay_ms(6000);

  // Create a new image cache named IMAGE_BW and fill it with white
  UBYTE *BlackImage, *RYImage; // Red or Yellow
  UWORD Imagesize = ((EPD_4IN2BC_WIDTH % 8 == 0) ? (EPD_4IN2BC_WIDTH / 8) : (EPD_4IN2BC_WIDTH / 8 + 1)) * EPD_4IN2BC_HEIGHT;
  if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL)
  {
    printf("Failed to apply for black memory...\r\n");
    while (1)
      ;
  }
  if ((RYImage = (UBYTE *)malloc(Imagesize)) == NULL)
  {
    printf("Failed to apply for red memory...\r\n");
    while (1)
      ;
  }
  printf("NewImage:BlackImage and RYImage\r\n");
  Paint_NewImage(BlackImage, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, 0, WHITE);
  Paint_NewImage(RYImage, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, 0, WHITE);

  // Select Image
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);
  Paint_SelectImage(RYImage);
  Paint_Clear(WHITE);

#if 1 // show image for array
  printf("show image for array\r\n");
  EPD_4IN2BC_Display(gImage_pu_wang_1, gImage_pu_wang_2);
  DEV_Delay_ms(2000);
#endif

#if 0 // Drawing on the image
	/*Horizontal screen*/
	//1.Draw black image
	printf("Draw black image\r\n");
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
	Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
	Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
	Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
	Paint_DrawPoint(10, 110, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
	Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
	Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	Paint_DrawString_EN(10, 0, "waveshare", &Font16, WHITE, BLACK);
	Paint_DrawString_CN(130, 20, "微雪电子", &Font24CN, BLACK, WHITE);
	Paint_DrawNum(10, 50, 987654321, &Font16, BLACK, WHITE);

	//2.Draw red image
	printf("Draw red image\r\n");
	Paint_SelectImage(RYImage);
	Paint_Clear(WHITE);
	Paint_DrawCircle(160, 95, 20, RED, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
	Paint_DrawCircle(210, 95, 20, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	Paint_DrawLine(85, 95, 125, 95, RED, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	Paint_DrawLine(105, 75, 105, 115, RED, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	Paint_DrawString_CN(130, 0, "你好abc", &Font12CN, RED, WHITE);
	Paint_DrawString_EN(10, 20, "hello world", &Font12, RED, WHITE);
	Paint_DrawNum(10, 33, 123456789, &Font12, WHITE, RED);


	printf("EPD_Display\r\n");
	EPD_4IN2BC_Display(BlackImage, RYImage);
	DEV_Delay_ms(5000);
#endif

  //	printf("Clear...\r\n");
  //	EPD_4IN2BC_Clear();

  printf("Goto Sleep...\r\n");
  EPD_4IN2BC_Sleep();
  free(BlackImage);
  free(RYImage);
  BlackImage = NULL;
  RYImage = NULL;
}

void EPD_4in2bc_weather_draw_w(weather_info_t *w, uint8_t *BlackImage, uint8_t *RYImage)
{
  Paint_SelectImage(BlackImage);

  for (int i = 0; i < w_codes_len; ++i)
  {
    for (int j = 0; j < CODE_MAP_MAX; ++j)
    {
      for (int k = 0; k < 3; ++k)
      {
        weather_t ww = w->weathers[k];
        int start_pic_x, start_pic_y;
        int start_temp_x, start_temp_y;
        int start_date_x, start_date_y;
        sFONT ff = Font24;
        unsigned char *buf = w_codes[i].code_pic_128;
        int bufS = 128;

        if (w_codes[i].code[j] == ww.code + 1)
        { //. matched
          if (k == 0)
          {
            start_pic_x = 40;
            start_pic_y = 70;
            start_temp_x = 90;
            start_temp_y = 20;
            start_date_x = 20;
            start_date_y = 45;
          }
          else if (k == 1)
          {
            start_pic_x = 210;
            start_pic_y = 30;
            start_temp_x = 310;
            start_temp_y = 30;
            start_date_x = 280;
            start_date_y = 60;
            ff = Font16;
            buf = w_codes[i].code_pic_48;
            bufS = 48;
          }
          else if (k == 2)
          {
            start_pic_x = 210;
            start_pic_y = 130;
            start_temp_x = 310;
            start_temp_y = 130;
            start_date_x = 280;
            start_date_y = 170;
            ff = Font16;
            buf = w_codes[i].code_pic_48;
            bufS = 48;
          }

          printf("pick  %d \r\n", w_codes[i].code[j]);
          Paint_SelectImage(RYImage);
          Paint_DrawImage(buf, start_pic_x, start_pic_y, bufS, bufS);

          Paint_SelectImage(BlackImage);
          Paint_DrawString_EN(start_date_x, start_date_y, ww.date, &ff, WHITE, BLACK);
          Paint_DrawString_EN(start_temp_x, start_temp_y, ww.temp, &ff, WHITE, BLACK);
        }
      }
    }
  }
}

void EPD_2in9_demo(void)
{
  printf("EPD_2in9_test Demo\r\n");

  EPD_2IN9_Init(&epd_gpio_2); // Electronic paper initialization
  EPD_WhiteScreen_ALL();      // Full screen refresh picture 1
  delay(500);

  //////////////////////Partial refresh digital presentation//////////////////////////////////////
  EPD_SetRAMValue_BaseMap(gImage_basemap); // Partial refresh background color
  EPD_Part_Init();                         // Local refresh initialization
  delay(100);

  EPD_Dis_Part(0, 296, gImage_num1, 32, 32); // x,y,datas,resolution 32*32
  EPD_Dis_Part(0, 296, gImage_num2, 32, 32); // x,y,datas,resolution 32*32
  EPD_Dis_Part(0, 296, gImage_num3, 32, 32); // x,y,datas,resolution 32*32
  EPD_Dis_Part(0, 296, gImage_num4, 32, 32); // x,y,datas,resolution 32*32
  EPD_Dis_Part(0, 296, gImage_num5, 32, 32); // x,y,datas,resolution 32*32
  EPD_Dis_Part(0, 296, gImage_num6, 32, 32); // x,y,datas,resolution 32*32
  EPD_Dis_Part(0, 296, gImage_num7, 32, 32); // x,y,datas,resolution 32*32
  EPD_Dis_Part(0, 296, gImage_num8, 32, 32); // x,y,datas,resolution 32*32
  EPD_Dis_Part(0, 296, gImage_num9, 32, 32); // x,y,datas,resolution 32*32
  
  //////////////////////////////////////////////////////////////////////// 
  // Clean
  printf("2in9 Goto Sleep...\r\n");
  // EPD_2IN9_Init(&epd_gpio_2);//Electronic paper initialization
  // EPD_WhiteScreen_White();  //Show all white
  EPD_DeepSleep(); // Enter deep sleep,Sleep instruction is necessary, please do not delete!!!
}

// Coordinate
////// epd
// 296-----<----Y-----<-------0
//                            |
//                            X
//                            |
//                           128
////// painter
//  0----->----X----->-------296
//  |
//  Y
//  |
// 128
//////////////////////////////
void EPD_2in9_station()
{
  printf("EPD_2in9_station!\r\n");

  EPD_2IN9_Init(&epd_gpio_2); // Electronic paper initialization
  EPD_WhiteScreen_ALL();      // Full screen refresh picture 1
  delay(500);

  uint32_t cnt=0;
  uint32_t header_x=0;
  while(1){
    if ((cnt%(REFRESH_ALL_INTERVAL/REFRESH_TIME_INTERVAL)==0)) {// 强制全局刷新
      printf("2in9 force all refresh...\r\n");
      EPD_SetRAMValue_BaseMap(nullptr);// Partial refresh background color | gImage_basemap
    }
  //////////////////////Partial refresh digital presentation//////////////////////////////////////
    EPD_Part_Init();                         // Local refresh initialization

    if (cnt%(REFRESH_WEATHER_INTERVAL/REFRESH_TIME_INTERVAL)==0){
      // cnt=0;// init
      
      printf("2in9 draw weather...\r\n");
      weather_info_t w = getForecastWeather("hangzhou");
      EPD_2in9_draw_weather(&w);
      delay(100);
    }
    printf("2in9 draw time...\r\n");
    EPD_2in9_draw_time_once();

    printf("2in9 draw header...\r\n");
    if (header_x <= EPD_2IN9_HEIGHT-100) {
      
      EPD_2in9_draw_header(header_x);
      header_x+=10;
    }else {
      header_x=0;
    }
    delay(100);
//////////////////////////////////////////////////////////////////////// 
    printf("2in9 Goto Sleep...\r\n");
    EPD_DeepSleep(); // Enter deep sleep,Sleep instruction is necessary, please do not delete!!!
    delay(REFRESH_TIME_INTERVAL * 1000);
    cnt++;
  }
}

void EPD_2in9_draw_time_once()
{
  sFONT ff = Font24;
  int area_height = ff.Height;
  int area_width = ff.Width * 7;

  UWORD Imagesize = ((area_height % 8 == 0) ? (area_height / 8) : (area_height / 8 + 1)) * area_width;
  UBYTE BlackImage[Imagesize]={};

  // printf("NewImage: time size %d %d, %d\r\n", area_height, area_width, Imagesize);
  Paint_NewImage(BlackImage, area_height, area_width, ROTATE_270, WHITE);
  Paint_Clear(BLACK);
  Paint_SetMirroring(MIRROR_VERTICAL);

  // for (;;) {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
      Serial.println("Failed to obtain time");

      return;
    }
    // Serial.printf(" | %d %d %d\r\n", timeinfo.tm_sec, timeinfo.tm_min, timeinfo.tm_hour);
    PAINT_TIME sPaint_time;
      sPaint_time.Hour = timeinfo.tm_hour;
      sPaint_time.Min = timeinfo.tm_min;
      sPaint_time.Sec = timeinfo.tm_sec;
    Paint_ClearWindows(0, 0, 0 + area_width, 0 + area_height, WHITE);
    Paint_DrawTime(0, 0, &sPaint_time, &ff, WHITE, BLACK);
    EPD_Dis_Part(104, 200, BlackImage, area_height, area_width); 
    // delay(1000);
  // }
}

void EPD_2in9_draw_header(int x)
{
  int area_height = 32;
  int area_width = 296;
  UWORD Imagesize = ((area_height % 8 == 0) ? (area_height / 8) : (area_height / 8 + 1)) * area_width;
  UBYTE BlackImage[Imagesize]={};

  Paint_NewImage(BlackImage, area_height, area_width, ROTATE_270, WHITE);
  Paint_Clear(WHITE);
  Paint_SetMirroring(MIRROR_VERTICAL); 
  // Paint_DrawString_EN(0, 0, "123456789", &Font20, BLACK, WHITE);
  Paint_DrawImage(gImage_header_cloud, 0, x, 32, 100);

  // for (size_t i = 296; i >= 100; i-=10)
  // {
    EPD_Dis_Part(0, 296, BlackImage, area_height, area_width); 
    // delay(1000);
  // }
}

void EPD_2in9_draw_weather(weather_info_t *w)
{
  int area_height = 48;
  int area_width = 296;
  UWORD Imagesize = ((area_height % 8 == 0) ? (area_height / 8) : (area_height / 8 + 1)) * area_width;
  UBYTE BlackImage[Imagesize]={};

  Paint_NewImage(BlackImage, area_height, area_width, ROTATE_270, WHITE);
  Paint_Clear(WHITE);
  Paint_SetMirroring(MIRROR_VERTICAL); 

  for (int i = 0; i < w_codes_len; ++i)
  {
    for (int j = 0; j < CODE_MAP_MAX; ++j)
    {
      for (int k = 0; k < 3; ++k)
      {
        weather_t ww = w->weathers[k];
        int start_pic_x, start_pic_y;
        int start_temp_low_x, start_temp_low_y;
        int start_temp_high_x, start_temp_high_y;
        sFONT ff = Font16;
        unsigned char *buf = w_codes[i].code_pic_48;
        int bufS = 48;

        if (w_codes[i].code[j] == ww.code + 1)
        { //. matched
          if (k == 0)
          {
            start_pic_x = 0;
            start_pic_y = 0;
            start_temp_low_x = 100;
            start_temp_low_y = 30;
            start_temp_high_x = 100;
            start_temp_high_y = 5;
          }
          else if (k == 1)
          {
            start_pic_x = 0;
            start_pic_y = 120;
            start_temp_low_x = 170;
            start_temp_low_y = 30;
            start_temp_high_x = 170;
            start_temp_high_y = 5;
          }
          else if (k == 2)
          {
            start_pic_x = 0;
            start_pic_y = 200;
            start_temp_low_x = 250;
            start_temp_low_y = 30;
            start_temp_high_x = 250;
            start_temp_high_y = 5;
          }

          printf("pick  %d \r\n", w_codes[i].code[j]);
          Paint_DrawImage(buf, start_pic_x, start_pic_y, bufS, bufS);

          Paint_DrawString_EN(start_temp_low_x, start_temp_low_y, ww.temp_low, &ff, WHITE, BLACK);
          Paint_DrawString_EN(start_temp_high_x, start_temp_high_y, ww.temp_high, &ff, WHITE, BLACK);
          // Paint_DrawString_EN(50, 5, w->weathers[0].date, &Font12, WHITE, BLACK);
          // Paint_DrawString_EN(50, 25, w->weathers[0].temp, &Font12, WHITE, BLACK);
        }
      }
    }
  }

  EPD_Dis_Part(45, 296, BlackImage, area_height, area_width); 
}
