#include "output.h"
#include "timer2.h"



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


