/*******************************************************************************
* Copyright (C) 2019 China Micro Semiconductor Limited Company. All Rights Reserved.
*
* This software is owned and published by:
* CMS LLC, No 2609-10, Taurus Plaza, TaoyuanRoad, NanshanDistrict, Shenzhen, China.
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with CMS
* components. This software is licensed by CMS to be adapted only
* for use in systems utilizing CMS components. CMS shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. CMS is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/

/*****************************************************************************/
/** \file demo_uart.h
**
**
**
** History:
** - 
*****************************************************************************/
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




void UART0_Config(void);
uint8_t BCC(uint8_t ver);


#endif /* __DEMO_UART_H__ */






