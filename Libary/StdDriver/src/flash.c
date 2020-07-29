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

/****************************************************************************/
/** \file FLASH.c
**
** 
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "flash.h"

/****************************************************************************/
/*	Local pre-processor symbols/macros('#define')
****************************************************************************/


/****************************************************************************/
/*	Global variable definitions(declared in header file with 'extern')
*****************************************************************************/

/****************************************************************************/
/*	Local type definitions('typedef')
*****************************************************************************/

/****************************************************************************/
/*	Local variable  definitions('static')
*****************************************************************************/

/****************************************************************************/
/*	Local function prototypes('static')
*****************************************************************************/

/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
*****************************************************************************/
/*****************************************************************************
 ** \brief	FLASH_UnLock
 **			½âËø
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void FLASH_UnLock(void)
{
	MLOCK = 0xAA;
}
/*****************************************************************************
 ** \brief	FLASH_Lock
 **			ÉÏËø
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void FLASH_Lock(void)
{
	MLOCK = 0x00;
}

/*****************************************************************************
 ** \brief	FLASH_Write
 **			Ð´»º´æ
 ** \param [in] FLASHModule	£º(1)FLASH_DATA
 **							  (2)FLASH_CODE
 **				Addr: 16bit	  (1)FLASH_DATA_ADDR: 0x00~0x3FF;
 **							  (2)FLASH_CODE_ADDR: 0x00~0x3FFF;	
 **				Data: 8bit
 ** \return  none
 ** \note	 
*****************************************************************************/
void FLASH_Write(uint8_t FLASHModule, uint16_t Addr, uint8_t Data)
{

	if( !(MCTRL & FLASH_MCTRL_MERR_Msk))
	{
		MDATA = Data;
		MADRL = Addr;
		MADRH = Addr>>8;
		MCTRL = FLASH_WRITE | FLASHModule;	
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();	
	}	
}

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
uint8_t FLASH_Read(uint8_t FLASHModule, uint16_t Addr)
{
	MADRL = Addr;
	MADRH = Addr>>8;
	MCTRL = FLASH_READ | FLASHModule;	
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	return (MDATA);
}

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
void FLASH_Erase(uint8_t FLASHModule, uint16_t Addr)
{
	MADRL = Addr;
	MADRH = Addr>>8;
	MCTRL  = FLASH_ERASE | FLASHModule;	
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

