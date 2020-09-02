#include "demo_buzzer.h"
#include "key.h"
#include "myflash.h"

#include "output.h"

uint16_t getMinute;
uint8_t TimerCnt;

uint8_t  BuzzerSound ;

volatile uint16_t Timer1_num;
uint8_t childLock ;
static uint8_t locklg=0;
uint8_t Timer2_num=0;
uint8_t CC2_num =0;


uint16_t timer0_num;
uint16_t timer0_ten_num;
uint8_t  vairI;
uint16_t rec_num;
uint16_t rec2_num;
uint16_t timer0_20ms_num;
uint16_t timer0_duty_num;



/******************************************************************************
 ** \brief	 INT0 interrupt service function
 **			
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void INT0_IRQHandler(void)  interrupt INT0_VECTOR
{

}
/******************************************************************************
 ** \brief	 Timer 0 interrupt service function
 **
 ** \param [in]  none   100us PM2.5
 **
 ** \return none
******************************************************************************/
void Timer0_IRQHandler(void)  interrupt TMR0_VECTOR 
{
	#if 0
   static uint8_t interval=0;
    timer0_ten_num++;
   
	timer0_20ms_num++;
	timer0_duty_num++;
	TimerCnt++;
	if(TimerCnt >10){ //5ms
	    TimerCnt =0;
        if(childLock  ==0) KEY_Handing();
	}
    if(timer0_ten_num==10){ //1ms
              timer0_ten_num=0;
			  interval ++;
	          if(interval==10){//10ms
	              interval =0;
				  timer0_num ++ ;
	              if(timer0_num > 1080)timer0_num=0;
	          }
              if(P22==0){
                   if(vairI==0){
                   rec_num++ ; 
                  // rec2_num=0;
                }
                else{
                   
                    rec2_num++;
                    //rec_num=0;
                }
              }
           
         
          
   }
 #endif 
  #if 1
	static uint16_t seconds=0;
    static uint8_t min60=0;
    seconds ++;
	if(seconds == 5000)// 500ms
	{ 
   		    seconds=0;
		Telecom.TimerEvent ++;
			 min60++;
		if(min60==41){ //60s = 1 分钟
			min60=0;
		    if(Telecom.TimerOn ==1)
		    {
			 //if(Telecom.TimeBaseUint == 0) Telecom.TimeBaseUint=1;
			  Telecom.TimeBaseUint --;
			} 

		}
	}
	#endif 

}
/******************************************************************************
 ** \brief	 INT0 interrupt service function
 **			
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void INT1_IRQHandler(void)  interrupt INT1_VECTOR
{
	;
}
/******************************************************************************
 ** \brief	 Timer 1 interrupt service function
 **
 ** \param [in]  none  100us timer
 **
 ** \return none
******************************************************************************/
void Timer1_IRQHandler(void)  interrupt TMR1_VECTOR 
{
	uint8_t num =0;
	static uint8_t minute=0;
    Timer1_num ++;
    
    if(Timer1_num ==5000){ //1s
         Timer1_num =0;
		
	      minute ++;
	     if(minute >=2){
		 	minute =0;
       
        if(KEY_HDScan(1)== WINDTI_PRES && num ==0)
        {
            locklg = locklg ^ 0x01;
			if(locklg==1 && num ==0){
                childLock=1;
			    num = 1;
				
                Timer1_num =0;
				childLock =1;
			   BuzzerSound = 1;
	           
			
			}
            else if(num==0){  
                locklg =0;
				num =1;
                childLock=0;
	             Timer1_num =0;
                childLock =0;
	            BuzzerSound =1;
				 
            }
        	}
        }
    }
	TH1 =(65536-200)>>8 ; //100us 
	TL1 = 65536-200; 
    
}
/******************************************************************************
 ** \brief	 UART 0 interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
******************************************************************************/
void UART0_IRQHandler(void)  interrupt UART0_VECTOR 
{

}
/******************************************************************************
 ** \brief	 Timer 2 interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
******************************************************************************/
void Timer2_IRQHandler(void)  interrupt TMR2_VECTOR 
{
	 if(TMR2_GetOverflowIntFlag())
	{

        
     TMR2_ConfigTimerPeriod((65536 - 78900)); //= 20.00ms
        
		TMR2_ClearOverflowIntFlag();
        
	}	
}
/******************************************************************************
 ** \brief	 UART 1 interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
******************************************************************************/
void UART1_IRQHandler(void)  interrupt UART1_VECTOR 
{
	;
}
/******************************************************************************
 ** \brief	 GPIO 0 interrupt service function
 **	
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void P0EI_IRQHandler(void)  interrupt P0EI_VECTOR 
{
	
}
/******************************************************************************
 ** \brief	 GPIO 1 interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void P1EI_IRQHandler(void)  interrupt P1EI_VECTOR 
{
	static uint8_t powerkey=0;

  
    

       if(childLock == 0){
		if(GPIO_GetIntFlag(GPIO1, GPIO_PIN_7))
		{
			powerkey= powerkey ^ 0x01;
	        if(powerkey==1)
	          Telecom.power_state = 1;
		    else  Telecom.power_state = 0;
		
		  
			GPIO_ClearIntFlag(GPIO1, GPIO_PIN_7);
		}
		
		if(GPIO_GetIntFlag(GPIO1, GPIO_PIN_6)) //风速按键
		{
			
	          Telecom.wind_state = 1;
		   
		    GPIO_ClearIntFlag(GPIO1, GPIO_PIN_6);
		  
		}
		
		if(GPIO_GetIntFlag(GPIO1, GPIO_PIN_5)) //定时按键
		{
			Telecom.timer_state = 1;
		    
		
		   
			GPIO_ClearIntFlag(GPIO1, GPIO_PIN_5);
		}

		if(GPIO_GetIntFlag(GPIO1, GPIO_PIN_4)) //置换虑网按键
		{
			
	         Telecom.net_state =1;
		   
		
			GPIO_ClearIntFlag(GPIO1, GPIO_PIN_4);
		}

	}
	
    
	
}
/******************************************************************************
 ** \brief	 GPIO 2 interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void P2EI_IRQHandler(void)  interrupt P2EI_VECTOR 
{

}
/******************************************************************************
 ** \brief	 GPIO 3 interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void P3EI_IRQHandler(void)  interrupt P3EI_VECTOR 
{
	;
}

/******************************************************************************
 ** \brief	 LVD interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void LVD_IRQHandler(void)  interrupt LVD_VECTOR 
{

}
/******************************************************************************
 ** \brief	 LSE interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void LSE_IRQHandler(void)  interrupt LSE_VECTOR 
{

}

/********************************************************************************
 ** \brief	 ACMP interrupt service function
 **			
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void ACMP_IRQHandler(void)  interrupt ACMP_VECTOR 
{

}
/******************************************************************************
 ** \brief	 Timer 3 interrupt service function
 **
 ** \param [in]  none  100us timer3 
 **
 ** \return none
******************************************************************************/
void Timer3_IRQHandler(void)  interrupt TMR3_VECTOR 
{
     #if 0
	static uint16_t seconds=0;
    static uint8_t min60=0;
    seconds ++;
	if(seconds == 5000)// 500ms
	{ 
   		    seconds=0;
		Telecom.TimerEvent ++;
			 min60++;
		if(min60==41){ //60s = 1 分钟
			min60=0;
		    if(Telecom.TimerOn ==1)
		    {
			 //if(Telecom.TimeBaseUint == 0) Telecom.TimeBaseUint=1;
			  Telecom.TimeBaseUint --;
			} 

		}
	}
	#endif 
	
    timer0_ten_num++;
   
	timer0_20ms_num++;
	timer0_duty_num++;
	//TimerCnt++;
	//if(TimerCnt >5){ //5ms
	  //  TimerCnt =0;
		
       // if(childLock  ==0) KEY_Handing();
	//}
	if(timer0_ten_num==10){ //1ms
              timer0_ten_num=0;
			  timer0_num ++ ;
	         if(timer0_num > 1080)timer0_num=0;
	          
              if(P22==0){
                   if(vairI==0){
                   rec_num++ ; 
                  // rec2_num=0;
                }
                else{
                   
                    rec2_num++;
                    //rec_num=0;
                }
              }
           
         
          
   }

}
/******************************************************************************
 ** \brief	 Timer 4 interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
******************************************************************************/
void Timer4_IRQHandler(void)  interrupt TMR4_VECTOR 
{

}
/******************************************************************************
 ** \brief	 EPWM interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void EPWM_IRQHandler(void)  interrupt EPWM_VECTOR
{

}
/******************************************************************************
 ** \brief	 ADC interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void ADC_IRQHandler(void)  interrupt ADC_VECTOR 
{

}
/******************************************************************************
 ** \brief	 WDT interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void WDT_IRQHandler(void)  interrupt WDT_VECTOR 
{

}
/******************************************************************************
 ** \brief	I2C interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void I2C_IRQHandler(void)  interrupt I2C_VECTOR 
{
	;
}
/******************************************************************************
 ** \brief	SPI interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void SPI_IRQHandler(void)  interrupt SPI_VECTOR 
{
	;
}















