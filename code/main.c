
#include "cms8s6990.h"
#include "demo_timer.h"
#include "demo_buzzer.h"
#include "timer0.h"
#include "key.h"
#include "led.h"
#include "tm1629d.h"
#include "timer2.h"
#include "output.h"


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
	uint8_t poweron=0,i=0,j=0;
    static uint8_t wdl=0;

    TMR1_Config();
	TMR0_Config();
    GPIO_Config();
    LED_GPIO_Init();




	while(1)
	{	
	   

		//Tm1629DDis();
		
        if(childLock  ==1){
            if(BuzzerSound==1){
                 BUZZER_Config();
				delay_20us(1000);
	           DisableBUZZER_Config();
               BuzzerSound =0;
               
            }
           LockKey_Function();					
        
        }
        else if(childLock  ==0){
            if(BuzzerSound==1){
                   BUZZER_Config();
				delay_20us(1000);
	           DisableBUZZER_Config();
               BuzzerSound =0;
            }
           
             KEY_Handing();
        
        }

	  if(timer0_num > 9000){
	  			i++;
            if(vairI==0){
                disp =rec_num ;
                vairI=1;
            }
            else {
                disp = rec2_num;
                vairI=0;
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
           // Tm1629DDis();
        
            timer0_num =0;
			if(i==1){
				for(j=0;j<10;j++)
				{
				  Telecom.PMaverageValue = Telecom.PMaverageValue + pmarr[i];
					
				}
                Telecom.PMaverageValue = (Telecom.PMaverageValue * 4)/ 10;
				if(Telecom.PMaverageValue < 75) wdl = wind_sleep;
				else if(Telecom.PMaverageValue > 75 && Telecom.PMaverageValue <150)wdl = wind_middle;
				else if(Telecom.PMaverageValue > 150 && Telecom.PMaverageValue  < 300)wdl = wind_high;
				else if(Telecom.PMaverageValue > 300)wdl = wind_high;
            }
            
			OutputData(wdl);
			
         }		

	} 


}
















