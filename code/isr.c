#include "demo_buzzer.h"
#include "key.h"
#include "myflash.h"

uint16_t getMinute;
uint16_t TimerCnt;

volatile uint16_t Timer1_num;
uint8_t childLock ;
static uint8_t locklg=0;


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
 ** \param [in]  none   
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
                if (TaskComps[i].Timer == 0 )       // 时间减完了
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
 ** \param [in]  none  30ms 100 
 **
 ** \return none
******************************************************************************/
void Timer1_IRQHandler(void)  interrupt TMR1_VECTOR 
{
	uint8_t num =0; 
    Timer1_num ++;
    
    if(Timer1_num ==35){
         Timer1_num =0;
       
        if(KEY_HDScan(1)== WINDTI_PRES && num ==0)
        {
            locklg = locklg ^ 0x01;
			if(locklg==1 && num ==0){
                childLock=1;
			    num = 1;
				
                Timer1_num =0;
				childLock =1;
			//	BUZZER_Config();
			//	delay_20us(10000);
	         //   DisableBUZZER_Config();
				//Flash_ToWriteData(0x00,0x01);
	           
			
			}
            else if(num==0){  
                locklg =0;
				num =1;
                childLock=0;
	             Timer1_num =0;
                childLock =0;
	           //  BUZZER_Config();
				// delay_20us(10000);
	            //  DisableBUZZER_Config();
				 
            }
        }
    }
	TH1 =(65536-60000)>>8 ;
	TL1 = 65536-60000; 
    
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
	;
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















