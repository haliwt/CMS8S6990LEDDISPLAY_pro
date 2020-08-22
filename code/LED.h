#ifndef __LED_H__
#define __LED_H__
#include "tm1650_i2c.h"
#include "key.h"

#define PI   P24
#define PJ   P25
#define PK   P26
#define PL   P30

#define COM5   P31    //5i
#define COM6   P32   //6i
#define COM7   P36   //7i
#define COM8   P05   //8i


#define LED0   P24 
#define LED1   P25

//extern volatile uint8_t DispData[3];//显示LED位数
#define		BitSET(x,y)		x|=(1<<y)				//置1
#define		BitCLR(x,y)		x&=~(1<<y)				//置0

//extern const uint8_t seg[];

#define  TM1650_OFF_DIS    0x00        //关闭显示

#define  TM1650_8_DIS      0x01          //开显示，8段显示方式，显示亮度级别8 -亮度低
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
#if 0 
                            //                a
#define  seg_a 0x10          //            ---------
#define  seg_b 0x20          //           |         |
#define  seg_c 0x40          //         f |         | b
#define  seg_d 0x08          //           |    g    |
#define  seg_e 0x04          //            ---------
#define  seg_f 0x01          //           |         |
#define  seg_g 0x02          //         e |         | c
#define  seg_h 0x80          //           |    d    |
                                          ----------- -h (小数点)

#endif 

#define   seg_a  0x01       //seg_a   //seg_e = 0x10
#define   seg_b  0x02      //seg_b , //seg_f = 0x20
#define   seg_c  0x04      //seg_c , //seg_g = 0x40
#define   seg_d  0x08      //seg_d , //seg_d = 0x08
#define   seg_e  0x10      //seg_e , //seg_c = 0x04
#define   seg_f  0x20      //seg_f   //seg_a = 0x01
#define   seg_g  0x40      //seg_g   //seg_b = 0x02 
#define   seg_h  0x80      //

extern const unsigned char segNumber[];
        



void LED_GPIO_Init(void);
void LEDDisplay_SleepLamp(void);
void LEDDisplay_TimerTim(void );
void LEDDisplay_RedColorRing(void);
void LEDDisplay_GreenColorRing(void);
//void LEDDisplay_BlueColorRing(void);

void TM1650_FULL_DISP(void);








#endif 