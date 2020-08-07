#ifndef __MYFLASH_H__
#define __MYFLASH_H__
#include "cms8s6990.h"


void Flash_ToWriteData(uint16_t addr,uint16_t dat);

uint8_t Flash_ToReadData(uint16_t addr);






#endif 