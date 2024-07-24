#include "EPD_2in9.h"
#include "Debug.h"

////IO settings
//int BUSY_Pin = 14; 
//int RES_Pin = 15; 
//int DC_Pin = 16; 
//int CS_Pin = 17; 
//int SCK_Pin =18; 
//int SDI_Pin =19; 
//
//
//#define EPD_W21_MOSI_0  digitalWrite(SDI_Pin,LOW)
//#define EPD_W21_MOSI_1  digitalWrite(SDI_Pin,HIGH) 
//
//#define EPD_W21_CLK_0 digitalWrite(SCK_Pin,LOW)
//#define EPD_W21_CLK_1 digitalWrite(SCK_Pin,HIGH)

#define EPD_W21_CS_0 digitalWrite(EPD_CS_PIN,LOW)
#define EPD_W21_CS_1 digitalWrite(EPD_CS_PIN,HIGH)

#define EPD_W21_DC_0  digitalWrite(EPD_DC_PIN,LOW)
#define EPD_W21_DC_1  digitalWrite(EPD_DC_PIN,HIGH)

#define EPD_W21_RST_0 digitalWrite(EPD_RST_PIN,LOW)
#define EPD_W21_RST_1 digitalWrite(EPD_RST_PIN,HIGH)

#define isEPD_W21_BUSY digitalRead(EPD_BUSY_PIN)
//296*128///////////////////////////////////////

#define MONOMSB_MODE 1
#define MONOLSB_MODE 2 
#define RED_MODE     3

#define MAX_LINE_BYTES EPD_2IN9_WIDTH/8 // =128/8 =16
#define MAX_COLUMN_BYTES  EPD_2IN9_HEIGHT // 296

#define ALLSCREEN_GRAGHBYTES  4736
//
//////////FUNCTION//////
////EPD

//
//
//
//
/////////////////////EXTERNAL FUNCTION////////////////////////////////////////////////////////////////////////
///////////////////////delay//////////////////////////////////////
void driver_delay_us(unsigned int xus)  //1us
{
  for(;xus>1;xus--);
}
void driver_delay_xms(unsigned long xms) //1ms
{  
    unsigned long i = 0 , j=0;

    for(j=0;j<xms;j++)
  {
        for(i=0; i<256; i++);
    }
}
void DELAY_S(unsigned int delaytime)     
{
//  delay(delaytime);
  int i,j,k;
  for(i=0;i<delaytime;i++)
  {
    for(j=0;j<4000;j++)           
    {
      for(k=0;k<222;k++);
                
    }
  }
}
////////////////////////SPI///////////////////////////////////
void SPI_Delay(unsigned char xrate)
{
  unsigned char i;
  while(xrate)
  {
    for(i=0;i<2;i++);
    xrate--;
  }
}


void SPI_Write(unsigned char value)                                    
{     
	DEV_SPI_WriteByte(value);

//    unsigned char i;  
//   SPI_Delay(1);
//    for(i=0; i<8; i++)   
//    {
//        EPD_W21_CLK_0;
//       SPI_Delay(1);
//       if(value & 0x80)
//          EPD_W21_MOSI_1;
//        else
//          EPD_W21_MOSI_0;   
//        value = (value << 1); 
//       SPI_Delay(1);
//       driver_delay_us(1);
//        EPD_W21_CLK_1; 
//        SPI_Delay(1);
//    }
}

