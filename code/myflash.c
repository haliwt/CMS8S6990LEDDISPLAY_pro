#include "myflash.h"




/*****************************************************************
	*
	*Function Name :void Flash_ToWriteData(void)
	*Function:read flash data
	*Input Ref:NO
	*Return Ref:NO
	*
******************************************************************/

void Flash_ToWriteData(void)
{
   uint8_t temparr[3],onlyone=0;
   uint16_t addr;

      temparr[0] =  NetRecMinute;
	  if(Telecom.ISR_NetHourAdj ==1){
	  	  Telecom.ISR_NetHourAdj =0;
		  NetRecMinute=0;
	     temparr[0] =  NetRecMinute;

	  }
	  temparr[1] = NetRecHour;
	  if(Telecom.ISR_NetMoreHourAdj==1){
          Telecom.ISR_NetMoreHourAdj=0;
		  NetRecHour =0;
	      temparr[1]= NetRecHour ;

	  }
	  temparr[2] =NetRecMoreHour;
      


	  if(onlyone ==0){
   	   onlyone ++ ;
	   //保存以前的数据
	   temparr[0]=Flash_ToReadMinuteData();
	     if(temparr[0] < NetRecMinute)temparr[0] = NetRecMinute;

	   temparr[1]=Flash_ToReadHourData();
	   if(temparr[1]< NetRecHour )temparr[1]=NetRecHour ;
		  
	   	temparr[2]=Flash_ToReadMoreHourData();
	    if(temparr[2]< NetRecMoreHour) temparr[2]=	NetRecMoreHour;

	  
      }
  
			
   

   addr =0;
   
    FLASH_UnLock();
   
   FLASH_Erase(FLASH_DATA,addr);
   for(addr = 0 ;addr< 0x10 ;addr++)
   {		   
   
	   if(addr ==0)		
		 FLASH_Write(FLASH_DATA,addr,temparr[0]);  
	   else if(addr == 0x01) 
		 FLASH_Write(FLASH_DATA,addr, temparr[1]);
	   else if(addr == 0x02) 
		 FLASH_Write(FLASH_DATA,addr, temparr[2]);
	  }
   FLASH_Lock();
	  
	 
}

/*****************************************************************
	*
	*Function Name :void FLASH_ToReadData(void)
	*Function:read flash data
	*Input Ref:NO
	*Return Ref:NO
	*
******************************************************************/
uint8_t Flash_ToReadMinuteData(void)
{
	
   uint16_t addr ;
   uint8_t temp;
   uint8_t dispnum=0,d1=0,d2=0,d3=0;
   addr = 0;


   FLASH_UnLock();
   
	temp  = FLASH_Read(FLASH_DATA,0);
	
	

	 return temp;

}
/*****************************************************************
	*
	*Function Name :void FLASH_ToReadData(void)
	*Function:read flash data
	*Input Ref:NO
	*Return Ref:NO
	*
******************************************************************/
uint8_t Flash_ToReadHourData(void)
{
	
   uint16_t addr ;
   uint8_t temp;
   uint8_t dispnum=0,d1=0,d2=0,d3=0;
   addr = 0;


   FLASH_UnLock();
   
	 temp  = FLASH_Read(FLASH_DATA,0x01);
	
	
	 return temp;

}
/*****************************************************************
	*
	*Function Name :void FLASH_ToReadData(void)
	*Function:read flash data
	*Input Ref:NO
	*Return Ref:NO
	*
******************************************************************/
uint8_t Flash_ToReadMoreHourData(void)
{
	
   uint16_t addr ;
   uint8_t temp;
   uint8_t dispnum=0,d1=0,d2=0,d3=0;
   addr = 0;


   FLASH_UnLock();
   
	 temp  = FLASH_Read(FLASH_DATA,0x02);
	
	

	 return temp;

}


