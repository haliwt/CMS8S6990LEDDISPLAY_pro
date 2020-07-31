
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
	
	GPIO_Config();
	I2C_Config();							/*设置I2C主控模式*/		
	LED_GPIO_Init();
	UART0_Config();
	
	printf("CMS8S6990 Test........\n\r");
								
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
   LEDDisplay_TimerTim();
   LEDDisplay_SleepLamp();

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
	uint8_t bcc_data;
  uint8_t senddata[4];       // 待检查数据
    
   Telecom->setWind_levels |=Telecom->setWind_levels <<0; //风速4档，睡眠风速，中速风速，高速风速 自动风速
    
	Telecom->power_state |= Telecom->power_state << 0;       //电源开关量
	
    Telecom->runstart  |=Telecom->runstart<<2;             //电机开启开关量

	senddata[0]=Telecom->power_state |Telecom->runstart;  //head code 8bit
	senddata[1]=0x0; 														           //wind speed of code hig code 8bit
	senddata[2]=Telecom->setWind_levels;										//wind speed of code low code 8 bit
	
   
  bcc_data=BCC(senddata,3);
	senddata[3]=bcc_data;

	UART_SendBuff(UART0,  senddata[0]); //头码
	UART_SendBuff(UART0,  senddata[1]); //风速码 高8bit
	UART_SendBuff(UART0,  senddata[2]); //风速码 低8bit
	UART_SendBuff(UART0,  senddata[3]); //校验码

	
}























