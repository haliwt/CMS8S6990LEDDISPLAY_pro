#ifndef __LED_H__
#define __LED_H__
#include "tm1650_i2c.h"


extern volatile uint8_t DispData[3];//显示LED位数


//extern const uint8_t seg[];


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




void LEDDisplay_Function(void);
void LEDDisplay_TimerTim(void );








#endif 