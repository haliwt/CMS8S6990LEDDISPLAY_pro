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
static void I2CWrByte(uint8_t oneByte) ;//дһ���ֽڸ�λ��ǰ����λ�ں�
/*****************************************************************************
 ** \brief	I2C_SendMasterCmd
 **			������������
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
  	//SCL�ߵ�ƽ�ڼ䣬SDA����һ���½��ر�ʾ��ʼ�ź�
  	SET_SDA_OUT_TM1650();
    SDA = 1;    	//�������ȱ���Ϊ�ߣ���ʼ�ź�Ҫ�ÿڵ��½��� 
	  _nop_(); ;
    SCL = 1;        //ʱ���߱���Ϊ��            
      _nop_(); ;//��һ�����5us����ʱ��������������    
      //_nop_(); ;
     // _nop_(); ;
     // _nop_(); ;        
     SDA = 0;        //���������ͳ����½���           
      _nop_(); ;
     // _nop_(); ;
      //_nop_(); ;      //��ʱ һС�ᣬ��֤�ɿ����½���
      //_nop_(); ;             
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
	  _nop_(); 
      _nop_(); 
     // _nop_(); 
     // _nop_(); 
	SDA = 0;		//��֤������Ϊ�͵�ƽ
	//delay_us(2);
    SCL= 1;		//�ȱ�֤ʱ����Ϊ�ߵ�ƽ
    //delay_us(1);    //��ʱ �Եõ�һ���ɿ��ĵ�ƽ�ź�            
    SDA = 1;        //�����߳���������           
   // delay_us(2);    //��ʱ ��֤һ���ɿ��ĸߵ�ƽ      
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
	//delay_us(1);
    SDA = 0;
   // delay_us(1);
    SCL= 0;
   // delay_us(2);
	SCL = 1;
	//delay_us(2);
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
	//delay_us(1);
    SDA = 1;
   // delay_us(1);
	SCL= 0;
	//delay_us(2);
    SCL = 1;
   // delay_us(2);
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
    //delay_us(1);	
	SDA = 1;//
	//delay_us(2);
	SET_SDA_IN_TM1650();//�л�Ϊ����ģʽ
	
    //ʱ��������
    SCL = 1;
    //delay_us(2);
    //�ȴ�����������Ӧ��
    while(SDA){
        //����ڸ�ʱ������δ����
        ackTime ++;
        if(ackTime > 50)
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
void IIC_WrByte_TM1650(uint8_t oneByte)
{
    //����һ����������
    uint8_t i;
    SCL =0;
    //delay_us(1);
	SET_SDA_OUT_TM1650();
    //��ʱ���������������ݸı�
    //    SCL = 0;
    //��λ��������
    for(i = 0;i < 8; i ++)
    {
	  
		if((oneByte&0x80))            //��λ��ǰ��������
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



static void I2CWrByte(uint8_t oneByte) //дһ���ֽڸ�λ��ǰ����λ�ں�
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

  #if 0
	TM1650_Set(0x68,segNumber[9]);//��ʼ��Ϊ5���Ҷȣ�����ʾ
   

	TM1650_Set(0x6A,segNumber[1]);//��ʼ��Ϊ5���Ҷȣ�����ʾ


    TM1650_Set(0x6C,segNumber[2]);//��ʼ��Ϊ5���Ҷȣ�����ʾ

	
   TM1650_Set(0x6E,segNumber[3]);//��ʼ��Ϊ5���Ҷȣ�����ʾ
    #endif 
	
}

