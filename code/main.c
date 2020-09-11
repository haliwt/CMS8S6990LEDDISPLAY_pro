
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
   
    uint8_t cont =0;
    uint8_t arr[2];
    TMR1_Config();
	TMR0_Config();
    LED_GPIO_Init();
    UART0_Config();

	while(1)
	{
        


	  if(Telecom.power_state == 1 ){

		if(Telecom.childLock ==1 ){
			    
				
				
			 if(Telecom.WindSelectLevel == 0x08){

				   Telecom.WindSelectLevel =0;
					BUZZER_Config();
					delay_20us(2000)  ; 
					BUZ_DisableBuzzer();
					delay_20us(2000)  ; 
					BUZZER_Config();
					delay_20us(2000)  ; 
					BUZ_DisableBuzzer();
					arr[0]= arr[1];
				 }
				
				

		}
        else {
		switch (Telecom.WindSelectLevel){

			  case  0x01 :
		       if(Telecom.lockSonudKey ==0){
			   	Telecom.lockSonudKey ++ ;
		        BUZZER_Config();
			     delay_20us(2000)  ; 
			    BUZ_DisableBuzzer();
		       	}
			  OutputData(0x01);
			  Telecom.WindSetupLevel=wind_sleep;
			break;
			
			case 0x02:
				if(Telecom.lockSonudKey ==0 ){
			   		Telecom.lockSonudKey ++ ;
		       		BUZZER_Config();
					delay_20us(2000)  ; 
			  		BUZ_DisableBuzzer();
			     }
				OutputData(0x02);
				Telecom.WindSetupLevel=wind_middle;
				
				
			break;
				
			case 0x03:
			
			    if(Telecom.lockSonudKey ==0){
			   	Telecom.lockSonudKey ++ ;
		       BUZZER_Config();
		        delay_20us(2000)  ; 
			    BUZ_DisableBuzzer();
			    }
				OutputData(0x03);
				Telecom.WindSetupLevel=wind_high;
				
				
		   break ;

		   case 0x04:
		   	  if(Telecom.lockSonudKey ==0){
			      Telecom.lockSonudKey ++ ;
		          BUZZER_Config();
				 delay_20us(2000)  ; 
			     BUZ_DisableBuzzer();
		       	}
				Telecom.WindSetupLevel=wind_auto;
					
			break;
			default :
					Telecom.WindSetupLevel=wind_auto;
			break;
		}
	
		}
		if(Telecom.WindSetupLevel==wind_sleep){
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
			delay_20us(1000); // disp bug

		}
			if(NetRecMinute %  55  == 0 )
			{
				Flash_ToWriteData();
				if(NetRecMinute !=0 )
				Telecom.net_dispnumb =1;
			} 
	    
		
	 	
	 }
	  	}
	}




  





















