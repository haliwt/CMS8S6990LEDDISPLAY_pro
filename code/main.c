
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "cms8s6990.h"
#include "timer0.h"
#include "demo_buzzer.h"
#include "key.h"
#include "tm1650_i2c.h"

 const uint8_t seg[]={

			0x3F,	// 0		
			0x06,	// 1		
			0x5B,	// 2		
			0x4F,	// 3		
			0x66,	// 4		
			0x6D,	// 5		
			0x7D,	// 6		
			0x07,	// 7		
			0x7F,	// 8		
			0x6F	// 9

};

void TaskLEDDisplay(void);
void TaskKeySan(void);
void TaskReceiveAirSensor(void);
void TaskTelecStatus(void);
void TaskProcess(void);


TASK_COMPONENTS TaskComps[TASK_NUM]={

    {0, 200, 200, TaskLEDDisplay},           // 显示数字 20ms = 100us * 10 *20，扫描一次
    {0, 40,  40, TaskKeySan},               // 按键扫描 4ms=100us * 10*4 扫描一次
    {0, 80, 80, TaskReceiveAirSensor},     // 接收到空气传感器   8ms = 100us * 80 执行一次
    {0, 100, 100, TaskTelecStatus}           // 同主板通讯 10ms = 100us * 100  执行一次 

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
    TMR0_Config();
    BUZZER_Config();
	
	GPIO_SET_MUX_MODE(P24CFG, GPIO_MUX_GPIO);
	GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_4);
	P24 =0;
	GPIO_Config();
	I2C_Config();							/*设置I2C主控模式*/		
								
  while(1)
	{	
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
	uint8_t i;
    for (i=0; i<TASKS_MAX; i++)           // 逐个任务轮询时间处理
    {
        if(TaskComps[i].Run)           // 时间不为0
        {
             TaskComps[i].TaskHook();         // 运行任务
             TaskComps[i].Run = 0;          // 标志清0
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
   TM1650_write_byte(TM1650_DIG1_ADDR ,seg);

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























