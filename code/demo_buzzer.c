
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "demo_buzzer.h"

/******************************************************************************
 ** \brief	 BUZZER_Init(void)
 ** \param [in] 
 **            	
 ** \return  none
 ** \note  
 ******************************************************************************/
void BUZZER_Init(void)
{
	/*
	(1)配置蜂鸣器时钟
	*/
	BUZ_ConfigBuzzer(BUZ_CKS_8,150);			//Fsys=24Mhz，Fbuz = Fsys/(2*8*150) =10khz
  BUZ_EnableBuzzer();	
}


/******************************************************************************
 ** \brief	 BUZZER_Config
 ** \param [in] 
 **            	
 ** \return  none
 ** \note  
 ******************************************************************************/
void BUZZER_Config(void)
{
	/*
	(1)配置蜂鸣器时钟
	*/
	BUZ_ConfigBuzzer(BUZ_CKS_8,150);			//Fsys=24Mhz，Fbuz = Fsys/(2*8*150) =10khz
	/*
	(2)配置蜂鸣器输出IO
	*/	
	
	#if CMS8S6990N_TSSOP20 
	  GPIO_SET_MUX_MODE(P04CFG,GPIO_MUX_BEEP); //

    #else 
	  GPIO_SET_MUX_MODE(P00CFG,GPIO_MUX_BEEP);
	#endif 
	/*
	(3)使能蜂鸣器时钟
	*/	
	BUZ_EnableBuzzer();	
}
























