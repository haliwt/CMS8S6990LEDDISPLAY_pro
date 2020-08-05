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
int16_t  TM1650_write_byte(uint8_t cmd2 ,uint16_t addr , uint8_t *ptr)
{
	volatile int16_t i,j;
	if(addr >AT24C256_MAX)
		return -1;
	else
	{			
		I2C_SendMasterCmd(TM1650_ORDER);	            /* дTM1650��������  */
		I2C_SendMasterCmd(cmd2);                       /* дTM1650 ��ʾ�����ʾ���𣬴���ʾ*/
		I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*����Ӧ���ź�*/  
		
		I2C_SendMasterCmd(I2C_I2CMCR_STOP_Msk);         /*ֹͣ�ź�*/
		I2C_SendMasterCmd(I2C_I2CMCR_START_Msk);        /* ���Ϳ�ʼ�ź�*/
		
		//I2C_MasterWriteAddr(addr);			            /*д�ӻ���ַ+д*/
		I2C_MasterWriteBuffer((addr>>8)& 0xff);			/*дBuffer(��λROM ��ַ)*/
		I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*����Ӧ���ź�*/ 
		while(!(I2C_GetMasterIntFlag()));				/*�ȴ����ͽ���*/
		I2C_ClearMasterIntFlag();

		I2C_MasterWriteBuffer(*ptr & 0xf0);					/*д����--��4λ����*/
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

		
		I2C_MasterWriteBuffer(((*ptr)>>4) & 0xf0);					/*д����---��4λ����*/
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

/*****************************************************************************
 ** \brief	 TM1650_write_Secialbyte(uint16_t addr , uint8_t number)
 **			 д���ݵ�TM1650��ʾ����
 ** \param [in] addr ����ַ
**				ch   : ����
 **            	
 ** \return  -1��������ַ��Χ 0��д���
 ** \note  
 *****************************************************************************/
void TM1650_write_Secialbyte(uint8_t cmd2,uint16_t addr , uint8_t number)
{
	volatile int16_t i,j;
				
		I2C_SendMasterCmd(I2C_I2CMCR_START_Msk);        /* ���Ϳ�ʼ�ź�*/
	 // I2C_SendMasterCmd(TM1650_ORDER);	            /* дTM1650��������  */
	//	I2C_SendMasterCmd(cmd2);               /* дTM1650 ��ʾ�����ʾ���𣬴���ʾ*/
	//	I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*����Ӧ���ź�*/  
		
	//	I2C_SendMasterCmd(I2C_I2CMCR_STOP_Msk);         /*ֹͣ�ź�*/
	//	I2C_SendMasterCmd(I2C_I2CMCR_START_Msk);        /* ���Ϳ�ʼ�ź�*/
		
	I2C_MasterWriteAddr(0x68);			            /*д�ӻ���ַ+д*/
	I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ; 
	//	I2C_MasterWriteBuffer((addr>>8)& 0xff);			/*дBuffer(��λROM ��ַ)*/
	//	I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*����Ӧ���ź�*/ 
	//	while(!(I2C_GetMasterIntFlag()));				/*�ȴ����ͽ���*/
	//	I2C_ClearMasterIntFlag();

		I2C_MasterWriteBuffer(number);					/*д����--��4λ����*/
	//	I2C_SendMasterCmd(I2C_MASTER_SEND);
	//	while(!(I2C_GetMasterIntFlag()));		
	//	I2C_ClearMasterIntFlag();
		
		I2C_SendMasterCmd(I2C_I2CMCR_ACK_Msk) ;         /*����Ӧ���ź�*/  
		I2C_SendMasterCmd(I2C_MASTER_STOP);				/*����ֹͣλ*/
		for(i=2000;i>0;i--)								/*��ʱȷ��TM1650д�������*/
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
  	//SCL�ߵ�ƽ�ڼ䣬SDA����һ���½��ر�ʾ��ʼ�ź�
  	SET_SDA_OUT_TM1650();
    SDA = 1;    	//�������ȱ���Ϊ�ߣ���ʼ�ź�Ҫ�ÿڵ��½��� 
	  _nop_(); ;
    SCL = 1;        //ʱ���߱���Ϊ��            
      _nop_(); ;//��һ�����5us����ʱ��������������    
      _nop_(); ;
      _nop_(); ;
      _nop_(); ;        
     SDA = 0;        //���������ͳ����½���           
      _nop_(); ;
      _nop_(); ;
      _nop_(); ;      //��ʱ һС�ᣬ��֤�ɿ����½���
      _nop_(); ;             
    SCL = 0;        //����ʱ���ߣ���֤����������������ı�   
        
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
    //SCL�ߵ�ƽ�ڼ䣬SDA����һ�������� ��ʾֹͣ
  	SET_SDA_OUT_TM1650();
	SCL= 0;
	  _nop_(); ;
      _nop_(); ;
	SDA = 0;		//��֤������Ϊ�͵�ƽ
	delay_us(40);
    SCL= 1;		//�ȱ�֤ʱ����Ϊ�ߵ�ƽ
    delay_us(10);    //��ʱ �Եõ�һ���ɿ��ĵ�ƽ�ź�            
    SDA = 1;        //�����߳���������           
    delay_us(40);    //��ʱ ��֤һ���ɿ��ĸߵ�ƽ      
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
    //������һֱ����Ϊ�͵�ƽ��ʱ���߳��������ؼ�ΪӦ��
 
	SET_SDA_OUT_TM1650();
	delay_us(10);
    SDA = 0;
    delay_us(10);
    SCL= 0;
    delay_us(40);
	SCL = 1;
	delay_us(40);
    //Ӧ����ɺ� ��ʱ�������� ���������޸�
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
    //��Ӧ���෴ ��Ӧ������Ϊ�����߱��ָߵ�ƽ����
	SET_SDA_OUT_TM1650();
	delay_us(10);
    SDA = 1;
    delay_us(10);
	SCL= 0;
	delay_us(40);
    SCL = 1;
    delay_us(40);
    //���Ҫ��ʱ�������� �������ݱ仯
    SCL = 0;
}
/******************************************************************************
 ** 
 ** Function Name: IIC_Wait_Ack_TM1650(void)
 ** Function:   �ȴ�Ӧ���ź�    	
 ** Input Ref:
 ** Return Ref: 0:Ӧ�� 1����Ӧ��
 **  
 ******************************************************************************/
 uint8_t IIC_Wait_Ack_TM1650(void)
{
    //Ӧ��ȴ�����
    uint8_t ackTime = 0;
    //�Ƚ�������Ҫ���ó�����ģʽ������δ���֣���Ӧ���������½���
	SCL = 0;
	SET_SDA_OUT_TM1650();
    delay_us(10);	
	SDA = 1;//
	delay_us(30);
	SET_SDA_IN_TM1650();//�л�Ϊ����ģʽ
	
    //ʱ��������
    SCL = 1;
    delay_us(30);
    //�ȴ�����������Ӧ��
    while(SDA){
        //����ڸ�ʱ������δ����
        ackTime ++;
        if(ackTime > 250)
        {
            //��Ϊ��Ӧ�� ֹͣ�ź�
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
    //����һ����������
    uint8_t i;
	SET_SDA_OUT_TM1650();
    //��ʱ���������������ݸı�
    //    SCL = 0;
    //��λ��������
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
 ** Function:     �������ʾ	
 ** Input Ref:
 ** Return Ref:
 ** 
 ******************************************************************************/
void TM1650_Set(uint8_t add,uint8_t dat) 
{
	//д�Դ����Ӹߵ�ַ��ʼд
	IIC_Start_TM1650();
	IIC_WrByte_TM1650(add); //��һ���Դ��ַ
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
	delay_30us(1000);			//��Ҫ��ʱһС��ʱ�䣬������ʾ������Ӧ
	TM1650_Set(0x48,0x31);//��ʼ��Ϊ5���Ҷȣ�����ʾ
	
}