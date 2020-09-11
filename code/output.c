#include "output.h"
#include "timer2.h"

 void OutputData(uint8_t wds);
 uint8_t PM_1;
 uint8_t PM_2;
 uint8_t PM_3;


/***************************************************
	*
	*Function Name:void OutputData(void)
	*Function: commniucation with main board
	*Input Ref: NO
	*Return Ref: NO
	*
***************************************************/
void PM_SendData(void)
{  
   static uint8_t disp =0,PMave1,PMave2,PMave3,PMave4;
	uint8_t i=0,j=0;
    uint8_t wdl=0;
       if(timer0_num >= 1000 && timer0_num <=1060 ){
			timer0_num =0;
			 i++;
		 if(vairI==0){
			 disp =rec_num ;
			 
			 vairI=1;
			PM_3 = (rec_num /100) %10;	 //百位
			 PM_2 = (rec_num /10) %10;  //十位
			 PM_3 = rec_num	%10;		//个位
			 rec2_num=0;
		 }
		 else {
			 disp = rec2_num;
			 vairI=0;
			 PM_3 = (rec2_num /100) %10;   //百位
			 PM_2 = (rec2_num /10) %10;	//十位
			 PM_1 = rec2_num  %10;		 //个位
			 rec_num =0;
		 }
		 LED_DispPMLogo();
		 LEDDisplay_TimerTim(PM_3,PM_2,PM_1);
	 
		 timer0_num =0;
        
         if(disp <75 && disp > 12){
              PMave1++;
          }
          else if(disp > 75 &&  disp <150) PMave2++;
          else if(disp > 150 && disp < 300)PMave3++;
          else if(disp > 300) PMave4++;
		
          if(PMave1 >=10){
              wdl= wind_sleep;
              PMave1=0;
               PMave2=0;
               PMave3=0;
               PMave4=0;
          }
          else if(PMave2 >=10){
              wdl= wind_middle;
              PMave1=0;
               PMave2=0;
               PMave3=0;
               PMave4=0;
          }
          else if(PMave3 >=10){
                wdl =  wind_high;
                PMave1=0;
               PMave2=0;
               PMave3=0;
               PMave4=0;
          }
          else if(PMave4 >=10){
               wdl =  wind_highest;
                PMave1=0;
               PMave2=0;
               PMave3=0;
               PMave4=0;
          
          }
		    
    
		 if(wdl == wind_sleep)OutputData(0x01);
		 else if(wdl == wind_middle)OutputData(0x02);
		 else if(wdl == wind_high)OutputData(0x03);
		 else if(wdl== wind_highest)OutputData(0x05);
		 
		 
	  }

     
   
}
/***************************************************
	*
	*Function Name:void OutputData(void)
	*Function: commniucation with main board
	*Input Ref: NO
	*Return Ref: NO
	*
***************************************************/
 void OutputData(uint8_t wds)
{

	 
	  switch(wds){

	  case wind_sleep :   //2%
	       TMR2_Config(wds);
	        windLevelHighest =0;

	  break;

	  case wind_middle: //4%
	        
	      TMR2_Config(wds);
		  windLevelHighest =0;

	  break;

	  case wind_high:  //7%
	  		
			 TMR2_Config(wds);
			 windLevelHighest =0;
	  break;

	  case wind_auto :   //7% 0x05
	    
		 windLevelHighest =0;

	  break;

	  case wind_highest :   //7% 0x05
	     TMR2_Config(0x03);
		 windLevelHighest =1;

	  break;
      
    
	  
      }



   }


