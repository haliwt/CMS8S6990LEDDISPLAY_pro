/****************************************************************************/
/** \file demo_gpio.c
**
**  
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "key.h"



/******************************************************************************
 ** \brief	 GPIO_Config
 ** \param [in] none
 **          GPIO中断功能
 ** \return  none
 ** \note  
 ******************************************************************************/
void GPIO_Config(void)
{
	/*
	(1)设置P23 IO功能
	*/
	GPIO_SET_MUX_MODE(P23CFG, GPIO_MUX_GPIO);		//设置P23为GPIO模式
	GPIO_ENABLE_INPUT(P2TRIS, GPIO_PIN_3);			//设置为输入模式
	GPIO_ENABLE_RD(P2RD, GPIO_PIN_3);				//开启下拉
	/*
	(2)设置中断方式
	*/
	GPIO_SET_INT_MODE(P23EICFG, GPIO_INT_FALLING);	//设置为下降沿中断模式
	GPIO_EnableInt(GPIO2, GPIO_PIN_3_MSK);			//开启P23中断
	/*
	(3)设置中断优先级
	*/
	IRQ_SET_PRIORITY(IRQ_P2, IRQ_PRIORITY_LOW);
	/*
	(4)开启总中断
	*/	
	IRQ_ALL_ENABLE();

	
}
























