#include "tm1629d.h"


const unsigned char segNumber[]={
         seg_a+seg_b+seg_c+seg_d+seg_e+seg_f+seg_h,        // char "0"  0x00
         seg_b+seg_c,                                      // char "1"  0x01
         seg_a+seg_b+seg_d+seg_e+seg_g+seg_h,              // char "2"  0x02
         seg_a+seg_b+seg_c+seg_d+seg_g+seg_h,              // char "3"  0x03
         seg_b+seg_c+seg_f+seg_g,                          // char "4"  0x04
         seg_a+seg_c+seg_d+seg_f+seg_g+seg_h,              // char "5"  0x05
         seg_a+seg_c+seg_d+seg_e+seg_f+seg_g+seg_h,        // char "6"  0x06
         seg_a+seg_b+seg_c+seg_f+seg_h,                    // char "7"  0x07
         seg_a+seg_b+seg_c+seg_d+seg_e+seg_f+seg_g+seg_h,  // char "8"  0x08
         seg_a+seg_b+seg_c+seg_d+seg_f+seg_g+seg_h,        // char "9"  0x09
         seg_h,                                             // char "."  0x0A
         0                                                  // Dont't display 0x0B
         
};

/******************************************************
  *
  *函数名称：Tm1620Dis
  *函数功能：驱动显示数据
  *入口参数：要操作的数据
  *出口参数：无
  *
//***************************************************/
void Tm1629DDis(void)
{
	

		STB_TM1629D =0 ;  
        Tm1629DSentData(ModeDisTM1629D); //写数据到显示寄存器
		
		STB_TM1629D =1; 
	

		
    STB_TM1629D=0;   
		//Tm1629DSentData(AddrAutoAdd);
        Tm1629DSentData(AddrFixed);//AddrFixed
		//写显示，固定定制模式
		STB_TM1629D=1; 
		
    STB_TM1629D=0;   
		Tm1629DSentData(Addr00H);
		//指向地址0   
	
		Tm1629DSentData(segNumber[4]); //主显示3 位---百位
	
      //写第二位 
      
  	STB_TM1629D=1; 
		
    STB_TM1629D=0;   
		Tm1629DSentData(Addr02H);
		//指向地址0   
	
		Tm1629DSentData(segNumber[3]); //主显示2位---十位
	
    //写第三位
    
    STB_TM1629D=1; 
		
    STB_TM1629D=0;   
		Tm1629DSentData(Addr04H);
		//指向地址0   
	
	   Tm1629DSentData(segNumber[2]); //主显示1位----个位
    
    //写第四位数据
    STB_TM1629D=1; 
		
    STB_TM1629D=0;   
    //指向地址6 
		Tm1629DSentData(Addr06H);
	  
	  Tm1629DSentData(segNumber[1]); //写数据//Tm1629DSentData(segNumber[keystr.TimeHour]); //写数据
    
    #if 1
       //写第五位数据  MANI RUN TIME
     STB_TM1629D=1; 
     STB_TM1629D=0;   
     //指向地址8 
      Tm1629DSentData(Addr08H);
      
      Tm1629DSentData(segNumber[6]); //写数据 //Tm1629DSentData(segNumber[keystr.windLevel]); //写数据
 
     //写第6位数据    MATIN RUN TIME 
     STB_TM1629D=1; 
    
     STB_TM1629D=0;   
     //指向地址8 
      Tm1629DSentData(Addr0AH);
    
      Tm1629DSentData(segNumber[5]); //写数据
      STB_TM1629D =1; 


	   STB_TM1629D=0;   
     //指向地址8 
      Tm1629DSentData(Addr0CH);
    
      Tm1629DSentData(segNumber[5]); //写数据
      STB_TM1629D =1; 

	
         STB_TM1629D=0;   
     //指向地址8 
      Tm1629DSentData(Addr0EH);
    
      Tm1629DSentData(segNumber[8]); //写数据
        STB_TM1629D =1; 
      

         STB_TM1629D=0;   
     //指向地址8 
      Tm1629DSentData(Addr0FH);
    
      Tm1629DSentData(segNumber[8]); //写数据
        STB_TM1629D =1; 
      




	
      STB_TM1629D =0; 
      Tm1629DSentData(OpenDisTM1629D|Set12_16TM1629D); 
      STB_TM1629D =1; 

}
/******************************************************
  *
  *函数名称：void  Tm1620_RunDisp(void)
  *函数功能：驱动显示数据
  *入口参数：要操作的数据
  *出口参数：无
  *
******************************************************/

