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
   if(Telecom->setWind_levels == wind_sleep)
   {
       LEDDisplay_BlueColorRing();

   }

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
	 //定时显示，3位7段
	 static uint8_t minhour=0;
	 uint8_t DispData[3];

   if(Telecom->showtimes <=60 && Telecom->getTimerHour < 1){//显示分钟时间
        if(Telecom->showtimes ==60 && Telecom->TimerEvent ==0){  //设置定时时间，按键输入定时时间值
			Telecom->getTimerHour++;
			Telecom->showtimes=0;
		}
		if(Telecom->TimerEvent == 1){ //显示定时时间，每次减一分钟 ，定时事件=1，定时开始
			Telecom->showtimes  = Telecom->showtimes - getMinute;
			if(Telecom->showtimes <=0) {
				minhour ++;    				//分钟时间减完了，---再减小时时间参数
				Telecom->showtimes=0;
				getMinute =0;
			}
 
		}

       	DispData[2] = segNumber[Telecom->showtimes %10];// LED个位
    	TM1650_Set(0x68, DispData[2]);//初始化为5级灰度，开显示 //写入个位 
       	DispData[1] = segNumber[Telecom->showtimes /10];// LED十位
        TM1650_Set(0x6A, DispData[1]);//写入十位
       	DispData[0] = segNumber[0];         //小时，个位
        TM1650_Set(0x6C, DispData[0]);//写入百位
        P24=1; //PM2.5显示
    }
    else if(Telecom->getTimerHour >=1){ //显示小时时间，分钟时间
        if(Telecom->showtimes ==60 && Telecom->TimerEvent==0){
			Telecom->getTimerHour++;
			Telecom->showtimes=0;
		}
		if(Telecom->TimerEvent == 1){ //定时事件开始
			if(Telecom->getTimerHour !=0){ //定时时间，大于一个小时
				Telecom->showtimes  = Telecom->showtimes - getMinute;
				if(Telecom->showtimes <=0) {
					minhour ++;
					Telecom->showtimes=60;
				}
				Telecom->getTimerHour  = Telecom->getTimerHour - minhour; //减小时时间
			}
		}
        
		     DispData[2] = segNumber[Telecom->showtimes %10];		//LED 显示个位  29分钟----‘9’
          TM1650_Set(0x68, DispData[2]);//写入个位 
        DispData[1] = segNumber[Telecom->showtimes / 10];		//LED 显示十位 分钟 29分--‘2’
          TM1650_Set(0x6A, DispData[1]);
        DispData[0] = segNumber[Telecom->getTimerHour / 10]; 	//---显示最高位时间，定时最大时间8小时
        TM1650_Set(0x6C, DispData[0]);
        P24=1; //PM2.5显示
        if(Telecom->getTimerHour >=8)Telecom->getTimerHour =0;  //最大定时时间是 8小时
    }

    

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