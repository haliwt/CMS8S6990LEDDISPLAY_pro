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
void LEDDisplay_TimerTim(uint8_t disdat3,uint8_t disdat2,uint8_t disdat1)
{
        STB_TM1629D =0 ;  
        Tm1629DSentData(ModeDisTM1629D); //写数据到显示寄存器
	    STB_TM1629D =1; 
	
        STB_TM1629D=0;   
		Tm1629DSentData(AddrFixed);//AddrFixed 写固定地址
		//写显示，固定定制模式
		STB_TM1629D=1; 
		
        STB_TM1629D=0;   
		Tm1629DSentData(Addr00H);
		//指向地址0   
	    Tm1629DSentData(segNumber[disdat3]); //主显示3 位---百位
	    STB_TM1629D=1; 
		
        STB_TM1629D=0;   
		Tm1629DSentData(Addr02H);
		//指向地址2   
	    Tm1629DSentData(segNumber[disdat2]); //主显示2位---十位
	    STB_TM1629D=1; 
		
        //写第三位
         STB_TM1629D=0;   
		Tm1629DSentData(Addr04H);
		//指向地址4   
	    Tm1629DSentData(segNumber[disdat1]); //主显示1位----个位
         STB_TM1629D=1; 
	
       STB_TM1629D =0; 
       Tm1629DSentData(OpenDisTM1629D|Set12_16TM1629D); //开显示，显示，设置脉冲宽带 12/16
       STB_TM1629D =1; 	 
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
