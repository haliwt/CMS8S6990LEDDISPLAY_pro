#include "demo_buzzer.h"
#include "key.h"
#include "myflash.h"

#include "output.h"
#include "demo_uart.h"

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

uint8_t lockchild ;

uint16_t NetSetTimer;          //PM sensor averageValue 
  
    uint8_t  NetRecMinute;      //记录虑网运行分钟时间
	uint8_t  NetRecHour;          //记录滤网的小时--运行“小时时间”
	uint8_t  NetRecMoreHour;
	uint8_t  NetChangeFlag ;
    uint8_t  NetRec750Hour ;
    uint8_t  NetRec1500Hour ;



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
    static uint8_t recMinute =0;
	static uint16_t seconds=0;
    static uint8_t min60=0;
   #if 1
    timer0_ten_num++;
    NetSetTimer++;
	 seconds ++;
    if(timer0_ten_num==10){
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
#endif     
 
    #if 1
    if(NetSetTimer ==5000){  // 滤网定时器6.0s
        NetSetTimer =0;
		recMinute ++ ;
		if(recMinute ==41)//1分钟时间=60秒 rec =10 2分30秒
		{
	            recMinute =0;
				NetRecMinute ++ ;    //存储分钟
				if(NetRecMinute ==60){ //1小时=60分钟
			   // if(NetRecMinute ==3){//test
			   
					NetRecMinute =0;
					 NetRecHour ++; //存储小时
					 Telecom.ISR_NetRecMinuteAdj=1;
					     if(NetRecHour ==200)//200个小时
					     {
							NetRecHour =0;
							NetRecMoreHour ++;  //存储小时 的倍数
							Telecom.ISR_NetRecHourAdj =1;

							 if(NetRecMoreHour ==15){//3000 小时
								NetChangeFlag=1; //更换虑网时间到
							    }
						 }
				}
	    }
	}
   #endif 

    #if 1
	
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
	uint8_t number=0,number1=0;
	static uint8_t minute=0;
    Timer1_num ++;

	TH1 =(65536-200)>>8 ; //100us 
	TL1 = 65536-200; 
    if(Timer1_num >=1000){ //1s
         Timer1_num =0;
		
	      minute ++;
	     if(minute >=2){
		 	minute =0;
       
	        if(KEY_HDScan(0)== WINDTI_PRES)
	        {
	            locklg = locklg ^ 0x01;
				
				if(locklg==1 ){
	                childLock=1;
				   Timer1_num =0;
					childLock =1;
				   BuzzerSound = 1;
		           lockchild =1;
				   Telecom.criticalKey=1;
				   
				}
	            else{  
	                
					
	                childLock=0;
		             Timer1_num =0;
	                childLock =0;
		            BuzzerSound =1;
					lockchild =0;
					Telecom.criticalKey=1;
					
					}
					 
	            }
	         }
	       }

	
    
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
     static uint8_t times;
     uint8_t arr[3],i=0;
	 times++ ;
    if(UART_GetSendIntFlag(UART0))
	{
		UART_ClearSendIntFlag(UART0);	
	}
	if(UART_GetReceiveIntFlag(UART0))
	{
        if(times ==1){usartdat.usart_1 =UART_GetBuff(UART0);
		    UART_SendBuff(UART0,usartdat.usart_1 );
           UART_ClearReceiveIntFlag(UART0);

        }
		if(times==2){
			usartdat.usart_2 =UART_GetBuff(UART0);
			 UART_SendBuff(UART0,usartdat.usart_2 );
		UART_ClearReceiveIntFlag(UART0);
		}
	    if(times==3){
			times=0;
		 	usartdat.usart_3 =UART_GetBuff(UART0);
		   UART_SendBuff(UART0,usartdat.usart_3 );
		   UART_ClearReceiveIntFlag(UART0);
	    }
		//UART_SendBuff(UART0,UART_GetBuff(UART0));
		//UART_ClearReceiveIntFlag(UART0);	
	}	
	
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















