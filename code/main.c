
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


uint32_t Systemclock = 24000000;



struct _WindLevel_ wdl;

Telec Telecom;



/*******************************************************
	*
	*Function Name: int main(void)
	*
	*
	*
*******************************************************/
int main(void)
{		
    uint8_t cont=0,cont1=0;
    TMR1_Config();
	TMR0_Config();
   // GPIO_Config();
    TMR3_Config();

    LED_GPIO_Init();
   GPIO_Interrupt_Init();

  
	while(1)
	{	

       //Flash_ToWriteData();
	  // Flash_ToReadData();
	//  TestFlash_ToWriteAndReadData();
	//PM_SendData();

/***************************************************************************/
	 #if 1

     if(childLock  ==1){
            if(BuzzerSound==1){
                BuzzerSound =0;
				BUZZER_Config();
				delay_20us(5000)  ; 
		        BUZ_DisableBuzzer();	
				
		   GPIO_ClearIntFlag(GPIO1, GPIO_PIN_7);
		   GPIO_ClearIntFlag(GPIO1, GPIO_PIN_6);
		   GPIO_ClearIntFlag(GPIO1, GPIO_PIN_5);
		   GPIO_ClearIntFlag(GPIO1, GPIO_PIN_4);
				 Telecom.criticalKey=1;
			}
			BuzzerSound =0;
	
		   GPIO_ClearIntFlag(GPIO1, GPIO_PIN_7);
		   GPIO_ClearIntFlag(GPIO1, GPIO_PIN_6);
		   GPIO_ClearIntFlag(GPIO1, GPIO_PIN_5);
		   GPIO_ClearIntFlag(GPIO1, GPIO_PIN_4);
		   Telecom.criticalKey=0;
        
        }
        else if(childLock  ==0){
			if(BuzzerSound==1 ){
				BuzzerSound =0;
				BUZZER_Config();
				delay_20us(5000)  ; 
				Telecom.criticalKey=1;
				BUZ_DisableBuzzer();
			   GPIO_ClearIntFlag(GPIO1, GPIO_PIN_7);
			   GPIO_ClearIntFlag(GPIO1, GPIO_PIN_6);
			   GPIO_ClearIntFlag(GPIO1, GPIO_PIN_5);
			   GPIO_ClearIntFlag(GPIO1, GPIO_PIN_4);
			}
			BuzzerSound =0;
			BUZ_DisableBuzzer();
			Telecom.criticalKey=0;
			KEY_Handing();

			if(Telecom.power_state == 0){

					cont++;
					if(cont >=50){

						LEDDisplay_TurnOff();
						cont1++;
						if(cont1>=100){
							cont1=0;
							cont=0;
						}
					}
					else{
						LEDDisplay_RedColorRing();
					}
					if(Telecom.power_state==0 && Telecom.PowerOnFrequency % 2==0 && Telecom.PowerOnFrequency !=0){

						
                        Flash_ToWriteData();

				  }
				 
              }
		}
        
	  if(Telecom.power_state == 1){
	           
				if(Telecom.TimerOn ==0 &&  Telecom.keyEvent ==0){
					if(Telecom.TimerEvent >= 5) //5s 后，自动跳转到定时功能
		            {
						Telecom.TimerEvent = 0;
						Telecom.TimerOn =1;
					}
			   }

			   if( Telecom.WindSelectLevel==wind_sleep){
	                  LEDDisplay_SleepLamp();
			
			   	}   
			    else{ 
                   LEDDisplay_GreenColorRing();
				   TimerOnDisplay();
				   LEDDisplay_TimerTim(Telecom.TimeHour,Telecom.TimeMinute,Telecom.TimeBaseUint);
				   if( Telecom.WindSelectLevel==wind_auto){
					    cont ++;
					   if(cont >100)
					   	{
							cont =0;
						   PM_SendData();
						
				     	}

				  }
			   }
	 			#endif 
	    	}
	}
    

}



















