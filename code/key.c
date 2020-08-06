#include "key.h"
#include "demo_buzzer.h"

Telec *Telecom= NULL;
static uint8_t Lockflag =0;
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
		  _nop_(); 
		  _nop_(); 
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
   static uint8_t pkey,lock;
	 uint8_t subutton=0,i=0;


	  if(WIND_KEY==1 && TIMER_KEY==1){//童琐按键 --长按3s---组合按键
		    delay_20us(1000);
		    delay_20us(1000);
		  //  delay_20us(1000);
			
		if(WIND_KEY==1 && TIMER_KEY==1 && subutton ==0 ){
			   
			   pkey ++;
			  //TM1650_Set(0x68,segNumber[ pkey ]);//初始化为5级灰度，开显示
			if(pkey ==1){
				
				   subutton =1;
				  Telecom->LockKey =1;  // 这个参数改不过来
			      lock =1;
				
				     BUZZER_Config(); 
			       
				  
				   BUZ_DisableBuzzer();
				  
				 
				   TM1650_Set(0x68,segNumber[ pkey ]);//初始化为5级灰度，开显示
   

						TM1650_Set(0x6A,segNumber[1]);//初始化为5级灰度，开显示


					    TM1650_Set(0x6C,segNumber[2]);//初始化为5级灰度，开显示

						
					   TM1650_Set(0x6E,segNumber[3]);//初始化为5级灰度，开显示
					
				      delay_20us(200);
			}
			if(pkey !=1){
				     P25=1;
				P26=1;
				subutton =1;
				    pkey =0;
					Lockflag = 0;
					 Telecom->LockKey =0;
				    lock =0;
				     BUZZER_Config(); 
			        delay_20us(1000);
				    BUZ_DisableBuzzer();
				    subutton =1;
				    Init_Tm1650();
				    TM1650_Set(0x68,segNumber[7]);//初始化为5级灰度，开显示
   

						TM1650_Set(0x6A,segNumber[6]);//初始化为5级灰度，开显示


					    TM1650_Set(0x6C,segNumber[5]);//初始化为5级灰度，开显示

						
					   TM1650_Set(0x6E,segNumber[4]);//初始化为5级灰度，开显示
				
			}
		}

	 }

   switch(lock){  //童琐按键

   	case 0 :
    
			if(POWER_KEY == 1){ //开关按键 P16
				delay_20us(1000);
				if(POWER_KEY ==1){   
					P26=1;
					pkey = pkey ^ 0x01;
					if(pkey==1){
						if(subutton ==0 && POWER_KEY==1){
							Telecom->power_state =1;
							LEDDisplay_GreenColorRing();//背光是绿色
							BUZZER_Config();
						} 
					}
					else{
							if(subutton ==0 && POWER_KEY==1){
							Telecom->power_state =0;
							LEDDisplay_RedColorRing();//电源指示灯红色，闪烁。
							BUZZER_Config();
						} 
					}
			    }
			}
			if(WIND_KEY == 1 && Telecom->power_state ==1){ //风速按键
				delay_20us(1000);
				if(subutton ==0 && WIND_KEY==1 && Telecom->power_state ==1){
					//Telecom->setWind_levels = wind_auto;
					Telecom->setWind_levels++;
					if(Telecom->setWind_levels>=4)
					Telecom->setWind_levels = wind_sleep;
					subutton =1;
					BUZZER_Config();
				} 
			}
		 if(TIMER_KEY==1 && Telecom->power_state ==1){ //定时按键,定时时间 8个小时,循环增加数值
				delay_20us(1000);
				P25=1;
				if(TIMER_KEY ==1 && Telecom->power_state ==1){
					
					Telecom->TimerEvent=1;
					Telecom->showtimes= 10+Telecom->showtimes;//每次增加 10分钟
					LEDDisplay_TimerTim();
					Telecom->TimerEvent=0;
					
				}
			}
			 if(FILTER_KEY==1 && Telecom->power_state ==1){ //滤网重置按键,时间到3000小时更换虑网
				delay_20us(1000);
				if(subutton ==0 && FILTER_KEY ==1 && Telecom->power_state ==1){
					subutton =1;
					BUZZER_Config();

				}

			}
	  break ;

	  case 1 :
	
		    if(POWER_KEY == 1 || WIND_KEY == 1 || TIMER_KEY ==1 || FILTER_KEY ==1){
			   delay_20us(1000);
			   if(POWER_KEY == 1 || WIND_KEY == 1 || TIMER_KEY ==1 || FILTER_KEY ==1 && subutton ==0){
			   	   subutton =1;
			   	   BUZZER_Config();     //蜂鸣器
				   delay_20us(5000);
				   BUZ_DisableBuzzer();
				   BUZZER_Config();     //蜂鸣器
				   delay_20us(5000);

			   }
		  }
		break;
	 

	}
}
























