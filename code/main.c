
#include "cms8s6990.h"
#include "demo_timer.h"
#include "demo_buzzer.h"
#include "timer0.h"
#include "key.h"
#include "led.h"
#include "tm1650_i2c.h"
#include "timer2.h"


uint32_t Systemclock = 24000000;

extern uint8_t  vairI;
extern uint16_t timer0_ten_num;
extern uint16_t timer0_num;
extern uint16_t rec_num;
extern uint16_t rec2_num;

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
    TMR1_Config();
	TMR0_Config();
 //   TMR2_Config();
    GPIO_Config();
    LED_GPIO_Init();
	IIC_Init_TM1650();
    Init_Tm1650();

	while(1)
	{	
	 
        
       
		if(childLock  ==1){
            if(BuzzerSound==1){
                 BUZZER_Config();
				delay_20us(10000);
	           DisableBUZZER_Config();
               BuzzerSound =0;
               
            }
         TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
									
				TM1650_Set(0x6A,segNumber[1]);//初始化为5级灰度，开显示
				LockKey_Function();					
        
        }
        if(childLock  ==0){
            if(BuzzerSound==1){
                    BUZZER_Config();
				delay_20us(10000);
	           DisableBUZZER_Config();
               BuzzerSound =0;
            }
           
             KEY_Handing();
        
        }

	  if(timer0_num > 9000){
	  			i++;
            if(vairI==0){
                disp =rec_num ;
                vairI=1;
            }
            else {
                disp = rec2_num;
                vairI=0;
            }
			if(disp !=0){
				if(i==1)pmarr[i-1]=disp;
				else if(i==2)pmarr[i-1]=disp;
				else if(i==3)pmarr[i-1]=disp;
				else if(i==4)pmarr[i-1]=disp;
				else if(i==5)pmarr[i-1]=disp;
				else if(i==6)pmarr[i-1]=disp;
				else if(i==7)pmarr[i-1]=disp;
				else if(i==8)pmarr[i-1]=disp;
				else if(i==9)pmarr[i-1]=disp;
				else if(i==10)pmarr[i-1]=disp;
			}
            TM1650_Set(0x6A,segNumber[disp %10]);// 个位
            delay_20us(1000);
            TM1650_Set(0x6C,segNumber[ (disp /10) %10]);//十位
            delay_20us(1000);
             TM1650_Set(0x6E,segNumber[(disp /100) %10 ]);// 百位
            delay_20us(1000);
            timer0_num =0;
			if(i==1){
				for(j=0;j<10;j++)
				{
				  Telecom.PMaverageValue = Telecom.PMaverageValue + pmarr[i];
					
				}
                Telecom.PMaverageValue = Telecom.PMaverageValue / 10;

			}
			
			
                                
        
        }
		
    
	}		
}




















