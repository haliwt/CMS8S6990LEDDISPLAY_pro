
#ifndef __TIMER0_H__
#define __TIMER0_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s6990.h"

#define TASK_NUM   (4)                  //  这里定义的任务数为4，表示有4个任务会使用此定时器定时。
//#define TASKS_MAX             4
//#define	DEBUG

typedef struct _TASK_COMPONENTS
{
    uint8_t Run;                  // 程序运行标记：0-不运行，1运行
    uint16_t Timer;                // 计时器
    uint16_t ItervalTime;              // 任务运行间隔时间
    void (*TaskHook)(void);    // 要运行的任务函数
} TASK_COMPONENTS;             // 任务定义

#if 1
typedef enum _TASK_LIST
{
    TAST_DISP_NUMBER,          // 显示数字
    TAST_KEY_SAN,             // 按键扫描
    TASK_RECE_IR,             // 接收IR
    TASK_TELEC_WS,            // 同控制主板通讯
    TASKS_MAX                 // 总的可供分配的定时任务数目
} TASK_LIST;

#endif 
extern TASK_COMPONENTS TaskComps[4]; 



/******************************************************************************
 ** \brief	 TMR0_Config
 ** \param [in] 
 **            	
 ** \return  none
 ** \note  
 ******************************************************************************/
void TMR0_Config(void);




#endif /* __DEMO_TIMER_H__ */






