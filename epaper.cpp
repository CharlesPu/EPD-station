#include "epaper.h"
#include "src/EPD/DEV_Config.h"
#include "src/EPD/EPD.h"
#include "src/EPD/GUI_Paint.h"
#include "ImageData.h"
#include "weather.h"

#include <stdlib.h>

epd_gpio_t epd_gpio = {
	.BUSY_Pin = 14, 
	.RES_Pin = 15,
	.DC_Pin = 16, 
	.CS_Pin = 17,
	.SCL_Pin = 18,
	.SDI_Pin = 19,
};

void EPD_4in2bc_weather(weather_info_t* w){
	printf("EPD_4IN2BC_test weather\r\n");
	DEV_Module_Init(&epd_gpio);

	printf("e-Paper Init and Clear...\r\n");
	EPD_4IN2BC_Init();
//	EPD_4IN2BC_Clear();
	DEV_Delay_ms(10);

	//Create a new image cache named IMAGE_BW and f ill it with white
	UBYTE *BlackImage, *RYImage; // Red or Yellow
	UWORD Imagesize = ((EPD_4IN2BC_WIDTH % 8 == 0) ? (EPD_4IN2BC_WIDTH / 8 ) : (EPD_4IN2BC_WIDTH / 8 + 1)) * EPD_4IN2BC_HEIGHT;
	if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
	  printf("Failed to apply for black memory...\r\n");
	  while(1);
	}
	if ((RYImage = (UBYTE *)malloc(Imagesize)) == NULL) {
	  printf("Failed to apply for red memory...\r\n");
	  while(1);
	}
	printf("NewImage:BlackImage and RYImage\r\n");
	Paint_NewImage(BlackImage, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, 0, WHITE);
	Paint_NewImage(RYImage, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, 0, WHITE);

	//Select Image
	for (int i = 0; i < 3; ++i)printf("----%s %s %d %s\r\n", w->weathers[i].date, w->weathers[i].text, w->weathers[i].code, w->weathers[i].temp);
	
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
	Paint_SelectImage(RYImage);
	Paint_Clear(WHITE);
	// draw back
	Paint_SelectImage(RYImage);
	Paint_DrawLine(10, 200, 390, 200, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
	Paint_DrawLine(200, 10, 200, 190, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
	Paint_DrawLine(210, 100, 390, 100, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
	
	EPD_4in2bc_weather_draw_w(w,BlackImage, RYImage);
	
	printf("EPD_Display\r\n");
	EPD_4IN2BC_Display(BlackImage, RYImage);
//	DEV_Delay_ms(20000);

#if 0   // show image for array    
	printf("show image for array\r\n");
	EPD_4IN2BC_Display(gImage_pu_wang_1, gImage_pu_wang_2);
	DEV_Delay_ms(2000);
#endif

#if 0   // Drawing on the image
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


void EPD_4in2bc_demo(void){
	printf("EPD_4IN2BC_test Demo\r\n");
	DEV_Module_Init(&epd_gpio);

	printf("e-Paper Init and Clear...\r\n");
	EPD_4IN2BC_Init();
	EPD_4IN2BC_Clear();
	DEV_Delay_ms(6000);

	//Create a new image cache named IMAGE_BW and fill it with white
	UBYTE *BlackImage, *RYImage; // Red or Yellow
	UWORD Imagesize = ((EPD_4IN2BC_WIDTH % 8 == 0) ? (EPD_4IN2BC_WIDTH / 8 ) : (EPD_4IN2BC_WIDTH / 8 + 1)) * EPD_4IN2BC_HEIGHT;
	if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
	  printf("Failed to apply for black memory...\r\n");
	  while(1);
	}
	if ((RYImage = (UBYTE *)malloc(Imagesize)) == NULL) {
	  printf("Failed to apply for red memory...\r\n");
	  while(1);
	}
	printf("NewImage:BlackImage and RYImage\r\n");
	Paint_NewImage(BlackImage, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, 0, WHITE);
	Paint_NewImage(RYImage, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, 0, WHITE);

	//Select Image
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
	Paint_SelectImage(RYImage);
	Paint_Clear(WHITE);

#if 1   // show image for array    
	printf("show image for array\r\n");
	EPD_4IN2BC_Display(gImage_pu_wang_1, gImage_pu_wang_2);
	DEV_Delay_ms(2000);
#endif

#if 0   // Drawing on the image
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


void EPD_2in9_demo(void){
	printf("EPD_2in9_test Demo\r\n");
	DEV_Module_Init(&epd_gpio);

	unsigned char fen_L,fen_H,miao_L,miao_H; 

    EPD_HW_Init(); //Electronic paper initialization
    EPD_WhiteScreen_ALL(); //Full screen refresh picture 1
    delay(3000);
    
//////////////////////Partial refresh digital presentation//////////////////////////////////////  

    EPD_SetRAMValue_BaseMap(gImage_basemap);  //Partial refresh background color
    EPD_Part_Init();//Local refresh initialization
    delay(100);
    EPD_Dis_Part(0,32,gImage_num1,32,32); //x,y,datas,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num2,32,32); //x,y,datas,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num3,32,32); //x,y,datas,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num4,32,32); //x,y,datas,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num5,32,32); //x,y,datas,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num6,32,32); //x,y,datas,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num7,32,32); //x,y,datas,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num8,32,32); //x,y,datas,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num9,32,32); //x,y,datas,resolution 32*32
   	delay(2000);   
  ////////////////////////////////////////////////////////////////////////  
      //Clean

    EPD_HW_Init();//Electronic paper initialization
    EPD_WhiteScreen_White();  //Show all white
    EPD_DeepSleep();  //Enter deep sleep,Sleep instruction is necessary, please do not delete!!!
}

void EPD_4in2bc_weather_draw_w(weather_info_t* w, uint8_t *BlackImage, uint8_t *RYImage){
	Paint_SelectImage(BlackImage);
	
	for (int i = 0; i < w_codes_len; ++i){
		for (int j = 0; j < CODE_MAP_MAX; ++j){

			for (int k = 0; k < 3; ++k){
				weather_t ww = w->weathers[k];
				int start_pic_x, start_pic_y;
				int start_temp_x, start_temp_y;
				int start_date_x, start_date_y;
				sFONT ff = Font24;
				unsigned char * buf = w_codes[i].code_pic_128;
				int bufS = 128;
				
				if (w_codes[i].code[j] == ww.code+1) { //. matched
					if (k == 0) {
						start_pic_x=40;start_pic_y=70;start_temp_x=90;start_temp_y=20;start_date_x=20;start_date_y=45;
					}else if (k == 1){
						start_pic_x=210;start_pic_y=30;start_temp_x=310;start_temp_y=30;start_date_x=280;start_date_y=60;
						ff = Font16;buf =w_codes[i].code_pic_48;bufS=48;
					}else if (k == 2){
						start_pic_x=210;start_pic_y=130;start_temp_x=310;start_temp_y=130;start_date_x=280;start_date_y=170;
						ff = Font16;buf =w_codes[i].code_pic_48;bufS=48;
					}
					
					printf("pick  %d \r\n", w_codes[i].code[j]);
					Paint_SelectImage(RYImage);
					Paint_DrawImage(buf, start_pic_x, start_pic_y, bufS, bufS);
					
					Paint_SelectImage(BlackImage);
					Paint_DrawString_EN(start_date_x, start_date_y, ww.date, &ff,WHITE, BLACK);
					Paint_DrawString_EN(start_temp_x, start_temp_y, ww.temp, &ff,WHITE, BLACK);
				}
			}	
		}
	}
}


