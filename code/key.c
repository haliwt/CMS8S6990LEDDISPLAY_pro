#include "key.h"
#include "demo_buzzer.h"
#include "myflash.h"

//static uint8_t KEY_Scan(void);
key_types   key;
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
uint8_t KEY_FUNCTION(void)
{
	static uint8_t pkey=0,datalogic=0;
	uint8_t subutton=0,i=0,readdata=0,readsecond=0,read1=0,read2=0;
	uint8_t arr[2]={0,0};

	  if(WIND_KEY==1 && TIMER_KEY==1){//童琐按键 --长按3s---组合按键
		    delay_20us(1000);
		    delay_20us(1000);
		    subutton =1;
			 if(WIND_KEY==1 && TIMER_KEY==1 && subutton ==1 ){
			   
			     subutton =2;
				   P25=1;
				   i++;
				   
				   readdata = Flash_ToReadData(0x00);
				   if(i==0){
					   
					   arr[0] = Flash_ToReadData(0x00);
					   if(arr[0]==0)Telecom->LockKey = 2;
					   if(arr[0]==1)Telecom->LockKey = 3;
				    }
				   if((readdata == 0 ||readdata == 1) && read2==0 && read1==0){
						 switch (readdata)
						 {
							case 0:     
										 Flash_ToWriteData(0x00,0x1);
										 read1 =Flash_ToReadData(0x00);
										 arr[1]= read1;
										 i++;
								break;
							case 1:
										 Flash_ToWriteData(0x00,0x0);
									    read2 =  Flash_ToReadData(0x00);
									    arr[1]= read2;
										 read1=1;
										 i++;
								break;
						 }
				  }
				   
				  if(Telecom -> LockKey ==2){
					  
					  if(arr[1]==1) return 1;
				  }
				  else if(Telecom -> LockKey ==3){
					  
					  if(arr[1]==0) return 1;
				  }
				  else{}
				  
				  if(arr[0]==arr[1]){
					  
					  switch(arr[0]){
						  
						  case 0: 
						  			Flash_ToWriteData(0x00,0x1);
									read1 =Flash_ToReadData(0x00);
									 arr[1]= read1;
						  break;
						  
						  case 1:
						  			Flash_ToWriteData(0x00,0x0);
									    read2 =  Flash_ToReadData(0x00);
									    arr[1]= read2;
						  break;
						  
						  
					  }
					  
					  
				  }
				  if(arr[0] != arr[1]){
				   TM1650_Set(0x68,segNumber[ readdata ]);//初始化为5级灰度，开显示
           		  TM1650_Set(0x6A,segNumber[read1]);//初始化为5级灰度，开显示

				  TM1650_Set(0x6C,segNumber[read2]);//初始化为5级灰度，开显
			       delay_20us(1000);
				   delay_20us(1000);
				   return 1;
				    
				  }
				 
		}

	 }
	readsecond = Flash_ToReadData(0x00);
//	if(readdata !=1 || readdata !=0) Flash_ToWriteData(0x00,0x0);
   TM1650_Set(0x6E,segNumber[readsecond]);//初始化为5级灰度，开显示
   delay_20us(1000);

     if(readsecond==0){
    
			if(POWER_KEY == 1)//开关按键 P16
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
			
			if(WIND_KEY == 1 && Telecom->power_state ==1)//风速按键
				delay_20us(1000);
				if(subutton ==0 && WIND_KEY==1 && Telecom->power_state ==1){
					//Telecom->setWind_levels = wind_auto;
					Telecom->setWind_levels++;
					if(Telecom->setWind_levels>=4)
					Telecom->setWind_levels = wind_sleep;
					subutton =1;
					BUZZER_Config();
				} 
			
		 if(TIMER_KEY==1 && Telecom->power_state ==1)//定时按键,定时时间 8个小时,循环增加数值
				delay_20us(1000);
			
				if(TIMER_KEY ==1 && Telecom->power_state ==1){
					
					Telecom->TimerEvent=1;
					Telecom->showtimes= 10+Telecom->showtimes;//每次增加 10分钟
					LEDDisplay_TimerTim();
					Telecom->TimerEvent=0;
					
				}
			
			 if(FILTER_KEY==1 && Telecom->power_state ==1)//滤网重置按键,时间到3000小时更换虑网
				delay_20us(1000);
				if(subutton ==0 && FILTER_KEY ==1 && Telecom->power_state ==1){
					subutton =1;
					BUZZER_Config();

				}

			
	  }

	  else{
	
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
	}
	 

	}


