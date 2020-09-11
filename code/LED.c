#include "LED.h"

uint8_t pmlog ;
#define  segPM(dat)   (segNumber[dat]) + seg_h)
    

const unsigned char segNumber[]={
	
     
         seg_a+seg_b+seg_c+seg_d+seg_e+seg_f,        		// char "0"  0x00
         seg_b+seg_c,                                      // char "1"  0x01
         seg_a+seg_b+seg_d+seg_e+seg_g,              		// char "2"  0x02
         seg_a+seg_b+seg_c+seg_d+seg_g,              		// char "3"  0x03
         seg_b+seg_c+seg_f+seg_g+seg_h,                   		 // char "4"  0x04
         seg_a+seg_c+seg_d+seg_f+seg_g,              		// char "5"  0x05
         seg_a+seg_c+seg_d+seg_e+seg_f+seg_g,              // char "6"  0x06
         seg_a+seg_b+seg_c+seg_f,                    		// char "7"  0x07
         seg_a+seg_b+seg_c+seg_d+seg_e+seg_f+seg_g,  		// char "8"  0x08
         seg_a+seg_b+seg_c+seg_d+seg_f+seg_g,        		// char "9"  0x09
         seg_h,                                             // char "."  0x0A
         0                                                  // Dont't display 0x0B
       
};




 unsigned char GreeNumber[]={

    seg_g + seg_h,
	seg_i + seg_j +seg_k ,
	seg_i + seg_j +seg_k +seg_l,
    seg_a+seg_b+seg_c+seg_d+seg_e+seg_f +seg_g+ seg_h,
    seg_k + seg_l,
    seg_j + seg_k + seg_l,
    seg_a+seg_b+seg_c+seg_d+seg_e+seg_f
   

};

unsigned char BlueNumber[]={
	seg_h,
    seg_i + seg_j +seg_k ,
	seg_j +seg_k,
	seg_a+seg_b+seg_c+seg_d+seg_e+seg_f +seg_g+ seg_h,
	seg_a+seg_b+seg_c+seg_d+seg_e+seg_f ,
	seg_g + seg_h,
	seg_i

};





