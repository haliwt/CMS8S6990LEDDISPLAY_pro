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
    if(Telecom.childLock ==1 && Telecom.lockSonudKey==0){

     
        
              Telecom.lockSonudKey=1;
			    BUZZER_Config();
				delay_20us(10000)  ; 
			    BUZ_DisableBuzzer();

				BUZZER_Config();
				delay_20us(10000)  ; 
			    BUZ_DisableBuzzer();
				Telecom.WindSelectLevel =0x80;
				
	}
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

void Net_Data(void)
{
	if(Telecom.childLock ==1 && Telecom.lockSonudKey==0){
	
		
		   
				 Telecom.lockSonudKey=1;
				   BUZZER_Config();
				   delay_20us(10000)  ; 
				   BUZ_DisableBuzzer();
	
				   BUZZER_Config();
				   delay_20us(10000)  ; 
				   BUZ_DisableBuzzer();
				 
				   
	}
	if(Telecom.net_state ==1){


                     FLASH_Init();
                    BUZZER_Config();
                     delay_20us(5000)  ; 
                   BUZ_DisableBuzzer();
	              Telecom.net_state =0;


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
void Timer_Data(void)
{

   if(Telecom.childLock ==1 && Telecom.lockSonudKey==0){
	
		
		   
				 Telecom.lockSonudKey=1;
				   BUZZER_Config();
				   delay_20us(10000)  ; 
				   BUZ_DisableBuzzer();
	
				   BUZZER_Config();
				   delay_20us(10000)  ; 
				   BUZ_DisableBuzzer();
				 
				   
	}

     if(Telecom.TimerFlg == 1 && Telecom.childLock ==0 ) Telecom.TimerOn=1;
   	   



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
    uint16_t i=0,j;  
    for(i=0;i<n;i++) {
		for(j=0;j<10;j++){
		   _nop_(); }
		    _nop_(); 
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




