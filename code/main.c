
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "cms8s6990.h"
#include "timer0.h"
#include "demo_buzzer.h"
#include "key.h"
#include "tm1650_i2c.h"
#include "LED.h"
#include "telecuart.h"



void TaskLEDDisplay(void);
void TaskKeySan(void);
void TaskReceiveAirSensor(void);
void TaskTelecStatus(void);
void TaskProcess(void);


TASK_COMPONENTS TaskComps[TASK_NUM]={

    {0, 30, 30, TaskLEDDisplay},           // 显示数字 15ms = 100us * 10 *15，扫描一次
    {0, 20, 20, TaskKeySan},              // 按键扫描 10ms=100us * 10* 2扫描一次
    {0, 100, 100, TaskReceiveAirSensor},     // 接收到空气传感器   40ms = 100us * 10* 40 执行一次
    {0, 200, 200, TaskTelecStatus}       // 同主板通讯 1.0s= 100us * 10000  执行一次 

};
uint32_t Systemclock = 24000000;
/*****************************************************************************
 ** \brief	 main
 **
 ** \param [in]  none   
 **
 ** \return 0
 *****************************************************************************/
int main(void)
{		
  //  static uint8_t taskState =0;
	  
    TMR0_Config();
    BUZZER_Init();
    IIC_Init_TM1650();
	
	GPIO_Config();
								
	LED_GPIO_Init();
	UART0_Config();
	UART1_Config();
  Init_Tm1650();
  
							
  while(1)
	{
		
	//TaskKeySan();
	TaskProcess();

	   
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

  
	TM1650_Set(0x68,segNumber[0]);//初始化为5级灰度，开显示
   

	TM1650_Set(0x6A,segNumber[8]);//初始化为5级灰度，开显示


    TM1650_Set(0x6C,segNumber[7]);//初始化为5级灰度，开显示

	
   TM1650_Set(0x6E,segNumber[ 4]);//初始化为5级灰度，开显示

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
	Key_Scan_Stick();
	GetAndSaveKey();

    KEY_FUNCTION();
	 
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
 // BUZZER_Config();  
	P26=0;
	//Analysis_UART0_ReceiveData() ;
//	BUZZER_Config();
	TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示

  
	TM1650_Set(0x68,segNumber[0]);//初始化为5级灰度，开显示
   

	TM1650_Set(0x6A,segNumber[0]);//初始化为5级灰度，开显示


    TM1650_Set(0x6C,segNumber[0]);//初始化为5级灰度，开显示

	
   TM1650_Set(0x6E,segNumber[0]);//初始化为5级灰度，开显示
	

	

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
  P25=1;
 
 
  TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示

  
	TM1650_Set(0x68,segNumber[1]);//初始化为5级灰度，开显示
   

	TM1650_Set(0x6A,segNumber[1]);//初始化为5级灰度，开显示


    TM1650_Set(0x6C,segNumber[1]);//初始化为5级灰度，开显示

	
   TM1650_Set(0x6E,segNumber[1]);//初始化为5级灰度，开显示

  
	
}