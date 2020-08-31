
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

extern uint8_t  vairI;
extern uint16_t timer0_ten_num;
extern uint16_t timer0_num;
extern uint16_t rec_num;
extern uint16_t rec2_num;


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
	uint16_t disp =0,pmarr[10];
    static uint16_t cont=0;
	uint8_t poweron=0,i=0,j=0,disdat3=0,disdat2=0,disdat1=0;
    static uint8_t wdl=0;

    TMR1_Config();
	TMR0_Config();
    GPIO_Config();
	GPIO_Interrupt_Init();
    LED_GPIO_Init();




	while(1)
	{	
	 
  
       
        if(childLock  ==1){
            if(BuzzerSound==1){
                 BUZZER_Config();
				delay_20us(1000);
			    BUZ_DisableBuzzer();
               BuzzerSound =0;
               
            }
           LockKey_Function();					
        
        }
        else if(childLock  ==0){
            if(BuzzerSound==1){
                   BUZZER_Config();
				delay_20us(1000);
	            BUZ_DisableBuzzer();
               BuzzerSound =0;
            }
           
             KEY_Handing();
        
        }

	   if(timer0_num > 9000 && Telecom.power_state == 1){
	  	       timer0_num =0;

				i++;
            if(vairI==0){
                disp =rec_num ;
                vairI=1;
			    disdat3 = (rec_num /100) %10;   //百位
				disdat2 = (rec_num /10) %10;  //十位
				disdat1 = rec_num  %10;        //个位
            }
            else {
                disp = rec2_num;
                vairI=0;
			    disdat3 = (rec2_num /100) %10;   //百位
				disdat2 = (rec2_num /10) %10;  //十位
				disdat1 = rec2_num  %10;        //个位
            }
			if(disp >2){
				if(i==1)pmarr[i-1]=disp;
				else if(i==2)pmarr[i-1]=disp;
				else if(i==3)pmarr[i-1]=disp;
				else if(i==4)pmarr[i-1]=disp;
				else if(i==5)pmarr[i-1]=disp;
				else if(i==6)pmarr[i-1]=disp;
				else if(i==7)pmarr[i-1]=disp;
				else if(i==8)pmarr[i-1]=disp;
				else if(i==9)pmarr[i-1]=disp;
				else if(i==10)pmarr[i-1]=disp;
			}
			
            LEDDisplay_TimerTim(disdat3,disdat2,disdat1);
        
            timer0_num =0;
			if(i==1){
				for(j=0;j<10;j++)
				{
				  Telecom.PMaverageValue = Telecom.PMaverageValue + pmarr[i];
					
				}
                Telecom.PMaverageValue = Telecom.PMaverageValue / 10;
				if(Telecom.PMaverageValue < 75) wdl = wind_sleep;
				else if(Telecom.PMaverageValue > 75 && Telecom.PMaverageValue <150)wdl = wind_middle;
				else if(Telecom.PMaverageValue > 150 && Telecom.PMaverageValue  < 300)wdl = wind_high;
				else if(Telecom.PMaverageValue > 300)wdl = wind_high;
            }
            
			OutputData(wdl);
			 if(Telecom.power_state==1){

				 LEDDisplay_GreenColorRing();
			  }
         }	
       #if 1
		if(Telecom.power_state == 0){
				
				cont++;
		        if(cont >=1000){
					
                    LEDDisplay_TurnOff();
                    if(timer0_num >8000) {
                        cont=0;
                        timer0_num=0;
                    }
                    
				}
                else{
                     LEDDisplay_RedColorRing();
                    cont++;
                }
			   
        }
		else{

           LEDDisplay_GreenColorRing();
		}
		#endif 
	    #endif 

	} 


}
















