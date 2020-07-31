#include "cms8s6990.h"
#include "timer0.h"
#include "key.h"
#include "telecuart.h"
volatile uint16_t getMinute; 
volatile uint16_t TimerCnt;
uint8_t cmdArrived=0,cmdIndex=0,cmdArriving=0;
 UART *pUart;


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
 ** \param [in]  none   100us interrupt times
 **
 ** \return none
******************************************************************************/
void Timer0_IRQHandler(void)  interrupt TMR0_VECTOR 
{
	static uint16_t seconds=0,minutes=0;
	uint8_t i;
	  seconds++;
	  TimerCnt++;
	  for (i=0; i<TASKS_MAX; i++)          // 逐个任务轮询时间处理
	  {
	        if (TaskComps[i].Timer)          // 时间不为0
	        {
	            TaskComps[i].Timer--;         // 减去一个节拍
	            if (TaskComps[i].Timer == 0)       // 时间减完了
	            {
	                 TaskComps[i].Timer = TaskComps[i].ItervalTime;       // 恢复计时器值，从新运行下一次
	                 TaskComps[i].Run = 1;           // 任务可以运行
	            }
	        }
		}

		if(seconds==60000){ //计时：6.0s
			seconds =0;
			 minutes ++;
			 TimerCnt =0;
			if(minutes ==10){ //1分钟时间
				minutes =0;
			    getMinute++; 
		    }
		}
		
		if(cmdArriving == 1 && TimerCnt == 500)
		{
			cmdArrived = 1;
			pUart->ReceNum = cmdIndex;
			cmdIndex = 0;
			TimerCnt = 0;
			cmdArriving =0;
		}
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
 ** \param [in]  none   
 **
 ** \return none
******************************************************************************/
void Timer1_IRQHandler(void)  interrupt TMR1_VECTOR 
{

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
	
	#if 1
	if(UART_GetSendIntFlag(UART0))	//软件清除发送中断标志位TI0 
	{
		UART_ClearSendIntFlag(UART0);	
	}
	if(UART_GetReceiveIntFlag(UART0)) //接收有中断 RI0，清空接收中断标志位
	{
        TimerCnt = 0;
        cmdArriving = 1;
        if(cmdArrived == 0)
        {
            pUart->ReceiveDataBuffer[cmdIndex++] = SBUF0;
			                  
			if(pUart->ReceiveDataBuffer[cmdIndex]==0xAB){
				cmdArrived =1;
				cmdArriving =0;
				pUart->ReceNum = cmdIndex;
				cmdIndex =0;
			}
        }
		UART_ClearReceiveIntFlag(UART0);	
	}
	#endif 	
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
	#if 0
	static uint8_t pkey=0;
	if(GPIO_GetIntFlag(GPIO1, GPIO_PIN_6))
	{
		pkey = pkey ^ 0x01;
		if(pkey ==1)
		Telecom.power_state =1;
		else 
		GPIO_ClearIntFlag(GPIO1, GPIO_PIN_6);
	}
	#endif 
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
		;
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
 ** \param [in]  none   
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















