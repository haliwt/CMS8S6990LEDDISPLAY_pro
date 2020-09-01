#include "timer0.h"


/******************************************************************************
** \brief	 TMR0_Config
** \param [in] 
**            	
** \return  none
** \note  
******************************************************************************/
void TMR0_Config(void)
{
	/*
	(1)设置Timer的运行模式
	*/
	TMR_ConfigRunMode(TMR0, TMR_MODE_TIMING,TMR_TIM_AUTO_8BIT);	
	/*
	(2)设置Timer 运行时钟
	*/
	TMR_ConfigTimerClk(TMR0, TMR_CLK_DIV_12);						/*Fsys = 24Mhz，Ftimer = 2Mhz,Ttmr=0.5us*/
	/*
	(3)设置Timer周期
	*/	
	TMR_ConfigTimerPeriod(TMR0, 256-200, 256-200); 				// (256-200)*0.5us = 100us,递增计数
		
	/*
	(4)开启中断
	*/
	TMR_EnableOverflowInt(TMR0);

	/*
	(5)设置Timer中断优先级
	*/	
	IRQ_SET_PRIORITY(IRQ_TMR0,IRQ_PRIORITY_LOW);
	IRQ_ALL_ENABLE();	

	/*
	(6)开启Timer
	*/
	TMR_Start(TMR0);
}



