/*****************************************************************
	*
	*Function Name :uint8_t Flash_ToRead1500And750Data(void)
	*Function:read flash data
	*Input Ref:NO
	*Return Ref:NO
	*
******************************************************************/
uint8_t Flash_ToRead1500And750Data(void)
{
	
  
   uint8_t temp;
 
 


   FLASH_UnLock();
   
	 temp  = FLASH_Read(FLASH_DATA,0x03);
	return temp ;
	

}
/*****************************************************************
	*
	*Function Name :uint8_t Flash_ADJ750AND1500_Vertict(void)
	*Function:read flash data
	*Input Ref:NO
	*Return Ref: 1--750小时 0 ---没有到
	*
******************************************************************/
uint8_t Flash_ADJ750AND1500_Vertict(void)
{

	uint8_t temp1,temp2,temp3,onetime=0;

	#if 1

        temp1 = NetRecMinute ;
	    temp2 = NetRecHour;
		temp3= NetRecMoreHour ;


	   if(onetime ==0){
		   	onetime ++ ;
	       FLASH_UnLock();
		  
	        temp1 = FLASH_Read(FLASH_DATA,0x01); 
			temp2 = FLASH_Read(FLASH_DATA,0x02); 
			temp3 = FLASH_Read(FLASH_DATA,0x03); 
	   }

		if(temp3==0x02) {

            NetRec1500Hour =0x02;
			return 0x02;
		}
		if(temp3==0x01){

            NetRec750Hour =1;
			return 1;
		}
		
		

		if(temp2==7)//1400
		 {
			if(temp1 ==100){ //1500小时
			    NetRec1500Hour =0x02;
               Flash_T01500Write(0x02);

			}
				
				return 0x02; //1500小时
         }
		
		if(temp2==3)//600
		 {
			if(temp1 ==150){ //150小时
			    NetRec750Hour =0x01;
              Flash_T01500Write(0x01);

			}
				
				return 0x01; //1500小时
		}
		
		#endif 

	   return 0;



}
/*****************************************************************
	*
	*Function Name :uint8_t Flash_T01500Write(uint8_t dat1)
	*Function:read flash data
	*Input Ref:NO
	*Return Ref: 1--750小时 0 ---没有到
	*
******************************************************************/

void Flash_T01500Write(uint8_t dat1)
{
	
	uint8_t temparr[3];
		 uint16_t addr;
	   
		  addr =0;
	
		 temparr[0]=Flash_ToReadMinuteData();
			  if(NetRecMinute > temparr[0]) temparr[0]=NetRecMinute;
			  
			  temparr[1]=Flash_ToReadHourData();
			  if(NetRecHour > temparr[1])temparr[1]=NetRecHour;
			  
			  temparr[2]=Flash_ToReadMoreHourData();
			  if(NetRecMoreHour > temparr[2]) temparr[2]= NetRecMoreHour ;
	  
		   
		 
		      FLASH_UnLock();
	
	
			  FLASH_Erase(FLASH_DATA,addr);
			  for(addr = 0 ;addr< 0x10 ;addr++)
			 {		  
	  
				  if(addr ==0)	   
				   FLASH_Write(FLASH_DATA,addr, temparr[0]);	
				  else if(addr == 0x01) 
					FLASH_Write(FLASH_DATA,addr, temparr[1]);
				  else if(addr == 0x02) 
					FLASH_Write(FLASH_DATA,addr, temparr[2]);
				  else if(addr == 0x03)
					FLASH_Write(FLASH_DATA,addr, dat1);
				 
			 }
			FLASH_Lock();
	
}

/*****************************************************************
	*
	*Function Name :Flash_To13000Hour_WriteData(void)
	*Function:read flash data
	*Input Ref:NO
	*Return Ref: 1--3000小时 0 ---没有到
	*
******************************************************************/
uint8_t Flash_To3000Hour_Vertict(void)
{
	   
	uint8_t temp;

	
	     FLASH_UnLock();
	  
         
		temp = FLASH_Read(FLASH_DATA,0x02); 
		
		
		if(temp==0x0f)//15
		 {
			return 1; //3000小时

		 }

	   return 0;



}
/*****************************************************************
	*
	*Function Name :uint8_t Flash_ToReadDiffData(void)
	*Function:read flash data
	*Input Ref:NO
	*Return Ref: 1--2250小时 ，2----1500小时 0---时间没到
	*
******************************************************************/
uint8_t Flash_ToReadDiffData(void)
{

	    uint8_t temp;

	
	     FLASH_UnLock();
	  
         
		temp = FLASH_Read(FLASH_DATA,0x02); 
		
		
		if(temp==0x0B)//11
		 {
			return 1; //2200小时

		 }
		if(temp == 0x07)
		{
			return 2; //1400小时

		}	

	   return 0;


}
/*****************************************************************
	*
	*Function Name :void FLASH_Init(void)
	*Function: intial zero
	*Input Ref:NO
	*Return Ref: NO 
	*
******************************************************************/
void FLASH_Init(void)
{
	 uint16_t addr=0;
	 
	 FLASH_UnLock();
   
   FLASH_Erase(FLASH_DATA,addr);
   for(addr = 0 ;addr< 0x10 ;addr++)
   {		   
   
	   if(addr ==0)		
		 FLASH_Write(FLASH_DATA,addr, 0x00);  
	   else if(addr == 0x01) 
		 FLASH_Write(FLASH_DATA,addr, 0x00);
	   else if(addr == 0x02) 
		 FLASH_Write(FLASH_DATA,addr, 0x00);
	   else if(addr == 0x03)
	     FLASH_Write(FLASH_DATA,addr, 0x00);
	   else if(addr == 0x04)
	     FLASH_Write(FLASH_DATA,addr, 0x00);
	}
   FLASH_Lock();
}


