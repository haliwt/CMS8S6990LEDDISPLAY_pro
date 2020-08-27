#include "myflash.h"



void Flash_ToWriteData(uint16_t addr,uint16_t dat)
{

	 volatile  uint16_t tempaddr =0;
     volatile  uint8_t temp =0;
	  FLASH_UnLock();
	  tempaddr = addr;
	  FLASH_Erase(FLASH_DATA,addr);
	  for(tempaddr =addr ; tempaddr< (addr + 0x10) ; tempaddr++) //第二扇区 512 *2 = 1024 = 0x400  512 = 0x200
	  { 		  
		  FLASH_Write(FLASH_DATA,addr, dat);		  
		  temp = FLASH_Read(FLASH_DATA,addr);	  
	  }
	//  FLASH_Lock();   
	  
	 
}



uint8_t Flash_ToReadData(uint16_t addr)
{
	volatile uint8_t temp=0;
	
	FLASH_UnLock();
	
	temp = FLASH_Read(FLASH_DATA,addr);	
    return temp;
}



    
