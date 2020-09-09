#include "key.h"

//static uint8_t KEY_Scan(void);
key_types   key;

/******************************************************************************
 **
 ** Function Name:	void WindLevel_Data(void)
 ** Function : 延时10*n微秒 24MHz ,实际测试32us
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/

void WindLevel_Data(void)
{

    switch (Telecom.WindSelectLevel ){

		   case  wind_sleep :
			   LEDDisplay_SleepLamp();
			   Telecom.WindSelectLevel =wind_sleep;
			  OutputData(0x01);
			break;
			
			case wind_middle:
			
				OutputData(0x02);
				Telecom.WindSelectLevel =wind_middle;
			break;
				
			case wind_high:
				OutputData(0x03);
				Telecom.WindSelectLevel =wind_high;
		   break ;

		   case wind_auto:
					Telecom.WindSelectLevel =wind_auto;
			break;
		}


 }

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
/******************************************************************************
 **
 ** Function Name:	void delay_10us(uint16_t n) 
 ** Function : 延时10*n微秒 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/

void delay_us(uint16_t n)  
{  
    uint16_t i=0;  
    for(i=0;i<n;i++) {
		   _nop_();  
		  
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


//	if(POWER_KEY == 1)
	{
//		key.read &= ~0x01; // 0x1E
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
				if(++key.off_time>10)
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
		delay_20us(1000);
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
  if(temp !=0) {
      temp=0;
	

    BUZZER_Config();
	delay_20us(5000)  ; 
    BUZ_DisableBuzzer();

	BUZZER_Config();
	delay_20us(5000)  ; 
    BUZ_DisableBuzzer();	
				
  }
} 


/******************************************************************************
 **
 ** Function Name:	void TimerOnDisplay(void);
 ** Function : display timer time 
 ** Input Ref:
 ** Return Ref:
 **   
 ******************************************************************************/ 
void TimerOnDisplay(void)
{
	 if( Telecom.TimeBaseUint <  0){

		 if(Telecom.TimeHour==0 &&  Telecom.TimeMinute==0 )
			{             Telecom.TimeBaseUint=0;
						   Telecom.TimeMinute=0;
							Telecom.TimeHour=0;
							
			}
		    else{
				// Telecom.TimeBaseUint=9;//借一当十
			
				 if( Telecom.TimeMinute==0){
						if(Telecom.TimeHour==0 ){
							
						   Telecom.TimeBaseUint=0;
							Telecom.TimeMinute=0;
							Telecom.TimeHour=0;
				
						}
						else{
						    Telecom.TimeBaseUint=9;
							Telecom.TimeMinute=5;//借一当5  60分钟 进位 “小时”
							
							if(Telecom.TimeHour ==0){
								
								Telecom.TimeBaseUint=0;
								Telecom.TimeMinute=0;
								Telecom.TimeHour=0;
									
								
							}
							else if(Telecom.TimeHour > 0){
								
								Telecom.TimeHour --	;					  
								Telecom.TimeMinute=5;//借一当5
								 Telecom.TimeBaseUint=9;
								
							}
									
						}			
				    }
			        else if(Telecom.TimeMinute > 0) { //借位 十位
						Telecom.TimeMinute --	;					  
						Telecom.TimeBaseUint=9;//借一当十
		   }						  
		} 
	}
}





