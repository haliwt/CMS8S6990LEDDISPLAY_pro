/****************************************************************************/
/*	include files
*****************************************************************************/
#include "tm1650_i2c.h"


/****************************************************************************/
/*	Local pre-processor symbols('#define')
****************************************************************************/
/*----AT24C256地址+读写-----------------------------------------------------*/
#define  AT24C256_WRITE		0xA0				/*Write Cmd*/
#define  AT24C256_READ      0xA1				/*Read  Cmd*/
#define  AT24C256_MAX		0x7fff				/*address  max*/

/*----I2C主控模式命令-------------------------------------------------------*/
#define I2C_MASTER_START_SEND				(I2C_I2CMCR_START_Msk | I2C_I2CMCR_RUN_Msk)		/*起始位+从机地址+写+1Byte数据*/
#define I2C_MASTER_SEND						(I2C_I2CMCR_RUN_Msk)							/*发送1Byte数据*/
#define I2C_MASTER_STOP						(I2C_I2CMCR_STOP_Msk)							/*发送停止位*/
#define I2C_MASTER_START_RECEIVE_NACK		(I2C_I2CMCR_START_Msk | I2C_I2CMCR_RUN_Msk)		/*起始位+从机地址+读+1Byte时钟+NACK*/
#define I2C_MASTER_START_RECEIVE_ACK		(I2C_I2CMCR_START_Msk | I2C_I2CMCR_RUN_Msk | I2C_I2CMCR_ACK_Msk) /*起始位+从机地址+读+1Byte时钟+ACK*/
#define I2C_MASTER_RECEIVE_NACK				(I2C_I2CMCR_RUN_Msk)							/*发送读1Byte时钟+NACK*/
#define I2C_MASTER_RECEIVE_ACK				(I2C_I2CMCR_RUN_Msk | I2C_I2CMCR_ACK_Msk)		/*发送读1Byte时钟+ACK*/

volatile uint8_t DispData[3];
/*****************************************************************************
 ** \brief	I2C_SendMasterCmd
 **			发送主控命令
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void  I2C_SendMasterCmd(uint8_t Cmd)
{
	I2CMCR = Cmd;
}
/*****************************************************************************
 ** \brief	I2C_MasterWriteAddr
 **			主控写从机地址
 ** \param [in] SlaveAddr ：从机地址+读写位R/W
 ** \return  none
 ** \note	 读写位在从机地址的第0位，即7位地址+R/W  
*****************************************************************************/
void  I2C_MasterWriteAddr(uint8_t SlaveAddr)
{
	I2CMSA   = SlaveAddr;
}
/*****************************************************************************
 ** \brief	I2C_MasterWriteBuffer
 **			主控写缓存
 ** \param [in] data
 ** \return  none
 ** \note	 
*****************************************************************************/
void  I2C_MasterWriteBuffer(uint8_t Data)
{
	I2CMBUF = Data;
}
/*****************************************************************************
 ** \brief	I2C_MasterReadBuffer
 **			主控读缓存
 ** \param [in] none
 ** \return  data
 ** \note	 
*****************************************************************************/
uint8_t I2C_MasterReadBuffer(void)
{
	return I2CMBUF;
}

/*****************************************************************************
 ** \brief	 At24c256_write_byte
 **			 写数据到At24C256
 ** \param [in] addr ：地址
**				ch   : 数据
 **            	
 ** \return  -1：超出地址范围 0：写完成
 ** \note  
 *****************************************************************************/
