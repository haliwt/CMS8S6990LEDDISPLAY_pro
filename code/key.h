#ifndef __KEY_H__
#define __KEY_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s6990.h"
#include "tm1650_i2c.h"
#include <stdio.h>

#define POWER_PRES 	      1
#define WIND_PRES	      2
#define TIMER_PRES	      3
#define FILTER_PRES       4
#define WINDTI_PRES       5


#define		_KEY_ALL_OFF				0X1F

//普通按键按下值
#define		_KEY_TRG_1_POWER     			0x01  //电源普通按键按下---按键值
#define		_KEY_TRG_2_WIND     			0x02  //风速按键按下--按键值
#define		_KEY_TRG_3_TIMER     			0x04   //定时按键
#define		_KEY_TRG_4_FILTER     			0x08
#define		_KEY_TRG_5_WINDTI   			0x09

//长按按键检查 按键值或者组合按键值
#define		_KEY_CONT_1_POWER     	     0x81    //电源按键长按--按键值
#define		_KEY_CONT_2_WIND     		 0x82    //风速按键长按--按键值
#define		_KEY_CONT_3_TIMER     	     0x84    //定时按键长按 长按按键。
#define		_KEY_CONT_4_FILTER     	     0x88    //长按键 --设置滤网键
#define		_KEY_CONT_5_WINDTI     		 0x89


#define		_KEY_CONT_1     	    0x81    //按键计数值
#define		_KEY_CONT_2     		0x82
#define		_KEY_CONT_3     		0x84
#define		_KEY_CONT_4     	    0x88
#define		_KEY_CONT_5     		0x90

typedef  struct  _state_
{
 unsigned char         read;
 unsigned char         buffer;
 unsigned char         value;
 unsigned short int    on_time;
 unsigned short int    off_time;
 enum{
  start  = 0,
  first  = 1,
  second = 2,
  cont   = 3,
  end    = 4,
  finish = 5,
 }state;
}key_types;

 extern key_types key;


#define  POWER_KEY      P16
#define  WIND_KEY       P15
#define  TIMER_KEY      P14
#define  FILTER_KEY     P13 

//通讯参数
typedef struct _TELEC_
{
    uint8_t LockKey ;
	uint8_t TimerEvent :1;                    //定时器通知信号
    uint8_t  TaskCompileFlag : 1;             //任务完成标志位
    
	uint8_t setWind_levels :3 ;              //设置风扇的级别，共4级 睡眠，中速风，高速风，自动
	uint8_t runstart:1;					// 风扇开启
	uint8_t power_state :1;               //开启电源
	uint8_t setTimerValue ;               //设置定时时间的值
	uint8_t getTimerSecond ;
	uint8_t getTimerHour;                 //定时器时间小时
	int16_t  showtimes;                 //显示时间，数据，按键输入
	uint16_t PMaverageValue;          //PM sensor averageValue 
} Telec;

extern Telec Telecom;


/******************************************************************************
 ** \brief	 GPIO_Config
 ** \param [in] 
 **            	
 ** \return  none
 ** \note  
 ******************************************************************************/
void delay_30us(uint16_t n) ;
void delay_20us(uint16_t n) ;
void delay_us(uint16_t n)  ;
void GPIO_Config(void);
uint8_t KEY_FUNCTION(void);
uint8_t KEY_Scan(void);
void KEY_Handing(void);
uint8_t KEY_HDScan(uint8_t mode);
void LockKey_Function(void);


#endif /* __DEMO_GPIO_H__ */






