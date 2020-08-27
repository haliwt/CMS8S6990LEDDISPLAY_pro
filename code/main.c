
#include "cms8s6990.h"
#include "demo_timer.h"
#include "demo_buzzer.h"
#include "timer0.h"
#include "key.h"
#include "led.h"
#include "tm1650_i2c.h"


uint32_t Systemclock = 24000000;

void TaskLEDDisplay(void);
void TaskKeySan(void);
void TaskReceiveAirSensor(void);
void TaskTelecStatus(void);
void TaskProcess(void);


TASK_COMPONENTS TaskComps[TASK_NUM]={

    {0, 150, 150, TaskLEDDisplay},           // 显示数字 15ms = 100us * 10 *15，扫描一次
    {0, 50, 50, TaskKeySan},              // 按键扫描 10ms=100us * 10* 2扫描一次
    {0, 400, 400, TaskReceiveAirSensor},     // 接收到空气传感器   40ms = 100us * 10* 40 执行一次
    {0, 10000, 10000, TaskTelecStatus}       // 同主板通讯 1.0s= 100us * 10000  执行一次 

};

/*******************************************************
	*
	*Function Name: int main(void)
	*
	*
	*
*******************************************************/
int main(void)
{		
	uint8_t poweron=0;
    TMR1_Config();
	TMR0_Config();
    GPIO_Config();
    LED_GPIO_Init();
	IIC_Init_TM1650();
    Init_Tm1650();

	while(1)
	{	
	 
        
       
		if(childLock  ==1){
            if(BuzzerSound==1){
                 BUZZER_Config();
				delay_20us(10000);
	           DisableBUZZER_Config();
               BuzzerSound =0;
               
            }
         TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
									
								    TM1650_Set(0x6A,segNumber[1]);//初始化为5级灰度，开显示
				LockKey_Function();					
        
        }
        if(childLock  ==0){
            if(BuzzerSound==1){
                    BUZZER_Config();
				delay_20us(10000);
	           DisableBUZZER_Config();
               BuzzerSound =0;
            }
           
             KEY_Handing();
        
        }
		
    
	}		
}


/***********************************************************
	*
	*Function Name: void TaskProcess(void)
	*Function : process
	*Input Ref:No
	*Output Ref:No
	*
***********************************************************/
void TaskProcess(void)
{
	uint8_t i=0;
    for (i=0; i<TASKS_MAX; i++)           // 逐个任务轮询时间处理
    {
      
			if(TaskComps[i].Run)           // 时间不为0
        {
             TaskComps[i].TaskHook();         // 运行任务
             TaskComps[i].Run = 0;  // 标志清0
					   
					   
        }
    }

}
/***********************************************************
	*
	*Function Name: void TaskDisplayClock(void)
	*Function : display LED numbers
	*Input Ref:No
	*Output Ref:No
	*
***********************************************************/
void TaskLEDDisplay(void)
{
   
	TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
	TM1650_Set(0x68,segNumber[9]);//³õÊ¼»¯Îª5¼¶»Ò¶È£¬¿ªÏÔÊ¾
   	TM1650_Set(0x6A,segNumber[1]);//³õÊ¼»¯Îª5¼¶»Ò¶È£¬¿ªÏÔÊ¾
	TM1650_Set(0x6C,segNumber[2]);//³õÊ¼»¯Îª5¼¶»Ò¶È£¬¿ªÏÔÊ¾
	TM1650_Set(0x6E,segNumber[3]);//³õÊ¼»¯Îª5¼¶»Ò¶È£¬¿ªÏÔÊ¾ 
	
	  

}
/***********************************************************
	*
	*Function Name: void TaskKeySan(void)
	*Function : Toch key scan 
	*Input Ref:No
	*Output Ref:No
	*
***********************************************************/
void TaskKeySan(void)
{
	
    KEY_HDScan(1);
    KEY_Handing();
	
	
	
}
/***********************************************************
	*
	*Function Name: void TaskReceiveIR(void)
	*Function : receive IR logic level
	*Input Ref:No
	*Output Ref:No
	*
***********************************************************/
void TaskReceiveAirSensor(void)
{
    #if 0
	TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
	TM1650_Set(0x68,segNumber[9]);//³õÊ¼»¯Îª5¼¶»Ò¶È£¬¿ªÏÔÊ¾
   	TM1650_Set(0x6A,segNumber[4]);//³õÊ¼»¯Îª5¼¶»Ò¶È£¬¿ªÏÔÊ¾
	TM1650_Set(0x6C,segNumber[5]);//³õÊ¼»¯Îª5¼¶»Ò¶È£¬¿ªÏÔÊ¾
	TM1650_Set(0x6E,segNumber[6]);//³õÊ¼»¯Îª5¼¶»Ò¶È£¬¿ªÏÔÊ¾ 
   #endif 
	

}
/***********************************************************************************************
	*
	*Function Name: void TaskTelecStatus(void)
	*Function : ommunicate serial baud rate =9600bps
	*Input Ref:No
	*Output Ref:No
	*
*************************************************************************************************/
void TaskTelecStatus(void)
{
  
	  
	
}



