void EPD_W21_WriteCMD(unsigned char command)
{
  SPI_Delay(1);
  EPD_W21_CS_0;                   
  EPD_W21_DC_0;   // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}

void EPD_W21_Writedatas(unsigned char data)
{
  SPI_Delay(1);
  EPD_W21_CS_0;                   
  EPD_W21_DC_1;   // command write
  SPI_Write(data);
  EPD_W21_CS_1;
}

///////////////////EPD settings Functions/////////////////////
//
///////////////////////////////////////LUT//////////////////////////////////////////////
const unsigned char LUT_datas[] PROGMEM= {    //30 bytes
0x50, //C221 25C Full update waveform
0xAA,
0x55,
0xAA,
0x11,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0xFF,
0xFF,
0x1F,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00
}; 
const unsigned char LUT_datas_part[] PROGMEM={  //30 bytes
0x10, //C221 25C partial update waveform
0x18,
0x18,
0x08,
0x18,
0x18,
0x08,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x13,
0x14,
0x44,
0x12,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00
};        
void EPD_select_LUT(const unsigned char * wave_datas)
{        
     unsigned char count;
     EPD_W21_WriteCMD(0x32);
   for(count=0;count<30;count++)
  EPD_W21_Writedatas(pgm_read_byte(&wave_datas[count]));

} 
//
///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
void EPD_HW_Init(void)
{
  EPD_W21_RST_0;  // Module reset      
  delay(1); //At least 10ms delay 
  EPD_W21_RST_1; 
  delay(1); //At least 10ms delay 

  EPD_W21_WriteCMD(0x01); //Driver output control      
  EPD_W21_Writedatas(0x27); //Y%256--->(295+1)=296
  EPD_W21_Writedatas(0x01); //Y%256 
  EPD_W21_Writedatas(0x00);
  
  EPD_W21_WriteCMD(0x0C); //softstart  
  EPD_W21_Writedatas(0xD7);   //is necessary
  EPD_W21_Writedatas(0xD6);   //is necessary
  EPD_W21_Writedatas(0x9D);  //is necessary

  EPD_W21_WriteCMD(0x2C);     //VCOM Voltage
  EPD_W21_Writedatas(0x9A);    

  EPD_W21_WriteCMD(0x3A);     //Dummy Line   
  EPD_W21_Writedatas(0x1A);    
  EPD_W21_WriteCMD(0x3B);     //Gate time 
  EPD_W21_Writedatas(0X08);  
  
  EPD_W21_WriteCMD(0x11); //datas entry mode       
  EPD_W21_Writedatas(0x01);

  EPD_W21_WriteCMD(0x3C); //BorderWavefrom
  EPD_W21_Writedatas(0x33);  

  EPD_W21_WriteCMD(0x44); //set Ram-X address start/end position   
  EPD_W21_Writedatas(0x00);
  EPD_W21_Writedatas(0x0F);    //0x0C-->(15+1)*8=128

  EPD_W21_WriteCMD(0x45); //set Ram-Y address start/end position          
  EPD_W21_Writedatas(0x27);   //Y%256--->(295+1)=296
  EPD_W21_Writedatas(0x01);  //Y%256 
  EPD_W21_Writedatas(0x00);
  EPD_W21_Writedatas(0x00); 

  EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
  EPD_W21_Writedatas(0x00);
  EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X127;    
  EPD_W21_Writedatas(0x27);  //Y%256 
  EPD_W21_Writedatas(0x01);  //Y/256 
  Epaper_READBUSY();
  EPD_select_LUT(LUT_datas); //LUT
  
}
//////////////////////////////All screen update////////////////////////////////////////////
void EPD_WhiteScreen_ALL(void)
{
   unsigned int i;
    EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     EPD_W21_Writedatas(pgm_read_byte(&gImage_1[i]));
   }
   EPD_Update();   
}

/////////////////////////////////////////////////////////////////////////////////////////
void EPD_Update(void)
{   
  EPD_W21_WriteCMD(0x22);  //Display Update Control
  EPD_W21_Writedatas(0xC4);   
  EPD_W21_WriteCMD(0x20);  //Activate Display Update Sequence
  Epaper_READBUSY();  

}