/******************************************************************************
 **
 ** Function Name:	void KEY_FUNCTION(void)
 ** Function : receive key input message 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
void KEY_Handing(void)
{
	static pkey =0,i=0;
	uint8_t  temp8;
	temp8 = KEY_Scan();
	switch(temp8)
	{
		case	_KEY_CONT_3_TIMER: //长按按键按键值
		         BUZZER_Config();
			    delay_20us(500);
		          TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
						TM1650_Set(0x68,segNumber[0]);//初始化为5级灰度，开显示
					    TM1650_Set(0x6A,segNumber[1]);//初始化为5级灰度，开显示
						TM1650_Set(0x6C,segNumber[1]);//初始化为5级灰度，开显示
						TM1650_Set(0x6E,segNumber[1]);//初始化为5级灰度，开显示
				
			break;
			
		case _KEY_CONT_2_WIND :
		        BUZZER_Config();
			    delay_20us(500);
		          TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
						TM1650_Set(0x68,segNumber[0]);//初始化为5级灰度，开显示
					    TM1650_Set(0x6A,segNumber[2]);//初始化为5级灰度，开显示
						TM1650_Set(0x6C,segNumber[2]);//初始化为5级灰度，开显示
						TM1650_Set(0x6E,segNumber[2]);//初始化为5级灰度，开显示
		
		break;
		
		case _KEY_CONT_1_POWER :
		        BUZZER_Config();
			    delay_20us(500);
		          TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
						TM1650_Set(0x68,segNumber[0]);//初始化为5级灰度，开显示
					    TM1650_Set(0x6A,segNumber[3]);//初始化为5级灰度，开显示
						TM1650_Set(0x6C,segNumber[3]);//初始化为5级灰度，开显示
						TM1650_Set(0x6E,segNumber[3]);//初始化为5级灰度，开显示
		
		break;
		
	     case _KEY_CONT_4_FILTER :
		        BUZZER_Config();
			    delay_20us(500);
		          TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
						TM1650_Set(0x68,segNumber[0]);//初始化为5级灰度，开显示
					    TM1650_Set(0x6A,segNumber[4]);//初始化为5级灰度，开显示
						TM1650_Set(0x6C,segNumber[4]);//初始化为5级灰度，开显示
						TM1650_Set(0x6E,segNumber[4]);//初始化为5级灰度，开显示
		
		break;
		
		case	_KEY_TRG_1_POWER: //一般按键按下
		             BUZZER_Config();
			    delay_20us(500);
		     LEDDisplay_GreenColorRing();//背光是绿色
			  delay_20us(500);
			 
			 	LEDDisplay_RedColorRing();//电源指示灯红色，闪烁。
				    P26=1;
					pkey = pkey ^ 0x01;
					if(pkey==1){
						
							Telecom->power_state =1;
							LEDDisplay_GreenColorRing();//背光是绿色
							BUZZER_Config();
						  delay_20us(100);
						
					}
					else{
							
							Telecom->power_state =0;
							LEDDisplay_RedColorRing();//电源指示灯红色，闪烁。
							BUZZER_Config();
						  delay_20us(500);
						
					
			    }
			
		
			break;
		
	
		
		case	_KEY_TRG_2_WIND:
		 
		   
		      LEDDisplay_RedColorRing();//电源指示灯红色，闪烁。
			    TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
						TM1650_Set(0x68,segNumber[0]);//初始化为5级灰度，开显示
					    TM1650_Set(0x6A,segNumber[5]);//初始化为5级灰度，开显示
						TM1650_Set(0x6C,segNumber[5]);//初始化为5级灰度，开显示
						TM1650_Set(0x6E,segNumber[5]);//初始化为5级灰度，开显示
						BUZZER_Config();
			    delay_20us(500);
		       
			break;
		
		case  _KEY_TRG_3_TIMER:
		// BUZZER_Config();
			//    delay_20us(500);
		         TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
						TM1650_Set(0x68,segNumber[0]);//初始化为5级灰度，开显示
					    TM1650_Set(0x6A,segNumber[6]);//初始化为5级灰度，开显示
						TM1650_Set(0x6C,segNumber[6]);//初始化为5级灰度，开显示
						TM1650_Set(0x6E,segNumber[6]);//初始化为5级灰度，开显示
						BUZZER_Config();
			    delay_20us(500);
		      
		     break;
		case	_KEY_TRG_4_FILTER:
		      
			  //  BUZZER_Config();
			  //  delay_20us(500);
				  TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
						TM1650_Set(0x68,segNumber[0]);//初始化为5级灰度，开显示
					    TM1650_Set(0x6A,segNumber[7]);//初始化为5级灰度，开显示
						TM1650_Set(0x6C,segNumber[7]);//初始化为5级灰度，开显示
						TM1650_Set(0x6E,segNumber[7]);//初始化为5级灰度，开显示
						BUZZER_Config();
			    delay_20us(500);
		    
	
		break;
			
			break;
		
		default:
			break;
	}
}
/******************************************************************************
 **
 ** Function Name:	void KEY_FUNCTION(void)
 ** Function : receive key input message 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
uint8_t KEY_Scan(void)
{
	uint8_t  reval = 0;
	
  
	key.read = _KEY_ALL_OFF; //0x1F 
	
	if(POWER_KEY == 1)
	{
		key.read &= ~0x01; // 0x1E
	}
	if(WIND_KEY == 1)
	{
		key.read &= ~0x02;   //0x1C
	}
	if(TIMER_KEY == 1)
	{
		key.read &= ~0x04;  //0x1B
	}
	if(FILTER_KEY == 1)
	{
		key.read &= ~0x08;  //0x17
	}
	switch(key.state )
	{
		case start:
		{
			if(key.read != _KEY_ALL_OFF)
			{
				key.buffer   = key.read; //例如：key.buffer = 0x1E  POWER KEY 
				key.state    = first;
				key.on_time  = 0;
				key.off_time = 0;
			}
			break;
		}
		case first:
		{
			if(key.read == key.buffer) //继续按下
			{
				if(++key.on_time> 10) //消抖  0.5us
				{
					key.value = key.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01
					key.on_time = 0;
					key.state   = second;
				}
			}
			else
			{
				key.state   = start;
			}
			break;
		}
		case second:
		{
			if(key.read == key.buffer) //再次确认按键是否按下
			{
				if(++key.on_time>300)//长按按键
				{
					key.value = key.value|0x80; //key.value = 0x01 | 0x80  =0x81  
					key.on_time = 0;
					
					key.state   = finish;
				}
			}
			else if(key.read == _KEY_ALL_OFF)  //按键松开
			{
				if(++key.off_time>5) //松开按键消抖
				{
					key.state   = finish; //一般按键按下状态
				}
			}
			break;
		}
		case finish:
		{
			reval = key.value; //分两种情况： 1.普通按键的按下返回值 TIMER_KEY = 0x04  2.长按键返回值：TIMER_KEY = 0X84
			key.state   = end;
			break;
		}
		case end:
		{
			if(key.read == _KEY_ALL_OFF)
			{
				if(++key.off_time>100)
				{
					key.state   = start;
				}
			}
			break;
		}
		default:
		{
			key.state   = start;
			break;
		}
	}
	return  reval;
}


















