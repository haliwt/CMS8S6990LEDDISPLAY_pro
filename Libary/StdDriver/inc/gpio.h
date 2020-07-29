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
/** \file gpio.h
**
** 
**
** History:
** 
*****************************************************************************/
#ifndef __GPIO_H__
#define __GPIO_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s6990.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/
/*----------------------------------------------------------------------------
 **GPIO引脚
 ---------------------------------------------------------------------------*/
#define  GPIO_PIN_0_MSK				(0x01)		/* GPIO Pin 0 mask */
#define  GPIO_PIN_1_MSK				(0x02)		/* GPIO Pin 1 mask */
#define  GPIO_PIN_2_MSK				(0x04)		/* GPIO Pin 2 mask */
#define  GPIO_PIN_3_MSK				(0x08)		/* GPIO Pin 3 mask */
#define  GPIO_PIN_4_MSK				(0x10)		/* GPIO Pin 4 mask */
#define  GPIO_PIN_5_MSK				(0x20)		/* GPIO Pin 5 mask */
#define  GPIO_PIN_6_MSK				(0x40)		/* GPIO Pin 6 mask */
#define  GPIO_PIN_7_MSK				(0x80)		/* GPIO Pin 7 mask */

#define  GPIO_PIN_0					(0x00)		/* GPIO Pin 0 number*/
#define  GPIO_PIN_1					(0x01)		/* GPIO Pin 1 number */
#define  GPIO_PIN_2					(0x02)		/* GPIO Pin 2 number */
#define  GPIO_PIN_3					(0x03)		/* GPIO Pin 3 number */
#define  GPIO_PIN_4					(0x04)		/* GPIO Pin 4 number */
#define  GPIO_PIN_5					(0x05)		/* GPIO Pin 5 number */
#define  GPIO_PIN_6					(0x06)		/* GPIO Pin 6 number */
#define  GPIO_PIN_7					(0x07)		/* GPIO Pin 7 number */

#define  GPIO0						(0x00)
#define  GPIO1						(0x01)
#define  GPIO2						(0x02)
#define  GPIO3						(0x03)

#define  GPIO_P00					(0x00)
#define  GPIO_P01					(0x01)
#define  GPIO_P02					(0x02)
#define  GPIO_P03					(0x03)
#define  GPIO_P04					(0x04)
#define  GPIO_P05					(0x05)
#define  GPIO_P13					(0x13)
#define  GPIO_P14					(0x14)
#define  GPIO_P15					(0x15)
#define  GPIO_P16					(0x16)
#define  GPIO_P17					(0x17)
#define  GPIO_P21					(0x21)
#define  GPIO_P22					(0x22)
#define  GPIO_P23					(0x23)
#define  GPIO_P24					(0x24)
#define  GPIO_P25					(0x25)
#define  GPIO_P26					(0x26)
#define  GPIO_P30					(0x30)
#define  GPIO_P31					(0x31)
#define  GPIO_P32					(0x32)
#define  GPIO_P35					(0x35)
#define  GPIO_P36					(0x36)

/*----------------------------------------------------------------------------
 **GPIO 引脚模式Mask
---------------------------------------------------------------------------*/
#define  GPIO_OPEN_DRAIN_MODE	(0x02)		/*GPIO 开漏模式*/
#define  GPIO_PUSH_PULL_MODE	(0x00)		/*GPIO 推挽输出模式*/
#define  GPIO_UP_MODE			(0x04)		/*GPIO 上拉模式*/
#define  GPIO_DR_MODE			(0x08)		/*GPIO 下拉模式*/
#define  GPIO_LOW_CURRENT_MODE	(0x10)		/*GPIO 低电流(弱驱动)模式*/
#define  GPIO_HIGH_CURRENT_MODE	(0x00)		/*GPIO 高电流(强驱动)模式*/
#define  GPIO_SLOW_SLOPE_MODE	(0x20)		/*GPIO 慢斜率模式*/
#define  GPIO_FAST_SLOPE_MODE	(0x00)		/*GPIO 快率模式*/


