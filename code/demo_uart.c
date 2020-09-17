
#include "demo_uart.h"

/******************************************************************************
 ** \brief	 UART0_Config
 ** \param [in] 
 **            	
 ** \return  none
 ** \note  
 ******************************************************************************/
void UART0_Config(void)
{
		//使用BRT作为UART模块的波特率时钟发生器
	 uint16_t  BRTValue = 0;
	 uint32_t  BaudRateVlue = 9600;
	 
	 /*
	 (1)设置UARTx的运行模式
	 */
	 UART_ConfigRunMode(UART0,UART_MOD_ASY_8BIT, UART_BAUD_BRT);
	 UART_EnableReceive(UART0);
	 /*
	 (2)配置UARTx的波特率
	 */
	 UART_ConfigBRTClk(BRT_CLK_DIV_1);	
	
	 UART_EnableDoubleFrequency(UART0); 							/*波特率使能倍频：SMOD =1*/
	
  #ifdef USE_FORMULA			//使用公式计算定时器的加载值(需要对Systemclock赋值(main.c))，USE_FORMULA 在 选项Option->C51->Preporcessor Symbols->Define中定义
	 BRTValue = UART_ConfigBaudRate(UART0, BaudRateVlue) ;
  #else 
	//BRTValue = 65380; 				//使用数据手册上推荐的加载值(BRT章节)
  BRTValue = 65484;           //WT.EDIT 

  #endif
 
	 UART_ConfigBRTPeriod(BRTValue);						/*配置重装值*/
	 UART_EnableBRT();										/*使能定时器*/
	 /*
	 (3)配置IO口
	 */
	// GPIO_SET_MUX_MODE(P23CFG,GPIO_MUX_TXD0);			/*TXD0*/
	// GPIO_SET_MUX_MODE(P22CFG,GPIO_MUX_RXD0);	 		/*RXD0*/
	 GPIO_SET_MUX_MODE(P16CFG,GPIO_MUX_TXD0);			/*TXD0*/
	  GPIO_SET_MUX_MODE(P17CFG,GPIO_MUX_RXD0);	 		/*RXD0*/     
	 
	 /*
	 (4)设置UART中断
	 */
	 UART_EnableInt(UART0);
	 IRQ_SET_PRIORITY(IRQ_UART0,IRQ_PRIORITY_HIGH);
	 IRQ_ALL_ENABLE();
	 
}



/*************************************************************************
 	*
	*Function Name: uint8_t BCC(uint8_t *sbytes,uint8_t width)
	*Function : BCC checksum code
	*Input Ref: 
	*Output Ref:No
	*
******************************************************************************/
uint8_t BCC(uint8_t ver,uint8_t ver2)
{
     uint8_t sbytes[3],tembyte;
	 sbytes[0]=0xAA;

	 
	 sbytes[1]= ver;
	 sbytes[2]= ver2;

      tembyte =  sbytes[0]^ sbytes[1]^ sbytes[2];
    
    return tembyte;

}


/*************************************************************************
 	*
	*Function Name: void ParseUART_Data(void)
	*Function : parse receive UART data
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/









