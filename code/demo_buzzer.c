
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "demo_buzzer.h"



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
	

	  GPIO_SET_MUX_MODE(P13CFG,GPIO_MUX_BEEP);

	/*
	(3)使能蜂鸣器时钟
	*/	
	BUZ_EnableBuzzer();	
}

/******************************************************************************
 ** 
 ** Function Name : void DisableBUZZER_Fun(void);
 **            	
 **
 ** \note  
 ******************************************************************************/

void DisableBUZZER_Config(void)
{

	/*
	(1)配置蜂鸣器时钟
	*/
	BUZ_ConfigBuzzer(BUZ_CKS_8,10);			//Fsys=24Mhz，Fbuz = Fsys/(2*8*150) =10khz
	/*
	(2)配置蜂鸣器输出IO
	*/	
	
	 GPIO_SET_MUX_MODE(P13CFG,GPIO_MUX_BEEP);
	/*
	(3)使能蜂鸣器时钟
	*/	
	BUZ_DisableBuzzer();	


}






















