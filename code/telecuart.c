#include "telecuart.h"

/******************************************************************************
 ** \brief	 UART0_Config
 ** \param [in] 
 **            	
 ** \return  none
 ** \note  
 ******************************************************************************/
void UART0_Config(void)
{
	 uint16_t  BRTValue = 0;
	 uint32_t  BaudRateVlue = 9600;
	 
	 /*
	 (1)设置UARTx的运行模式   	//使用BRT作为UART模块的波特率时钟发生器
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
	 BRTValue = 65380; 				//使用数据手册上推荐的加载值(BRT章节)
  #endif
 
	 UART_ConfigBRTPeriod(BRTValue);						/*配置重装值*/
	 UART_EnableBRT();										/*使能定时器*/
	 /*
	 (3)配置IO口
	 */
	 GPIO_SET_MUX_MODE(P23CFG,GPIO_MUX_TXD0);			/*TXD0*/
	 GPIO_SET_MUX_MODE(P22CFG,GPIO_MUX_RXD0);	 		/*RXD0*/	
	 
	 /*
	 (4)设置UART中断
	 */
	 // UART_EnableInt(UART0);  //UART_DisableInt(uint8_t UARTn)
	 //IRQ_SET_PRIORITY(IRQ_UART0,IRQ_PRIORITY_LOW);
	 //IRQ_ALL_ENABLE();
 }

/*************************************************************************
 	*
	*Function Name: USART_SendData(uint8 data)
	*Function : GPIO口模拟串口，波特率 =9600bps ，间隔发送时间= 1s/9600=104us
	*Input Ref: data ，需要发送的数据32bit
	*Output Ref:No
	*
**************************************************************************/
void USART_SendData(uint8_t UARTn,uint8_t *arr)
{
	UART_SendBuff(UARTn, *arr);
	
}
/*************************************************************************
 	*
	*Function Name: uint8_t BCC(uint8_t *sbytes,uint8_t wid)
	*Function : 传输数据的校验码
	*Input Ref: *sbytes ---传输的字节数（1 byte = 8bit）
                width ----字节数
	*Output Ref: BCC校验码
	*
**************************************************************************/
uint8_t BCC(uint8_t *sbytes,uint8_t width)
{
     uint8_t i;
	 uint8_t tembyte = sbytes[0];
    for (i = 1; i <width; i++) {
        tembyte ^= sbytes[i];
    }
    return tembyte;

}
 /******************************************************************************
 ** \brief	 putchar
 ** \param [in] data
 **            	
 ** \return  none
 ** \note   <stdio.h>中需要的函数
 ******************************************************************************/
char putchar (char ch)
{
	SBUF0 = ch;
	while( !(SCON0 & (1<<1)));
	SCON0 &=~(1<<1);		
	return 0;
}

/******************************************************************************
 ** \brief	 putchar
 ** \param [in] none
 **            	
 ** \return  data
 ** \note   <stdio.h>中需要的函数
 ******************************************************************************/
char getchar (void)
{
	while(!(SCON0 & (1<<0)));
	SCON0 &=~(1<<0);
	return  SBUF0;	
}
/********************************************************************************
 ** \brief	 puts 
 **
 ** \param [in]  bytes addr for sending
 **
 ** \return  <stdio.h>中需要的函数
 ******************************************************************************/
int  puts( const char  * s)
{
	while(*(s ++))
		putchar(*s);
	return 0;
}


