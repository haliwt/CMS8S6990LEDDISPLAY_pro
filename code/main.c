
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
    uint8_t cont=0,cont1=0,ONone=0,ver;
    uint8_t d1,d2,d3;
    
    TMR1_Config();
	TMR0_Config();
    LED_GPIO_Init();
    UART0_Config();



  
	while(1)
	{
        
        
          if(usartdat.usart_1 == 0xAA ){
             
             ver = BCC(usartdat.usart_2);
            if(ver == usartdat.usart_3){
				Telecom.power_state = usartdat.usart_2 & 0x80;
			    Telecom.childLock = usartdat.usart_2 & 0x40;
			    Telecom.TimerOn  = usartdat.usart_2 & 0x20;
				Telecom.net_state =   usartdat.usart_2 & 0x10;
				Telecom.WindSelectLevel = usartdat.usart_2 & 0x0f;
                 
            }
        }
	   else if(usartdat.usart_2 == 0xAA ){
             
             ver = BCC(usartdat.usart_3);
            if(ver == usartdat.usart_1){
				Telecom.power_state = usartdat.usart_3 & 0x80;
			    Telecom.childLock = usartdat.usart_3 & 0x40;
			    Telecom.TimerOn  = usartdat.usart_3 & 0x20;
				Telecom.net_state =   usartdat.usart_3 & 0x10;
				Telecom.WindSelectLevel = usartdat.usart_3 & 0x0f;
                 
            }
        }
        else if(usartdat.usart_3 == 0xAA ) {
             
             ver = BCC(usartdat.usart_1);
            if(ver == usartdat.usart_2){
				Telecom.power_state = usartdat.usart_1 & 0x80;
			    Telecom.childLock = usartdat.usart_1 & 0x40;
			    Telecom.TimerOn  = usartdat.usart_1 & 0x20;
				Telecom.net_state =   usartdat.usart_1 & 0x10;
				Telecom.WindSelectLevel = usartdat.usart_1 & 0x0f;
                 
            }
        }

   // if(usartdat.usart_1 == 0x80)Telecom.power_state = 1;
	//	 if(usartdat.usart_3 == 0x80)Telecom.power_state = 1;
		// if(usartdat.usart_2 == 0x80)Telecom.power_state = 1;
#if 1
       d3= (usartdat.usart_2 /100) %10;
	   d2= (usartdat.usart_2 /10) %10;
	   d1= usartdat.usart_2 % 10;
	   LEDDisplay_TimerTim(d3,d2,d1);
	   delay_20us(40000);
	   delay_20us(40000);
	   delay_20us(40000);
	   delay_20us(40000);
	   delay_20us(40000);
	   delay_20us(40000);
	    if(usartdat.usart_1 == 128)Telecom.power_state = 1;
		 if(usartdat.usart_3 == 128)Telecom.power_state = 1;
		 if(usartdat.usart_2 == 128)Telecom.power_state = 1;
	    d3= (usartdat.usart_1 /100) %10;
	   d2= (usartdat.usart_1 /10) %10;
	   d1= usartdat.usart_1 % 10;
	   LEDDisplay_TimerTim(d3,d2,d1);
	   delay_20us(40000);
	   delay_20us(40000);
	   delay_20us(40000);
	   delay_20us(40000);
	   delay_20us(40000);
	   delay_20us(40000);
	    if(usartdat.usart_3 == 128)Telecom.power_state = 1;
	     d3= (usartdat.usart_3 /100) %10;
	   d2= (usartdat.usart_3 /10) %10;
	   d1= usartdat.usart_3 % 10;
	   LEDDisplay_TimerTim(d3,d2,d1);
	   delay_20us(40000);
	   delay_20us(40000);
	   delay_20us(40000);
	   delay_20us(40000);
	   delay_20us(40000);
	   delay_20us(40000);
	   if(usartdat.usart_2 == 128)Telecom.power_state = 1;

	   #endif 
      #if 1

       if(Telecom.power_state == 1){
           LEDDisplay_GreenColorRing();
	      if(Telecom.childLock ==1){
        
              Telecom.lockSonudKey=0;
			    BUZZER_Config();
				delay_20us(10000)  ; 
			    BUZ_DisableBuzzer();

				BUZZER_Config();
				delay_20us(10000)  ; 
			    BUZ_DisableBuzzer();
				if(NetRecMinute %  55  == 0 )
				  {
				  	   Flash_ToWriteData();
                       if(NetRecMinute !=0 )
                        Telecom.net_dispnumb =1;
                  } 
		}
	    else {

	    

	  
		  WindLevel_Data();
       
		  if( Telecom.WindSelectLevel==wind_sleep){

	                 LEDDisplay_SleepLamp();
					 if(NetRecMinute %  55  == 0 )
				  	{
				  	   Flash_ToWriteData();
                       if(NetRecMinute !=0 )
                        Telecom.net_dispnumb =1;
                    } 
			
			}
		  else{ 
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
					   	     LEDDisplay_TimerTim(PM_3,PM_2,PM_1);
							LEDDisplay_GreenColorRing();
					  }
					  delay_20us(1000); // disp bug
			

					if( Telecom.WindSelectLevel==wind_auto){
					    cont ++;
					   if(cont >20)
					   	{
							cont =0;
						   PM_SendData();
						
				     	}
					}
			
	  	     }
	    }
	 	#endif 
	}
}
}   


  





















