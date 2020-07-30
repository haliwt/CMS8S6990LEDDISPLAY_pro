/****************************************************************************/
/*	include files
*****************************************************************************/
#include "tm1650_i2c.h"


/****************************************************************************/
/*	Local pre-processor symbols('#define')
****************************************************************************/
/*----AT24C256��ַ+��д-----------------------------------------------------*/
#define  AT24C256_WRITE		0xA0				/*Write Cmd*/
#define  AT24C256_READ      0xA1				/*Read  Cmd*/
#define  AT24C256_MAX		0x7fff				/*address  max*/

/*----I2C����ģʽ����-------------------------------------------------------*/
#define I2C_MASTER_START_SEND				(I2C_I2CMCR_START_Msk | I2C_I2CMCR_RUN_Msk)		/*��ʼλ+�ӻ���ַ+д+1Byte����*/
#define I2C_MASTER_SEND						(I2C_I2CMCR_RUN_Msk)							/*����1Byte����*/
#define I2C_MASTER_STOP						(I2C_I2CMCR_STOP_Msk)							/*����ֹͣλ*/
#define I2C_MASTER_START_RECEIVE_NACK		(I2C_I2CMCR_START_Msk | I2C_I2CMCR_RUN_Msk)		/*��ʼλ+�ӻ���ַ+��+1Byteʱ��+NACK*/
#define I2C_MASTER_START_RECEIVE_ACK		(I2C_I2CMCR_START_Msk | I2C_I2CMCR_RUN_Msk | I2C_I2CMCR_ACK_Msk) /*��ʼλ+�ӻ���ַ+��+1Byteʱ��+ACK*/
#define I2C_MASTER_RECEIVE_NACK				(I2C_I2CMCR_RUN_Msk)							/*���Ͷ�1Byteʱ��+NACK*/
#define I2C_MASTER_RECEIVE_ACK				(I2C_I2CMCR_RUN_Msk | I2C_I2CMCR_ACK_Msk)		/*���Ͷ�1Byteʱ��+ACK*/

volatile uint8_t DispData[3];
/*****************************************************************************
 ** \brief	I2C_SendMasterCmd
 **			������������
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
 **			����д�ӻ���ַ
 ** \param [in] SlaveAddr ���ӻ���ַ+��дλR/W
 ** \return  none
 ** \note	 ��дλ�ڴӻ���ַ�ĵ�0λ����7λ��ַ+R/W  
*****************************************************************************/
void  I2C_MasterWriteAddr(uint8_t SlaveAddr)
{
	I2CMSA   = SlaveAddr;
}
/*****************************************************************************
 ** \brief	I2C_MasterWriteBuffer
 **			����д����
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
 **			���ض�����
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
 **			 д���ݵ�At24C256
 ** \param [in] addr ����ַ
**				ch   : ����
 **            	
 ** \return  -1��������ַ��Χ 0��д���
 ** \note  
 *****************************************************************************/
