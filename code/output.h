#ifndef __OUTPUT_H__
#define __OUTPUT_H__
#include "cms8s6990.h"


#define POSTAL        P17

typedef struct _WindLevel_
{
   uint8_t windLevel ;
   
   

};

extern struct _WindLevel_ wdl;

enum WindSpeed{wind_stop,wind_sleep,wind_middle,wind_high,wind_auto};

extern uint16_t timer0_20ms_num;
extern uint16_t timer0_duty_num;



void OUTPUT_GPIO_Init(void);

void OutputData(uint8_t wds);



#endif 