/*----------------------------------------------------------------------------
 ** IO引脚复用模式
---------------------------------------------------------------------------*/
#define  GPIO_MUX_GPIO		(0x00)			/*GPIO功能*/
/*--GPIO数字功能（所有IO均可配置）-------------------------------------------*/
/*----Timer2比较输出通道-----------------------------------------------------*/
#define  GPIO_MUX_CC0		(0x04)
#define  GPIO_MUX_CC1		(0x05)
#define  GPIO_MUX_CC2		(0x06)
#define  GPIO_MUX_CC3		(0x07)
/*----UART通道---------------------------------------------------------------*/
#define  GPIO_MUX_TXD0		(0x08)
#define  GPIO_MUX_RXD0		(0x09)
#define  GPIO_MUX_TXD1		(0x0A)
#define  GPIO_MUX_RXD1		(0x0B)
/*----I2C通道---------------------------------------------------------------*/
#define  GPIO_MUX_SCL		(0x0C)
#define  GPIO_MUX_SDA		(0x0D)
/*----SPI通道---------------------------------------------------------------*/
#define  GPIO_MUX_NSS		(0x0E)
#define  GPIO_MUX_SCLK		(0x0F)
#define  GPIO_MUX_MOSI		(0x10)
#define  GPIO_MUX_MISO		(0x11)
/*----EPWM通道---------------------------------------------------------------*/
#define  GPIO_MUX_PG0		(0x12)
#define  GPIO_MUX_PG1		(0x13)
#define  GPIO_MUX_PG2		(0x14)
#define  GPIO_MUX_PG3		(0x15)
#define  GPIO_MUX_PG4		(0x16)
#define  GPIO_MUX_PG5		(0x17)
/*----BEEP通道---------------------------------------------------------------*/
#define  GPIO_MUX_BEEP		(0x18)
/*----ACMP通道---------------------------------------------------------------*/
#define  GPIO_MUX_C0O		(0x1A)
#define  GPIO_MUX_C1O		(0x1B)

/*--ANALOG功能--------------------------------------------------------------*/
#define  GPIO_MUX_ANALOG	(0x01)			/*模拟功能(GPIO功能关闭)*/
/*----ADC输入通道-----------------------------------------------------------*/
#define  GPIO_P00_MUX_AN0	(0x01)
#define  GPIO_P01_MUX_AN1	(0x01)
#define  GPIO_P02_MUX_AN2	(0x01)
#define  GPIO_P03_MUX_AN3	(0x01)
#define  GPIO_P04_MUX_AN4	(0x01)
#define  GPIO_P05_MUX_AN5	(0x01)
#define  GPIO_P13_MUX_AN6	(0x01)
#define  GPIO_P14_MUX_AN7	(0x01)
#define  GPIO_P15_MUX_AN18	(0x01)
#define  GPIO_P16_MUX_AN19	(0x01)
#define  GPIO_P17_MUX_AN20	(0x01)
#define  GPIO_P21_MUX_AN21	(0x01)
#define  GPIO_P22_MUX_AN8	(0x01)
#define  GPIO_P23_MUX_AN9	(0x01)
#define  GPIO_P24_MUX_AN10	(0x01)
#define  GPIO_P25_MUX_AN11	(0x01)
#define  GPIO_P26_MUX_AN12	(0x01)
#define  GPIO_P30_MUX_AN22	(0x01)
#define  GPIO_P31_MUX_AN13	(0x01)
#define  GPIO_P32_MUX_AN14	(0x01)
#define  GPIO_P35_MUX_AN16	(0x01)
#define  GPIO_P36_MUX_AN17	(0x01)
/*----ACMP输入通道-----------------------------------------------------------*/
#define  GPIO_P13_MUX_C0P0	(0x01)
#define  GPIO_P00_MUX_C0P1	(0x01)
#define  GPIO_P01_MUX_C0P2	(0x01)
#define  GPIO_P30_MUX_C0P4	(0x01)
#define  GPIO_P24_MUX_C0P5	(0x01)
#define  GPIO_P14_MUX_C0N	(0x01)

#define  GPIO_P04_MUX_C1P0	(0x01)
#define  GPIO_P03_MUX_C1P1	(0x01)
#define  GPIO_P02_MUX_C1P2	(0x01)
#define  GPIO_P30_MUX_C1P4	(0x01)
#define  GPIO_P24_MUX_C1P5	(0x01)
#define  GPIO_P05_MUX_C1N	(0x01)

/*----OPA输入通道-----------------------------------------------------------*/
#define  GPIO_P30_MUX_OP0O	(0x01)
#define  GPIO_P31_MUX_OP0N	(0x01)
#define  GPIO_P32_MUX_OP0P	(0x01)

#define  GPIO_P22_MUX_OP1P	(0x01)
#define  GPIO_P23_MUX_OP1N	(0x01)
#define  GPIO_P24_MUX_OP1O	(0x01)

