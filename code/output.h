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
extern uint8_t windLevelHighest ;


extern  uint8_t PM_1;
extern  uint8_t PM_2;
extern  uint8_t PM_3;

enum WindSpeed{wind_stop,wind_sleep,wind_middle,wind_high,wind_auto,wind_highest};








void OutputData(uint8_t wds);
void PM_SendData(void);


#endif 
