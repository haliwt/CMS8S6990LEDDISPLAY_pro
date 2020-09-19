
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
   
    static uint8_t cont =0,ReceiveData=0,ReceiveRefData=0;
	static uint8_t childlockflg =0,icount=0,timerOn=0;
	static uint8_t ReceiveTimerDatat =0,timecount=0,timingflg =0 ;
    uint8_t arr[2],timing[2];
    TMR1_Config();
	TMR0_Config();
    LED_GPIO_Init();
    UART0_Config();
	GPIO_PMConfig(); //PM GPIO port

	while(1)
	{

		
		ReceiveData =usartdat.usart_1; //usartdat.usart_1;
		ReceiveRefData= usartdat.usart_2;
		ReceiveTimerDatat = usartdat.usart_3;
		
	   
			Telecom.power_state = ReceiveData >> 7;  //power on flg
			Telecom.childLock  = ReceiveData >> 6;    //Chilid Lock flg 
			Telecom.timer_state = ReceiveData >>5; //timer time  flg
			Telecom.netResetflg = ReceiveData >>4;   //Be changed net flg
			Telecom.WindSelectLevel = ReceiveData & 0x0f;
		
		
		if(Telecom.power_state == 1 ){
			Telecom.PowerOnFrequency=1;

		    if(Telecom.childLock ==1){
				      childlockflg =1;
				      cont ++;
					  if(cont >250)cont=1;
					  if(cont ==1)
				          arr[0] = Telecom.WindSelectLevel;
					  else { // Turn on nondeterminacy
					  	  arr[1] = Telecom.WindSelectLevel;
						  cont =0;
					   }
					  if(arr[0]==arr[1])Telecom.lockSonudKey =1;
					  else Telecom.lockSonudKey =0;

			          
				    if(Telecom.lockSonudKey == 0){ 
						
						Telecom.lockSonudKey =1;
                 
						BUZZER_Config();
						delay_20us(400)  ; 
						BUZ_DisableBuzzer();
						delay_20us(400)  ; 
						BUZZER_Config();
						delay_20us(400)  ; 
						BUZ_DisableBuzzer();
				    }
				
		    }
		   else {
			          icount ++;
					  if(icount >250)icount=1;
					  if(icount ==1)
				          arr[0] = ReceiveRefData;
					  else {
					  	  arr[1] = ReceiveRefData;
						  icount =0;
					   }
					  if(arr[0]==arr[1])Telecom.lockSonudKey =1;
					  else Telecom.lockSonudKey =0;
					  
					 

			        if(Telecom.lockSonudKey == 0 ){ 
						
						Telecom.lockSonudKey =1;
                 
						BUZZER_Config();
						delay_20us(400)  ; 
						BUZ_DisableBuzzer();
						delay_20us(400)  ; 
						if(childlockflg == 1){
							
							childlockflg =0;
							BUZZER_Config();
							delay_20us(400)  ; 
							BUZ_DisableBuzzer();
							delay_20us(400)  ; 
							
						}
					}
					
	
			   switch (Telecom.WindSelectLevel){

					case  0x01 :
				       OutputData(0x01);
					   Telecom.WindSetupLevel=wind_sleep;
					  
				       
					  
					break;
					
					case 0x02:
						
						OutputData(0x02);
						Telecom.WindSetupLevel=wind_middle;
						
						
					break;
						
					case 0x03:
					    OutputData(0x03);
						Telecom.WindSetupLevel=wind_high;
					
						
						 break ;

				   case 0x04:
				   	
						Telecom.WindSetupLevel=wind_auto;
					
					break;
					default :
					       Telecom.WindSetupLevel=wind_auto;
					
					break;
				
				}
            
				
				if(Telecom.WindSetupLevel==wind_sleep){
					LEDDisplay_SleepLamp();
					 
				
				} 
				else if(Telecom.WindSetupLevel==wind_high || Telecom.WindSetupLevel==wind_middle) {

						LEDDisplay_TimerTim(PM_3,PM_2,PM_1);
						LEDDisplay_GreenColorRing();
				}
				else if(Telecom.WindSetupLevel==wind_auto ){

				
		            PM_SendData();
					LEDDisplay_TimerTim(PM_3,PM_2,PM_1);
					#if 1
					if(Flash_ToReadDiffData()==3)LED_DispThreeRadin();
					else if(Flash_ToReadDiffData()==2)LED_DispTwoRadin();
					else if(Flash_ToReadDiffData()==1)LED_DispOneRadin();
					else if(Flash_ToReadDiffData()==5)LEDDisplay_RedColorRing(); //到更换滤网时间
					else { 
							LEDDisplay_TimerTim(PM_3,PM_2,PM_1);
							LED_DispPMLogo();
							LEDDisplay_GreenColorRing();
					}
					#endif 
					//LED_DispPMLogo();
					//LEDDisplay_GreenColorRing();
					

				}
				
				if(Telecom.timer_state  == 1) //timer setup for times 
				{
				     timecount ++ ;
					 Telecom.TimerOn =1;
					 if(timecount ==1)timing[0] = ReceiveTimerDatat;
					 else if(timecount ==2){
						 timing[1] = ReceiveTimerDatat;
						 timecount =0;
					 }
					 if(timing[0]==timing[1])timingflg = 1;  //the same timer timing ,don't recoder the second timing
					 else  timingflg = 0;
					
					 if(timingflg==0){
					        Telecom.TimeBaseUint = ReceiveTimerDatat;
							timingflg = 1;
					 }
					 
				
					 if(Telecom.TimeBaseUint ==0){
						 
						 Telecom.power_state =0;
						 timerOn =0;
						 timingflg =0;
						 LEDDisplay_TimerTim(segNumber[7],segNumber[7],segNumber[7]);
						
					  }
					 
				}
				else timingflg =0;
				
				if(Telecom.netResetflg == 1){ //be changed net 
					FLASH_Init(); //clear recoder times hours
					Telecom.netResetflg =0;
				}
				else{
					if(NetRecMinute %  55  == 0 )
					{
						Flash_ToWriteData();
						if(NetRecMinute !=0 )
						Telecom.net_dispnumb =1;
					} 
			    
				}
			 	
			 }
		}
		else{ //turn off be recived times
                LEDDisplay_TurnOff();
			 
						
				if(Telecom.PowerOnFrequency ==1){
					Telecom.PowerOnFrequency ++ ;
                    Flash_ToWriteData();

				}
			
			
		}
	
	}

}


  





















