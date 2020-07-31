#ifndef __TELECUART_H__
#define __TELECUART_H__

#include "cms8s6990.h"

typedef struct _UART_{
    uint8_t ReceiveDataBuffer[10];            //定义数据包长度为80个bit
    volatile uint8_t ReceNum;
    uint8_t  achieveUartFlag : 1;

}UART;
extern UART *pUart;
//uint8_t ReceiveDataBuffer[10];            //定义数据包长度为80个bit
//extern volatile uint8_t ReceNum;

void UART0_Config(void);
void UART1_Config(void);
void USART1_SendDataToMain(void);  //同主控制板通信

uint8_t BCC(uint8_t *sbytes,uint8_t wid);
uint8_t Analysis_UART0_ReceiveData(void)  ;








#endif 