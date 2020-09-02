
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
	uint16_t disp =0,pmarr[10],cont=0;
	uint8_t poweron=0,i=0,j=0,disdat3=0,disdat2=0,disdat1=0,cont1;
    static uint8_t lockflg=0;

    TMR1_Config();
	TMR0_Config();
    GPIO_Config();
    TMR3_Config();

    LED_GPIO_Init();




	while(1)
	{	
           

		 #if 1
 	    if(childLock  ==1){
            if(BuzzerSound==1){
                BUZZER_Config();
				
	            delay_20us(20000);
			    BUZ_DisableBuzzer();
               BuzzerSound =0;
               
            }
           LockKey_Function();					
        
        }
        else if(childLock  ==0){
            if(BuzzerSound==1){
                   BUZZER_Config();
				  delay_20us(20000);
	                 BUZ_DisableBuzzer();
               BuzzerSound =0;
               
            }
           
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
			   
        }
		else{
			LEDDisplay_GreenColorRing();
            
		}
			
        }
        
	 
	    if( Telecom.power_state == 1){

			if(Telecom.TimerOn ==0 &&  Telecom.keyEvent ==0){
				if(Telecom.TimerEvent >= 5)
	            {
					Telecom.TimerEvent = 0;
					Telecom.TimerOn =1;
					

				}
			}
next:			if(Telecom.TimerOn ==1) TimerOnDisplay();

			 
			   LEDDisplay_TimerTim(Telecom.TimeHour,Telecom.TimeMinute,Telecom.TimeBaseUint);
			    cont ++;
			   if(cont >500)
			   	{
			   	 cont =0;
			  	 PM_SendData();
			     goto next;
			   	}


		 }
	   
    
	   #endif 

	} 


}
















