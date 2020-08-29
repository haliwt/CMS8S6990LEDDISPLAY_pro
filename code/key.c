#include "key.h"
#include "demo_buzzer.h"

#include "demo_timer.h"
#include "myflash.h"

//static uint8_t KEY_Scan(void);
key_types   key;

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

	GPIO_SET_MUX_MODE(P22CFG, GPIO_MUX_GPIO);   //	PM2.5 sensor Input
	GPIO_ENABLE_INPUT(P2TRIS, GPIO_PIN_2);
	GPIO_ENABLE_UP(P2UP,GPIO_PIN_2) ;
	
    GPIO_SET_MUX_MODE(P02CFG,GPIO_MUX_GPIO);   //开机按键  P02
	GPIO_ENABLE_INPUT(P0TRIS,GPIO_PIN_2); 
	GPIO_ENABLE_RD(P0RD,GPIO_PIN_2) ; 
   
    
    
    
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

	uint8_t  temp8;
	temp8 = KEY_Scan();
	
	switch(temp8)
	{


		case	_KEY_CONT_3_TIMER: //长按按键按键值
		      //   BUZZER_Config();
			  
		          TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
						TM1650_Set(0x68,segNumber[0]);//初始化为5级灰度，开显示
					    TM1650_Set(0x6A,segNumber[1]);//初始化为5级灰度，开显示
						TM1650_Set(0x6C,segNumber[1]);//初始化为5级灰度，开显示
						TM1650_Set(0x6E,segNumber[1]);//初始化为5级灰度，开显示
				
			break;
			
		case _KEY_CONT_2_WIND :
		      //  BUZZER_Config();
			   
		          TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
						TM1650_Set(0x68,segNumber[0]);//初始化为5级灰度，开显示
					    TM1650_Set(0x6A,segNumber[2]);//初始化为5级灰度，开显示
						TM1650_Set(0x6C,segNumber[2]);//初始化为5级灰度，开显示
						TM1650_Set(0x6E,segNumber[2]);//初始化为5级灰度，开显示
		
		break;
		
		case _KEY_CONT_1_POWER :
		      //  BUZZER_Config();
			   
		          TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
						TM1650_Set(0x68,segNumber[0]);//初始化为5级灰度，开显示
					    TM1650_Set(0x6A,segNumber[3]);//初始化为5级灰度，开显示
						TM1650_Set(0x6C,segNumber[3]);//初始化为5级灰度，开显示
						TM1650_Set(0x6E,segNumber[3]);//初始化为5级灰度，开显示
		
		break;
		
	     case _KEY_CONT_4_FILTER :
		     //   BUZZER_Config();
			
		          TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
						TM1650_Set(0x68,segNumber[0]);//初始化为5级灰度，开显示
					    TM1650_Set(0x6A,segNumber[4]);//初始化为5级灰度，开显示
						TM1650_Set(0x6C,segNumber[4]);//初始化为5级灰度，开显示
						TM1650_Set(0x6E,segNumber[4]);//初始化为5级灰度，开显示
		
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
				if(++key.on_time> 100) //消抖  0.5us
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
uint8_t KEY_HDScan(uint8_t mode)
{
    
	static uint8_t key_up=1;     //°´¼üËÉ¿ª±êÖ¾
    if(mode==1)key_up=1;    // 支持连续按键
    if(key_up&&(WIND_KEY==1&&TIMER_KEY==1))
    {
       
        key_up =0 ;
		if(WIND_KEY==1 &&TIMER_KEY==1 )		return WINDTI_PRES;
	//	else if(POWER_KEY==1)       return POWER_PRES;
     //   else if(WIND_KEY==1)    return WIND_PRES;
     //   else if(TIMER_KEY==1)  return TIMER_PRES;
    //    else if(FILTER_KEY==1) return FILTER_PRES;
		
    }else if(WIND_KEY==0&&TIMER_KEY==0)key_up=1;
    return 0;   //没有按键按下
}
/******************************************************************************
 **
 ** Function Name:	void LockKey_Fuction(void)
 ** Function : receive key input message 
 ** Input Ref:连续按键选择，1 -支持连续按键  0- 不支持连续按键 
  			  //  按键优先级 KEY0>KEY1>KEY2>WK_UP!!
 ** Return Ref: 0--没有按键按下， 1---有按键按下
 **   
 ******************************************************************************/
void LockKey_Function(void)
{
   uint8_t  temp=0;
  temp = KEY_Scan();
  if(temp !=0)
  {
                BUZZER_Config();
			    delay_20us(1000);
	           BUZ_DisableBuzzer();	
				BUZZER_Config();
			    delay_20us(1000);
	            BUZ_DisableBuzzer();
                delay_20us(1000);
                 BUZZER_Config();
                 delay_20us(1000);
                 BUZ_DisableBuzzer();
		
   }


}
  






