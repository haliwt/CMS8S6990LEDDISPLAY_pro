#include "LED.h"

static void LEDDisplay_BlueColorRing(void);
/******************************************************************************
 **
 ** Function Name:	void LED_GPIO_Init(void)
 ** Function : receive key input message 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
void LED_GPIO_Init(void)
{
    GPIO_SET_MUX_MODE(P24CFG,GPIO_MUX_GPIO);   //SDA = P24
	GPIO_ENABLE_OUTPUT(P2TRIS,GPIO_PIN_4); 
	//GPIO_ENABLE_RD(P2UP,GPIO_PIN_4) ;  
	P24=1;

    GPIO_SET_MUX_MODE(P25CFG,GPIO_MUX_GPIO);   // SCL= P25
	GPIO_ENABLE_OUTPUT(P2TRIS,GPIO_PIN_5); 
	//GPIO_ENABLE_RD(P2UP,GPIO_PIN_5) ;  
    P25=1;
	
   GPIO_SET_MUX_MODE(P26CFG,GPIO_MUX_GPIO);   // STB= P26    片选信号
	GPIO_ENABLE_OUTPUT(P2TRIS,GPIO_PIN_6); 
	//GPIO_ENABLE_RD(P2UP,GPIO_PIN_6) ;  
	P26=1;
  
    
}

/******************************************************************************
 **
 ** Function Name:	void KEY_FUNCTION(void)
 ** Function : receive key input message 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
void LEDDisplay_SleepLamp(void)
{
  

}
/****************************************************************************************************
 * 	*
	*函数名称：void LEDDisplay_TimerTim(void)
	*函数功能：定时时间显示,按键设置定时时间
	*入口参数：NO
	*出口参数：NO
	*
*******************************************************************************************************/
void LEDDisplay_TimerTim(void)
{
	 
}
/****************************************************************************************************
 * 	*
	*函数名称：void LEDDisplay_RedColorRing(void);
	*函数功能：LED数码管，光圈显示红色
	*入口参数：NO
	*出口参数：NO
	*
*******************************************************************************************************/
void LEDDisplay_RedColorRing(void)
{
    
   
    
}
/****************************************************************************************************
 * 	*
	*函数名称：void LEDDisplay_GreenColorRing(void);
	*函数功能：LED数码管，光圈显示绿色
	*入口参数：NO
	*出口参数：NO
	*
*******************************************************************************************************/
void LEDDisplay_GreenColorRing(void)
{
  
   
   

}
/****************************************************************************************************
 * 	*
	*函数名称：void LEDDisplay_BlueColorRing(void);
	*函数功能：LED数码管，光圈显示蓝色---睡眠灯
	*入口参数：NO
	*出口参数：NO
	*
*******************************************************************************************************/
void LEDDisplay_BlueColorRing(void)
{

 
 
}
