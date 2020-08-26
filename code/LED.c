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
    GPIO_SET_MUX_MODE(P24CFG,GPIO_MUX_GPIO);   //LED显示段 1I = P24
	GPIO_ENABLE_OUTPUT(P2TRIS,GPIO_PIN_4); 
	GPIO_ENABLE_RD(P2UP,GPIO_PIN_4) ;  

    GPIO_SET_MUX_MODE(P25CFG,GPIO_MUX_GPIO);   //LED显示段 1J = P25
	GPIO_ENABLE_OUTPUT(P2TRIS,GPIO_PIN_5); 
	GPIO_ENABLE_RD(P2UP,GPIO_PIN_5) ;  

    GPIO_SET_MUX_MODE(P26CFG,GPIO_MUX_GPIO);   //LED显示段 1K = P26
	GPIO_ENABLE_OUTPUT(P2TRIS,GPIO_PIN_6); 
	GPIO_ENABLE_RD(P2UP,GPIO_PIN_6) ;  

    GPIO_SET_MUX_MODE(P30CFG,GPIO_MUX_GPIO);   //LED显示段 6L = P30
	GPIO_ENABLE_OUTPUT(P3TRIS,GPIO_PIN_0); 
	GPIO_ENABLE_RD(P3UP,GPIO_PIN_0) ; 


    //LED 位选

    GPIO_SET_MUX_MODE(P31CFG,GPIO_MUX_GPIO);   //LED 位选 COM5 = P31
	GPIO_ENABLE_OUTPUT(P3TRIS,GPIO_PIN_1); 
	GPIO_ENABLE_RD(P3UP,GPIO_PIN_1) ; 

    GPIO_SET_MUX_MODE(P32CFG,GPIO_MUX_GPIO);   //LED 位选 COM6 = P32
	GPIO_ENABLE_OUTPUT(P3TRIS,GPIO_PIN_2); 
	GPIO_ENABLE_RD(P3UP,GPIO_PIN_2) ; 

    GPIO_SET_MUX_MODE(P36CFG,GPIO_MUX_GPIO);   //LED 位选 COM7 =P36
	GPIO_ENABLE_OUTPUT(P3TRIS,GPIO_PIN_6); 
	GPIO_ENABLE_RD(P3UP,GPIO_PIN_6) ; 

    GPIO_SET_MUX_MODE(P05CFG,GPIO_MUX_GPIO);   //LED 位选 COM8 = P05
	GPIO_ENABLE_OUTPUT(P0TRIS,GPIO_PIN_5); 
	GPIO_ENABLE_RD(P0UP,GPIO_PIN_5) ; 
    
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
    
    COM7 = 0; 
    COM8 = 0;   
 //   TM1650_write_byte(TM1650_5_NDISP,TM1650_COM1_ADDR , &seg[8]);

    PI= 1;
    PJ =1;
    PK =1;
    delay_30us(5000); //50ms
    COM7=1;
    COM8=1;
    PI= 0;
    PJ =0;
    PK =0;
    TM1650_FULL_DISP();
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
   
   //100% 显示
  // TM1650_write_byte(TM1650_5_NDISP,TM1650_COM1_ADDR , &seg[8]);
   PI= 1;
   PJ =1;
   PK =1;
   PL = 1;
   COM6=0;
  // TM1650_write_byte(TM1650_5_NDISP,TM1650_COM1_ADDR , &seg[8]);
   
   

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

 // TM1650_write_byte(TM1650_5_NDISP,TM1650_COM4_ADDR , &seg[8]);
   COM5= 0;

 //  TM1650_write_byte(TM1650_5_NDISP,TM1650_COM1_ADDR , &seg[11]);

  // TM1650_write_byte(TM1650_5_NDISP,TM1650_COM2_ADDR , &seg[11]);
   
   PI= 1;
   PJ =1;
   PK =1;
   
 //  TM1650_write_byte(TM1650_5_NDISP,TM1650_COM3_ADDR , &seg[0]);
   PI= 0;
   PJ =1;
   PK =1;
 
}
/****************************************************************************************************
 * 	*
	*函数名称：void TM1650_FULL_DISP(void)
	*函数功能：LED数码管，光圈显示蓝色---睡眠灯
	*入口参数：NO
	*出口参数：NO
	*
*******************************************************************************************************/
void TM1650_FULL_DISP(void){

	TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
	TM1650_Set(0x68,segNumber[0x0B]);//初始化为5级灰度，开显示
	TM1650_Set(0x6A,segNumber[0x0B]);//初始化为5级灰度，开显示
	TM1650_Set(0x6C,segNumber[0x0B]);//初始化为5级灰度，开显示
 	TM1650_Set(0x6E,segNumber[0x0B]);//初始化为5级灰度，开显示



}