/*----PGA输入通道-----------------------------------------------------------*/
#define  GPIO_P31_MUX_PGAP		(0x01)
#define  GPIO_P32_MUX_PGAGND	(0x01)
#define  GPIO_P26_MUX_PGAO		(0x01)

/********************************************************************************
 ** \brief	 GPIO_SET_MUX_MODE
 **			 设置IO口的复用功能
 ** \param [in] PorttCFG ：IO口的复用寄存器 P00CFG.....
 **            PinMode ：IO口的复用功能 
 ** \return  none
********************************************************************************/
#define  GPIO_SET_MUX_MODE(PortCFG,PinMode)		(PortCFG = PinMode)	

/********************************************************************************
 ** \brief	 GPIO_SET_PS_MODE
 **			 设置端口输入功能分配
 ** \param [in]  Ps_mode；PS_INT0、PS_INT1..... PS_FB
 **				 gpio:	GPIO_P00 .... GPIO_P36 
 ** \return  none
********************************************************************************/
#define  GPIO_SET_PS_MODE(Ps_mode,gpio)		(Ps_mode = gpio)	

/********************************************************************************
 ** \brief	 GPIO_ENABLE_OUTPUT
 **			 使能GPIO为推挽输出模式
 ** \param [in] PortTRIS ：方向寄存器 P0TRIS 、P1TRIS 、P2TRIS 、P3TRIS 
 **            PinNum 
 ** \return  none
 ******************************************************************************/
#define	 GPIO_ENABLE_OUTPUT(PortTRIS, PinNum)	(PortTRIS |= (1<<PinNum))

/********************************************************************************
 ** \brief	 GPIO_ENABLE_OUTPUT
 **			 使能GPIO为三态输入模式
 ** \param [in] PorttRIS ：方向寄存器 P0TRIS 、P1TRIS 、P2TRIS 、P3TRIS 
 **            PinNum 
 ** \return  none
 ******************************************************************************/
#define  GPIO_ENABLE_INPUT(PortTRIS, PinNum)	(PortTRIS &= ~(1<<PinNum))

/********************************************************************************
 ** \brief	 GPIO_ENABLE_OD
 **			 GPIO开漏功能开启
 ** \param [in] PorttOD  :开漏功能寄存器：P0OD、P1OD、P2OD、P3OD
 **            PinNum  : 0~7
 ** \return  none
 ******************************************************************************/
#define  GPIO_ENABLE_OD(PortOD, PinNum)			(PortOD |= (1<<PinNum))
/********************************************************************************
 ** \brief	 GPIO_DISABLE_OD
 **			 GPIO开漏功能关闭
 ** \param [in] PorttOD  :开漏功能寄存器：P0OD、P1OD、P2OD、P3OD
 **            PinNum  : 0~7
 ** \return  none
 ******************************************************************************/
#define  GPIO_DISABLE_OD(PortOD, PinNum)		(PortOD &= ~(1<<PinNum))
/********************************************************************************
 ** \brief	 GPIO_ENABLE_UP
 **			 GPIO上拉功能开启
 ** \param [in] PorttUP  :上拉功能寄存器：P0UP、P1UP、P2UP、P3UP
 **            PinNum  : 0~7
 ** \return  none
 ******************************************************************************/
#define  GPIO_ENABLE_UP(PortUP, PinNum)			(PortUP |= (1<<PinNum))
/********************************************************************************
 ** \brief	 GPIO_DISABLE_UP
 **			 GPIO上拉功能关闭
 ** \param [in] PorttUP  :上拉功能寄存器：P0UP、P1UP、P2UP、P3UP
 **            PinNum  : 0~7
 ** \return  none
 ******************************************************************************/
#define  GPIO_DISABLE_UP(PortUP, PinNum)		(PortUP &= ~(1<<PinNum))
/********************************************************************************
 ** \brief	 GPIO_ENABLE_RD
 **			 GPIO下拉功能开启
 ** \param [in] PorttRD  :下拉功能寄存器：P0RD、P1RD、P2RD、P3RD
 **            PinNum  : 0~7
 ** \return  none
 ******************************************************************************/
#define  GPIO_ENABLE_RD(PortRD, PinNum)			(PortRD |= (1<<PinNum))
/********************************************************************************
 ** \brief	 GPIO_DISABLE_RD
 **			 GPIO下拉功能关闭
 ** \param [in] PorttRD  :下拉功能寄存器：P0RD、P1RD、P2RD、P3RD
 **            PinNum  : 0~7
 ** \return  none
 ******************************************************************************/
