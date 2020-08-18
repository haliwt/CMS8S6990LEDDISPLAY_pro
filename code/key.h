#ifndef __KEY_H__
#define __KEY_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s6990.h"
#include "tm1650_i2c.h"
#include <stdio.h>

//typedef __IO uint16_t vu16;
typedef volatile  unsigned char   vu8;


#define  POWER_KEY      P16  //0
#define  WIND_KEY       P15  //1
#define  TIMER_KEY      P14  //2
#define  FILTER_KEY     P13  //3

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
	
} Telec;

extern Telec *Telecom;

enum WindSpeed{wind_sleep,wind_middle,wind_high,wind_auto};




//根据需求可修改定义如下参数.
#define TICKS_INTERVAL    	5				//ms,　后台调用间隔时间
#define DEBOUNCE_TICKS    	4				//消除抖动次数，即时长至少为5ms*4
#define NORMAL_SCAN_FREQ    6   //正常情况下扫键频率因子，如为6则表示稳定后扫键周期为6*TICKS_INTERVAL＝30ms
#define SHORT_TICKS       	(300 /TICKS_INTERVAL)  //短按时间定义300ms
#define LONG_TICKS        	(1200 /TICKS_INTERVAL) //长按时间定义1200ms
#define KEYBUFFSIZE					8  //按键缓存FIFO深度，定义保存16个键值

//***************** 以下与具体系统的硬件相关 ********************************************
#define 	KeyNumMax					4			//硬件实体按键数量
typedef		unsigned char			KeyS_Type;    //键态字类型定义（根据按键总数定义足够长度的数据类型，
//本例程只有4个键，用uint8_t足矣，但为扩充方便这里用了u16，最大可满足16键,大于16键时请定义为u32）
//按键硬件读端口位置
#define KEY0_IN  	P16//PCin(1)			POWER_KEY//按键0输入端口
#define KEY1_IN  	P15//PCin(13)			WIND_KEY//按键1输入端口
#define KEY2_IN  	P14//PEin(2)			TIMER_KEY //按键2输入端口 
#define KEY3_IN 	P13//PAin(0)			FILTER_KEY//按键3输入端口(WK_UP)  

//硬件实体按键编号，键态字KeyS_Type依此顺序按位组合，每BIT位对应一个实体按键
#define POWER_PRES 		0x01     //POWER_KEY
#define WIND_PRES 		0x02     //WIND_KEY
#define TIMER_PRES     	0x04   //TIMER_KEY
#define FILTER_PRES 	0x08   //FILTER_KEY



//************ 以下基本与硬件无关（除增删组合键码定义外一般无须修改） *********************

//定义一个特殊值用于复位状态机
#define KB_CLR			44


//这里可以定义一些特殊键码（如组合键等）
#define WKUP_PLUSKEY0_PRES	1							//示例：WKUP+KEY0组合按键（先按下WKUP再按下KEY0）


//功能键值输出：
#define KEYOUT_BASE_DEF					10*(KeyNum+2) //为保留组合键值等空间，这里定义为20以上，可视情修改）

#define KEY_EVENT(m,n)					(uint8_t)(10*(m+2)+n) 		//按键事件(即键值)宏定义
//有了上述宏定义后，无须再为各个按键单独写宏定义，使用KEY_EVENT(键编号,键值事件)就可以代表特定按键事件了。
//例如：用KEY_EVENT(KB_WKUP,DOUBLE_CLICK)就表示了WKUP键双击的键值（或称事件值）


//状态机键值事件宏定义如下：
#define NONE_PRESS				0
#define PRESS_UP				1
#define PRESS_DOWN				2
#define SINGLE_CLICK			3
#define DOUBLE_CLICK			4
#define LONG_RRESS_START	5
#define LONG_PRESS_HOLD		6


//按键已经全部释放
#define KEY_RELEASED 				(Cont==0)  //简化的条件
//#define KEY_RELEASED 				(Cont==0 && Trg==0) //严格的条件



/**************数据和函数接口声明*******************/
extern KeyS_Type Trg;
extern KeyS_Type Cont;
extern uint16_t KeyTime;


void KEY_Init(void);//键硬件IO端口初始化，由主函数调用
void GetAndSaveKey(void);//本函数由SYSTICK调用，在后台读键，如果有键值则存入按键缓冲区
uint8_t Read_A_Key(void);//读取按键值：由系统主循环调用。
void Key_Scan_Stick(void);//本函数由SYSTICK调用，在后台扫描按键获取消除抖动后的稳定键值
uint8_t Get_Key_State(uint8_t KeyNum);//按键状态机，本函数一般由Get_Key()内部调用
void SysTick_Handler(void); //按键扫描时间，设置

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
void KEY_FUNCTION(void);



#endif /* __DEMO_GPIO_H__ */






