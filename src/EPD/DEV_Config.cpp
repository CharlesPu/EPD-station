/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-02-19
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "DEV_Config.h"
//#include <SPI.h>

int EPD_SCK_PIN;
int EPD_MOSI_PIN;
int EPD_CS_PIN;
int EPD_RST_PIN;
int EPD_DC_PIN;
int EPD_BUSY_PIN;

void EPD_SPI_init(epd_gpio_t* g){
//	pinMode(g->BUSY_Pin, INPUT); 
//	pinMode(g->RES_Pin, OUTPUT);  
//	pinMode(g->DC_Pin, OUTPUT);    
//	pinMode(g->CS_Pin, OUTPUT);    
//	//SPI
//	//	 SPI.beginTransaction(SPISettings(6000000, MSBFIRST, SPI_MODE0)); 
//	//	 SPI.begin ();	
//
//	SPI.begin(g->SCL_Pin, 0, g->SDI_Pin, 0);	//初始化，并绑定引脚;0为忽略
//	SPI.setFrequency(6000000);					//设置频率，6MHz
//	SPI.setBitOrder(SPI_MSBFIRST);				 //设置高位bit先传输
//	SPI.setDataMode(SPI_MODE0);    
}

void GPIO_Config(void)
{
    pinMode(EPD_BUSY_PIN,  INPUT);
    pinMode(EPD_RST_PIN , OUTPUT);
    pinMode(EPD_DC_PIN  , OUTPUT);
    
    pinMode(EPD_SCK_PIN, OUTPUT);
    pinMode(EPD_MOSI_PIN, OUTPUT);
    pinMode(EPD_CS_PIN , OUTPUT);

    digitalWrite(EPD_CS_PIN , HIGH);
    digitalWrite(EPD_SCK_PIN, LOW);
}

void GPIO_Mode(UWORD GPIO_Pin, UWORD Mode)
{
    if(Mode == 0) {
        pinMode(GPIO_Pin , INPUT);
	} else {
		pinMode(GPIO_Pin , OUTPUT);
	}
}
/******************************************************************************
function:	Module Initialize, the BCM2835 library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
UBYTE DEV_Module_Init(epd_gpio_t* g)
{
	EPD_SCK_PIN = g->SCL_Pin;
	EPD_MOSI_PIN = g->SDI_Pin;
	EPD_CS_PIN = g->CS_Pin;
	EPD_RST_PIN= g->RES_Pin;
	EPD_DC_PIN= g->DC_Pin;
	EPD_BUSY_PIN= g->BUSY_Pin;
	
	//gpio
	GPIO_Config();

	//serial printf
//	Serial.begin(115200);

	// spi
	// SPI.setDataMode(SPI_MODE0);
	// SPI.setBitOrder(MSBFIRST);
	// SPI.setClockDivider(SPI_CLOCK_DIV4);
	// SPI.begin();
	
//	SPI.begin(g->SCL_Pin, 0, g->SDI_Pin, 0);	//初始化，并绑定引脚;0为忽略
//	SPI.setFrequency(6000000);					//设置频率，6MHz
//	SPI.setBitOrder(SPI_MSBFIRST);				 //设置高位bit先传输
//	SPI.setDataMode(SPI_MODE0);  

	return 0;
}

/******************************************************************************
function:
			SPI read and write
******************************************************************************/
void DEV_SPI_WriteByte(UBYTE data)
{
//	digitalWrite(EPD_CS_PIN, GPIO_PIN_RESET);
//	SPI.transfer(data);
//	digitalWrite(EPD_CS_PIN, GPIO_PIN_SET);
//	return;

    //SPI.beginTransaction(spi_settings);
    digitalWrite(EPD_CS_PIN, GPIO_PIN_RESET);

    for (int i = 0; i < 8; i++)
    {
        if ((data & 0x80) == 0) digitalWrite(EPD_MOSI_PIN, GPIO_PIN_RESET); 
        else                    digitalWrite(EPD_MOSI_PIN, GPIO_PIN_SET);

        data <<= 1;
        digitalWrite(EPD_SCK_PIN, GPIO_PIN_SET);     
        digitalWrite(EPD_SCK_PIN, GPIO_PIN_RESET);
    }

    //SPI.transfer(data);
    digitalWrite(EPD_CS_PIN, GPIO_PIN_SET);
    //SPI.endTransaction();	
}

UBYTE DEV_SPI_ReadByte()
{
    UBYTE j=0xff;
    GPIO_Mode(EPD_MOSI_PIN, 0);
    digitalWrite(EPD_CS_PIN, GPIO_PIN_RESET);
    for (int i = 0; i < 8; i++)
    {
        j = j << 1;
        if (digitalRead(EPD_MOSI_PIN))  j = j | 0x01;
        else                            j = j & 0xfe;
        
        digitalWrite(EPD_SCK_PIN, GPIO_PIN_SET);     
        digitalWrite(EPD_SCK_PIN, GPIO_PIN_RESET);
    }
    digitalWrite(EPD_CS_PIN, GPIO_PIN_SET);
    GPIO_Mode(EPD_MOSI_PIN, 1);
    return j;
}

void DEV_SPI_Write_nByte(UBYTE *pData, UDOUBLE len)
{
    for (int i = 0; i < len; i++)
        DEV_SPI_WriteByte(pData[i]);
}
