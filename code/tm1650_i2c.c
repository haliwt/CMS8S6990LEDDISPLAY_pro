/****************************************************************************/
/*	include files
*****************************************************************************/
#include "tm1650_i2c.h"
#include "LED.h"


const unsigned char segNumber[]={
         seg_a+seg_b+seg_c+seg_d+seg_e+seg_f,        // char "0"  0x00
         seg_b+seg_c,                                // char "1"  0x01
         seg_a+seg_b+seg_d+seg_e+seg_g,              // char "2"  0x02
         seg_a+seg_b+seg_c+seg_d+seg_g,              // char "3"  0x03
         seg_b+seg_c+seg_f+seg_g,                    // char "4"  0x04
         seg_a+seg_c+seg_d+seg_f+seg_g,              // char "5"  0x05
         seg_a+seg_c+seg_d+seg_e+seg_f+seg_g,        // char "6"  0x06
         seg_a+seg_b+seg_c+seg_f,                    // char "7"  0x07
         seg_a+seg_b+seg_c+seg_d+seg_e+seg_f+seg_g,  // char "8"  0x08
         seg_a+seg_b+seg_c+seg_d+seg_f+seg_g,        // char "9"  0x09
         seg_h,                                      // char "."  0x0A
         0                                           // Dont't display
         
};



volatile uint8_t DispData[3];

static void TM1650_WriteAddr(uint8_t addr,uint8_t mdata);
static void I2CWrByte(uint8_t oneByte) ;//写一个字节高位在前，低位在后
/*****************************************************************************
 ** \brief	I2C_SendMasterCmd
 **			发送主控命令
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/

/******************************************************************************
 ** 
 ** Function Name: void IIC_Init_TM1650(void)
 ** Function:          	
 ** Input Ref:
 ** Return Ref: 
 **  
 ******************************************************************************/
void IIC_Init_TM1650(void)
{
    
	GPIO_SET_MUX_MODE(P03CFG, GPIO_MUX_GPIO);		//I2C SCL 
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_3);			//Output
		

	GPIO_SET_MUX_MODE(P04CFG, GPIO_MUX_GPIO);		//I2C SDA 
	GPIO_ENABLE_INPUT(P0TRIS, GPIO_PIN_4);			//Input

	SCL =1;
	
	
}
/******************************************************************************
 ** 
 ** Function Name: void IIC_Start_TM1650(void)
 ** Function:          	
 ** Input Ref:
 ** Return Ref: 
 **  
 ******************************************************************************/
void IIC_Start_TM1650(void)
{
	
	 // SDA 1->0 while SCL High
  	//SCL高电平期间，SDA出现一个下降沿表示起始信号
  	SET_SDA_OUT_TM1650();
    SDA = 1;    	//数据线先保持为高，起始信号要该口的下降沿 
	  _nop_(); ;
    SCL = 1;        //时钟线保持为高            
      _nop_(); ;//有一个大概5us的延时具体以器件而定    
      //_nop_(); ;
     // _nop_(); ;
     // _nop_(); ;        
     SDA = 0;        //数据线拉低出现下降沿           
      _nop_(); ;
     // _nop_(); ;
      //_nop_(); ;      //延时 一小会，保证可靠的下降沿
      //_nop_(); ;             
    SCL = 0;        //拉低时钟线，保证接下来数据线允许改变   
        
}

/******************************************************************************
 ** 
 ** Function Name: void I2C_Stop_TM1650(void)
 ** Function:          	
 ** Input Ref:
 ** Return Ref: 
 **  
 ******************************************************************************/
void IIC_Stop_TM1650(void)
{

	// SDA 0->1 while SCL High
    //SCL高电平期间，SDA产生一个上升沿 表示停止
  	SET_SDA_OUT_TM1650();
	SCL= 0;
	  _nop_(); 
      _nop_(); 
     // _nop_(); 
     // _nop_(); 
	SDA = 0;		//保证数据线为低电平
	//delay_us(2);
    SCL= 1;		//先保证时钟线为高电平
    //delay_us(1);    //延时 以得到一个可靠的电平信号            
    SDA = 1;        //数据线出现上升沿           
   // delay_us(2);    //延时 保证一个可靠的高电平      
}
/******************************************************************************
 ** 
 ** Function Name: void IIC_Ack_TM1650(void)
 ** Function:          	
 ** Input Ref:
 ** Return Ref: 
 **  
 ******************************************************************************/
void IIC_Ack_TM1650(void)
{
    //数据线一直保持为低电平，时钟线出现上升沿即为应答
 
	SET_SDA_OUT_TM1650();
	//delay_us(1);
    SDA = 0;
   // delay_us(1);
    SCL= 0;
   // delay_us(2);
	SCL = 1;
	//delay_us(2);
    //应答完成后 将时钟线拉低 允许数据修改
    SCL = 0;
}
/******************************************************************************
 ** 
 ** Function Name: void IIC_NAck_TM1650(void)
 ** Function:          	
 ** Input Ref:
 ** Return Ref: 
 **  
 ******************************************************************************/