/******************************************************************************
 **
 ** Function Name:	void LED_GPIO_Init(void)
 ** Function : receive key input message 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
void LED_GPIO_Init(void)
{
    GPIO_SET_MUX_MODE(P24CFG,GPIO_MUX_GPIO);   //SDA = P24
	GPIO_ENABLE_OUTPUT(P2TRIS,GPIO_PIN_4); 
	//GPIO_ENABLE_RD(P2UP,GPIO_PIN_4) ;  
	P24=1;

    GPIO_SET_MUX_MODE(P25CFG,GPIO_MUX_GPIO);   // SCL= P25
	GPIO_ENABLE_OUTPUT(P2TRIS,GPIO_PIN_5); 
	//GPIO_ENABLE_RD(P2UP,GPIO_PIN_5) ;  
    P25=1;
	
   GPIO_SET_MUX_MODE(P26CFG,GPIO_MUX_GPIO);   // STB= P26    片选信号
	GPIO_ENABLE_OUTPUT(P2TRIS,GPIO_PIN_6); 
	//GPIO_ENABLE_RD(P2UP,GPIO_PIN_6) ;  
	P26=1;
  
    
}
/******************************************************************************
 **
 ** Function Name:	void LEDDisplay_TurnOff(void)
 ** Function : receive key input message 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
void LEDDisplay_TurnOff(void)
{
        
     
	STB_TM1629D =0 ;  
				Tm1629DSentData(ModeDisTM1629D); //写数据到显示寄存器
				STB_TM1629D =1; 
			
				STB_TM1629D=0;	 
				Tm1629DSentData(AddrFixed);//AddrFixed 写固定地址
				//写显示，固定定制模式
				STB_TM1629D=1; 
				
				STB_TM1629D=0;	 
				Tm1629DSentData(Addr0DH); //高字节  
				Tm1629DSentData(0x00); //COM7
				STB_TM1629D=1; 
				
				STB_TM1629D=0;	 
				Tm1629DSentData(Addr0FH); //高字节	
				Tm1629DSentData(0x00); //COM8
				STB_TM1629D=1; 
				/****************SEG9~SEG12**********************/
				 STB_TM1629D=0;   
				Tm1629DSentData(Addr01H);  //地址 01 COM1 高段
				//指向地址0E   
				Tm1629DSentData(0x00);
				STB_TM1629D=1; 
		 
				 STB_TM1629D=0;   
				Tm1629DSentData(Addr03H);  //地址 03 COM2 高段
				//指向地址0E   
				Tm1629DSentData(0x00);
				STB_TM1629D=1; 
		 
				 STB_TM1629D=0;   
				Tm1629DSentData(Addr05H);  //地址 05 COM3 高段
				//指向地址0E   
				Tm1629DSentData(0x00);
				STB_TM1629D=1; 
		 
		 
				 STB_TM1629D=0;   
				Tm1629DSentData(Addr07H);  //地址 07 COM4 高段
				//指向地址0E   
				Tm1629DSentData(0x00);
				STB_TM1629D=1; 
		 
				 STB_TM1629D=0;   
				Tm1629DSentData(Addr09H);  //地址 09 COM5 高段
				//指向地址0E   
				Tm1629DSentData(0x00);
				STB_TM1629D=1; 
		 
				 STB_TM1629D=0;   
				Tm1629DSentData(Addr0BH);  //地址 0B COM6 高段
				//指向地址0E   
				Tm1629DSentData(0x00);
				STB_TM1629D=1; 
		 
				
		 
				/***************低段显示SEG1~SEG8********************/
				
			   
			   STB_TM1629D=0;	
				Tm1629DSentData(Addr00H);
				 Tm1629DSentData(0x00); //指向地址00	 
				STB_TM1629D=1; 
				   
			   STB_TM1629D=0;	
				 Tm1629DSentData(Addr02H);
				 Tm1629DSentData(0x00); //指向地址02	 
			   STB_TM1629D=1; 
				   
			   STB_TM1629D=0;	
				Tm1629DSentData(Addr04H);
				Tm1629DSentData(0x00); //指向地址04
				STB_TM1629D=1; 
				   
			 
			   STB_TM1629D=0;	
			   Tm1629DSentData(Addr06H);
				Tm1629DSentData(0x00); //指向地址06
		 
				STB_TM1629D=0;	 
				//指向地址8 
				 Tm1629DSentData(Addr08H);
				 Tm1629DSentData(0x00); //指向地址08
				STB_TM1629D=1; 
		 
		 
				STB_TM1629D=0;	 
				Tm1629DSentData(Addr0AH);
				 Tm1629DSentData(0x00); //指向地址0A	 
				 STB_TM1629D=1; 
				 
				 STB_TM1629D=0;  
				Tm1629DSentData(Addr0CH);
				 Tm1629DSentData(0x00); //指向地址0C	 
				 STB_TM1629D=1; 
				 
				 STB_TM1629D=0;  
				Tm1629DSentData(Addr0EH);
				 Tm1629DSentData(0x00); //指向地址0E	 
				 STB_TM1629D=1; 
	
	
		 STB_TM1629D =0; 
		// Tm1629DSentData(CloseDisTM1629D|Set12_16TM1629D); //关显示，显示，设置脉冲宽带 12/16
		  Tm1629DSentData(OpenDisTM1629D|Set14_16TM1629D); //开显示，显示，设置脉冲宽带 14/16
		 STB_TM1629D =1;	  


}
/****************************************************************************************************
 * 	*
	*函数名称：void LEDDisplay_TimerTim(void)
	*函数功能：定时时间显示,按键设置定时时间
	*入口参数：NO
	*出口参数：NO
	*
*******************************************************************************************************/
void LEDDisplay_TimerTim(uint8_t disdat3,uint8_t disdat2,uint8_t disdat1)
{
        STB_TM1629D =0 ;  
        Tm1629DSentData(ModeDisTM1629D); //写数据到显示寄存器
	    STB_TM1629D =1; 
	
        STB_TM1629D=0;   
		Tm1629DSentData(AddrFixed);//AddrFixed 写固定地址
		//写显示，固定定制模式
		STB_TM1629D=1; 
		
        STB_TM1629D=0;   
		Tm1629DSentData(Addr00H);
		//指向地址0   
	    Tm1629DSentData(segNumber[disdat3]); //主显示3 位---百位
	    STB_TM1629D=1; 
		
        STB_TM1629D=0;   
		Tm1629DSentData(Addr02H);
		//指向地址2   
	    Tm1629DSentData(segNumber[disdat2]); //主显示2位---十位
	    STB_TM1629D=1; 
		

		

		//写第三位
         STB_TM1629D=0;   
		Tm1629DSentData(Addr04H);
		//指向地址4  
	
	       Tm1629DSentData(segNumber[disdat1]); //主显示2位---十位
         STB_TM1629D=1; 


	
       STB_TM1629D =0; 
       Tm1629DSentData(OpenDisTM1629D|Set14_16TM1629D); //开显示，显示，设置脉冲宽带 14/16
       STB_TM1629D =1; 	 
	
}


