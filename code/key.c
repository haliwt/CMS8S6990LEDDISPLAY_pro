#include "key.h"
#include "demo_buzzer.h"
#include "myflash.h"

//static uint8_t KEY_Scan(void);
key_types   key;
Telec *Telecom= NULL;
static uint8_t Lockflag =0;
static uint8_t KEY_HDScan(uint8_t mode);

static uint8_t ReadKey(void);  
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
	//temp8 = KEY_Scan();
	temp8= ReadKey();
	switch(temp8)
	{
	
		
		case WINDTI_PRES:
		
		  BUZZER_Config();
			    delay_20us(10);
		          TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
						TM1650_Set(0x68,segNumber[0]);//初始化为5级灰度，开显示
					    TM1650_Set(0x6A,segNumber[1]);//初始化为5级灰度，开显示
						TM1650_Set(0x6C,segNumber[1]);//初始化为5级灰度，开显示
						TM1650_Set(0x6E,segNumber[1]);//初始化为5级灰度，开显示
				
		break;
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
					    TM1650_Set(0x6A,segNumber[2]);//初始化为5级灰度，开显示
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
					    TM1650_Set(0x6A,segNumber[3]);//初始化为5级灰度，开显示
						TM1650_Set(0x6C,segNumber[6]);//初始化为5级灰度，开显示
						TM1650_Set(0x6E,segNumber[5]);//初始化为5级灰度，开显示
						BUZZER_Config();
			    delay_20us(500);
		      
		     break;
		case	_KEY_TRG_4_FILTER:
		      
			  //  BUZZER_Config();
			  //  delay_20us(500);
				  TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
						TM1650_Set(0x68,segNumber[0]);//初始化为5级灰度，开显示
					    TM1650_Set(0x6A,segNumber[4]);//初始化为5级灰度，开显示
						TM1650_Set(0x6C,segNumber[7]);//初始化为5级灰度，开显示
						TM1650_Set(0x6E,segNumber[5]);//初始化为5级灰度，开显示
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
						key.value = key.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01
						
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



/******************************************************************************
 **
 ** Function Name:	KEY_Scan(uint8_t mode)
 ** Function : receive key input message 
 ** Input Ref:连续按键选择，1 -支持连续按键  0- 不支持连续按键 
  			  //  按键优先级 KEY0>KEY1>KEY2>WK_UP!!
 ** Return Ref: 0--没有按键按下， 1---有按键按下
 **   
 ******************************************************************************/
static uint8_t KEY_HDScan(uint8_t mode)
{
    static uint8_t key_up=1;     //°´¼üËÉ¿ª±êÖ¾

    if(mode==1)key_up=1;    // 支持连续按键
    if(key_up&&(POWER_KEY==1||WIND_KEY==1||TIMER_KEY==1||FILTER_KEY==1))
    {
        
		if(WIND_KEY==1 &&TIMER_KEY==1 )		return WINDTI_PRES;
		else if(POWER_KEY==1)       return POWER_PRES;
        else if(WIND_KEY==1)    return WIND_PRES;
        else if(TIMER_KEY==1)  return TIMER_PRES;
        else if(FILTER_KEY==1) return FILTER_PRES;
		
    }else if(WIND_KEY==0&&POWER_KEY==0&&TIMER_KEY==0&&FILTER_KEY==0)key_up=1;
    return 0;   //没有按键按下
}


/******************************************************************************
 **
 ** Function Name:	KEY_Scan(uint8_t mode)
 ** Function : receive key input message 
 ** Input Ref:连续按键选择，1 -支持连续按键  0- 不支持连续按键 
  			  //  按键优先级 KEY0>KEY1>KEY2>WK_UP!!
 ** Return Ref: 0--没有按键按下， 1---有按键按下
 **   
 ******************************************************************************/
 #if 0
uint8_t  KeyScan(void)
{
	uint8_t io_value;
	static uint8_t key_Press;  // 这个是要返回的键值
	static uint8_t key_Old = 0x00;
	static uint8_t DownCnt = 0; //按下计数
	static struct _sta{
		uint8_t up:		1;  //弹起
		uint8_t dn:		1;	//按下
		uint8_t rep:	1;
	}Status;  //按键状态标记
	uint8_t ret;  
	
	io_value = 0x00;
	ret = KEY_OFF;

	//获取当前按下的按键
	if (!Key1_ReadSta())io_value |= KEY_S1;
	if (!Key2_ReadSta())io_value |= KEY_S2;
	if (!Key3_ReadSta())io_value |= KEY_S3;
	if (!Key4_ReadSta())io_value |= KEY_S4;

	if (io_value) //如果按键被按下
	{
		if (key_Old == io_value) //判断与上次扫描到的是否为同一个按键
		{
			DownCnt++; //计数

			if(DownCnt < KEY_DOWN_CNT)//当前计数小于长按的时间
			{
				if (Status.rep == 0) // 不是重复
				{
					Status.dn = 1;
					key_Press = io_value; //记下按键
				}				
			}

			if (DownCnt >= KEY_DOWN_CNT) //当前计数大于长按的时间
			{
				Status.rep = 1;  //标记重复

				if(CntLongPress++ == KEY_REP_3S)//按下超过3秒
				{
					ret = io_value | KEY_LONG_FLAG; //加长按标记
				}
				else
				{
					ret = io_value | KEY_REP_FLAG; //重复
				}
				
				DownCnt = KEY_SPEED;	//重复起始值				
			}
		}
		key_Old = io_value;	 //记录键值
	}
	else  //按键松开
	{
		if (Status.dn && !Status.rep) //返回松开前的键值
		{
			ret = key_Press;
		}

		//清除标记
		Status.dn = 0;
		Status.rep = 0;
		DownCnt = 0;
		key_Old = KEY_NO;
	}

	return (KeyValue_ENUM)ret;  //返回键值
}
#endif 
//////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------------------------
/*****************************硬件I/O引脚定义,根据实际应用修改******************************/
//#define KEY_PORT           //PIND                                                                        // 独立按键所占用端口.

#define K_STOP              	P16// (1<<PD3)                                                                // "停止"键
#define K_START             P15 //(1<<PD4)                                                                // "启动"键
#define K_SEL              P14 // (1<<PD5)                                                                // "选择"键
#define K_ADD              P13  // (1<<PD6)                                                                // "+ "键
#define K_DEC                (1<<PD7)                                                                // "- "键
#define OneKeyTime        300                                                                                // 单键长按时长 = OneKeyTime * 10ms
#define MuxKeyTime        1100                                                                             // 组合键长按时长 = MuxKeyTime * 10ms
#define RepeatTime        5                                                                                // 单键连发功能重复间隔时间 = RepeatTime * 10ms

#define Key_Mask        (K_STOP|K_START|K_SEL|K_ADD|K_DEC)                        // 按键掩码值

//-------------------------------------------------------------------------------------------------------
#define GetKey()        (KEY_PORT & Key_Mask)                                                // 读取按键端口值

#define key_state_0        0                                                                                // 初始态.
#define key_state_1        1                                                                                // 确认态.
#define key_state_2        2                                                                                // 组合键,长按键确认态.
#define key_state_3        3                                                                                // 长按连发功能确认态.
#define key_state_4        4                                                                                // 等待释放态.

//-------------------------------------------------------------------------------------------------------
/****************************************数据类型定义**************************************/
typedef enum {NO_KEY,STOP,START,SEL,ADD,DEC,SETUP} eKEY;        // 按键返回值类型定义.

//-------------------------------------------------------------------------------------------------------
/*****************************************函数声明****************************************/
                                                                                      //读取按键.                                       

/********************************************************************************************
* eKEY ReadKey(void);
* 功能: 独立按键扫描,10ms扫描一次.
* 返回值:枚举类型,{NO_KEY,STOP,START,SEL,ADD,DEC,SETUP}.
* 参数:
********************************************************************************************/
static uint8_t ReadKey(void)
{
        static unsigned int key_time = 0;                                                        // 长按键计时
        static unsigned char key_state = 0;                                                // 记录按键扫当前描状态
        static unsigned char key_press_old = 0;                                        // 记录上一次按键状态
        static eKEY key_value_old = NO_KEY;                                                // 保存上一次按键返回值
        eKEY key_return = NO_KEY;                                                                // 按键功能返回值
        unsigned char key_press;
       
        //key_press = GetKey() ^ Key_Mask;                                             // 读按键I/O电平,只保留被按下的键(被按下的键位为1)
// looptkeytime:  
      key_press=KEY_HDScan(0);
looptkeytime:		switch (key_state)
        {
                case key_state_0:                                                                // 1.按键初始态
                        if (key_press)
                        {
                                key_state = key_state_1;                                        // 键被按下,状态转换到按键确认态
                                key_press_old = key_press;                                // 保存当前按键状态
                        }
                        break;
                case key_state_1:                                                                // 2.按键确认态
                        if (key_press == key_press_old)                                        // 与初始态的按键状态相同?
                        {
                                key_time = 0;                                                        // 清另按键时间计数器
                                switch(key_press)
                                {
                                        case POWER_PRES:
                                                key_state  = key_state_4;                         // 转按键释放态
                                                key_return = POWER_PRES;                                // "停止"键
                                                break;
                                        case 	WIND_PRES:
                                                key_state  = key_state_4;                         // 转按键释放态
                                                key_return = WIND_PRES;                                // "起动"键                                               
                                                break;       
                                        case  TIMER_PRES:
                                                key_state  = key_state_2;                         // 转长按键态
                                                key_return = TIMER_PRES;                                // "选择"键                                                               
                                                break;       
                                        case  FILTER_PRES:
                                                key_state  = key_state_2;                         // 转长按键态
                                                key_return = FILTER_PRES;                                // "+"键
                                                break;       
                                     
                                        case WINDTI_PRES  :                                        // "组合"键,长按键
                                                key_state  = key_state_2;                         // 组合键按键仍按下，状态转换到计时1
                                               break;  
												
                         					#if 0
												++key_time;                                                        // 按键计时
												if (key_press == WINDTI_PRES )                        // "配置"键?
												{
														if(key_time >= MuxKeyTime)                        // 组合键长按计时
														{
															//	key_state = key_state_4;                        // 按下时间>=MuxKeyTime,转到按键释放状态
																return WINDTI_PRES;                                // 组合键功能,"配置"键
														}
												}
												else
												{
														if(key_time >= OneKeyTime)                        // 单键长按计时
														{
																key_state = key_state_3;                        // 按下时间>=OneKeyTime,转到连发功能态,用于触发连发功能
																key_time = 0;                                        // 清按键计数器
																key_return = key_value_old;                // 返回上一次按键值
														}
												}
												goto looptkeytime;
												break;  
												#endif 
                                        default:
                                                key_state  = key_state_4;                         // 转按键释放态
                                                break;
                                }
                        }
                        else if (!key_press)
                            key_state = key_state_0;                                        // 按键已抬起(是干扰),转换到按键初始态
                        else
                                key_state = key_state_4;                                        // 按键已发生变化,转到按键释放态
                               
                               key_value_old = key_return;                                        // 保存按键返回值
                        break;
                case key_state_2:                                                                // 3.长按键确认态
                        if (key_press == key_press_old)
                        {
                                ++key_time;                                                        // 按键计时
                                if (key_press == WINDTI_PRES )                        // "配置"键?
                                {
                                        if(key_time >= MuxKeyTime)                        // 组合键长按计时
                                        {
                                                key_state = key_state_4;                        // 按下时间>=MuxKeyTime,转到按键释放状态
                                                key_return = WINDTI_PRES;                                // 组合键功能,"配置"键
                                        }
                                }
                                goto looptkeytime;
                                #if 0
                                else
                                {
                                        if(key_time >= OneKeyTime)                        // 单键长按计时
                                        {
                                                key_state = key_state_3;                        // 按下时间>=OneKeyTime,转到连发功能态,用于触发连发功能
                                                key_time = 0;                                        // 清按键计数器
                                                key_return = key_value_old;                // 返回上一次按键值
                                        }
                                }
                                #endif 
                        }
                        else
                                key_state = key_state_4;                                        // 按键已发生变化,转到按键释放态
                        break;
                case key_state_3:                                                                // 4.按键连发功能
                        if (key_press == key_press_old)
                        {
                                if (++key_time >= RepeatTime)                                // 按键时间计数
                                {
                                        key_time = 0;                                                // 按下时间>=0.05s，清0按键计数器
                                        key_return = key_value_old;                        // 返回上一次按键值
                                }                               
                        }
                        else
                            key_state = key_state_4;                                         // 按键已发生变化,转到按键释放态
                        break;
                case key_state_4:                                                                // 5.等待所有按键释放开
                        //if (!key_press)                                                                // 等待所有按键释放,才进入一次新的按键确认过程
                        if (key_press != key_press_old)                                        // 按键发生变化,就进入一次新的确认过程
                            key_state = key_state_0;                                         // 按键已释放,转换到初始态.
                        break;                       
        }       
    return key_return;
}