int16_t  TM1650_write_byte(uint8_t cmd2 ,uint16_t addr , uint8_t *ptr)
{
	volatile int16_t i,j;
	if(addr >AT24C256_MAX)
		return -1;
	else
	{			
		I2C_SendMasterCmd(TM1650_ORDER);	            /* 写TM1650数据命令  */
		I2C_SendMasterCmd(cmd2);                       /* 写TM1650 显示命令，显示级别，打开显示*/
		I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*发送应答信号*/  
		
		I2C_SendMasterCmd(I2C_I2CMCR_STOP_Msk);         /*停止信号*/
		I2C_SendMasterCmd(I2C_I2CMCR_START_Msk);        /* 发送开始信号*/
		
		//I2C_MasterWriteAddr(addr);			            /*写从机地址+写*/
		I2C_MasterWriteBuffer((addr>>8)& 0xff);			/*写Buffer(高位ROM 地址)*/
		I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*发送应答信号*/ 
		while(!(I2C_GetMasterIntFlag()));				/*等待发送结束*/
		I2C_ClearMasterIntFlag();

		I2C_MasterWriteBuffer(*ptr & 0xf0);					/*写数据--高4位数据*/
		I2C_SendMasterCmd(I2C_MASTER_SEND);
		while(!(I2C_GetMasterIntFlag()));		
		I2C_ClearMasterIntFlag();

		I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*发送应答信号*/  
		I2C_SendMasterCmd(I2C_I2CMCR_STOP_Msk);         /*停止信号*/
		I2C_SendMasterCmd(I2C_I2CMCR_START_Msk);        /* 发送开始信号*/

		I2C_MasterWriteBuffer(addr & 0xff);				/*低位ROM 地址*/
		I2C_SendMasterCmd(I2C_MASTER_SEND);				/*发送Buffer*/
		while(!(I2C_GetMasterIntFlag()));
		I2C_ClearMasterIntFlag();	

		
		I2C_MasterWriteBuffer(((*ptr)>>4) & 0xf0);					/*写数据---低4位数据*/
		I2C_SendMasterCmd(I2C_MASTER_SEND);
		while(!(I2C_GetMasterIntFlag()));		
		I2C_ClearMasterIntFlag();
		
		I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*发送应答信号*/  
		I2C_SendMasterCmd(I2C_MASTER_STOP);				/*发送停止位*/
		for(i=2000;i>0;i--)								/*延时确保TM1650写数据完成*/
			for(j=200;j>0;j--);
	}
	return 0;
}

/*****************************************************************************
 ** \brief	 TM1650_write_Secialbyte(uint16_t addr , uint8_t number)
 **			 写数据到TM1650显示数据
 ** \param [in] addr ：地址
**				ch   : 数据
 **            	
 ** \return  -1：超出地址范围 0：写完成
 ** \note  
 *****************************************************************************/
void TM1650_write_Secialbyte(uint8_t cmd2,uint16_t addr , uint8_t number)
{
	volatile int16_t i,j;
				
		I2C_SendMasterCmd(I2C_I2CMCR_START_Msk);        /* 发送开始信号*/
	 // I2C_SendMasterCmd(TM1650_ORDER);	            /* 写TM1650数据命令  */
	//	I2C_SendMasterCmd(cmd2);               /* 写TM1650 显示命令，显示级别，打开显示*/
	//	I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*发送应答信号*/  
		
	//	I2C_SendMasterCmd(I2C_I2CMCR_STOP_Msk);         /*停止信号*/
	//	I2C_SendMasterCmd(I2C_I2CMCR_START_Msk);        /* 发送开始信号*/
		
	I2C_MasterWriteAddr(0x68);			            /*写从机地址+写*/
	I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ; 
	//	I2C_MasterWriteBuffer((addr>>8)& 0xff);			/*写Buffer(高位ROM 地址)*/
	//	I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*发送应答信号*/ 
	//	while(!(I2C_GetMasterIntFlag()));				/*等待发送结束*/
	//	I2C_ClearMasterIntFlag();

		I2C_MasterWriteBuffer(number);					/*写数据--高4位数据*/
	//	I2C_SendMasterCmd(I2C_MASTER_SEND);
	//	while(!(I2C_GetMasterIntFlag()));		
	//	I2C_ClearMasterIntFlag();
		
		I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*发送应答信号*/  
		I2C_SendMasterCmd(I2C_MASTER_STOP);				/*发送停止位*/
		for(i=2000;i>0;i--)								/*延时确保TM1650写数据完成*/
			for(j=200;j>0;j--);
	

}
#if 1

