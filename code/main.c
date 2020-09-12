
#include "cms8s6990.h"
#include "demo_timer.h"
#include "demo_buzzer.h"
#include "timer0.h"
#include "key.h"
#include "led.h"
#include "tm1629d.h"
#include "timer2.h"
#include "output.h"
#include "buzzer.h"
#include "demo_uart.h"


uint32_t Systemclock = 24000000;

Telec Telecom;

uint8_t windLevelHighest ;
uint8_t flashflg=0;
struct usarts  usartdat;


/*******************************************************
	*
	*Function Name: int main(void)
	*
	*
	*
*******************************************************/
int main(void)
{		
   
    uint8_t cont =0,vair;
    TMR1_Config();
	TMR0_Config();
    LED_GPIO_Init();
    UART0_Config();

	while(1)
	{
        
		if(Telecom.power_state == 1 ){
#if 0
		if(Telecom.childLock ==1  ){
			    UART0_Config();
				
			if(Telecom.WindSelectLevel == 0x08){
			   if(Telecom.lockSonudKey ==0){
			   		Telecom.lockSonudKey ++ ;
					BUZZER_Config();
					delay_20us(2000)  ; 
					BUZ_DisableBuzzer();
					delay_20us(2000)  ; 
					BUZZER_Config();
					delay_20us(2000)  ; 
					BUZ_DisableBuzzer();
					
				 }
				
			}

		}

        else
		#endif
		 {
		
		  if(Telecom.WindSelectLevel == 0x01){

			  if(Telecom.lockSonudKey ==0){
			   	Telecom.lockSonudKey ++ ;
		        BUZZER_Config();
			     delay_20us(2000)  ; 
			    BUZ_DisableBuzzer();
		       	}
			  OutputData(0x01);
			  Telecom.WindSetupLevel=wind_sleep;

		  }
		  if(Telecom.WindSelectLevel == 0x02){
			
		     	if(Telecom.lockSonudKey ==0 ){
			   		Telecom.lockSonudKey ++ ;
		       		BUZZER_Config();
					delay_20us(2000)  ; 
			  		BUZ_DisableBuzzer();
			     }
				OutputData(0x02);
				Telecom.WindSetupLevel=wind_middle;
			
		  }
			
			
				
		if(Telecom.WindSelectLevel == 0x03){
			
		if(Telecom.lockSonudKey ==0){
			   	Telecom.lockSonudKey ++ ;
		       BUZZER_Config();
		        delay_20us(2000)  ; 
			    BUZ_DisableBuzzer();
			    }
				OutputData(0x03);
				Telecom.WindSetupLevel=wind_high;
				
				
		}

		if(Telecom.WindSelectLevel == 0x04){
		   	  if(Telecom.lockSonudKey ==0){
			      Telecom.lockSonudKey ++ ;
		          BUZZER_Config();
				 delay_20us(2000)  ; 
			     BUZ_DisableBuzzer();
		       	}
				Telecom.WindSetupLevel=wind_auto;
		}
	
	
		}
#if 1
		if(Telecom.WindSetupLevel==wind_sleep ){
			LEDDisplay_SleepLamp();
			 
		
		} 
		else if(Telecom.WindSetupLevel==wind_high || Telecom.WindSetupLevel==wind_middle) {

				LEDDisplay_TimerTim(PM_3,PM_2,PM_1);
				LEDDisplay_GreenColorRing();
				
				 
		}
		else if(Telecom.WindSetupLevel==wind_auto && Telecom.WindSetupLevel!=wind_sleep ){

			 LED_DispPMLogo();
             PM_SendData();
			#if 0
			if(Flash_ToReadDiffData()==3)LED_DispThreeRadin();
			else if(Flash_ToReadDiffData()==2)LED_DispTwoRadin();
			else if(Flash_ToReadDiffData()==1)LED_DispOneRadin();
			else if(Flash_ToReadDiffData()==5)LEDDisplay_RedColorRing(); //到更换滤网时间
			else { 
					LEDDisplay_TimerTim(PM_3,PM_2,PM_1);
					LEDDisplay_GreenColorRing();
			}
			#endif 
			LED_DispPMLogo();
			LEDDisplay_GreenColorRing();
		

		}
			if(NetRecMinute %  55  == 0 )
			{
				Flash_ToWriteData();
				
			} 
	    
		
	 	#endif 
}
	}

	
}




  





















