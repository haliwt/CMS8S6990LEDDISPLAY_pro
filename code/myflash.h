#ifndef __MYFLASH_H__
#define __MYFLASH_H__
#include "cms8s6990.h"
#include "led.h"

#define TESTCODES   1


extern    uint8_t  NetRecMinute;      //记录虑网运行分钟时间
extern    uint8_t  NetRecHour;          //记录滤网的小时--运行“小时时间”
extern    uint8_t  NetRecMoreHour;
extern     uint8_t  NetChangeFlag ;

extern   uint8_t  NetRec750Hour ;
extern   uint8_t  NetRec1500Hour ;


uint8_t Flash_ToReadMinuteData(void);

uint8_t Flash_ToReadHourData(void);


uint8_t Flash_ToReadMoreHourData(void);
void Flash_ToWriteData(void);

void Flash_ToReadData(void);

uint8_t Flash_To750Hour_Vertict(void);
uint8_t  Flash_To1500Hour_Vertict(void);
uint8_t  Flash_To3000Hour_Vertict(void);
void Flash_ToRepeat_WriteData(uint8_t dat3,uint8_t dat4);
uint8_t Flash_ToReadDiffData(void);

void FLASH_Init(void); //初始化清零

void TestFlash_ToWriteAndReadData(void);


void Flash_DisplayNumber(void);


#endif 