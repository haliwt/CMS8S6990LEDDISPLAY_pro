#include "telecuart.h"
#include "key.h"
#include "cms8s6990.h"
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
	// GPIO_SET_MUX_MODE(P23CFG,GPIO_MUX_TXD1);			/*TXD1*/
	// GPIO_SET_MUX_MODE(P22CFG,GPIO_MUX_RXD1);	 		/*RXD1*/


}
/******************************************************************************
 ** 
 **Function Name: UART0_Config(void)
 **Function : setup UART0 for serial port reference   Air Sensor          	
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
void USART1_SendDataToMain(void)
{
	float PM25;
	static uint8_t autoWindValue=0;
	uint8_t bcc_data,Judeflag=0;
    uint8_t senddata[4];       // 发送数据
    Judeflag = Analysis_UART0_ReceiveData();
	if(Judeflag ==1){
			//PM2.5
			PM25 = (pUart->ReceiveDataBuffer[2]*16 + 1+ (pUart->ReceiveDataBuffer[3]*16 + 1)*256) * 0.1;
		//	PM10 = (pUart->ReceiveDataBuffer[4]*16 + 1+ (pUart->ReceiveDataBuffer[5]*16 + 1)*256) * 0.1;
    }
    
	if(Telecom->setWind_levels == wind_auto){
          if(PM25<=75) autoWindValue = 0x01;             //当PM2.5检查到PM2.5值小于75ug/m^3 风速一档
		  if(PM25 >75 && PM25<=150) autoWindValue  = 0x02; //风速 2档
		  if(PM25 >150 && PM25<=300)  autoWindValue  = 0x03; //风速 3档
		  if(PM25 >300 )  autoWindValue  = 0x04; //风速 H 档 ，显示H档。

	}
     
    Telecom->setWind_levels |=Telecom->setWind_levels <<0; //风速4档，睡眠风速，中速风速，高速风速 自动风速
	
	Telecom->power_state |= Telecom->power_state << 0;       //电源开关量
	
    Telecom->runstart  |=Telecom->runstart<<2;             //电机开启开关量

	senddata[0]=Telecom->power_state |Telecom->runstart;  //head code 8bit
	senddata[1]=autoWindValue ;     //自动档，风速判定，PM2.5值调节风速大小
	senddata[2]=Telecom->setWind_levels;									//风扇档位值：
	
   
  	bcc_data=BCC(senddata,3);
	senddata[3]=bcc_data;

	UART_SendBuff(UART1,  senddata[0]); //头码
	UART_SendBuff(UART1,  senddata[1]); //风速码 高8bit  //自动档，风速的判断值
	UART_SendBuff(UART1,  senddata[2]); //风速码 低8bit
	UART_SendBuff(UART1,  senddata[3]); //校验码
	
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
	*Function Name: uint8_t Analysis_UART0_ReceiveData(void) 
	*Function :  处理串口接收数据包函数，判断接收数据的可靠性
	*Input Ref:  No             
    *Return Ref: 接收数据成功 1，接收数据失败：0
	*
**************************************************************************/
uint8_t Analysis_UART0_ReceiveData(void)  
{
     uint8_t checkSum=0;
	 if(pUart->achieveUartFlag==1){
		if(pUart->ReceiveDataBuffer[0]==0xAA)  //进行数据包头尾标记验证
		{        
			if(pUart->ReceiveDataBuffer[1]==0xC0)        //识别发送者设备ID的第1位数字
			{
			checkSum = 
				pUart->ReceiveDataBuffer[2]+             //PM2.5 数据低8bit
				pUart->ReceiveDataBuffer[3]+             //PM2.5 数据高8bit
				pUart->ReceiveDataBuffer[4]+             //PM10  数据低8bit
				pUart->ReceiveDataBuffer[5]+             //PM10  数据高8bit
				pUart->ReceiveDataBuffer[6]+
				pUart->ReceiveDataBuffer[7];

				if(checkSum == pUart->ReceiveDataBuffer[8] )
				{
				
					if(pUart->ReceiveDataBuffer[pUart->ReceNum]==0xAB) 
						return 1;
				}
			}
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



