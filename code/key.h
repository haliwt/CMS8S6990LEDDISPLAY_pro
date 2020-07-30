#ifndef __KEY_H__
#define __KEY_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s6990.h"
#include "tm1650_i2c.h"

//通讯参数
typedef struct _TELEC_
{
	uint8_t getTimerSecond ;
	uint8_t TimerEvent :1;                    //定时器通知信号
    int16_t  showtimes;                 //显示时间，数据，按键输入
    uint8_t getTimerHour;                 //定时器时间小时
	uint8_t setWind_levels :3 ;              //设置风扇的级别，共4级 睡眠，中速风，高速风，自动
	uint8_t runstart:1;
	uint8_t power_state :1;               //开启电源
	uint8_t setTimerValue ;               //设置定时时间的值
	
}Telec;

extern Telec Telecom;

enum WindSpeed{wind_sleep,wind_middle,wind_high,wind_auto};
/******************************************************************************
 ** \brief	 GPIO_Config
 ** \param [in] 
 **            	
 ** \return  none
 ** \note  
 ******************************************************************************/
void delay_10us(uint16_t n) ;
void GPIO_Config(void);
void KEY_FUNCTION(void);


#endif /* __DEMO_GPIO_H__ */






