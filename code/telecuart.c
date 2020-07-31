#include "telecuart.h"

/*************************************************************************
 	*
	*Function Name: void UART1_Config(void)
	*Function : Config USART1 Initialital reference
	*Input Ref: 
    *Output Ref: BCC校验码
	*
**************************************************************************/
void UART1_Config(void)
{
	//使用TMR2作为UART模块的波特率时钟发生器	 
	 uint16_t  TMR2Value = 0;
	 uint32_t  BaudRateVlue = 9600;	 
	/*
	 (1)设置UARTx的运行模式
	 */
	 UART_ConfigRunMode(UART1,UART_MOD_ASY_8BIT, UART_BAUD_TMR2);
	 UART_EnableReceive(UART1);
	/*
	 (2)配置UARTx的波特率
	 */
	 TMR2_ConfigTimerClk(TMR2_CLK_DIV_12);						/*T2PS =0*/
	 TMR2_ConfigRunMode(TMR2_MODE_TIMING, TMR2_AUTO_LOAD); 		/*设置为8位重装模式*/
	
	 UART_EnableDoubleFrequency(UART1); 							/*波特率使能倍频：SMOD =1*/
	
  #ifdef USE_FORMULA				//使用公式计算定时器的加载值(需要对Systemclock赋值(main.c))，USE_FORMULA 在 选项Option->C51->Preporcessor Symbols->Define中定义
	 TMR2Value = UART_ConfigBaudRate(UART1, BaudRateVlue) ;
  #else 
	 TMR2Value = 65523; 				
  #endif
  
	 TMR2_ConfigTimerPeriod(TMR2Value);						/*配置重装值*/
	 TMR2_Start();											/*使能定时器*/
	
	 /*
	 (3)配置IO口
	 */
	 GPIO_SET_MUX_MODE(P23CFG,GPIO_MUX_TXD1);			/*TXD1*/
	 GPIO_SET_MUX_MODE(P22CFG,GPIO_MUX_RXD1);	 		/*RXD1*/


}

/******************************************************************************
 ** 
 **Function Name: UART0_Config(void)
 **Function : setup UART0 for serial port reference          	
 **Input Ref:NO
 ** Return Ref: NO
 **  
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
	 UART_EnableInt(UART0);  //UART_DisableInt(uint8_t UARTn)
	 IRQ_SET_PRIORITY(IRQ_UART0,IRQ_PRIORITY_LOW);
	 IRQ_ALL_ENABLE();
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
/*************************************************************************
 	*
	*Function Name: void USART_AirSensorReceiveData(uint8_t uartn,uint8_t recedata)
	*Function :  receive air sensor data 
	*Input Ref:  uartn: be used to UART0 
	             recedata: form air sensor receive data
    *Output Ref: NO
	*
**************************************************************************/

/*************************************************************************
 	*
	*Function Name: 
	*Function :  处理串口接收数据包函数（成功处理数据包则返回1，否则返回0）
	*Input Ref:               
    *Return Ref: 接收数据成功 1，
	*
**************************************************************************/
uint8_t Analysis_UART0_ReceiveData(void)  
{
     //PutString(ReceiveDataBuffer);
     if(pUart->ReceiveDataBuffer[0]==0xAA)  //进行数据包头尾标记验证
     {        
        if(pUart->ReceiveDataBuffer[1]==0xC0)        //识别发送者设备ID的第1位数字
        {
            if(pUart->ReceiveDataBuffer[pUart->ReceNum]==0xAB) 
				     return 1;
        }
     }
     return 0;
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



