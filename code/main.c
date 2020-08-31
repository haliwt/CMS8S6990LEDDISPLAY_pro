
#include "cms8s6990.h"
#include "demo_timer.h"
#include "demo_buzzer.h"
#include "timer0.h"
#include "key.h"
#include "led.h"
#include "tm1629d.h"
#include "timer2.h"
#include "output.h"


uint32_t Systemclock = 24000000;

extern uint8_t  vairI;
extern uint16_t timer0_ten_num;
extern uint16_t timer0_num;
extern uint16_t rec_num;
extern uint16_t rec2_num;


struct _WindLevel_ wdl;

Telec Telecom;

/*******************************************************
	*
	*Function Name: int main(void)
	*
	*
	*
*******************************************************/
int main(void)
{		
	uint16_t disp =0,pmarr[10];
	uint8_t poweron=0,i=0,j=0;
    static uint8_t wdl=0;

    TMR1_Config();
	TMR0_Config();
    GPIO_Config();
    LED_GPIO_Init();




	while(1)
	{	
	   

		Tm1629DDis();

	
		
       
}		

} 



















