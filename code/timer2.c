
#include "timer2.h"


/******************************************************************************
** \brief	 TMR2_Config
** \param [in] 
**            	
** \return  none
** \note  
******************************************************************************/
void TMR2_Config(uint8_t windl)
{
	/*
	(1)设置运行模式
	*/
	TMR2_ConfigRunMode(TMR2_MODE_TIMING, TMR2_LOAD_DISBALE);
	
	TMR2_EnableCompare(TMR2_CC1,TMR2_CMP_MODE_0);		
		
	
	/*
	(2)设置时钟
	*/
	TMR2_ConfigTimerClk( TMR2_CLK_DIV_12);						/*Fsys = 24Mhz->Ftimer = 2Mhz,Ttmr=0.5us*/
	/*
	(3)设置周期	
	*/	

	 TMR2_ConfigTimerPeriod((65536 - 40000)); 		//20ms	
	/*
	(4)设置比较值
	*/
	 if(windl==0)
	 	 TMR2_ConfigCompareValue(TMR2_CC1,(65536-0)); //输出占空比 99.83%
     else if(windl==1)
	   TMR2_ConfigCompareValue(TMR2_CC1,(65536-300)); //输出占空比 2%， 风速-----1档
	 else if(windl==2)
	 	TMR2_ConfigCompareValue(TMR2_CC1,(65536-500)); //输出占空比：占空比 4%  ----风速2档
     else if(windl==3)
	 	TMR2_ConfigCompareValue(TMR2_CC1,(65536-1000)); //输出占空比 7% ------风速3档
    

	/*
	(5)设置中断
	*/
	TMR2_EnableOverflowInt();

	TMR2_EnableCompareInt(TMR2_CC1);	
	
			
	TMR2_ConfigCompareIntMode(TMR2_CMP_INT_MODE0);		
	/*
	(6)设置优先级
	*/		
	IRQ_SET_PRIORITY(IRQ_TMR2,IRQ_PRIORITY_LOW);	
	TMR2_AllIntEnable();
	IRQ_ALL_ENABLE();	
	
	/*
	(7)设置IO复用
	*/	

    //GPIO_SET_MUX_MODE(P01CFG, GPIO_MUX_CC1); //配置GPIO口复用,P01
    GPIO_SET_MUX_MODE(P04CFG, GPIO_MUX_CC1); //配置GPIO口复用,P04 --tm1629d

	/*
	(8开启Tiemr2
	*/
	TMR2_Start();
}




























