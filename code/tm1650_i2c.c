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
int16_t  TM1650_write_byte(uint16_t addr , uint8_t *ptr)
{
	volatile int16_t i,j;
	if(addr >AT24C256_MAX)
		return -1;
	else
	{			
		I2C_SendMasterCmd(TM1650_ORDER);	            /* 写TM1650数据命令  */
		I2C_SendMasterCmd(TM1650_ON_DIS);               /* 写TM1650 显示命令，显示级别，打开显示*/
		I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*发送应答信号*/  
		
		I2C_SendMasterCmd(I2C_I2CMCR_STOP_Msk);         /*停止信号*/
		I2C_SendMasterCmd(I2C_I2CMCR_START_Msk);        /* 发送开始信号*/
		
		//I2C_MasterWriteAddr(addr);			            /*写从机地址+写*/
		I2C_MasterWriteBuffer((addr>>8)& 0xff);			/*写Buffer(高位ROM 地址)*/
		I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*发送应答信号*/ 
		while(!(I2C_GetMasterIntFlag()));				/*等待发送结束*/
		I2C_ClearMasterIntFlag();

		I2C_MasterWriteBuffer(*ptr);					/*写数据--高4位数据*/
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

		
		I2C_MasterWriteBuffer((*ptr)>>4);					/*写数据---低4位数据*/
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

#if 0

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
	 GPIO_SET_MUX_MODE(P23CFG, GPIO_MUX_SCL);			/*SCL*/
	 GPIO_SET_MUX_MODE(P22CFG, GPIO_MUX_SDA);	 		/*SDA*/	 
	 
}