#define  GPIO_DISABLE_RD(PortRD, PinNum)		(PortRD &= ~(1<<PinNum))
/********************************************************************************
 ** \brief	 GPIO_ENABLE_LOW_CURRENT
 **			 GPIO弱电流驱动功能开启
 ** \param [in] PorttDR  :驱动功能寄存器：P0DR、P1DR、P2DR、P3DR
 **            PinNum  : 0~7
 ** \return  none
 ******************************************************************************/
#define  GPIO_ENABLE_LOW_CURRENT(PortDR, PinNum)	(PortDR |= (1<<PinNum))
/********************************************************************************
 ** \brief	 GPIO_ENABLE_LOW_CURRENT
 **			 GPIO弱电流驱动功能关闭
 ** \param [in] PorttDR  :驱动功能寄存器：P0DR、P1DR、P2DR、P3DR
 **            PinNum  : 0~7
 ** \return  none
 ******************************************************************************/
#define  GPIO_DISABLE_LOW_CURRENT(PortDR, PinNum)	(PortDR &= ~(1<<PinNum))

/********************************************************************************
 ** \brief	 GPIO_ENABLE_LOW_CURRENT
 **			 GPIO慢斜率功能开启
 ** \param [in] PorttSR  :斜率控制功能寄存器：P0SR、P1SR、P2SR、P3SR
 **            PinNum  : 0~7
 ** \return  none
 ******************************************************************************/
#define  GPIO_ENABLE_SLOW_SLOPE(PortSR, PinNum)      (PortSR |= (1<<PinNum))
/********************************************************************************
 ** \brief	 GPIO_ENABLE_LOW_CURRENT
 **			 GPIO慢斜率功能关闭
 ** \param [in] PorttSR  :斜率控制功能寄存器：P0SR、P1SR、P2SR、P3SR
 **            PinNum  : 0~7
 ** \return  none
 ******************************************************************************/
#define  GPIO_DISABLE_SLOW_SLOPE(PortSR, PinNum)     (PortSR &= ~(1<<PinNum))


/*----------------------------------------------------------------------------
 **GPIO 引脚中断触发模式
/*---------------------------------------------------------------------------*/
#define  GPIO_INT_RISING	(0x01)			/*上升沿触发中断*/
#define  GPIO_INT_FALLING	(0x02)			/*下降沿触发中断*/
#define  GPIO_INT_BOTH_EDGE	(0x03)			/*上升、下降沿均触发中断*/

/********************************************************************************
 ** \brief	 GPIO_SET_INT_MODE
 **			 设置IO口的外部中断功能
 ** \param [in] PorttEICFG ：IO口的外部中断模式配置寄存器
 **            PinIntMode ：IO口的复用功能 
 ** \return  none
 ******************************************************************************/
#define  GPIO_SET_INT_MODE(PortEICFG, PinIntMode)	(PortEICFG = PinIntMode)

/********************************************************************************
 ** \brief	 GPIO_ENABLE_INT_MODE
 **			使能IO口的外部中断功能
 ** \param [in] PorttEXTIE ：IO口的外部中断寄存器
 **            PinMSK：GPIO_PIN_0_MSK .. GPIO_PIN_7_MSK
 ** \return  none
 ******************************************************************************/
#define  GPIO_ENABLE_INT_MODE(PortEXTIE,PinMSK)		(PortEXTIE |= PinMSK)	

/********************************************************************************
 ** \brief	 GPIO_DISABLE_INT_MODE
 **			关闭IO口的外部中断功能
 ** \param [in] PorttEXTIE ：IO口的外部中断寄存器
 **            PinMSK: GPIO_PIN_0_MSK .. GPIO_PIN_7_MSK
 ** \return  none
 ******************************************************************************/
#define  GPIO_DISABLE_INT_MODE(PortEXTIE,PinMSK)	(PortEXTIE &= ~PinMSK)	

/*****************************************************************************/
/* Global type definitions ('typedef') */
/*****************************************************************************/



/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source) */
/*****************************************************************************/


/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source) */
/*****************************************************************************/
/****************************************************************************
 ** \brief	 GPIO_ConfigGPIOMode
 **			 配置GPIO模式
 ** \param [in] Port  ： GPIO0、GPIO1、GPIO2、GPIO3
 **			   PinMSK: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK	
 **            PinMode：
 **						  (1)GPIO_OPEN_DRAIN_MODE:  开漏输出模式
 **						  (2)GPIO_UP_MODE ：		上拉模式
 **						  (3)GPIO_DR_MODE： 		下拉模式
 **						  (4)GPIO_LOW_CURRENT_MODE： 弱电流驱动模式
 **						  (5)GPIO_SLOW_SLOPE_MODE：  慢斜率模式
 **						  (6)GPIO_PUSH_PULL_MODE:    推挽输出模式
 **						  (7)GPIO_HIGH_CURRENT_MODE：强电流驱动模式
 **						  (8)GPIO_FAST_CURRENT_MODE：快斜率模式
 ** \return  none
 ** \note   
 ***************************************************************************/