int16_t  At24c256_write_byte(uint16_t addr , uint8_t ch)
{
	volatile int16_t i,j;
	if(addr >AT24C256_MAX)
		return -1;
	else
	{			
		
		I2C_MasterWriteAddr(AT24C256_WRITE);			/*写从机地址+写*/
		I2C_MasterWriteBuffer((addr>>8)& 0xff);			/*写Buffer(高位ROM 地址)*/
		I2C_SendMasterCmd(I2C_MASTER_START_SEND);
		while(!(I2C_GetMasterIntFlag()));				/*等待发送结束*/
		I2C_ClearMasterIntFlag();
								
		I2C_MasterWriteBuffer(addr & 0xff);				/*低位ROM 地址*/
		I2C_SendMasterCmd(I2C_MASTER_SEND);				/*发送Buffer*/
		while(!(I2C_GetMasterIntFlag()));
		I2C_ClearMasterIntFlag();	
		
		I2C_MasterWriteBuffer(ch);							/*写数据*/
		I2C_SendMasterCmd(I2C_MASTER_SEND);
		while(!(I2C_GetMasterIntFlag()));		
		I2C_ClearMasterIntFlag();
		
		I2C_SendMasterCmd(I2C_MASTER_STOP);					/*发送停止位*/
		for(i=2000;i>0;i--)								/*延时确保AT24C256写数据完成*/
			for(j=200;j>0;j--);
	}
	return 0;
}
#endif 
/********************************************************************************
 ** \brief	 At24c256_read_byte
 **			 从At24C256中读数据
 ** \param [in]  addr : 地址
 **            	
 ** \return  返回8位数据
 ** \note   
 ******************************************************************************/
uint8_t  At24c256_read_byte(uint16_t addr)
{
	unsigned char buffer;
	if(addr > AT24C256_MAX)
		return -1;
	
	I2C_MasterWriteAddr(AT24C256_WRITE);			/*写从机地址+写*/
	I2C_MasterWriteBuffer((addr>>8)& 0xff);			/*写Buffer(高位ROM 地址)*/
	I2C_SendMasterCmd(I2C_MASTER_START_SEND);
	while(!(I2C_GetMasterIntFlag()));				/*等待发送结束*/
	I2C_ClearMasterIntFlag();
							
	I2C_MasterWriteBuffer(addr & 0xff);				/*低位ROM 地址*/
	I2C_SendMasterCmd(I2C_MASTER_SEND);				/*发送Buffer*/
	while(!(I2C_GetMasterIntFlag()));
	I2C_ClearMasterIntFlag();	
	
	I2C_MasterWriteAddr(AT24C256_READ);					/*写从机地址+读*/	
	I2C_SendMasterCmd(I2C_MASTER_START_RECEIVE_NACK);	
		
	while(!(I2C_GetMasterIntFlag()));					/*等待数据接收完成*/
	I2C_ClearMasterIntFlag();							
	buffer=I2C_MasterReadBuffer();						/*读取数据*/
	
	I2C_SendMasterCmd(I2C_MASTER_STOP);					/*发送停止位*/
	return buffer;
}
/********************************************************************************
 ** \brief	 At24c256_read_str
 **			 连续读取At24c256数据
 ** \param [in] addr ：起始地址
 **            	ch	 : 数据保存的容器(数组)  
**				sizevalue: 读取的数据的个数
 ** \return  0/1
 ** \note  	 例：  unsigned char  array[10];			//定义一个10字节的容器
 **	  At24c256_read_str(0x0010, Buffer, 5); //从地址0x0010开始读取5个字节的数据放到数组array中
 ******************************************************************************/