#if TESTCODES 

/*****************************************************************
	*
	*Function Name :void TestFlash_ToWriteData(void)
	*Function:read flash data
	*Input Ref:NO
	*Return Ref:NO
	*
******************************************************************/
void TestFlash_ToWriteAndReadData(void)
{
		
   uint16_t addr ;
   uint8_t temp,temp1,temp2;
   uint8_t dispnum=0,d1=0,d2=0,d3=0;
   
    addr =0;
   #if 0
    FLASH_UnLock();
   
   FLASH_Erase(FLASH_DATA,addr);
   for(addr = 0 ;addr< 0x1010 ;addr++)
   {		   
   
	   if(addr ==0)		
		
		 FLASH_Write(FLASH_DATA,addr, 0x01);  
	   else if(addr == 0x01) 
		
		  FLASH_Write(FLASH_DATA,addr, 0x02);  
	   else if(addr == 0x02) 
		 // FLASH_Write(FLASH_DATA,addr, NetRecMoreHour);
		  FLASH_Write(FLASH_DATA,addr, 0x03);  
	   else if(addr == 0x03)
	     // FLASH_Write(FLASH_DATA,addr, NetRec750Hour);
	      FLASH_Write(FLASH_DATA,addr, 0x0f);  
	   else if(addr == 0x04)
	     // FLASH_Write(FLASH_DATA,addr, NetRec1500Hour);
	      FLASH_Write(FLASH_DATA,addr, 0x09);  

   #endif 
   


   FLASH_UnLock();
   
	 temp = FLASH_Read(FLASH_DATA,0x0); 	 
	   
	 dispnum = temp;
	 d1= dispnum % 10;
	 d2= (dispnum/10) %10;
	 d3= (dispnum/100) %10;
	 
	 LEDDisplay_TimerTim(d3,d2,d1);
	 delay_20us(20000);
	 delay_20us(20000);
	 delay_20us(20000);
     delay_20us(20000);
	 delay_20us(20000);
	 delay_20us(20000);
	 delay_20us(20000);
	
     
	
#if 1
	 FLASH_UnLock();
	   

	 temp1 = FLASH_Read(FLASH_DATA,0x01); 	 
	   
	 dispnum = temp1;
	 d1= dispnum % 10;
	 d2= (dispnum/10) %10;
	 d3= (dispnum/100) %10;
	 
	 LEDDisplay_TimerTim(d3,d2,d1);
	 delay_20us(20000);
	 delay_20us(20000);
	 delay_20us(20000);
     delay_20us(20000);
	 delay_20us(20000);
	 delay_20us(20000);
	 delay_20us(20000);
	

	  FLASH_UnLock();
   

	  temp2 = FLASH_Read(FLASH_DATA,0x02); 	 
	   
	 dispnum = temp2;
	 d1= dispnum % 10;
	 d2= (dispnum/10) %10;
	 d3= (dispnum/100) %10;
	 
	 LEDDisplay_TimerTim(d3,d2,d1);
	 delay_20us(20000);
	 delay_20us(20000);
	 delay_20us(20000);
     delay_20us(20000);
	 delay_20us(20000);
	 delay_20us(20000);
	 delay_20us(20000);
	 
#if 0
	   FLASH_UnLock();
   
	  temp3 = FLASH_Read(FLASH_DATA,0x03); 	 
	   
	 dispnum = temp3;
	 d1= dispnum % 10;
	 d2= (dispnum/10) %10;
	 d3= (dispnum/100) %10;
	 
	 LEDDisplay_TimerTim(d3,d2,d1);
	 delay_20us(20000);
	 delay_20us(20000);
	 delay_20us(20000);
     delay_20us(20000);
	 delay_20us(20000);
	 delay_20us(20000);
	 delay_20us(10000);
#endif 	 
	
#if 0
	  temp3 = FLASH_Read(FLASH_DATA,0x03); 	 
	   
	 dispnum = temp3;
	 d1= dispnum % 10;
	 d2= (dispnum/10) %10;
	 d3= (dispnum/100) %10;
	 
	 LEDDisplay_TimerTim(d3,d2,d1);
	 delay_20us(20000);
	 delay_20us(20000);
	 delay_20us(20000);
	
     
       temp4 = FLASH_Read(FLASH_DATA,0x04); 	 
	   
	 dispnum = temp4;
	 d1= dispnum % 10;
	 d2= (dispnum/10) %10;
	 d3= (dispnum/100) %10;
	 
	 LEDDisplay_TimerTim(d3,d2,d1);
	 delay_20us(20000);
	 delay_20us(20000);
	 delay_20us(20000);
#endif 
	
#endif  


   	}




#endif 
