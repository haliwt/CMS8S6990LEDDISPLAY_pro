
#ifndef __DEMO_UART_H__
#define __DEMO_UART_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s6990.h"
#include "key.h"


//通讯参数
typedef struct usarts
{
    int8_t usart_1;    //
    
    uint8_t usart_2 ;
    uint8_t usart_3;
	uint8_t usart_4;
   
 } ;

extern struct usarts  usartdat;

extern unsigned char bufRxd[4]; //接收字节缓冲区



void UART0_Config(void);
uint8_t BCC(uint8_t ver,uint8_t ver2);

void ParseUART_Data(uint8_t n);


#endif /* __DEMO_UART_H__ */