void GPIO_ConfigGPIOMode( uint8_t Port, uint8_t PinMSK, uint8_t PinMode);

 /********************************************************************************
 ** \brief	 GPIO_EnableInt
 **			 使能IO口的中断功能
 ** \param [in] Port  ： GPIO0、GPIO1、GPIO2、GPIO3
 **			    PinMSK: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK			 
 ** \return  none
 ** \note   
 **  (1)P0的PinMSK输入值范围：GPIO_PIN_0_MSK ~ GPIO_PIN_5_MSK
 **  (2)P1的PinMSK输入值范围：GPIO_PIN_3_MSK ~ GPIO_PIN_7_MSK
 **  (3)P2的PinMSK输入值范围：GPIO_PIN_1_MSK ~ GPIO_PIN_6_MSK
 **  (4)P3的PinMSK输入值范围：GPIO_PIN_0_MSK ~ GPIO_PIN_2_MSK、GPIO_PIN_5_MSK、GPIO_PIN_6_MSK
 ******************************************************************************/
void GPIO_EnableInt(uint8_t Port, uint8_t PinMSK);
/********************************************************************************
 ** \brief	 GPIO_DisableInt
 **			 关闭IO口的中断功能
 ** \param [in] Port  ： GPIO0、GPIO1、GPIO2、GPIO3
 **			    PinMSK: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK			 
 ** \return  none
 ** \note   
 **  (1)P0的PinMSK输入值范围：GPIO_PIN_0_MSK ~ GPIO_PIN_5_MSK
 **  (2)P1的PinMSK输入值范围：GPIO_PIN_3_MSK ~ GPIO_PIN_7_MSK
 **  (3)P2的PinMSK输入值范围：GPIO_PIN_1_MSK ~ GPIO_PIN_6_MSK
 **  (4)P3的PinMSK输入值范围：GPIO_PIN_0_MSK ~ GPIO_PIN_2_MSK、GPIO_PIN_5_MSK、GPIO_PIN_6_MSK
 ******************************************************************************/
void GPIO_DisableInt(uint8_t Port, uint8_t PinMSK);

 /******************************************************************************
 ** \brief	 GPIO_GetIntFlag
 **			 获取中断标志
 ** \param [in] Port  ： GPIO0、GPIO1、GPIO2、GPIO3
 **			    PinNum:  GPIO_PIN_0~GPIO_PIN_7 (0~7)		 
 ** \return  0：无中断产生
 **			 1：有中断产生
 ** \note  
 **  (1)P0的PinNum输入值范围：GPIO_PIN_0~GPIO_PIN_5
 **  (2)P1的PinNum输入值范围：GPIO_PIN_3~GPIO_PIN_7
 **  (3)P2的PinNum输入值范围：GPIO_PIN_1~GPIO_PIN_6
 **  (4)P3的PinNum输入值范围：GPIO_PIN_0~GPIO_PIN_2、GPIO_PIN_5、GPIO_PIN_6
 ******************************************************************************/
uint8_t  GPIO_GetIntFlag(uint8_t Port, uint8_t PinNum);
 /********************************************************************************
 ** \brief	 GPIO_ClearIntFlag
 **			清除中断标志位
 ** \param [in] Port  ： GPIO0、GPIO1、GPIO2、GPIO3
 **			    PinNum:  GPIO_PIN_0~GPIO_PIN_7 (0~7)		 
 ** \return  none
 ** \note  
 **  (1)P0的PinNum输入值范围：GPIO_PIN_0~GPIO_PIN_5
 **  (2)P1的PinNum输入值范围：GPIO_PIN_3~GPIO_PIN_7
 **  (3)P2的PinNum输入值范围：GPIO_PIN_1~GPIO_PIN_6
 **  (4)P3的PinNum输入值范围：GPIO_PIN_0~GPIO_PIN_2、GPIO_PIN_5、GPIO_PIN_6   
 ******************************************************************************/
void GPIO_ClearIntFlag(uint8_t Port, uint8_t PinNum);

#endif /* __GPIO_H__ */






