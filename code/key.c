#include "key.h"
#include "demo_buzzer.h"

Telec *Telecom= NULL;
/******************************************************************************
 **
 ** Function Name:	void delay_10us(uint16_t n) 
 ** Function : 延时10*n微秒 24MHz ,实际测试32us
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
void delay_30us(uint16_t n)  
{  
    uint16_t i=0;  
    uint8_t j=0;  
    for(i=0;i<n;i++)  
       for(j=0;j<2;j++){
        {
		 _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
		 _nop_(); 
		} 
	}
}  
/******************************************************************************
 **
 ** Function Name:	void delay_10us(uint16_t n) 
 ** Function : 延时10*n微秒 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
void delay_20us(uint16_t n)   
{  
    uint16_t i=0;  
    for(i=0;i<n;i++) {
		  _nop_(); 
		  
     } 
}  

void delay_us(uint16_t n)  
{  
    uint16_t i=0;  
    for(i=0;i<n;i++) {
		   _nop_();  
		  
     } 
}  
/******************************************************************************
 ** \brief	 GPIO_Config
 ** \param [in] none
 **          GPIO中断功能
 ** \return  none
 ** \note  
 ******************************************************************************/
void GPIO_Config(void)
{
	
	
	GPIO_SET_MUX_MODE(P26CFG, GPIO_MUX_GPIO);		//??P13?GPIO??
	GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_6);			//???????
	P26 = 0 ;
	GPIO_SET_MUX_MODE(P25CFG, GPIO_MUX_GPIO);		//??P13?GPIO??
	GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_5);			//???????
	P25 = 0;
	
	
	/*
	(1)设置P23 IO功能
	*/
	
	GPIO_SET_MUX_MODE(P13CFG,GPIO_MUX_GPIO);   //开机按键  P13
	GPIO_ENABLE_INPUT(P1TRIS,GPIO_PIN_3); 
	GPIO_ENABLE_RD(P1RD,GPIO_PIN_3) ; 
   
	GPIO_SET_MUX_MODE(P15CFG, GPIO_MUX_GPIO);		//设置P15为GPIO模式--风速按键
	GPIO_ENABLE_INPUT(P1TRIS, GPIO_PIN_5);			//设置为输入模式
	GPIO_ENABLE_RD(P1RD, GPIO_PIN_5);				//开启下拉

	
	GPIO_SET_MUX_MODE(P14CFG,GPIO_MUX_GPIO);   //定时按键 P14
	GPIO_ENABLE_INPUT(P1TRIS,GPIO_PIN_4);      //设置为输入模式
	GPIO_ENABLE_RD(P1RD,GPIO_PIN_4);           //开启下拉

	GPIO_SET_MUX_MODE(P16CFG,GPIO_MUX_GPIO);   //虑网重置按键  P16
	GPIO_ENABLE_INPUT(P1TRIS,GPIO_PIN_6); 
	GPIO_ENABLE_RD(P1RD,GPIO_PIN_6) ;    
	/*
	(2)设置中断方式
	*/
	//GPIO_SET_INT_MODE(P16EICFG, GPIO_INT_FALLING);	//设置为下降沿中断模式 P16电源按键
	//GPIO_EnableInt(GPIO1, GPIO_PIN_6_MSK);			//开启P16中断 
	/*
	(3)设置中断优先级
	*/
//	IRQ_SET_PRIORITY(IRQ_P1, IRQ_PRIORITY_LOW);
	/*
	(4)开启总中断
	*/	
//	IRQ_ALL_ENABLE();
}
/******************************************************************************
 **
 ** Function Name:	void KEY_FUNCTION(void)
 ** Function : receive key input message 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
void KEY_FUNCTION(void)
{
   static uint8_t Lockflag =0,lockey=0,pkey=0;
	 uint8_t subutton=0,i=0;
	 if(Lockflag ==0 ){
			if(P13 == 1){ //开关按键
				delay_30us(1000);
				P26=1;
				pkey = pkey ^ 0x01;
				if(pkey==1){
					if(subutton ==0 && P13==1){
						Telecom->power_state =1;
						LEDDisplay_GreenColorRing();//背光是绿色
						 BUZZER_Config();
					} 
				}
				else{
						if(subutton ==0 && P13==1){
						Telecom->power_state =0;
						LEDDisplay_RedColorRing();//电源指示灯红色，闪烁。
						BUZZER_Config();
					} 
				}
			}
			else if(P15 == 1 && Telecom->power_state ==1){ //风速按键
				delay_30us(1000);
				if(subutton ==0 && P15==1 && Telecom->power_state ==1){
					//Telecom->setWind_levels = wind_auto;
					Telecom->setWind_levels++;
					if(Telecom->setWind_levels>=4)
					Telecom->setWind_levels = wind_sleep;
					subutton =1;
					BUZZER_Config();
				} 
			}
			else if(P14==1 && Telecom->power_state ==1){ //定时按键,定时时间 8个小时,循环增加数值
				delay_30us(1000);
				P25=1;
				if(P14 ==1 && Telecom->power_state ==1){
					
					Telecom->TimerEvent=1;
					Telecom->showtimes= 10+Telecom->showtimes;//每次增加 10分钟
					LEDDisplay_TimerTim();
					Telecom->TimerEvent=0;
					
				}
			}
			else if(P16==1 && Telecom->power_state ==1){ //滤网重置按键,时间到3000小时更换虑网
				delay_30us(1000);
				if(subutton ==0 && P16==1 && Telecom->power_state ==1){
					subutton =1;
					BUZZER_Config();

				}

			}
	 }
	 else{
		//BUZZER_Config();

	 }

	 if(P15==1 && P14==1){//童琐按键 --长按3s---组合按键
	    for(i=0;i<=300;i++){
			delay_30us(10000);
		}
		lockey = lockey ^ 0x01;
		if(lockey ==1){
			if(P15==1 && P14==1){
				Lockflag = 1;
			  BUZZER_Config();     //蜂鸣器
				delay_30us(50000);
				
			}
		}
		else{
			if(P15==1 && P14==1){
				Lockflag = 0;
				BUZZER_Config();
				delay_30us(50000);
			
			}
		}

	 }
}
























