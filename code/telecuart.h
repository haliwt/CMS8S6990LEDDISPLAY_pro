#ifndef __TELECUART_H__
#define __TELECUART_H__

#include "cms8s6990.h"


void UART0_Config(void);
void USART1_Config(void);
void USART_SendData(uint8_t UARTn,uint8_t *arr);  //同主控制板通信
void USART_AirSensorReceiveData(uint8_t uartn,uint8_t recedata); //接收空气PM1.5传感器数据
uint8_t BCC(uint8_t *sbytes,uint8_t wid);








#endif 