void IIC_NAck_TM1650(void)
{
    //非应答即相反 与应答区别即为数据线保持高电平即可
	SET_SDA_OUT_TM1650();
	//delay_us(1);
    SDA = 1;
   // delay_us(1);
	SCL= 0;
	//delay_us(2);
    SCL = 1;
   // delay_us(2);
    //最后要将时钟线拉低 允许数据变化
    SCL = 0;
}
/******************************************************************************
 ** 
 ** Function Name: IIC_Wait_Ack_TM1650(void)
 ** Function:   等待应答信号    	
 ** Input Ref:
 ** Return Ref: 0:应答 1：无应答
 **  
 ******************************************************************************/
uint8_t IIC_Wait_Ack_TM1650(void)
{
    //应答等待计数
    uint8_t ackTime = 0;
    //先将数据线要设置成输入模式本程序未体现，有应答则会出现下降沿
	SCL = 0;
	SET_SDA_OUT_TM1650();
    //delay_us(1);	
	SDA = 1;//
	//delay_us(2);
	SET_SDA_IN_TM1650();//切换为输入模式
	
    //时钟线拉高
    SCL = 1;
    //delay_us(2);
    //等待数据线拉低应答
    while(SDA){
        //如果在该时间内仍未拉低
        ackTime ++;
        if(ackTime > 50)
        {
            //认为非应答 停止信号
            IIC_Stop_TM1650();
            return 1;
        }
    }
    SCL = 0;
    return 0 ;
}
/******************************************************************************
 ** 
 ** Function Name: void IIC_WrByte_TM1650(uint8_t number)
 ** Function:     	
 ** Input Ref:
 ** Return Ref:
 ** 
 ******************************************************************************/
void IIC_WrByte_TM1650(uint8_t oneByte)
{
    //定义一个计数变量
    uint8_t i;
    SCL =0;
    //delay_us(1);
	SET_SDA_OUT_TM1650();
    //将时钟线拉低允许数据改变
    //    SCL = 0;
    //按位发送数据
    for(i = 0;i < 8; i ++)
    {
	  
		if((oneByte&0x80))            //高位在前发送数据
        SDA=1;
		else                     //  TM1650_DIO_L;
        SDA= 0;

        //delay_us(1);
        SCL=1;
        //delay_us(1);
        SCL=0;//TM1650_CLK_L;
       // delay_us(1);
        oneByte<<=1;        

    }
   //  delay_us(1);
}



static void I2CWrByte(uint8_t oneByte) //写一个字节高位在前，低位在后
{
    uint8_t  i;
    SCL =0;
 //   delay_us(1);
    for(i=0;i<8;i++)
    {    
        if((oneByte&0x80))            //   TM1650_DIO_H;
           SDA=1;
				else                     //  TM1650_DIO_L;
         SDA= 0;
     //   delay_us(1);
       SCL=1;
      //  delay_us(1);
      SCL=0;//TM1650_CLK_L;
      //  delay_us(1);
        oneByte<<=1;        
    }
//    TM1650_CLK_H;
    //delay_us(1);
}

/******************************************************************************
 ** 
 ** Function Name: void TM1650_Set(u8 add,u8 dat)
 ** Function:     数码管显示	
 ** Input Ref:
 ** Return Ref:
 ** 
 ******************************************************************************/
void TM1650_Set(uint8_t add,uint8_t dat) 
{
	//写显存必须从高地址开始写
	IIC_Start_TM1650();
  IIC_WrByte_TM1650(add); //第一个显存地址
	IIC_Ack_TM1650();
	IIC_WrByte_TM1650(dat);
	IIC_Ack_TM1650();
	IIC_Stop_TM1650();
}

/******************************************************************************
 ** 
 ** Function Name: Init_Tm1650(void)
 ** Function:    
 ** Input Ref:
 ** Return Ref:
 ** 
 ******************************************************************************/
void Init_Tm1650(void)
{
	IIC_Init_TM1650();
	delay_30us(1000);			//需要延时一小段时间，否则开显示会无响应
	TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示

  #if 0
	TM1650_Set(0x68,segNumber[9]);//初始化为5级灰度，开显示
   

	TM1650_Set(0x6A,segNumber[1]);//初始化为5级灰度，开显示


    TM1650_Set(0x6C,segNumber[2]);//初始化为5级灰度，开显示

	
   TM1650_Set(0x6E,segNumber[3]);//初始化为5级灰度，开显示
    #endif 
	
}

