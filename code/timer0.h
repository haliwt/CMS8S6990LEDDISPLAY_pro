#ifndef __TIMER0_H__
#define __TIMER0_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s6990.h"

extern volatile uint16_t getMinute; 
extern volatile uint16_t getHour;
extern volatile uint16_t Timer1_num;
extern uint8_t  childLock ;
extern uint8_t  BuzzerSound ;



/******************************************************************************
 ** \brief	 TMR0_Config
 ** \param [in] 
 **            	
 ** \return  none
 ** \note  
 ******************************************************************************/
void TMR0_Config(void);





#endif /* __DEMO_TIMER_H__ */






