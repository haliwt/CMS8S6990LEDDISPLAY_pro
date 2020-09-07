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
   uint8_t temparr[3];
   uint16_t addr;

 
	   temparr[0]=Flash_ToReadMinuteData();
	   if(NetRecMinute > temparr[0]) temparr[0]=NetRecMinute;
	   else NetRecMinute= temparr[0];
	   
	   temparr[1]=Flash_ToReadHourData();
	   if(NetRecHour > temparr[1])temparr[1]=NetRecHour;
	   else NetRecHour =temparr[1];
	   
	   temparr[2]=Flash_ToReadMoreHourData();
	   if(NetRecMoreHour >= temparr[2]) temparr[2]= NetRecMoreHour ;
	   else NetRecMoreHour  =temparr[2];
	  
   
     if(Telecom.ISR_NetRecMinuteAdj ==1){
	  Telecom.ISR_NetRecMinuteAdj=0;
	  NetRecMinute =0 ;
       temparr[0] =NetRecMinute ;

	  }
	  if(Telecom.ISR_NetRecHourAdj ==1){
		
	  Telecom.ISR_NetRecHourAdj=0;
		   NetRecHour =0 ;
			temparr[1] =NetRecHour ;

	  }

   addr =0;
   
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
	 
}
   FLASH_Lock();
	  
	 
}
/*****************************************************************
	*
	*Function Name :void Flash_ToRepeat_WriteData(void)
	*Function:read flash data,删除是整片删除，512字节一起删除
	*Input Ref: be write data
	*Return Ref:NO
	*
******************************************************************/
void Flash_ToRepeat_WriteData(uint8_t dat1,uint8_t dat2)
{

	  uint8_t temparr[3],onlyone=0;
	   uint16_t addr;
	
	   addr =0;

	   if(onlyone ==0){
	   	   onlyone ++ ;

		   temparr[0]=Flash_ToReadMinuteData();
		   if(NetRecMinute > temparr[0]) temparr[0]=NetRecMinute;
		   
		   temparr[1]=Flash_ToReadHourData();
		   if(NetRecHour > temparr[1])temparr[1]=NetRecHour;
		   
		   temparr[2]=Flash_ToReadMoreHourData();
		   if(NetRecMoreHour > temparr[2]) temparr[2]= NetRecMoreHour ;
   
	   	}
		FLASH_UnLock();
	   
	   FLASH_Erase(FLASH_DATA,addr);
	   for(addr = 0 ;addr< 0x1010 ;addr++)
	   {		   
	   
		   if(addr ==0)		
			 FLASH_Write(FLASH_DATA,addr, temparr[0]);  
		   else if(addr == 0x01) 
			 FLASH_Write(FLASH_DATA,addr, temparr[1]);
		   else if(addr == 0x02) 
			 FLASH_Write(FLASH_DATA,addr, temparr[2]);
		   else if(addr == 0x03)
			 FLASH_Write(FLASH_DATA,addr, dat1);
		   else if(addr == 0x04)
			 FLASH_Write(FLASH_DATA,addr, dat2);
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
	
	#if 0 
	   
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
	 delay_20us(20000);
	#endif 

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
	
	#if 0 
	   
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
	 delay_20us(20000);
	 #endif 

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
	
	 #if 0
	   
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
	 delay_20us(20000);
	 #endif 

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
void Flash_ToReadData(void)
{
	
   uint16_t addr ;
   uint8_t temp,temp1,temp2,temp3,temp4;
   uint8_t dispnum=0,d1=0,d2=0,d3=0;
   addr = 0;


   FLASH_UnLock();
   
	 temp  = FLASH_Read(FLASH_DATA,0);
	 temp1 = FLASH_Read(FLASH_DATA,0x01); 
	 temp2 = FLASH_Read(FLASH_DATA,0x02); 
	 temp3 = FLASH_Read(FLASH_DATA,0x03); 
	 temp4 = FLASH_Read(FLASH_DATA,0x04); 
	#if 0
	   
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
	 delay_20us(20000);
	 #endif 

}
/*****************************************************************
	*
	*Function Name :Flash_To750Hour_WriteData(void)
	*Function:read flash data
	*Input Ref:NO
	*Return Ref: 1--750小时 0 ---没有到
	*
******************************************************************/
uint8_t Flash_To750Hour_Vertict(void)
{

	uint8_t temp1,temp2,temp3;

	NetRec1500Hour =Flash_To1500Hour_Vertict();

		
	FLASH_UnLock();
	  
        temp1 = FLASH_Read(FLASH_DATA,0x01); 
		temp2 = FLASH_Read(FLASH_DATA,0x02); 
		temp3 = FLASH_Read(FLASH_DATA,0x03); 

		if(temp3==0x01) {

            NetRec750Hour =1;
			return 1;
		}
		
		if(temp2==3)// 600小时
		 {
			if(temp1 ==150){
                   NetRec750Hour = 0x01;
				
                 Flash_ToRepeat_WriteData(0x01,NetRec1500Hour);


			}
				return 1; //750小时

		 }

	   return 0;



}
/*****************************************************************
	*
	*Function Name :Flash_To1500Hour_WriteData(void)
	*Function:read flash data
	*Input Ref:NO
	*Return Ref: 1--1500小时 0 ---没有到
	*
******************************************************************/
uint8_t Flash_To1500Hour_Vertict(void)
{
	   
  
	uint8_t temp1,temp2,temp4;

	 FLASH_UnLock();
	    temp1 = FLASH_Read(FLASH_DATA,0x01); 
		temp2 = FLASH_Read(FLASH_DATA,0x02); 
		temp4 = FLASH_Read(FLASH_DATA,0x04); 
		
		if(temp4==0x01)    return 1;
		
		if(temp2==7)//1400
		 {
			if(temp1 ==100){ //1500小时
			    NetRec1500Hour =1;
                Flash_ToRepeat_WriteData(0x01,0x01);


			}
				
				return 1; //1500小时

		 }

	   return 0;



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

	    uint8_t temp1,temp0,temp2;

	
	     FLASH_UnLock();
	  
        temp0 = FLASH_Read(FLASH_DATA,0x00); 
		temp1 = FLASH_Read(FLASH_DATA,0x01); 
		temp2 = FLASH_Read(FLASH_DATA,0x02); 
		
		//显示全部
		if(temp1 <= 3)//3*200 = 600 (750 从1 开始计时 到 3000小时)
		 {
            if(temp0 <=150 )
			return 0; //    
		 }
		//显示3个弧度
		if(temp1 >3  && temp1 <=7 )
		{
            if(temp0 > 150 )
			return 3; //   750 houres <  x < 1500小时

		}	
		//显示两个绿色弧度
	   if(temp1 >7	&& temp2 <=11 )
	   {
		   if(temp0 <= 150 )
		   return 2; //   2250 houres <	x < 1500小时

	   }
	   
	  //显示1个绿色弧度
		if(temp1 >11  && temp2 <=15 )
		  {
			  if(temp0 > 150 )
			  return 1; //	 750 houres <  x < 1500小时
  
		  }

		//到更换滤网时间
		if( temp2==15 )
		  {
			 
			 return 5; //	 750 houres <  x < 1500小时
  
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
/*****************************************************************
	*
	*Function Name :void Flash_DisplayNumber(void)
	*Function:read flash data
	*Input Ref:NO
	*Return Ref:NO
	*
******************************************************************/
void Flash_DisplayNumber(void)
{
		
 
   uint8_t temp,temp1,temp2;
   uint8_t dispnum=0,d1=0,d2=0,d3=0;
   
  
    FLASH_UnLock();
   
	 temp = FLASH_Read(FLASH_DATA,0); 	 
	   
	 dispnum = temp;
	 d1= dispnum % 10;
	 d2= (dispnum/10) %10;
	 d3= (dispnum/100) %10;
	 
	 LEDDisplay_TimerTim(d3,d2,d1);
	 delay_20us(20000);
#if 0	
	 delay_20us(20000);
	  delay_20us(20000);
	   delay_20us(20000);
	    delay_20us(20000);
        delay_20us(20000);
	  delay_20us(20000);
	   delay_20us(20000);
	    delay_20us(20000);
#endif 	

	 temp1 = FLASH_Read(FLASH_DATA,0x01); 	 
	   
	 dispnum = temp1;
	 d1= dispnum % 10;
	 d2= (dispnum/10) %10;
	 d3= (dispnum/100) %10;
	 
	 LEDDisplay_TimerTim(d3,d2,d1);
	 delay_20us(20000);

#if 0
	  delay_20us(20000);
	  delay_20us(20000);
	   delay_20us(20000);
	    delay_20us(20000);
        delay_20us(20000);
	  delay_20us(20000);
	   delay_20us(20000);
	    delay_20us(20000);
#endif 
	
	 temp2 = FLASH_Read(FLASH_DATA,0x02); 	 
	   
	 dispnum = temp2;
	 d1= dispnum % 10;
	 d2= (dispnum/10) %10;
	 d3= (dispnum/100) %10;
	 
	 LEDDisplay_TimerTim(d3,d2,d1);
	 delay_20us(20000);
#if 0
	  delay_20us(20000);
	  delay_20us(20000);
	   delay_20us(20000);
	    delay_20us(20000);
        delay_20us(20000);
	  delay_20us(20000);
	   delay_20us(20000);
	    delay_20us(20000);
#endif 
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
   
	 temp = FLASH_Read(FLASH_DATA,0); 	 
	   
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
	 delay_20us(20000);
#if 1
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
	 delay_20us(20000);

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
	 delay_20us(20000);

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
	 delay_20us(20000);
     delay_20us(20000);
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
	 delay_20us(20000);
     delay_20us(20000);
	 delay_20us(20000);
	 delay_20us(20000);
	 delay_20us(20000);
	#endif 
#endif  


   	}




#endif 
