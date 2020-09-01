#include "output.h"
#include "timer2.h"

static void OutputData(uint8_t wds);


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
	uint8_t disp =0,pmarr[10];
	uint8_t i=0,j=0,disdat3=0,disdat2=0,disdat1=0,wdl=0;
	uint16_t PMaverageValue;          //PM sensor averageValue 
 
if(timer0_num >= 1000 && timer0_num <=1060 ){
			timer0_num =0;
			 i++;
		 if(vairI==0){
			 disp =rec_num ;
			 
			 vairI=1;
			 disdat3 = (rec_num /100) %10;	 //百位
			 disdat2 = (rec_num /10) %10;  //十位
			 disdat1 = rec_num	%10;		//个位
			 rec2_num=0;
		 }
		 else {
			 disp = rec2_num;
			 vairI=0;
			 disdat3 = (rec2_num /100) %10;   //百位
			 disdat2 = (rec2_num /10) %10;	//十位
			 disdat1 = rec2_num  %10;		 //个位
			 rec_num =0;
		 }
		 if(disp >2){
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
		 
		// LEDDisplay_PMValue(disdat3,disdat2,disdat1);
	 
		 timer0_num =0;
		 if(i==1){
			 for(j=0;j<10;j++)
			 {
			   PMaverageValue = PMaverageValue + pmarr[i];
				 
			 }
			 PMaverageValue = PMaverageValue / 10;
		 
			 if(PMaverageValue < 75) wdl = wind_sleep;
			 else if(PMaverageValue > 75 && PMaverageValue <150)wdl = wind_middle;
			 else if(PMaverageValue > 150 && PMaverageValue  < 300)wdl = wind_high;
			 else if(PMaverageValue > 300)wdl = wind_high;
			 
		 }
		if(wdl == wind_sleep)OutputData(0x01);
		else if(wdl == wind_middle)OutputData(0x02);
		else if(wdl == wind_high)OutputData(0x03);

		 
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
static void OutputData(uint8_t wds)
{

	 
	  switch(wds){

	  case wind_sleep :   //2%
	       TMR2_Config(wds);

	  break;

	  case wind_middle: //4%
	        
	      TMR2_Config(wds);

	  break;

	  case wind_high:  //7%
	  		
			 TMR2_Config(wds);
	  break;
      
      case wind_stop:
          TMR2_Config(wds);
      break;
	  
      }



   }


