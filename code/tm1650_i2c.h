#ifndef __TM1650_I2C_H__
#define __TM1650_I2C_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s6990.h"
#include "key.h"
#include "timer0.h"
#include "LED.h"


#define SCL 	P03
#define SDA     P04 
#define SET_SDA_OUT_TM1650()       (GPIO_SET_MUX_MODE(P04CFG, GPIO_MUX_GPIO),GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_4))
#define SET_SDA_IN_TM1650() 	   (GPIO_SET_MUX_MODE(P04CFG, GPIO_MUX_GPIO),GPIO_ENABLE_INPUT(P0TRIS, GPIO_PIN_4))
/*---向TM1650显示 写指令*/
#define  TM1650_ORDER      0x48        //数字指令 写数据





/******************************************************************************
 ** \brief	 I2C_Config
 ** \param [in] 
 **            	
 ** \return  none
 ** \note  
 ******************************************************************************/
void I2C_Config(void);

/*****************************************************************************
 ** \brief	 At24c256_read_str
 **			 连续读取At24c256数据
 ** \param [in] addr ：起始地址
 **            	ch	 : 数据保存的容器(数组)  
**				sizevalue: 读取的数据的个数
 ** \return  0/1
 ** \note  	 例：  unsigned char  array[10];			//定义一个10字节的容器
 **	  At24c256_read_str(0x0010, Buffer, 5); //从地址0x0010开始读取5个字节的数据放到数组array中
 *****************************************************************************/
uint16_t At24c256_read_str(uint16_t addr,  uint8_t *ch, uint16_t sizevalue);
 
/*****************************************************************************
 ** \brief	 At24c256_read_byte
 **			 从At24C256中读数据
 ** \param [in]  addr : 地址
 **            	
 ** \return  返回8位数据
 ** \note   
 ****************************************************************************/
uint8_t  At24c256_read_byte(uint16_t addr);
/*****************************************************************************
 ** \brief	 At24c256_write_byte
 **			 写数据到At24C256
 ** \param [in] addr ：地址
**				ch   : 数据
 **            	
 ** \return  -1：超出地址范围 0：写完成
 ** \note  
 *****************************************************************************/ 
 int16_t  TM1650_write_byte(uint8_t cmd2,uint16_t addr , uint8_t *pointer);
 void     TM1650_write_Secialbyte(uint8_t cmd2,uint16_t addr , uint8_t number);
//int16_t  At24c256_write_byte(uint16_t addr , uint8_t ch);


void IIC_Init_TM1650(void);
void IIC_Start_TM1650(void);
void IIC_Stop_TM1650(void);
void IIC_Ack_TM1650(void);
void IIC_NAck_TM1650(void);
uint8_t IIC_Wait_Ack_TM1650(void);
void IIC_WrByte_TM1650(uint8_t number);
void TM1650_Set(uint8_t add,uint8_t dat) ;
void Init_Tm1650(void);

#endif /* __DEMO_I2C_H__ */