/******************************************************************************
 **
 ** Function Name:	void KEY_FUNCTION(void)
 ** Function : receive key input message 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
void LEDDisplay_SleepLamp(void)
{
              STB_TM1629D =0 ;  
			  Tm1629DSentData(ModeDisTM1629D); //写数据到显示寄存器
			  STB_TM1629D =1; 
		  
			  STB_TM1629D=0;   
			  Tm1629DSentData(AddrFixed);//AddrFixed 写固定地址
			  //写显示，固定定制模式
			  STB_TM1629D=1; 

		      /*********** DISPLAY Blue 1i 2i 3i 4i 5i 低字节 **************/
			    // 5i ---5g,5h,5i,5j,5k    6i----6a ....6l
		         STB_TM1629D=0;	
				 Tm1629DSentData(Addr00H);    //COM1
				 Tm1629DSentData(BlueNumber[0]); //指向地址00 ---GRID1  
			     STB_TM1629D=1; 

				 STB_TM1629D=0;	
				 Tm1629DSentData(Addr01H);    //COM1  ---高字节
				 Tm1629DSentData(BlueNumber[1]); //指向地址01 ---GRID1 
			     STB_TM1629D=1; 

		         STB_TM1629D=0;	 
			     Tm1629DSentData(Addr02H); 
				 Tm1629DSentData(BlueNumber[0]); //指向地址02	 ---COM2
			     STB_TM1629D=1; 

				 STB_TM1629D=0;	 
			     Tm1629DSentData(Addr03H); 
				 Tm1629DSentData(BlueNumber[1]); //指向地址02---COM2 高字节
			     STB_TM1629D=1; 

                 STB_TM1629D=0;	 
			     Tm1629DSentData(Addr05H); 
				 Tm1629DSentData(BlueNumber[2]); //指向地址03---COM3 高字节
			     STB_TM1629D=1; 

                 STB_TM1629D=0;	 
			     Tm1629DSentData(Addr06H); 
				 Tm1629DSentData(BlueNumber[3]); //指向地址06	 ---COM4
			     STB_TM1629D=1; 

				 STB_TM1629D=0;	 
			     Tm1629DSentData(Addr07H); 
				 Tm1629DSentData(BlueNumber[1]); //指向地址07---COM4
			     STB_TM1629D=1; 

				 STB_TM1629D=0;	 
			     Tm1629DSentData(Addr08H); 
				 Tm1629DSentData(BlueNumber[4]); //指向地址08---COM5
			     STB_TM1629D=1; 


				/***************end*********************/
				/************don't display*****************/    
			     STB_TM1629D=0;	
				Tm1629DSentData(Addr00H);
				 Tm1629DSentData(~segNumber[8]); //指向地址00	 
			    STB_TM1629D=1; 
				   
			   STB_TM1629D=0;	
				 Tm1629DSentData(Addr02H);
				 Tm1629DSentData(~segNumber[8]); //指向地址02	 
			   STB_TM1629D=1; 
				   
			   STB_TM1629D=0;	
				Tm1629DSentData(Addr04H);
				Tm1629DSentData(~BlueNumber[3]); //指向地址03
			    STB_TM1629D=1; 

					   
			    STB_TM1629D=0;	
				Tm1629DSentData(Addr05H);
				Tm1629DSentData(~BlueNumber[6]); //指向地址04---COM3
			    STB_TM1629D=1; 

				STB_TM1629D=0;	
				Tm1629DSentData(Addr08H);
				Tm1629DSentData(~BlueNumber[5]); //指向地址08---COM5
			    STB_TM1629D=1; 
				
				   
		         STB_TM1629D=0;	
			   Tm1629DSentData(Addr09H);
				Tm1629DSentData(~BlueNumber[1]); //指向地址09-----COM5
				 STB_TM1629D=1; 


				STB_TM1629D=0;	 
				Tm1629DSentData(Addr0AH);
				 Tm1629DSentData(0x00); //指向地址08
			    STB_TM1629D=1; 


				STB_TM1629D=0;	 
			    Tm1629DSentData(Addr0BH);
				 Tm1629DSentData(0x00); //指向地址0A	 
			     STB_TM1629D=1; 
		         
		         STB_TM1629D=0;	 
			    Tm1629DSentData(Addr0CH);
				 Tm1629DSentData(0x00); //指向地址0C	 
			     STB_TM1629D=1; 
		         
		         STB_TM1629D=0;	 
			    Tm1629DSentData(Addr0DH);
				 Tm1629DSentData(0x00); //指向地址0E	 
			     STB_TM1629D=1; 

				    STB_TM1629D=0;	 
			    Tm1629DSentData(Addr0EH);
				 Tm1629DSentData(0x00); //指向地址0E	 
			     STB_TM1629D=1; 

				    STB_TM1629D=0;	 
			    Tm1629DSentData(Addr0FH);
				 Tm1629DSentData(0x00); //指向地址0E	 
			     STB_TM1629D=1; 

				
				
	   STB_TM1629D =0; 
       Tm1629DSentData(OpenDisTM1629D|Set14_16TM1629D); //开显示，显示，设置脉冲宽带 12/16
       STB_TM1629D =1; 	    

}