void  Tm1629D_RunDisp(void)
{
    STB_TM1629D =0 ;  
        Tm1629DSentData(ModeDisTM1629D); 
    //设置显示模式，6位8段--上电默认是7段8段
    STB_TM1629D =1; 
    
    STB_TM1629D=0;   
    //Tm1629DSentData(AddrAutoAdd);
     Tm1629DSentData(AddrFixed);//AddrFixed
    //写显示，固定定制模式
         STB_TM1629D=1;

      //写第五位数据  MANI RUN TIME
     STB_TM1629D=0;   
     //指向地址8 
      Tm1629DSentData(Addr08H);
      
      Tm1629DSentData(segNumber[0]); //写数据 //Tm1629DSentData(segNumber[keystr.windLevel]); //写数据
    
     //写第6位数据    MATIN RUN TIME 
     STB_TM1629D=1; 
    
     STB_TM1629D=0;   
     //指向地址8 
      Tm1629DSentData(Addr0AH);
    
      Tm1629DSentData(segNumber[0]); //写数据
    
      
      
      STB_TM1629D =1; 
      STB_TM1629D =0; 
      Tm1629DSentData(OpenDisTM1629D|Set12_16TM1629D); 
      STB_TM1629D =1; 


}
//************************************************************************
// 函数名称：Tm1629DSentData
// 函数功能：向TM1620发数据 8位数据-1个字节的数据
// 入口参数：要操作的数据
// 出口参数：无
// 技术简要：上升沿操作一位 从低位开始操作数据
//***************************************************************************/
void  PowerOn_RunDisp(void)
{
     STB_TM1629D =0 ;  
        Tm1629DSentData(ModeDisTM1629D); 
    //设置显示模式，6位8段--上电默认是7段8段
    STB_TM1629D =1; 
     _nop_(); 
    STB_TM1629D=0;   
    //Tm1629DSentData(AddrAutoAdd);
        Tm1629DSentData(AddrFixed);//AddrFixed
    //写显示，固定定制模式
         STB_TM1629D=1;
	  _nop_(); 

      //写第五位数据  MANI RUN TIME
     STB_TM1629D=0;   
     //指向地址8 
      Tm1629DSentData(Addr08H);
      
      Tm1629DSentData(segNumber[0]); //写数据 //Tm1629DSentData(segNumber[keystr.windLevel]); //写数据
     
    
     //写第6位数据    MATIN RUN TIME 
     STB_TM1629D=1; 
     _nop_(); 
     STB_TM1629D=0;   
     //指向地址8 
      Tm1629DSentData(Addr0AH);
    
      Tm1629DSentData(segNumber[3]); //写数据
     
      STB_TM1629D =1; 


	  
      STB_TM1629D =0; 
      Tm1629DSentData(OpenDisTM1629D|Set12_16TM1629D); 
      STB_TM1629D =1; 


}
//************************************************************************
// 函数名称：Tm1629DSentData
// 函数功能：向TM1620发数据 8位数据-1个字节的数据
// 入口参数：要操作的数据
// 出口参数：无
// 技术简要：上升沿操作一位 从低位开始操作数据
//***************************************************************************/
void Tm1629DSentData(uint8_t oneByte)
{
	uint8_t i;  
   
	
  for(i=0;i<8;i++)   
  {   
    
		 TM1629D_SCL = 0;//CLK_TM1620_CLR; 
		//  _nop_(); 
		 if(oneByte & (1 << i))  
		 {
	       TM1629D_SDA  = 1;//DIO_TM1620_SET;
	       // _nop_(); 
			// _nop_(); 
	      }   
		 else 
		 {
	          TM1629D_SDA =0;//DIO_TM1620_CLR;
	        //   _nop_(); 
			//   _nop_(); 
       
         }   
	     //  _nop_(); 
		//  _nop_(); 
		 TM1629D_SCL = 1;//CLK_TM1620_SET; //上升沿操作      
      }   
 
}
