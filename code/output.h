#ifndef __OUTPUT_H__
#define __OUTPUT_H__
#include "cms8s6990.h"
#include "key.h"
#include "timer0.h"


extern uint8_t  vairI;
extern uint16_t timer0_ten_num;
extern uint16_t timer0_num;
extern uint16_t rec_num;
extern uint16_t rec2_num;

typedef struct _WindLevel_
{
   uint8_t windLevel ;
   
   

};

extern struct _WindLevel_ wdl;

enum WindSpeed{wind_stop,wind_sleep,wind_middle,wind_high,wind_auto};








void OutputData(uint8_t wds);
uint16_t PM_SendData(void);


#endif 
