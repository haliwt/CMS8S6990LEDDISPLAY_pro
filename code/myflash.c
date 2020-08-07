#include "myflash.h"


void Flash_ToWriteData(uint16_t addr,uint16_t dat)
{

   FLASH_UnLock();
   FLASH_Erase(FLASH_DATA,addr);
   FLASH_Write(FLASH_DATA,addr, dat);	
  // FLASH_Lock();		
}



uint8_t Flash_ToReadData(uint16_t addr)
{
	volatile uint8_t temp=0;
//	FLASH_UnLock();
	temp = FLASH_Read(FLASH_DATA,addr);	
    return temp;
}