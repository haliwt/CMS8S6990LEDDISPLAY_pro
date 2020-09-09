
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
    BRTValue = 65484; //WT.EDIT 2020.09.09 
  #endif
 
	 UART_ConfigBRTPeriod(BRTValue);						/*������װֵ*/
	 UART_EnableBRT();										/*ʹ�ܶ�ʱ��*/
	 /*
	 (3)����IO��
	 */
	// GPIO_SET_MUX_MODE(P23CFG,GPIO_MUX_TXD0);			/*TXD0*/
	// GPIO_SET_MUX_MODE(P22CFG,GPIO_MUX_RXD0);	 		/*RXD0*/
	GPIO_SET_MUX_MODE(P17CFG,GPIO_MUX_TXD0);			/*TXD0*/
	GPIO_SET_MUX_MODE(P16CFG,GPIO_MUX_RXD0);	 		/*RXD0*/
	 
	 /*
	 (4)����UART�ж�
	 */
	 UART_EnableInt(UART0);
	 IRQ_SET_PRIORITY(IRQ_UART0,IRQ_PRIORITY_HIGH);
	 IRQ_ALL_ENABLE();
	 
}