/****************************************************************************************************
 * 	*
	*函数名称：void LEDDisplay_RedColorRing(void);
	*函数功能：LED数码管，光圈显示红色
	*入口参数：NO
	*出口参数：NO
	*
*******************************************************************************************************/
void LEDDisplay_RedColorRing(void)
{
     STB_TM1629D =0 ;  
        Tm1629DSentData(ModeDisTM1629D); //写数据到显示寄存器
	    STB_TM1629D =1; 
	
        STB_TM1629D=0;   
		Tm1629DSentData(AddrFixed);//AddrFixed 写固定地址
		//写显示，固定定制模式
		STB_TM1629D=1; 
		
        STB_TM1629D=0;   
		Tm1629DSentData(Addr0DH); //高字节  
	    Tm1629DSentData(0x0E); //COM7
	    STB_TM1629D=1; 
		
        STB_TM1629D=0;   
		Tm1629DSentData(Addr0FH); //高字节   
	    Tm1629DSentData(0x0E); //COM8
	    STB_TM1629D=1; 
        /****************SEG9~SEG12**********************/
		 STB_TM1629D=0;   
		Tm1629DSentData(Addr01H);  //地址 01 COM1 高段
		//指向地址0E   
	    Tm1629DSentData(0x00);
	    STB_TM1629D=1; 

		 STB_TM1629D=0;   
		Tm1629DSentData(Addr03H);  //地址 03 COM2 高段
		//指向地址0E   
	    Tm1629DSentData(0x00);
	    STB_TM1629D=1; 

		 STB_TM1629D=0;   
		Tm1629DSentData(Addr05H);  //地址 05 COM3 高段
		//指向地址0E   
	    Tm1629DSentData(0x00);
	    STB_TM1629D=1; 


		 STB_TM1629D=0;   
		Tm1629DSentData(Addr07H);  //地址 07 COM4 高段
		//指向地址0E   
	    Tm1629DSentData(0x00);
	    STB_TM1629D=1; 

		 STB_TM1629D=0;   
		Tm1629DSentData(Addr09H);  //地址 09 COM5 高段
		//指向地址0E   
	    Tm1629DSentData(0x00);
	    STB_TM1629D=1; 

		 STB_TM1629D=0;   
		Tm1629DSentData(Addr0BH);  //地址 0B COM6 高段
		//指向地址0E   
	    Tm1629DSentData(0x00);
	    STB_TM1629D=1; 

		

		/***************低段显示SEG1~SEG8********************/
		
	   
	   STB_TM1629D=0;	
		Tm1629DSentData(Addr00H);
		 Tm1629DSentData(0x00); //指向地址00	 
	    STB_TM1629D=1; 
		   
	   STB_TM1629D=0;	
		 Tm1629DSentData(Addr02H);
		 Tm1629DSentData(0x00); //指向地址02	 
	   STB_TM1629D=1; 
		   
	   STB_TM1629D=0;	
		Tm1629DSentData(Addr04H);
		Tm1629DSentData(0x00); //指向地址04
	    STB_TM1629D=1; 
		   
     
	   STB_TM1629D=0;	
	   Tm1629DSentData(Addr06H);
		Tm1629DSentData(0x00); //指向地址06
		 STB_TM1629D=1; 

		STB_TM1629D=0;	 
		
		 Tm1629DSentData(Addr08H);
		 Tm1629DSentData(0x00); //指向地址08
	    STB_TM1629D=1; 


		STB_TM1629D=0;	 
	    Tm1629DSentData(Addr0AH);
		 Tm1629DSentData(0x00); //指向地址0A	 
	     STB_TM1629D=1; 
         
         STB_TM1629D=0;	 
	    Tm1629DSentData(Addr0CH);
		 Tm1629DSentData(0xFE); //指向地址0C	 
	     STB_TM1629D=1; 
         
         STB_TM1629D=0;	 
	    Tm1629DSentData(Addr0EH);
		 Tm1629DSentData(0xFE); //指向地址0E	 
	     STB_TM1629D=1; 

		
	   STB_TM1629D =0; 
       Tm1629DSentData(OpenDisTM1629D|Set14_16TM1629D); //开显示，显示，设置脉冲宽带 12/16
       STB_TM1629D =1; 	 
   
    
}
/****************************************************************************************************
 * 	*
	*函数名称：void LEDDisplay_GreenColorRing(void);
	*函数功能：LED数码管，光圈显示绿色
	*入口参数：NO
	*出口参数：NO
	*
*******************************************************************************************************/
void LEDDisplay_GreenColorRing(void)
{
        STB_TM1629D =0 ;  
			  Tm1629DSentData(ModeDisTM1629D); //写数据到显示寄存器
			  STB_TM1629D =1; 
		  
			  STB_TM1629D=0;   
			  Tm1629DSentData(AddrFixed);//AddrFixed 写固定地址
			  //写显示，固定定制模式
			  STB_TM1629D=1; 

		        /*********** DISPLAY Green 5i 6i**************/
			    // 5i ---5g,5h,5i,5j,5k    6i----6a ....6l
		         STB_TM1629D=0;	
				 Tm1629DSentData(Addr08H);    //偶数地址段 SEG1~SEG8
				 Tm1629DSentData(GreeNumber[0]); //指向地址08 ---GRID5  
			     STB_TM1629D=1; 

		         STB_TM1629D=0;	 
			     Tm1629DSentData(Addr0AH); 
				 Tm1629DSentData(GreeNumber[3]); //指向地址0A	 ---GRID6
			     STB_TM1629D=1; 
		         /*******High bit*************/
				 STB_TM1629D=0;   
				Tm1629DSentData(Addr09H);  //地址 09 COM5 高段 
			    Tm1629DSentData(GreeNumber[1]);
			    STB_TM1629D=1; 

				 STB_TM1629D=0;   
				Tm1629DSentData(Addr0BH);  //地址 0B COM6 高段
			    Tm1629DSentData(GreeNumber[2]);
			    STB_TM1629D=1; 
				/***********END*****************/


			  
			
			  /****************SEG9~SEG12**********************/
			   STB_TM1629D=0;	
			  Tm1629DSentData(Addr01H);  //地址 01 COM1 高段
			  //指向地址0E	 
			  Tm1629DSentData(0x00);
			  STB_TM1629D=1; 
	   
			   STB_TM1629D=0;	
			  Tm1629DSentData(Addr03H);  //地址 03 COM2 高段
			  //指向地址0E	 
			  Tm1629DSentData(0x00);
			  STB_TM1629D=1; 
			 
	   
			   STB_TM1629D=0;	
			  Tm1629DSentData(Addr05H);  //地址 05 COM3 高段, 显示ug/M^3
			  //指向地址0E	 
			  Tm1629DSentData(0x01);
			  STB_TM1629D=1; 
	   
	   
			   STB_TM1629D=0;	
			  Tm1629DSentData(Addr07H);  //地址 07 COM4 高段
			  //指向地址0E	 
			  Tm1629DSentData(0x00);
			  STB_TM1629D=1; 
	   
			    
			  STB_TM1629D=0;   
			  Tm1629DSentData(Addr0DH); //高字节  
			  Tm1629DSentData(0x00); //COM7
			  STB_TM1629D=1; 
			  
			  STB_TM1629D=0;   
			  Tm1629DSentData(Addr0FH); //高字节   
			  Tm1629DSentData(0x00); //COM8
			  STB_TM1629D=1; 
	   
			  
	 
			/***************低段显示SEG1~SEG8********************/
			  
			#if 0 
			 STB_TM1629D=0;   
			  Tm1629DSentData(Addr00H);
			   Tm1629DSentData(0x00); //指向地址00	   
			  STB_TM1629D=1; 
				 
			 STB_TM1629D=0;   
			   Tm1629DSentData(Addr02H);
			   Tm1629DSentData(0x00); //指向地址02	   
			 STB_TM1629D=1; 
				 
			 STB_TM1629D=0;   
			  Tm1629DSentData(Addr04H);
			  Tm1629DSentData(0x00); //指向地址04
			  STB_TM1629D=1; 
			#endif 	 
            

			
			 STB_TM1629D=0;   
			 Tm1629DSentData(Addr06H);
			  Tm1629DSentData(segNumber[0x0B]); //指向地址06
	   		  STB_TM1629D=1; 
	   
	   
			   
			   STB_TM1629D=0;  
			  Tm1629DSentData(Addr0CH);
			   Tm1629DSentData(segNumber[0x0B]); //指向地址0C	   
			   STB_TM1629D=1; 
			   
			   STB_TM1629D=0;  
			  Tm1629DSentData(Addr0EH);
			   Tm1629DSentData(segNumber[0x0B]); //指向地址0E	   
			   STB_TM1629D=1; 


	   STB_TM1629D =0; 
      // Tm1629DSentData(CloseDisTM1629D|Set14_16TM1629D); //关显示，显示，设置脉冲宽带 12/16
      Tm1629DSentData(OpenDisTM1629D|Set14_16TM1629D); //开显示，显示，设置脉冲宽带 12/16
       STB_TM1629D =1; 	    
   

}

