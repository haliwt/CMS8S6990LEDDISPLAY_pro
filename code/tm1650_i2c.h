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






