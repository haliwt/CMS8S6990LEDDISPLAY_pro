
#include "timer2.h"


/******************************************************************************
** \brief	 TMR2_Config
** \param [in] 
**            	
** \return  none
** \note  
******************************************************************************/
void TMR2_Config(void)
{
	/*
	(1)设置Timer的运行模式
	*/
	TMR2_ConfigRunMode(TMR2_MODE_TIMING, TMR2_LOAD_DISBALE);
	TMR2_EnableCapture(TMR2_CC0, TMR2_CAP_EDGE_RISING);
	TMR2_EnableCapture(TMR2_CC1, TMR2_CAP_EDGE_RISING);	
	TMR2_EnableCapture(TMR2_CC2, TMR2_CAP_EDGE_RISING);	
	TMR2_EnableCapture(TMR2_CC3, TMR2_CAP_EDGE_RISING);	
		
	/*
	(2)设置Timer 运行时钟
	*/
	TMR2_ConfigTimerClk( TMR2_CLK_DIV_12);						/*Fsys = 24Mhz，Ftimer = 2Mhz,Ttmr=0.5us*/
	/*
	(3)设置Timer周期
	*/	
	TMR2_ConfigTimerPeriod((65536 - 20000)); 			//10ms
		
	/*
	(5)开启中断
	*/
	TMR2_EnableOverflowInt();
	TMR2_EnableCaptureInt(TMR2_CC0);
	TMR2_EnableCaptureInt(TMR2_CC1);	
	TMR2_EnableCaptureInt(TMR2_CC2);	
	TMR2_EnableCaptureInt(TMR2_CC3);	
	
	/*
	(6)设置Timer中断优先级
	*/	
	IRQ_SET_PRIORITY(IRQ_TMR2,IRQ_PRIORITY_LOW);
	
	TMR2_AllIntEnable();
	IRQ_ALL_ENABLE();	
	
	/*
	(7)设置Timer捕获
	*/
  	#if 0
	GPIO_SET_MUX_MODE(P00CFG, GPIO_MUX_GPIO);
	GPIO_SET_PS_MODE(PS_CAP0, GPIO_P00);				/*捕获通道0输入*/
	GPIO_ENABLE_RD(P0RD, GPIO_PIN_0);					/*开下拉*/	
	
	GPIO_SET_MUX_MODE(P01CFG, GPIO_MUX_GPIO);
	GPIO_SET_PS_MODE(PS_CAP1, GPIO_P01);				/*捕获通道0输入*/
	GPIO_ENABLE_RD(P0RD, GPIO_PIN_1);					/*开下拉*/		
	
	
	
	GPIO_SET_MUX_MODE(P03CFG, GPIO_MUX_GPIO);
	GPIO_SET_PS_MODE(PS_CAP3, GPIO_P03);				/*捕获通道0输入*/
	GPIO_ENABLE_RD(P0RD, GPIO_PIN_3);					/*开下拉*/
    #endif 
    
    GPIO_SET_MUX_MODE(P02CFG, GPIO_MUX_GPIO);
	GPIO_SET_PS_MODE(PS_CAP2, GPIO_P02);				/*捕获通道0输入*/
	GPIO_ENABLE_RD(P0RD, GPIO_PIN_2);					/*开下拉*/		
	
	/*

	(8)开启Timer
	*/
    TMR2_EnableGATE(); //WT.EDIT 门控定时器功能
	TMR2_Start();

}




























