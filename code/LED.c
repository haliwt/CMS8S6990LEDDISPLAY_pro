#include "LED.h"

const uint8_t seg[]={

			0x3F,	// 0		
			0x06,	// 1		
			0x5B,	// 2		
			0x4F,	// 3		
			0x66,	// 4		
			0x6D,	// 5		
			0x7D,	// 6		
			0x07,	// 7		
			0x7F,	// 8		
			0x6F	// 9

};

/******************************************************************************
 **
 ** Function Name:	void KEY_FUNCTION(void)
 ** Function : receive key input message 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
void LEDDisplay_Function(void)
{



}
/**********************************************************
 * 	*
	*函数名称：void LEDDisplay_TimerTim(void)
	*函数功能：定时时间显示,按键设置定时时间
	*入口参数：NO
	*出口参数：NO
	*
**********************************************************/
void LEDDisplay_TimerTim(void)
{
	 //定时显示，3位7段
	 static uint8_t minhour=0;
    if(Telecom->showtimes <=60 && Telecom->getTimerHour < 1){//显示分钟时间
        if(Telecom->showtimes ==60 && Telecom->TimerEvent ==0){  //设置定时时间，按键输入定时时间值
			Telecom->getTimerHour++;
			Telecom->showtimes=0;
		}
		if(Telecom->TimerEvent == 1){ //显示定时时间，每次减一分钟 ，定时事件=1，定时开始
			Telecom->showtimes  = Telecom->showtimes - getMinute;
			if(Telecom->showtimes <=0) {
				minhour ++;    				//分钟时间减完了，---再减小时时间参数
				Telecom->showtimes=0;
				getMinute =0;
			}
 
		}

       //	DispData[2] = seg[Telecom->showtimes %10];// LED个位
        TM1650_write_byte(TM1650_COM3_ADDR,&seg[Telecom->showtimes %10]); //写入个位 
       //	DispData[1] = seg[Telecom->showtimes /10];// LED十位
        TM1650_write_byte(TM1650_COM2_ADDR , &seg[Telecom->showtimes /10])	;
       //	DispData[0] = seg[0];         //小时，个位
        TM1650_write_byte(TM1650_COM1_ADDR , &seg[0]);

    }
    else if(Telecom->getTimerHour >=1){ //显示小时时间，分钟时间
        if(Telecom->showtimes ==60 && Telecom->TimerEvent==0){
			Telecom->getTimerHour++;
			Telecom->showtimes=0;
		}
		if(Telecom->TimerEvent == 1){ //定时事件开始
			if(Telecom->getTimerHour !=0){ //定时时间，大于一个小时
				Telecom->showtimes  = Telecom->showtimes - getMinute;
				if(Telecom->showtimes <=0) {
					minhour ++;
					Telecom->showtimes=60;
				}
				Telecom->getTimerHour  = Telecom->getTimerHour - minhour; //减小时时间
			}
		}
        
		//DispData[2] = seg[Telecom->showtimes %10];		//LED 显示个位  29分钟----‘9’
        TM1650_write_byte(TM1650_COM3_ADDR, &seg[Telecom->showtimes %10]); //写入个位 
        //DispData[1] = seg[Telecom->showtimes / 10];		//LED 显示十位 分钟 29分--‘2’
        TM1650_write_byte(TM1650_COM2_ADDR , &seg[Telecom->showtimes /10])	;
        //DispData[0] = seg[Telecom->getTimerHour / 10]; 	//---显示最高位时间，定时最大时间8小时
        TM1650_write_byte(TM1650_COM1_ADDR , &seg[Telecom->getTimerHour / 10]);
        if(Telecom->getTimerHour >=8)Telecom->getTimerHour =0;  //最大定时时间是 8小时
    }

   

}
