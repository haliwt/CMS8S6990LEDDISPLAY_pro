
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
		//ʹ��BRT��ΪUARTģ��Ĳ�����ʱ�ӷ�����
	 uint16_t  BRTValue = 0;
	 uint32_t  BaudRateVlue = 9600;
	 
	 /*
	 (1)����UARTx������ģʽ
	 */
	 UART_ConfigRunMode(UART0,UART_MOD_ASY_8BIT, UART_BAUD_BRT);
	 UART_EnableReceive(UART0);
	 /*
	 (2)����UARTx�Ĳ�����
	 */
	 UART_ConfigBRTClk(BRT_CLK_DIV_1);	
	
	 UART_EnableDoubleFrequency(UART0); 							/*������ʹ�ܱ�Ƶ��SMOD =1*/
	
  #ifdef USE_FORMULA			//ʹ�ù�ʽ���㶨ʱ���ļ���ֵ(��Ҫ��Systemclock��ֵ(main.c))��USE_FORMULA �� ѡ��Option->C51->Preporcessor Symbols->Define�ж���
	 BRTValue = UART_ConfigBaudRate(UART0, BaudRateVlue) ;
  #else 
	//BRTValue = 65380; 				//ʹ�������ֲ����Ƽ��ļ���ֵ(BRT�½�)
  BRTValue = 65484;           //WT.EDIT 

  #endif
 
	 UART_ConfigBRTPeriod(BRTValue);						/*������װֵ*/
	 UART_EnableBRT();										/*ʹ�ܶ�ʱ��*/
	 /*
	 (3)����IO��
	 */
	// GPIO_SET_MUX_MODE(P23CFG,GPIO_MUX_TXD0);			/*TXD0*/
	// GPIO_SET_MUX_MODE(P22CFG,GPIO_MUX_RXD0);	 		/*RXD0*/
	 GPIO_SET_MUX_MODE(P16CFG,GPIO_MUX_TXD0);			/*TXD0*/
	  GPIO_SET_MUX_MODE(P17CFG,GPIO_MUX_RXD0);	 		/*RXD0*/     
	 
	 /*
	 (4)����UART�ж�
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
uint8_t BCC(uint8_t ver)
{
     uint8_t sbytes[2],tembyte;
	 sbytes[0]=0xAA;

	 
	 sbytes[1]= ver;

      tembyte =  sbytes[0]^ sbytes[1];
    
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
void ParseUART_Data(uint8_t n)
{
    uint8_t uartR=0,uartData;;
    if(bufRxd[n]==0xAA){

        uartData = bufRxd[n++]; 
        uartR= BCC(uartData);
         
		 if(bufRxd[n++]== uartR){
		  
			  if( uartData & 0x80 == 0x80)Telecom.power_state = 1;
				
               if( uartData & 0x40  ==0x40) Telecom.childLock =1;
			   if(  uartData & 0x20  == 0x20)Telecom.TimerFlg =1;
			   if( uartData & 0x10  == 0x10)Telecom.net_state =1;
				 
				Telecom.WindSelectLevel =  uartData & 0x0f;
			


			}



		  }
    n=0;

}








