
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
    uint8_t cont=0,cont1=0,ONone=0;
    uint8_t d1,d2,d3;
    TMR1_Config();
	TMR0_Config();
    LED_GPIO_Init();
    UART0_Config();



  
	while(1)
	{

    
					
	

	   LEDDisplay_GreenColorRing();  
      // PM_SendData();  
	   
	
  
	   

	 #if 0

      
        
	   if(Telecom.power_state == 0){

	    

	       if(Telecom.TimerOn ==0){

				if(Telecom.TimerEvent >= 3) //5s 后，自动跳转到定时功能
	            {
					Telecom.TimerEvent = 0;
					Telecom.TimerOn =1;
				}
			}
			   
       
		//	if( Telecom.WindSelectLevel==wind_sleep){

	           //       LEDDisplay_SleepLamp();
			
			// }
			// else if(windLevelHighest ==1 && Telecom.WindSelectLevel == wind_auto){ //检查到PM值大于300 ，显示 “H”
                   
 			//	LED_DispHlogo();
				if( Telecom.WindSelectLevel==wind_auto){
				    cont ++;
				   if(cont >20)
				   	{
						cont =0;
					   PM_SendData();
					
			     	}
			    }
						    
		 	}
			 else {
			   
					TimerOnDisplay();
					if(NetRecMinute %  55  == 0 )
				  	{
				  	   Flash_ToWriteData();
                       if(NetRecMinute !=0 )
                        Telecom.net_dispnumb =1;
                    }
					//display LED
					if( Telecom.net_dispnumb ==1 ){
						   	    Telecom.net_dispnumb =0;
								 Flash_DisplayNumber();
						         LEDDisplay_GreenColorRing();
					}
					else if(Flash_ToReadDiffData()==3)LED_DispThreeRadin();
	                  else if(Flash_ToReadDiffData()==2)LED_DispTwoRadin();
					  else if(Flash_ToReadDiffData()==1)LED_DispOneRadin();
					  else if(Flash_ToReadDiffData()==5)LEDDisplay_RedColorRing(); //到更换滤网时间
					  else { 
					   	   // LEDDisplay_TimerTim(Telecom.TimeHour,Telecom.TimeMinute,Telecom.TimeBaseUint);
							LEDDisplay_GreenColorRing();
					  }
					  delay_20us(1000); // disp bug
			 }

			if( Telecom.WindSelectLevel==wind_auto){
			    cont ++;
			   if(cont >20)
			   	{
					cont =0;
				   PM_SendData();
				
		     	}
			}
			
	  	}
	  	     
	 	#endif 
	}	

}
  





