uint16_t At24c256_read_str(uint16_t addr,  uint8_t *ch, uint16_t sizevalue)
{
	volatile int16_t i;
	if(addr > AT24C256_MAX)
		return 0;
	
	I2C_MasterWriteAddr(AT24C256_WRITE);			/*写从机地址+写*/
	I2C_MasterWriteBuffer((addr>>8)& 0xff);			/*写Buffer(高位ROM 地址)*/
	I2C_SendMasterCmd(I2C_MASTER_START_SEND);
	while(!(I2C_GetMasterIntFlag()));				/*等待发送结束*/
	I2C_ClearMasterIntFlag();
							
	I2C_MasterWriteBuffer(addr & 0xff);				/*低位ROM 地址*/
	I2C_SendMasterCmd(I2C_MASTER_SEND);				/*发送Buffer*/
	while(!(I2C_GetMasterIntFlag()));
	I2C_ClearMasterIntFlag();	
	
	I2C_MasterWriteAddr(AT24C256_READ);					/*写从机地址+读*/	
	I2C_SendMasterCmd(I2C_MASTER_START_RECEIVE_ACK);	

	for(i=0;i<sizevalue-2;i++)
	{		
		while(!(I2C_GetMasterIntFlag()));				/*等待数据接收完成*/
		I2C_ClearMasterIntFlag();						
		*ch++ = I2C_MasterReadBuffer();					/*读数据*/
		I2C_SendMasterCmd(I2C_MASTER_RECEIVE_ACK);
	}
	
	while(!(I2C_GetMasterIntFlag()));
	I2C_ClearMasterIntFlag();							
	*ch++ =I2C_MasterReadBuffer();							
	
	I2C_SendMasterCmd(I2C_MASTER_RECEIVE_NACK);			/*读取最后一个数据,不发送ACK*/
	*ch =I2C_MasterReadBuffer();														
														
	I2C_SendMasterCmd(I2C_MASTER_STOP);					/*发送停止位*/
	return 1;
}
/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
****************************************************************************/
/******************************************************************************
 ** \brief	 I2C_Config
 ** \param [in] 
 **            	
 ** \return  none
 ** \note  
 ******************************************************************************/
void I2C_Config(void)
{
	/*
	 (1)开启I2C主控模式
	 */
	 I2C_EnableMasterMode();
	/*
	 (2)设置I2C通讯时钟
	 */	 
	I2C_ConfigCLK(10);							/*设置时钟100K*/
	/*
	(3)设置IO复用
	*/
	 GPIO_SET_MUX_MODE(P03CFG, GPIO_MUX_SCL);			/*SCL*/
	 GPIO_SET_MUX_MODE(P04CFG, GPIO_MUX_SDA);	 		/*SDA*/	 
	 
}
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
	SDA = 1;
	
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
      _nop_(); ;
      _nop_(); ;
      _nop_(); ;        
     SDA = 0;        //数据线拉低出现下降沿           
      _nop_(); ;
      _nop_(); ;
      _nop_(); ;      //延时 一小会，保证可靠的下降沿
      _nop_(); ;             
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
	  _nop_(); ;
      _nop_(); ;
	SDA = 0;		//保证数据线为低电平
	delay_us(40);
    SCL= 1;		//先保证时钟线为高电平
    delay_us(10);    //延时 以得到一个可靠的电平信号            
    SDA = 1;        //数据线出现上升沿           
    delay_us(40);    //延时 保证一个可靠的高电平      
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
	delay_us(10);
    SDA = 0;
    delay_us(10);
    SCL= 0;
    delay_us(40);
	SCL = 1;
	delay_us(40);
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
	delay_us(10);
    SDA = 1;
    delay_us(10);
	SCL= 0;
	delay_us(40);
    SCL = 1;
    delay_us(40);
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
    delay_us(10);	
	SDA = 1;//
	delay_us(30);
	SET_SDA_IN_TM1650();//切换为输入模式
	
    //时钟线拉高
    SCL = 1;
    delay_us(30);
    //等待数据线拉低应答
    while(SDA){
        //如果在该时间内仍未拉低
        ackTime ++;
        if(ackTime > 250)
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
void IIC_WrByte_TM1650(uint8_t number)
{
    //定义一个计数变量
    uint8_t i;
	SET_SDA_OUT_TM1650();
    //将时钟线拉低允许数据改变
    //    SCL = 0;
    //按位发送数据
    for(i = 0;i < 8; i ++)
    {
	  	delay_us(2);
        if((number &0x80)>>7) //0x80  1000 0000
			SDA=1;
		else
			SDA=0;
        number<<=1; 	  
		delay_us(20);   
		SCL=1;
		delay_us(20);  
		SCL=0;	
		delay_us(20); 
    }
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
	
}