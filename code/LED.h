#ifndef __LED_H__
#define __LED_H__

#include "key.h"



//extern volatile uint8_t DispData[3];//显示LED位数
#define		BitSET(x,y)		x|=(1<<y)				//置1
#define		BitCLR(x,y)		x&=~(1<<y)				//置0












extern const unsigned char segNumber[];
        



void LED_GPIO_Init(void);
void LEDDisplay_SleepLamp(void);
void LEDDisplay_TimerTim(void );
void LEDDisplay_RedColorRing(void);
void LEDDisplay_GreenColorRing(void);
//void LEDDisplay_BlueColorRing(void);









#endif 