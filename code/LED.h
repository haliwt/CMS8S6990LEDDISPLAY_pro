#ifndef __LED_H__
#define __LED_H__
#include "tm1650_i2c.h"
#include "key.h"


//extern volatile uint8_t DispData[3];//显示LED位数
#define		BitSET(x,y)		x|=(1<<y)				//置1
#define		BitCLR(x,y)		x&=~(1<<y)				//置0

//extern const uint8_t seg[];

#define  TM1650_OFF_DIS    0x00        //关闭显示

#define  TM1650_8_DIS      0x01          //开显示，8段显示方式，显示亮度级别8 
#define  TM1650_1_DISP     0x11         //显示亮度级别 1
#define  TM1650_2_DISP     0x21         //显示亮度级别 2
#define  TM1650_3_DISP     0x31         //显示亮度级别 3
#define  TM1650_4_DISP     0x41         //显示亮度级别 4
#define  TM1650_5_DISP     0x51         //显示亮度级别 5
#define  TM1650_6_DISP     0x61         //显示亮度级别 6
#define  TM1650_7_DISP     0x71         //显示亮度级别 7




/*----TM1650 显示地址-----*/
#define  TM1650_COM4_ADDR		0x68        /*TM1650显示段选COM1，地址 低字节 和高字节*/
#define  TM1650_COM3_ADDR		0x6A        /*TM1650显示段选COM2，地址*/
#define  TM1650_COM2_ADDR		0x6C        /*TM1650显示段选COM3，地址*/
#define  TM1650_COM1_ADDR		0x6E        /*TM1650显示段选COM4，地址*/

/*---向TM1650显示,写关闭显示*/

#define  TM1650_8_NDIS      0x00          //关闭显示，8段显示方式，显示亮度级别8 
#define  TM1650_1_NDISP     0x10         //不显示亮度级别 1
#define  TM1650_2_NDISP     0x20         //不显示亮度级别 2
#define  TM1650_3_NDISP     0x30         //不显示亮度级别 3
#define  TM1650_4_NDISP     0x40         //不显示亮度级别 4
#define  TM1650_5_NDISP     0x50         //不显示亮度级别 5
#define  TM1650_6_NDISP     0x60         //不显示亮度级别 6
#define  TM1650_7_NDISP     0x70         //不显示亮度级别 7



/**************************************************
	*XinTong LED Display Data Data:2020.07.23

	    //                a
        //            ---------
        //           |         |
        //         f |         | b
        //           |    g    |
        //            ---------
        //           |         |
        //         e |         | c
        //           |    d    |
        //            ---------   O <- h
**************************************************/



void LED_GPIO_Init(void);
void LEDDisplay_Function(void);
void LEDDisplay_TimerTim(void );
void LEDDisplay_RedColorRing(void);
void LEDDisplay_GreenColorRing(void);
void LEDDisplay_BlueColorRing(void);








#endif 