/******************************************************************************
 * 	*
	*函数名称：void LED_DispPMLogo(void)
	*函数功能：display PM logo "PM2.5" "ug/m^3"
	*入口参数：NO
	*出口参数：NO
	*
********************************************************************************/
void LED_DispPMLogo(void)
{

               STB_TM1629D =0 ;	
			   Tm1629DSentData(ModeDisTM1629D); //写数据到显示寄存器
			   STB_TM1629D =1; 
		   
			   STB_TM1629D=0;	
			   Tm1629DSentData(AddrFixed);//AddrFixed 写固定地址
			   //写显示，固定定制模式
			   STB_TM1629D=1; 

	

			  STB_TM1629D=0;   
			  Tm1629DSentData(Addr05H);
			  Tm1629DSentData(0x01); //指向地址05---位选 ug/m^3
			  STB_TM1629D=1; 

					
			   STB_TM1629D =0; 
		        Tm1629DSentData(OpenDisTM1629D|Set14_16TM1629D); //开显示，显示，设置脉冲宽带 12/16
		       STB_TM1629D =1; 	    



}

/******************************************************************************
 * 	*
	*函数名称：void LED_DispPMLogo(void)
	*函数功能：display PM logo "PM2.5" "ug/m^3"
	*入口参数：NO
	*出口参数：NO
	*
********************************************************************************/
void LED_DispHlogo(void)
{
    STB_TM1629D =0 ;  
        Tm1629DSentData(ModeDisTM1629D); //写数据到显示寄存器
	    STB_TM1629D =1; 
	
        STB_TM1629D=0;   
		Tm1629DSentData(AddrFixed);//AddrFixed 写固定地址
		//写显示，固定定制模式
		STB_TM1629D=1; 
		
        STB_TM1629D=0;   
		Tm1629DSentData(Addr00H);
		//指向地址0   
	    Tm1629DSentData(char_H); //主显示3 位---百位
	    STB_TM1629D=1; 
		
        STB_TM1629D=0;   
		Tm1629DSentData(Addr02H);
		//指向地址2   
	    Tm1629DSentData(char_H); //主显示2位---十位
	    STB_TM1629D=1; 
		
        //写第三位
         STB_TM1629D=0;   
		Tm1629DSentData(Addr04H);
		//指向地址4   
	    Tm1629DSentData(char_H); //主显示1位----个位
         STB_TM1629D=1; 
	
       STB_TM1629D =0; 
       Tm1629DSentData(OpenDisTM1629D|Set14_16TM1629D); //开显示，显示，设置脉冲宽带 14/16
       STB_TM1629D =1; 	 

}
/******************************************************************************
 * 	*
	*函数名称：void LED_DispThreeRadin(void)
	*函数功能：display tree radin
	*入口参数：NO
	*出口参数：NO
	*
********************************************************************************/
void LED_DispThreeRadin(void) //显示三个弧度
{
	          STB_TM1629D =0 ;  
			  Tm1629DSentData(ModeDisTM1629D); //写数据到显示寄存器
			  STB_TM1629D =1; 
		  
			  STB_TM1629D=0;   
			  Tm1629DSentData(AddrFixed);//AddrFixed 写固定地址
			  //写显示，固定定制模式
			  STB_TM1629D=1; 

		        /***********three radin DISPLAY Green turn off 6K 6L **************/
			    // 5i ---5g,5h,5i,5j,5k    6i----6a ....6l
		         STB_TM1629D=0;	
				 Tm1629DSentData(Addr08H);    //偶数地址段 SEG1~SEG8
				 Tm1629DSentData(GreeNumber[0]); //指向地址08 ---GRID5  
			     STB_TM1629D=1; 

				 STB_TM1629D=0;   
				Tm1629DSentData(Addr09H);  //地址 09 COM5 高段 
			    Tm1629DSentData(GreeNumber[1]);
				STB_TM1629D=1; 

		         /*******GRID6*************/
				
			     STB_TM1629D=0;	 
			     Tm1629DSentData(Addr0AH); 
				 Tm1629DSentData(GreeNumber[6]); //指向地址0A	 ---GRID6
			     STB_TM1629D=1; 

				 STB_TM1629D=0;   
				Tm1629DSentData(Addr0BH);  //地址 0B COM6 高段
			    Tm1629DSentData(GreeNumber[4]);
			    STB_TM1629D=1; 
				/***********END*****************/
				 /****************SEG9~SEG12**********************/
			   STB_TM1629D=0;	
			  Tm1629DSentData(Addr01H);  //地址 01 COM1 高段
			  //指向地址0E	 
			  Tm1629DSentData(0x00);
			  STB_TM1629D=1; 
	   
			   STB_TM1629D=0;	
			  Tm1629DSentData(Addr03H);  //地址 03 COM2 高段
			  //指向地址0E	 
			  Tm1629DSentData(0x00);
			  STB_TM1629D=1; 
	   
			   STB_TM1629D=0;	
			  Tm1629DSentData(Addr05H);  //地址 05 COM3 高段, 显示ug/M^3
			  //指向地址0E	 
			  Tm1629DSentData(0x00);
			  STB_TM1629D=1; 
	   
	   
			   STB_TM1629D=0;	
			  Tm1629DSentData(Addr07H);  //地址 07 COM4 高段
			  //指向地址0E	 
			  Tm1629DSentData(0x00);
			  STB_TM1629D=1; 
	   
			    
			  STB_TM1629D=0;   
			  Tm1629DSentData(Addr0DH); //高字节  
			  Tm1629DSentData(0x00); //COM7
			  STB_TM1629D=1; 
			  
			  STB_TM1629D=0;   
			  Tm1629DSentData(Addr0FH); //高字节   
			  Tm1629DSentData(0x00); //COM8
			  STB_TM1629D=1; 
	   
			  
	 
			/***************低段显示SEG1~SEG8********************/
			  
	          STB_TM1629D=0;   
			 Tm1629DSentData(Addr06H);
			  Tm1629DSentData(segNumber[0x0B]); //指向地址06
	   		STB_TM1629D=1; 
	   
	   
			   
			   STB_TM1629D=0;  
			  Tm1629DSentData(Addr0CH);
			   Tm1629DSentData(segNumber[0x0B]); //指向地址0C	   
			   STB_TM1629D=1; 
			   
			   STB_TM1629D=0;  
			  Tm1629DSentData(Addr0EH);
			   Tm1629DSentData(segNumber[0x0B]); //指向地址0E	   
			   STB_TM1629D=1; 


	   STB_TM1629D =0; 
      // Tm1629DSentData(CloseDisTM1629D|Set14_16TM1629D); //关显示，显示，设置脉冲宽带 12/16
      Tm1629DSentData(OpenDisTM1629D|Set14_16TM1629D); //开显示，显示，设置脉冲宽带 12/16
       STB_TM1629D =1; 	    
   

}
/******************************************************************************
 * 	*
	*函数名称：void LED_DispTwoRadin(void)
	*函数功能：display      two radin
	*入口参数：NO
	*出口参数：NO
	*
********************************************************************************/
void LED_DispTwoRadin(void)
{
               STB_TM1629D =0 ;  
			  Tm1629DSentData(ModeDisTM1629D); //写数据到显示寄存器
			  STB_TM1629D =1; 
		  
			  STB_TM1629D=0;   
			  Tm1629DSentData(AddrFixed);//AddrFixed 写固定地址
			  //写显示，固定定制模式
			  STB_TM1629D=1; 

		        /***********three radin DISPLAY Green turn off 6K 6L **************/
			    
			     
		        /***********three radin DISPLAY Green turn off 6K 6L **************/
			    // 5i ---5g,5h,5i,5j,5k    6i----6a ....6l
		         STB_TM1629D=0;	
				 Tm1629DSentData(Addr08H);    //偶数地址段 SEG1~SEG8
				 Tm1629DSentData(0x00); //指向地址08 ---GRID5  
			     STB_TM1629D=1; 

				 STB_TM1629D=0;   
				Tm1629DSentData(Addr09H);  //地址 09 COM5 高段 
			    Tm1629DSentData(0x00);
				STB_TM1629D=1; 

		         /*******GRID6*************/
				
			     STB_TM1629D=0;	 
			     Tm1629DSentData(Addr0AH); 
				 Tm1629DSentData(GreeNumber[6]); //指向地址0A	 ---GRID6
			     STB_TM1629D=1; 

				 STB_TM1629D=0;   
				Tm1629DSentData(Addr0BH);  //地址 0B COM6 高段
			    Tm1629DSentData(GreeNumber[4]);
			    STB_TM1629D=1; 
				/***********END*****************/
				/****************SEG9~SEG12**********************/
			   STB_TM1629D=0;	
			  Tm1629DSentData(Addr01H);  //地址 01 COM1 高段
			  //指向地址0E	 
			  Tm1629DSentData(0x00);
			  STB_TM1629D=1; 
	   
			   STB_TM1629D=0;	
			  Tm1629DSentData(Addr03H);  //地址 03 COM2 高段
			  //指向地址0E	 
			  Tm1629DSentData(0x00);
			  STB_TM1629D=1; 
	   
			   STB_TM1629D=0;	
			  Tm1629DSentData(Addr05H);  //地址 05 COM3 高段, 显示ug/M^3
			  //指向地址0E	 
			  Tm1629DSentData(0x00);
			  STB_TM1629D=1; 
	   
	   
			   STB_TM1629D=0;	
			  Tm1629DSentData(Addr07H);  //地址 07 COM4 高段
			  //指向地址0E	 
			  Tm1629DSentData(0x00);
			  STB_TM1629D=1; 
	   
			    
			  STB_TM1629D=0;   
			  Tm1629DSentData(Addr0DH); //高字节  
			  Tm1629DSentData(0x00); //COM7
			  STB_TM1629D=1; 
			  
			  STB_TM1629D=0;   
			  Tm1629DSentData(Addr0FH); //高字节   
			  Tm1629DSentData(0x00); //COM8
			  STB_TM1629D=1; 
	   
		     /********低段显示SEG1~SEG8*************/
			  
	          STB_TM1629D=0;   
			 Tm1629DSentData(Addr06H);
			  Tm1629DSentData(0x00); //指向地址06
	   		  STB_TM1629D=1; 
	   
	   
			   STB_TM1629D=0;  
			  Tm1629DSentData(Addr0CH);
			   Tm1629DSentData(0x00); //指向地址0C	   
			   STB_TM1629D=1; 
			   
			   STB_TM1629D=0;  
			  Tm1629DSentData(Addr0EH);
			   Tm1629DSentData(0x00); //指向地址0E	   
			   STB_TM1629D=1; 


	   STB_TM1629D =0; 
      // Tm1629DSentData(CloseDisTM1629D|Set14_16TM1629D); //关显示，显示，设置脉冲宽带 12/16
      Tm1629DSentData(OpenDisTM1629D|Set14_16TM1629D); //开显示，显示，设置脉冲宽带 12/16
       STB_TM1629D =1; 	    

}
/******************************************************************************
 * 	*
	*函数名称：void LED_DispOneRadin(void)
	*函数功能：display      on radin  一个弧度亮
	*入口参数：NO
	*出口参数：NO
	*
********************************************************************************/
void LED_DispOneRadin(void)
{

		      STB_TM1629D =0 ;  
			  Tm1629DSentData(ModeDisTM1629D); //写数据到显示寄存器
			  STB_TM1629D =1; 
		  
			  STB_TM1629D=0;   
			  Tm1629DSentData(AddrFixed);//AddrFixed 写固定地址
			  //写显示，固定定制模式
			  STB_TM1629D=1; 

		        /***********three radin DISPLAY Green turn off 6K 6L **************/
			    
			     
		        /***********three radin DISPLAY Green turn off 6K 6L **************/
			    // 5i ---5g,5h,5i,5j,5k    6i----6a ....6l
		         STB_TM1629D=0;	
				 Tm1629DSentData(Addr08H);    //偶数地址段 SEG1~SEG8
				 Tm1629DSentData(0x00); //指向地址08 ---GRID5  
			     STB_TM1629D=1; 

				 STB_TM1629D=0;   
				Tm1629DSentData(Addr09H);  //地址 09 COM5 高段 
			    Tm1629DSentData(0x00);
				STB_TM1629D=1; 

		         /*******GRID6*************/
				
			     STB_TM1629D=0;	 
			     Tm1629DSentData(Addr0AH); 
				 Tm1629DSentData(0x00); //指向地址0A	 ---GRID6
			     STB_TM1629D=1; 

				 STB_TM1629D=0;   
				Tm1629DSentData(Addr0BH);  //地址 0B COM6 高段
			    Tm1629DSentData(GreeNumber[4]);
			    STB_TM1629D=1; 
				/***********END*****************/
				/****************SEG9~SEG12**********************/
			   STB_TM1629D=0;	
			  Tm1629DSentData(Addr01H);  //地址 01 COM1 高段
			  //指向地址0E	 
			  Tm1629DSentData(0x00);
			  STB_TM1629D=1; 
	   
			   STB_TM1629D=0;	
			  Tm1629DSentData(Addr03H);  //地址 03 COM2 高段
			  //指向地址0E	 
			  Tm1629DSentData(0x00);
			  STB_TM1629D=1; 
	   
			   STB_TM1629D=0;	
			  Tm1629DSentData(Addr05H);  //地址 05 COM3 高段, 显示ug/M^3
			  //指向地址0E	 
			  Tm1629DSentData(0x00);
			  STB_TM1629D=1; 
	   
	   
			   STB_TM1629D=0;	
			  Tm1629DSentData(Addr07H);  //地址 07 COM4 高段
			  //指向地址0E	 
			  Tm1629DSentData(0x00);
			  STB_TM1629D=1; 
	   
			    
			  STB_TM1629D=0;   
			  Tm1629DSentData(Addr0DH); //高字节  
			  Tm1629DSentData(0x00); //COM7
			  STB_TM1629D=1; 
			  
			  STB_TM1629D=0;   
			  Tm1629DSentData(Addr0FH); //高字节   
			  Tm1629DSentData(0x00); //COM8
			  STB_TM1629D=1; 
	   
		     /********低段显示SEG1~SEG8*************/
			  
	          STB_TM1629D=0;   
			 Tm1629DSentData(Addr06H);
			  Tm1629DSentData(0x00); //指向地址06
	   		  STB_TM1629D=1; 
	   
	   
			   STB_TM1629D=0;  
			  Tm1629DSentData(Addr0CH);
			   Tm1629DSentData(0x00); //指向地址0C	   
			   STB_TM1629D=1; 
			   
			   STB_TM1629D=0;  
			  Tm1629DSentData(Addr0EH);
			   Tm1629DSentData(0x00); //指向地址0E	   
			   STB_TM1629D=1; 


	   STB_TM1629D =0; 
      // Tm1629DSentData(CloseDisTM1629D|Set14_16TM1629D); //关显示，显示，设置脉冲宽带 12/16
      Tm1629DSentData(OpenDisTM1629D|Set14_16TM1629D); //开显示，显示，设置脉冲宽带 12/16
       STB_TM1629D =1; 	    


}