int16_t  TM1650_write_byte(uint16_t addr , uint8_t *ptr)
{
	volatile int16_t i,j;
	if(addr >AT24C256_MAX)
		return -1;
	else
	{			
		I2C_SendMasterCmd(TM1650_ORDER);	            /* дTM1650��������  */
		I2C_SendMasterCmd(TM1650_ON_DIS);               /* дTM1650 ��ʾ�����ʾ���𣬴���ʾ*/
		I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*����Ӧ���ź�*/  
		
		I2C_SendMasterCmd(I2C_I2CMCR_STOP_Msk);         /*ֹͣ�ź�*/
		I2C_SendMasterCmd(I2C_I2CMCR_START_Msk);        /* ���Ϳ�ʼ�ź�*/
		
		//I2C_MasterWriteAddr(addr);			            /*д�ӻ���ַ+д*/
		I2C_MasterWriteBuffer((addr>>8)& 0xff);			/*дBuffer(��λROM ��ַ)*/
		I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*����Ӧ���ź�*/ 
		while(!(I2C_GetMasterIntFlag()));				/*�ȴ����ͽ���*/
		I2C_ClearMasterIntFlag();

		I2C_MasterWriteBuffer(*ptr);					/*д����--��4λ����*/
		I2C_SendMasterCmd(I2C_MASTER_SEND);
		while(!(I2C_GetMasterIntFlag()));		
		I2C_ClearMasterIntFlag();

		I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*����Ӧ���ź�*/  
		I2C_SendMasterCmd(I2C_I2CMCR_STOP_Msk);         /*ֹͣ�ź�*/
		I2C_SendMasterCmd(I2C_I2CMCR_START_Msk);        /* ���Ϳ�ʼ�ź�*/

		I2C_MasterWriteBuffer(addr & 0xff);				/*��λROM ��ַ*/
		I2C_SendMasterCmd(I2C_MASTER_SEND);				/*����Buffer*/
		while(!(I2C_GetMasterIntFlag()));
		I2C_ClearMasterIntFlag();	

		
		I2C_MasterWriteBuffer((*ptr)>>4);					/*д����---��4λ����*/
		I2C_SendMasterCmd(I2C_MASTER_SEND);
		while(!(I2C_GetMasterIntFlag()));		
		I2C_ClearMasterIntFlag();
		
		I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*����Ӧ���ź�*/  
		I2C_SendMasterCmd(I2C_MASTER_STOP);				/*����ֹͣλ*/
		for(i=2000;i>0;i--)								/*��ʱȷ��TM1650д�������*/
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
		
		I2C_MasterWriteAddr(AT24C256_WRITE);			/*д�ӻ���ַ+д*/
		I2C_MasterWriteBuffer((addr>>8)& 0xff);			/*дBuffer(��λROM ��ַ)*/
		I2C_SendMasterCmd(I2C_MASTER_START_SEND);
		while(!(I2C_GetMasterIntFlag()));				/*�ȴ����ͽ���*/
		I2C_ClearMasterIntFlag();
								
		I2C_MasterWriteBuffer(addr & 0xff);				/*��λROM ��ַ*/
		I2C_SendMasterCmd(I2C_MASTER_SEND);				/*����Buffer*/
		while(!(I2C_GetMasterIntFlag()));
		I2C_ClearMasterIntFlag();	
		
		I2C_MasterWriteBuffer(ch);							/*д����*/
		I2C_SendMasterCmd(I2C_MASTER_SEND);
		while(!(I2C_GetMasterIntFlag()));		
		I2C_ClearMasterIntFlag();
		
		I2C_SendMasterCmd(I2C_MASTER_STOP);					/*����ֹͣλ*/
		for(i=2000;i>0;i--)								/*��ʱȷ��AT24C256д�������*/
			for(j=200;j>0;j--);
	}
	return 0;
}
#endif 
/********************************************************************************
 ** \brief	 At24c256_read_byte
 **			 ��At24C256�ж�����
 ** \param [in]  addr : ��ַ
 **            	
 ** \return  ����8λ����
 ** \note   
 ******************************************************************************/
