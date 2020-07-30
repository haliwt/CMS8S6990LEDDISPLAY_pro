#ifndef __TM1650_I2C_H__
#define __TM1650_I2C_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s6990.h"
#include "key.h"
#include "timer0.h"


/*---向TM1650显示 写指令*/
#define  TM1650_ORDER      0x48        //数字指令 写数据
#define  TM1650_ON_DIS     0x01        //开显示，显示亮度级别8 最高
#define  TM1650_OFF_DIS    0x00        //关闭显示
#define  TM1650_1_DISP     0x11    //显示亮度级别 1
#define  TM1650_2_DISP     0x21    //显示亮度级别 2
#define  TM1650_3_DISP     0x31    //显示亮度级别 3



/*----TM1650 显示地址-----*/
#define  TM1650_DIG1_ADDR		0x68        /*TM1650显示段选COM1，地址 低字节 和高字节*/
#define  TM1650_DIG2_ADDR		0x6A        /*TM1650显示段选COM2，地址*/
#define  TM1650_DIG3_ADDR		0x6C        /*TM1650显示段选COM3，地址*/
#define  TM1650_DIG4_ADDR		0x6E        /*TM1650显示段选COM4，地址*/

extern volatile uint8_t DispData[3];//显示LED位数

/**************************************************
	*XinTong LED Display Data Data:2020.07.23

	    //                a
        //            ---------
        //           |         |
        //         f |         | b
        //           |    g    |
        //            ---------
        //           |         |
        //         e |         | c
        //           |    d    |
        //            ---------   O <- h
**************************************************/
extern const uint8_t seg[];

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
 int16_t  TM1650_write_byte(uint16_t addr , uint8_t *pointer);
 void LEDDisplay_TimerTim(void );
//int16_t  At24c256_write_byte(uint16_t addr , uint8_t ch);

#endif /* __DEMO_I2C_H__ */






