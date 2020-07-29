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
/** \file flash.h
**
** 
**
** History:
** 
*****************************************************************************/
#ifndef __FLASH_H__
#define __FLASH_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s6990.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/
/*----------------------------------------------------------------------------
 **FLASH ÇøÓò
/*---------------------------------------------------------------------------*/
#define	FLASH_CODE			(0x00)
#define	FLASH_DATA			(0x01<< FLASH_MCTRL_MREG_Pos)
/*----------------------------------------------------------------------------
 **FLASH ²Ù×÷
/*---------------------------------------------------------------------------*/
#define	FLASH_WRITE			((0x2<< FLASH_MCTRL_MMODE_Pos) | FLASH_MCTRL_MSTART_Msk)
#define	FLASH_READ			((0x0<< FLASH_MCTRL_MMODE_Pos) | FLASH_MCTRL_MSTART_Msk)
#define	FLASH_ERASE			((0x3<< FLASH_MCTRL_MMODE_Pos) | FLASH_MCTRL_MSTART_Msk)

/*****************************************************************************/
/* Global type definitions ('typedef') */
/*****************************************************************************/


/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source) */
/*****************************************************************************/


/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source) */
/*****************************************************************************/
/*****************************************************************************
 ** \brief	FLASH_UnLock
 **			½âËø
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void FLASH_UnLock(void);
/*****************************************************************************
 ** \brief	FLASH_Lock
 **			ÉÏËø
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void FLASH_Lock(void);

/*****************************************************************************
 ** \brief	FLASH_Write
 **			Ð´»º´æ
 ** \param [in] FLASHModule	£º(1)FLASH_DATA:FlashÊý¾Ý¿Õ¼ä
 **							  (2)FLASH_CODE£ºFlash³ÌÐò¿Õ¼ä
 **				Addr: 16bit	  (1)FLASH_DATA_ADDR: 0x00~0x3FF;
 **							  (2)FLASH_CODE_ADDR: 0x00~0x3FFF;	
 **				Data: 8bit
 ** \return  none
 ** \note	 
*****************************************************************************/
void FLASH_Write(uint8_t FLASHModule, uint16_t Addr, uint8_t Data);

/*****************************************************************************
 ** \brief	FLASH_Read
 **			¶Á»º´æ
 ** \param [in]  FLASHModule£º(1)FLASH_DATA
 **							  (2)FLASH_CODE
 **				Addr: 16bit	  (1)FLASH_DATA_ADDR: 0x00~0x3FF;
 **							  (2)FLASH_CODE_ADDR: 0x00~0x3FFF;	
 ** \return  8bit Data
 ** \note	
*****************************************************************************/
uint8_t FLASH_Read(uint8_t FLASHModule, uint16_t Addr);

/*****************************************************************************
 ** \brief	FLASH_Erase
 **			²Á³ý
 ** \param [in]  FLASHModule£º(1)FLASH_DATA
 **							  (2)FLASH_CODE
 **				Addr: 16bit	  (1)FLASH_DATA_ADDR: 0x00~0x3FF;
 **							  (2)FLASH_CODE_ADDR: 0x00~0x3FFF;
 ** \return  none
 ** \note	
*****************************************************************************/
void FLASH_Erase(uint8_t FLASHModule, uint16_t Addr);

#endif /* __FLASH_H__ */