uint8_t  At24c256_read_byte(uint16_t addr)
{
	unsigned char buffer;
	if(addr > AT24C256_MAX)
		return -1;
	
	I2C_MasterWriteAddr(AT24C256_WRITE);			/*д�ӻ���ַ+д*/
	I2C_MasterWriteBuffer((addr>>8)& 0xff);			/*дBuffer(��λROM ��ַ)*/
	I2C_SendMasterCmd(I2C_MASTER_START_SEND);
	while(!(I2C_GetMasterIntFlag()));				/*�ȴ����ͽ���*/
	I2C_ClearMasterIntFlag();
							
	I2C_MasterWriteBuffer(addr & 0xff);				/*��λROM ��ַ*/
	I2C_SendMasterCmd(I2C_MASTER_SEND);				/*����Buffer*/
	while(!(I2C_GetMasterIntFlag()));
	I2C_ClearMasterIntFlag();	
	
	I2C_MasterWriteAddr(AT24C256_READ);					/*д�ӻ���ַ+��*/	
	I2C_SendMasterCmd(I2C_MASTER_START_RECEIVE_NACK);	
		
	while(!(I2C_GetMasterIntFlag()));					/*�ȴ����ݽ������*/
	I2C_ClearMasterIntFlag();							
	buffer=I2C_MasterReadBuffer();						/*��ȡ����*/
	
	I2C_SendMasterCmd(I2C_MASTER_STOP);					/*����ֹͣλ*/
	return buffer;
}
/********************************************************************************
 ** \brief	 At24c256_read_str
 **			 ������ȡAt24c256����
 ** \param [in] addr ����ʼ��ַ
 **            	ch	 : ���ݱ��������(����)  
**				sizevalue: ��ȡ�����ݵĸ���
 ** \return  0/1
 ** \note  	 ����  unsigned char  array[10];			//����һ��10�ֽڵ�����
 **	  At24c256_read_str(0x0010, Buffer, 5); //�ӵ�ַ0x0010��ʼ��ȡ5���ֽڵ����ݷŵ�����array��
 ******************************************************************************/
uint16_t At24c256_read_str(uint16_t addr,  uint8_t *ch, uint16_t sizevalue)
{
	volatile int16_t i;
	if(addr > AT24C256_MAX)
		return 0;
	
	I2C_MasterWriteAddr(AT24C256_WRITE);			/*д�ӻ���ַ+д*/
	I2C_MasterWriteBuffer((addr>>8)& 0xff);			/*дBuffer(��λROM ��ַ)*/
	I2C_SendMasterCmd(I2C_MASTER_START_SEND);
	while(!(I2C_GetMasterIntFlag()));				/*�ȴ����ͽ���*/
	I2C_ClearMasterIntFlag();
							
	I2C_MasterWriteBuffer(addr & 0xff);				/*��λROM ��ַ*/
	I2C_SendMasterCmd(I2C_MASTER_SEND);				/*����Buffer*/
	while(!(I2C_GetMasterIntFlag()));
	I2C_ClearMasterIntFlag();	
	
	I2C_MasterWriteAddr(AT24C256_READ);					/*д�ӻ���ַ+��*/	
	I2C_SendMasterCmd(I2C_MASTER_START_RECEIVE_ACK);	

	for(i=0;i<sizevalue-2;i++)
	{		
		while(!(I2C_GetMasterIntFlag()));				/*�ȴ����ݽ������*/
		I2C_ClearMasterIntFlag();						
		*ch++ = I2C_MasterReadBuffer();					/*������*/
		I2C_SendMasterCmd(I2C_MASTER_RECEIVE_ACK);
	}
	
	while(!(I2C_GetMasterIntFlag()));
	I2C_ClearMasterIntFlag();							
	*ch++ =I2C_MasterReadBuffer();							
	
	I2C_SendMasterCmd(I2C_MASTER_RECEIVE_NACK);			/*��ȡ���һ������,������ACK*/
	*ch =I2C_MasterReadBuffer();														
														
	I2C_SendMasterCmd(I2C_MASTER_STOP);					/*����ֹͣλ*/
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
	 (1)����I2C����ģʽ
	 */
	 I2C_EnableMasterMode();
	/*
	 (2)����I2CͨѶʱ��
	 */	 
	I2C_ConfigCLK(10);							/*����ʱ��100K*/
	/*
	(3)����IO����
	*/
	 GPIO_SET_MUX_MODE(P23CFG, GPIO_MUX_SCL);			/*SCL*/
	 GPIO_SET_MUX_MODE(P22CFG, GPIO_MUX_SDA);	 		/*SDA*/	 
	 
}