void EPD_DeepSleep(void)
{  
  EPD_W21_WriteCMD(0x10); //enter deep sleep
  EPD_W21_Writedatas(0x01); 
  delay(100);
}
void Epaper_READBUSY(void)
{ 
  while(1)
  {   //=1 BUSY
     if(isEPD_W21_BUSY==0) break;
  }  
}
/////////////////////////////Part update//////////////////////////////////////////////
void EPD_SetRAMValue_BaseMap( const unsigned char * datass)
{
  unsigned int i;   
  const unsigned char  *datass_flag; 
  unsigned int x_end,y_start1,y_start2,y_end1,y_end2;
  unsigned int x_start=0,y_start=296;
  unsigned int PART_COLUMN=296,PART_LINE=128;   
  datass_flag=datass;
  //FULL update
  EPD_HW_Init(); 
  EPD_W21_WriteCMD(0x24);   //Write Black and White image to RAM
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     EPD_W21_Writedatas(pgm_read_byte(&datass[i]));
   } 
  EPD_Update();  
  delay(100);  
  //PART update
  EPD_Part_Init();//Local initialization (the top left corner of the screen is the origin of the coordinates)
  datass=datass_flag;//Record array first address
  x_start=x_start/8;//Convert to byte
  x_end=(x_start+PART_LINE)/8-1; 
  
  y_start1=0;
  y_start2=y_start-1;
  if(y_start>=256)
  {
    y_start1=y_start2/256;
    y_start2=y_start2%256;
  }
  y_end1=0; //0
  y_end2=0; //0
  if(y_end2>=256)
  {
    y_end1=y_end2/256;
    y_end2=y_end2%256;    
  }   

  EPD_W21_WriteCMD(0x44);       // set RAM x address start/end, in page 35
  EPD_W21_Writedatas(x_start);    // RAM x address start at 00h;
  EPD_W21_Writedatas(x_end);    // RAM x address end at 0fh(15+1)*8->128 
  EPD_W21_WriteCMD(0x45);       // set RAM y address start/end, in page 35
  EPD_W21_Writedatas(y_start2);    // RAM y address start at 0127h;
  EPD_W21_Writedatas(y_start1);    // RAM y address start at 0127h;
  EPD_W21_Writedatas(y_end2);    // RAM y address end at 00h;
  EPD_W21_Writedatas(y_end1);    // ????=0 


  EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
  EPD_W21_Writedatas(x_start); 
  EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X127;    
  EPD_W21_Writedatas(y_start2);
  EPD_W21_Writedatas(y_start1);
  

   EPD_W21_WriteCMD(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {                         
     EPD_W21_Writedatas(pgm_read_byte(&datass[i]));
   } 
   EPD_Part_Update();
   delay(100); 
     
  datass=datass_flag;
  EPD_W21_WriteCMD(0x44);       // set RAM x address start/end, in page 35
  EPD_W21_Writedatas(x_start);    // RAM x address start at 00h;
  EPD_W21_Writedatas(x_end);    // RAM x address end at 0fh(15+1)*8->128 
  EPD_W21_WriteCMD(0x45);       // set RAM y address start/end, in page 35
  EPD_W21_Writedatas(y_start2);    // RAM y address start at 0127h;
  EPD_W21_Writedatas(y_start1);    // RAM y address start at 0127h;
  EPD_W21_Writedatas(y_end2);    // RAM y address end at 00h;
  EPD_W21_Writedatas(y_end1);    // ????=0 


  EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
  EPD_W21_Writedatas(x_start); 
  EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X127;    
  EPD_W21_Writedatas(y_start2);
  EPD_W21_Writedatas(y_start1);
  
   EPD_W21_WriteCMD(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {                         
     EPD_W21_Writedatas(pgm_read_byte(&datass[i]));
   }   
   
}

void EPD_Part_Init(void)
{
  EPD_HW_Init(); //Electronic paper initialization
  EPD_select_LUT(LUT_datas_part);

  //POWER ON
  EPD_W21_WriteCMD(0x22);  //Display Update Control
  EPD_W21_Writedatas(0xC0);   
  EPD_W21_WriteCMD(0x20);  //Activate Display Update Sequence
  Epaper_READBUSY();  
  
  EPD_W21_WriteCMD(0x3C); //BorderWavefrom
  EPD_W21_Writedatas(0x01);

}
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datass,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
  const unsigned char  *datass_flag; 
  unsigned int i;  
  unsigned int x_end,y_start1,y_start2,y_end1,y_end2;
  datass_flag=datass;//Record array first address
  x_start=x_start/8;//Convert to byte
  x_end=x_start+PART_LINE/8-1; 
  
  y_start1=0;
  y_start2=y_start-1;
  if(y_start>=256)
  {
    y_start1=y_start2/256;
    y_start2=y_start2%256;
  }
  y_end1=0;
  y_end2=y_start+PART_COLUMN-1;
  if(y_end2>=256)
  {
    y_end1=y_end2/256;
    y_end2=y_end2%256;    
  }   
  
  EPD_W21_WriteCMD(0x44);       // set RAM x address start/end, in page 35
  EPD_W21_Writedatas(x_start);    // RAM x address start at 00h;
  EPD_W21_Writedatas(x_end);    // RAM x address end at 0fh(15+1)*8->128 
  EPD_W21_WriteCMD(0x45);       // set RAM y address start/end, in page 35
  EPD_W21_Writedatas(y_start2);    // RAM y address start at 0127h;
  EPD_W21_Writedatas(y_start1);    // RAM y address start at 0127h;
  EPD_W21_Writedatas(y_end2);    // RAM y address end at 00h;
  EPD_W21_Writedatas(y_end1);    // ????=0 


  EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
  EPD_W21_Writedatas(x_start); 
  EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X127;    
  EPD_W21_Writedatas(y_start2);
  EPD_W21_Writedatas(y_start1);
  
  
   EPD_W21_WriteCMD(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {                         
     EPD_W21_Writedatas(pgm_read_byte(&datass[i]));
   } 
   EPD_Part_Update(); 
   
   
   datass=datass_flag;
  EPD_W21_WriteCMD(0x44);       // set RAM x address start/end, in page 35
  EPD_W21_Writedatas(x_start);    // RAM x address start at 00h;
  EPD_W21_Writedatas(x_end);    // RAM x address end at 0fh(15+1)*8->128 
  EPD_W21_WriteCMD(0x45);       // set RAM y address start/end, in page 35
  EPD_W21_Writedatas(y_start2);    // RAM y address start at 0127h;
  EPD_W21_Writedatas(y_start1);    // RAM y address start at 0127h;
  EPD_W21_Writedatas(y_end2);    // RAM y address end at 00h;
  EPD_W21_Writedatas(y_end1);    // ????=0 


  EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
  EPD_W21_Writedatas(x_start); 
  EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X127;    
  EPD_W21_Writedatas(y_start2);
  EPD_W21_Writedatas(y_start1);
  
  
   EPD_W21_WriteCMD(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {                         
     EPD_W21_Writedatas(pgm_read_byte(&datass[i]));
   } 

}

void EPD_Part_Update(void)
{
  EPD_W21_WriteCMD(0x22); 
  EPD_W21_Writedatas(0x04);   //different
  EPD_W21_WriteCMD(0x20); 
  Epaper_READBUSY();    
}


/////////////////////////////////Single display////////////////////////////////////////////////

void EPD_WhiteScreen_Black(void)

{
   unsigned int i,k;
    EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)
  for(k=0;k<296;k++)
  {
    for(i=0;i<16;i++)
    {
      EPD_W21_Writedatas(0x00);
      }
  }
    EPD_Update();
}

void EPD_WhiteScreen_White(void)

{
   unsigned int i,k;
    EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)
  for(k=0;k<296;k++)
  {
    for(i=0;i<16;i++)
    {
      EPD_W21_Writedatas(0xff);
      }
  }
  EPD_Update();
}



//////////////////////////////////END//////////////////////////////////////////////////

