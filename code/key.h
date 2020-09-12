#ifndef __KEY_H__
#define __KEY_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s6990.h"

#include <stdio.h>
#include "led.h"
#include "demo_buzzer.h"
#include "demo_timer.h"
#include "myflash.h"
#include "buzzer.h"
#include "output.h"



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


#define  POWER_KEY      P17
#define  WIND_KEY       P16
#define  TIMER_KEY      P15
#define  FILTER_KEY     P14 

//通讯参数
typedef struct _TELEC_
{
    int8_t TimeBaseUint;    //
    
    uint8_t TimeHour ;
    uint8_t TimeMinute;

    uint8_t TimerEvent ;                  //定时器通知信号
   
    uint8_t WindSelectLevel ;

    uint8_t receChilddata;
 
    uint8_t PowerOnFrequency:1 ;          //开关机的次数
	uint8_t power_state :1;               //开启电源
	uint8_t childLock : 1;
	uint8_t TimerFlg:1;

    uint8_t TimerOn:1;
	uint8_t keyEvent:1;
    uint8_t WindSetupLevel: 3;
	uint8_t timer_state: 1;
	uint8_t net_state:1;
	uint8_t net_dispnumb : 1;

	uint8_t lockSonudKey :1;
	uint8_t ISR_NetRecMinuteAdj:1;
	uint8_t ISR_NetRecHourAdj:1;
	
	
	
} Telec;

extern Telec Telecom;

//extern uint8_t NetKeyNum;
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



void WindLevel_Data(void);
void Net_Data(void);
void Timer_Data(void);


#endif /* __DEMO_GPIO_H__ */






