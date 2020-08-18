#include "key.h"
#include "demo_buzzer.h"
#include "myflash.h"

//static uint8_t KEY_Scan(void);

//key_types   key;
Telec *Telecom= NULL;
static uint8_t Lockflag =0;

uint8_t New_KeyBuff[KEYBUFFSIZE];
uint8_t pNewKey=0;
static uint8_t Key_PrePro(void);
static uint8_t Get_Key(void);
/******************************************************************************
 **
 ** Function Name:	void delay_10us(uint16_t n) 
 ** Function : 延时10*n微秒 24MHz ,实际测试32us
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
void delay_30us(uint16_t n)  
{  
    uint16_t i=0;  
    uint8_t j=0;  
    for(i=0;i<n;i++)  
       for(j=0;j<2;j++){
        {
		 _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
        _nop_(); 
		 _nop_(); 
		} 
	}
}  
/******************************************************************************
 **
 ** Function Name:	void delay_10us(uint16_t n) 
 ** Function : 延时10*n微秒 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
void delay_20us(uint16_t n)   
{  
    uint16_t i=0;  
    for(i=0;i<n;i++) {
		  _nop_(); 
		  _nop_(); 
		  _nop_(); 
		  _nop_(); 
		  
     } 
}  

void delay_us(uint16_t n)  
{  
    uint16_t i=0;  
    for(i=0;i<n;i++) {
		   _nop_();  
		  
     } 
}  
/******************************************************************************
 ** \brief	 GPIO_Config
 ** \param [in] none
 **          GPIO中断功能
 ** \return  none
 ** \note  
 ******************************************************************************/
void GPIO_Config(void)
{
	
	
	GPIO_SET_MUX_MODE(P26CFG, GPIO_MUX_GPIO);		//??P13?GPIO??
	GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_6);			//???????
	P26 = 0 ;
	GPIO_SET_MUX_MODE(P25CFG, GPIO_MUX_GPIO);		//??P13?GPIO??
	GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_5);			//???????
	P25 = 0;
	
	
	/*
	(1)设置P23 IO功能
	*/
	
	GPIO_SET_MUX_MODE(P13CFG,GPIO_MUX_GPIO);   //开机按键  P13
	GPIO_ENABLE_INPUT(P1TRIS,GPIO_PIN_3); 
	GPIO_ENABLE_RD(P1RD,GPIO_PIN_3) ; 
   
	GPIO_SET_MUX_MODE(P15CFG, GPIO_MUX_GPIO);		//设置P15为GPIO模式--风速按键
	GPIO_ENABLE_INPUT(P1TRIS, GPIO_PIN_5);			//设置为输入模式
	GPIO_ENABLE_RD(P1RD, GPIO_PIN_5);				//开启下拉

	
	GPIO_SET_MUX_MODE(P14CFG,GPIO_MUX_GPIO);   //定时按键 P14
	GPIO_ENABLE_INPUT(P1TRIS,GPIO_PIN_4);      //设置为输入模式
	GPIO_ENABLE_RD(P1RD,GPIO_PIN_4);           //开启下拉

	GPIO_SET_MUX_MODE(P16CFG,GPIO_MUX_GPIO);   //虑网重置按键  P16
	GPIO_ENABLE_INPUT(P1TRIS,GPIO_PIN_6); 
	GPIO_ENABLE_RD(P1RD,GPIO_PIN_6) ;    
	/*
	(2)设置中断方式
	*/
	//GPIO_SET_INT_MODE(P16EICFG, GPIO_INT_FALLING);	//设置为下降沿中断模式 P16电源按键
	//GPIO_EnableInt(GPIO1, GPIO_PIN_6_MSK);			//开启P16中断 
	/*
	(3)设置中断优先级
	*/
//	IRQ_SET_PRIORITY(IRQ_P1, IRQ_PRIORITY_LOW);
	/*
	(4)开启总中断
	*/	
//	IRQ_ALL_ENABLE();
}
/******************************************************************************
 **
 ** Function Name:	void KEY_FUNCTION(void)
 ** Function : receive key input message 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
void KEY_FUNCTION(void)
{
	vu8 key=0;	
	key=Read_A_Key();	//得到键值
	switch(key)
		{				 
      //常规一般按键测试（按下键就起作用）：
			//case KEY_EVENT(TIMER_PRES,PRESS_DOWN):	//KEY3按下即有效，定时器键
			  case TIMER_PRES:
				BUZZER_Config();
			    delay_20us(10);
			    	IIC_Init_TM1650();
					delay_30us(100);			//需要延时一小段时间，否则开显示会无响应
					TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
				TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
				TM1650_Set(0x68,segNumber[9]);//初始化为5级灰度，开显示
		    	TM1650_Set(0x6A,segNumber[1]);//初始化为5级灰度，开显示
		    	TM1650_Set(0x6C,segNumber[1]);//初始化为5级灰度，开显示
		     	TM1650_Set(0x6E,segNumber[1]);//初始化为5级灰度，开显示
				break;
		//	case KEY_EVENT(POWER_PRES,PRESS_DOWN):	//KEY0按下即有效，电源键 
		    case POWER_PRES:
			    BUZZER_Config();
			    delay_20us(10);
				break;
			
		//	case KEY_EVENT(WIND_PRES,PRESS_DOWN):	//KEY1按下即有效，风速键
		    case WIND_PRES:
			    BUZZER_Config();
			    delay_20us(10);
				break;

		//	case KEY_EVENT(FILTER_PRES,PRESS_DOWN):	//KEY3按下即有效，虑网置换键
		    case FILTER_PRES:
			    BUZZER_Config();
			    delay_20us(10);
				break;
			//下面可自由增加其它按键测试，比如（仅举数例）：
	
			//case WKUP_PLUSKEY0_PRES:	//WKUP+KEY0组合按键（先按下WKUP再按下KEY0）
				
			//	break;
			
		
		}
	 //delay_ms(50);//这个延时值可以模拟CPU干其它工作的时间，可试着增大这个值，感受按键因来不及处理被缓存的效果 

}

/******************************************************************************
 **
 ** Function Name:	void KEY_FUNCTION(void)
 ** Function : receive key input message 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/

//硬件按键编码（为应用三行读键程序而准备）
//以战舰版的四键为例（最大暂支持16键，KeyS_Type定义为u32则可支持32键）
uint8_t GetHalKeyCode(void)
{
	uint8_t ktmp=0;
	if(KEY0_IN) 	   return POWER_PRES ;//ktmp|=1<<POWER_PRES;
	else if(KEY1_IN)   return WIND_PRES;	//ktmp|=1<<WIND_PRES;
	else if(KEY2_IN)   return TIMER_PRES;//ktmp|=1<<TIMER_PRES;    //if(!KEY2_IN) 	ktmp|=1<<TIMER_PRES;低电平有效
	else if(KEY3_IN)   return FILTER_PRES; //ktmp|=1<<TIMER_PRES;    //注意本键为高电平有效 
	return ktmp;
}

//********************************************************************************
static KeyS_Type KeyStable=0; //存有稳定(消除抖动后)的键态(读键前)

uint16_t Trg=0;  		//全局变量：存有本次读键时的按键触发状态
uint16_t Cont=0; 		//全局变量：存有本次读键时的实时键态
uint16_t KeyTime=0;  //全局变量：存有本次读键时当前键态持续的时长

/******************** 用户应用程序按键判断接口函数(请根据具体需求修改) *********************************/
//最终由GetAndSaveKey()在SYSTICK中调用，存入按键队列，主循环调用时请使用Read_A_Key()
//返回稳定的键值，用户程序直接处理事先定义的键值即可。

//可适应的按键类型如下：
//普通：按下即有效，不用等按键释放
//单击：按下再松开后有效
//双击：快速单击两次（两次单击之间时间不超过SHORT_TICKS）
//长按：按下超过规定的时间LONG_TICKS，超过后可连续输出，通过软件可设置间隔一定时间输出一次键值
//组合：双键组合（其实多键组合也可同理实现）
/**********************************************************************************/
//不使用组合按键等条件判断时，以下宏定义可删除
#define KEY0_ON 						(0x0001<<POWER_PRES)  //宏定义：按键未释放值
#define KEY1_ON 						(0x0001<<WIND_PRES)
#define KEY2_ON 						(0x0001<<TIMER_PRES)
#define WKUP_ON 						(0x0001<<TIMER_PRES)
#define KEY0_PRESSED 				(Trg==KEY0_ON)  //宏定义：按键触发值
#define KEY1_PRESSED 				(Trg==KEY1_ON)
#define KEY2_PRESSED 				(Trg==KEY2_ON)
#define WKUP_PRESSED 				(Trg==WKUP_ON)

/******************************************************************************
 **
 ** Function Name:	Read_A_Key(void)
 ** Function : Read PRESS key of value ,is real hardware key
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
uint8_t Read_A_Key(void)
{
	static uint8_t pReadKey=0;//读键指针
	if(pReadKey==KEYBUFFSIZE)pReadKey=0;//按键缓冲区循环使用
	if(pReadKey==pNewKey) return 0;//键已经取尽，返回0
	return New_KeyBuff[pReadKey++]; //存储 按键按下的键值
}

/******************************************************************************
 **
 ** Function Name:	void Key_Scan_Stick(void)
 ** Function : key scan ,得到实体按键输入的键值
             //按键扫描函数：一般由Systick中断服务程序以5ms一次的时间节拍调用此函数
			 //采用了键盘自适应变频扫描措施，在键盘正常稳定期间（非消抖期间）扫描频率降低以减少CPU资源占用
			//该函数将影响全局变量：消除抖动后的稳定键态值KeyStable及累计时长KeyTime
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
void Key_Scan_Stick(void)
{
	 uint8_t KeyValTemp;
	static uint8_t KeyValTempOld=0;
	static uint8_t debounce_cnt=0;
	static uint8_t debouncing=0;
	
	KeyTime++;//在稳定键态（包括无键）状态下，全局变量KeyTime是持续增加的
	if((!debouncing) && (KeyTime%NORMAL_SCAN_FREQ))//非消抖期间且累计计时不是6的倍数(即6*5＝30ms才扫描一次)						NORMAL_SCAN_FREQ=6
		return;	//则不扫描键盘直接返回，这里可调整NORMAL_SCAN_FREQ为其它数，估计最大到40即120ms扫描一次都问题不大的。
	
	KeyValTemp=GetHalKeyCode();//扫描键盘，得到实时键值（合并），可存16个键值（按下相应位为1松开为0）;
	
	if(KeyValTemp!=KeyStable) //如果当前值不等于旧存值，即键值有变化，处理按键按下消抖
	{
		debouncing=1;//标示为消抖期
		if(!(KeyValTemp^KeyValTempOld))//如果临时值不稳定（即新键值有变化）
		{
			debounce_cnt=0;
			KeyValTempOld=KeyValTemp;
		}
		else//临时值稳定
		{
		 if(++debounce_cnt >= DEBOUNCE_TICKS) 
		 {
			KeyStable = KeyValTemp;//键值更新为当前值.按键值 存储在KeyStable
			debounce_cnt = 0;//并复位消抖计数器.
			KeyTime=1; //新键值累计时长复位为1个时间单位
			debouncing=0;//消抖期结束
		 }
	  } 
	} 
	else //如果键值仍等于旧存值：
	{ //则复位消抖计数器（注意：只要消抖中途读到一次键值等于旧存值，消抖计数器均从0开始重新计数）.
		debounce_cnt = 0;
		KeyValTempOld=KeyValTemp;
	}
}
/******************************************************************************
 **
 ** Function Name:	void GetAndSaveKey(void)
 ** Function : 得到键值 
 			 //本函数由SYSTICK调用，在后台读键，如果有键值则存入按键缓冲区
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/



void GetAndSaveKey(void)
{
	uint8_t newkeytmp;
	if(KeyTime>=LONG_TICKS && KEY_RELEASED)
		{//键盘长时间闲置，直接返回（绝大部分时间基本都是这种状态，此举将大大节省CPU资源）
			KeyTime=LONG_TICKS;//此句防止KeyTime溢出(KeyTime由扫键程序累增)
			return; 
	  }
	Trg=KeyStable & (KeyStable ^ Cont); //调用三行读键方法,其实核心只有此行，使得Trg在某按键被按下后有且只有一次读取到对应位为1;
	//KeyStable --在按键扫描函数中---得到输入按键的-键值
	Cont=KeyStable; //键值
	newkeytmp=Key_PrePro();//从键预处理程序中读键值
	if(newkeytmp)//如果有新的键值
	{
		New_KeyBuff[pNewKey++]=newkeytmp;//存入按键缓冲区(pNewKey永远指向下一空位置),按键值存入Buffer
		if(pNewKey==KEYBUFFSIZE)pNewKey=0;//按键缓冲区循环使用
	}
}
/******************************************************************************
 **
 ** Function Name:	void KEY_FUNCTION(void)
 ** Function : receive key input message 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
//
//按键预处理程序:  允许对有强实时性需要的紧要按键无须排队优先执行，其效果有点儿类似回调函数
//本函数根据实际项目需求可以有三种具体实现模式选择：
//模式一：如果按键处理占用时间短（无延时语句、长循环等），按键要求强实时处理，则可以把所有的按键处理都放在这里
//        这样主循环就无须处理按键了（相当于使用中断服务的方式处理全部按键）
//模式二：对按键处理实时性要求不高，能够忍受一定程序的按键响应时延，可以把所有按键处理放在主循环中查询响应，
//        此时本函数可以简化为return Get_Key();
//模式三（前两种的折中方案）：强实时性需要紧急处理的键，直接在这里写执行代码，其它允许延时的键留待主循环查询处理，形式如下例所示。
uint8_t Key_PrePro(void)
{
	return Get_Key(); //模式二时，本函数简化到只须这一句，以下可全部删除。
	//uint8_t newkeytmp,ret=0;
	//newkeytmp=Get_Key();
	//switch(newkeytmp)
	//{
		//case KEY_EVENT(WIND_PRES,DOUBLE_CLICK)://KEY1双击，执行两灯同时翻转（仅作为示例）
		//	LED0=!LED0;LED1=!LED1; //控制两灯翻转
     // break;
   // default:
		//	ret=newkeytmp;
	//}
	//return ret;
}
/******************************************************************************
 **
 ** Function Name: Get_Key(void)
 ** Function : receive key input message 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
uint8_t Get_Key(void)
{
	uint8_t i,keyp=0;
/*按键的判断条件设定技巧：
	全局变量Trg中体现了对应按键的触发状态，在某按键被按下后有且只有一次读取到对应位为1;
	全局变量Cont则体现了当前按键的状态，处于按下的对应位为1，处于松开的对应位为0;
	而全局变量KeyTime里面，记录了当前键态持续的时间
*/
	
	//以下是按键判断，用户可根据需要随意添加或删改（注释掉的部分也可根据需要作为参考语句使用）
	
//注意：排在前面的判断条件具有高的优先级，一旦条件满足即刻返回，不再执行后续语句。
	if((Cont==(WKUP_ON+KEY0_ON)) && KEY0_PRESSED)	
		{ //WKUP+KEY0组合按键（先按下WKUP再按下KEY0）
			Get_Key_State(KB_CLR); //复位状态机，防止本按键对其干扰(本按键与状态机有冲突时请调用此句)
			return WKUP_PLUSKEY0_PRES;
		} 

//以下是使用状态机得到判断单击、双击、长按、保持等键码	
	for(i=0;i<KeyNumMax;i++)
	  {
			keyp=Get_Key_State(i);	
			if(keyp) return keyp; 
		}
	return keyp;
}




//***************************************************************
//  无须单击、双击、长按、连续保持等功能键的可以删除以下函数
//***************************************************************
/**　多功能按键状态机
  * 入口参数：实体按键编号（参数为KEYCLR用于复位状态机）
  * 返回：键值（按键事件值）＝(KeyNum+2)*10+键事件值; 其它返回0.
  */
#define THE_KEY_IS_OFF			(!(Cont & KeyOnCode))
#define THE_KEY_IS_ON				(Cont & KeyOnCode)
#define THE_KEY_PRESSED			((Trg & KeyOnCode) && (Cont & KeyOnCode))
/*********************************************************************
 *
 *Function Name:Get_Key_State(uint8_t KeyNum)
 *Function: 
 *Iinput Ref:keyNum --输入的实体按键数
 *Return Ref:返回按键的键值
 *
**********************************************************************/
uint8_t Get_Key_State(uint8_t KeyNum)
{
	//按键记忆状态(每字节低四位存state，高4位存repeat)
	static uint8_t KeyState[KeyNumMax];
   
	
	uint8_t KeyOnCode,keyHardNum;
	uint8_t i,state,repeat,event=0;
	keyHardNum = KeyNum;
	if(KeyNum==KB_CLR) //参数为KB_CLR时，则消除所有按键记忆状态
	{
		for(i=0;i<KeyNumMax;i++) KeyState[i]=0;
		return 0;
	}
	//KeyOnCode=(uint8_t)1<<KeyNum;//WT.EDIT 
	if(keyHardNum  ==0)KeyOnCode =0x01;
	else if(keyHardNum ==1)KeyOnCode =0x02;
	else if(keyHardNum ==2)KeyOnCode =0x04;
	else if(keyHardNum ==3)KeyOnCode =0x08;
	state=KeyState[KeyNum]&0x0f; //取相应的记忆状态值
	repeat=KeyState[KeyNum]>>4; //4个按键循环，查询按键，按下状态
	//Trg = 在按键扫描函数中，得到键值，列如;POWER_KEY 0X01
	if(Trg && (Trg!=KeyOnCode)) state=0; //出现其它键，则状态清0
	
	switch (state) 
	{
	case 0://状态0：键完全松开
		if(THE_KEY_PRESSED) 
			{	//初次按键触发并有效
			event = (uint8_t)PRESS_DOWN;
			repeat = 1;
			state = 1;//初次按键有效，变成状态1
			} 
			else //无效电平，即按键为松开状态
			  event = (uint8_t)NONE_PRESS;
	  break;

	case 1://状态1：初次按键触发并有效
		if(THE_KEY_IS_OFF) { //检测到按键松开		
			event = (uint8_t)PRESS_UP;
			state = 2;//按键按下后松开，变成状态2
      }
		 else if(KeyTime > LONG_TICKS) {//按键未松开，且持续时间已经超过LONG_TICKS
			event = (uint8_t)LONG_RRESS_START;
			state = 5;//即长按触发启动，变成状态5
		  }
		break;

	case 2://状态2：按键按下后已松开
		if(THE_KEY_PRESSED) { //再次检测到按下   
			event = (uint8_t)PRESS_DOWN;
			repeat++;//重按次数累计
			if(repeat == 2) state = 3;//如果重按次数等于2,则变成状态3
			} 
		else //持续松开
      	{
		   if(KeyTime > SHORT_TICKS)  
			  {//如果松开时间超过SHORT_TICKS，即一次按键结束
				 state = 0;//因按键松开时间超过SHORT_TICKS，则复位成状态0	
				 if(repeat==1) event=(uint8_t)SINGLE_CLICK;//次数为1的情况下触发单击事件
			   else if(repeat==2) event=(uint8_t)DOUBLE_CLICK;//重按次数为2的情况下触发双击事件
			  }
			} //隐含：如果松开时间还没有超过SHORT_TICKS，仍然维持状态2，有待后续判断		
		break;

	case 3://状态3：按下、松开、又按下（即第二次按下）				
		if(THE_KEY_IS_OFF)  //检测到按键松开
			{
				event = (uint8_t)PRESS_UP;
			  if(KeyTime < SHORT_TICKS) state = 2; //松开时间小于SHORT_TICKS，回到状态2 
			  else state = 0;//松开时间大于SHORT_TICKS，则变成状态0
		  }//隐含：如果仍按下则停留在状态3等待松开（第二次按下没有长按之说）
		break;

	case 5://状态5：长按触发已经启动
		if(THE_KEY_IS_ON)  //如果按键仍持续按下				
	     event = (uint8_t)LONG_PRESS_HOLD;//长按并保持按键事件成立
		else { //如果按键松开
			event = (uint8_t)PRESS_UP;
			state = 0; //则恢复到状态0
		  }
		break;
	}
	KeyState[KeyNum]=state; //保存相应的记忆状态值
	KeyState[KeyNum]+= repeat<<4;
	if(event>=(uint8_t)PRESS_DOWN) //设定只输出特殊功能键（修改此处可输出按下/松开等一般事件）
	{
		return KeyOnCode ; //WT.EDIT 返回按键，按下
	}
	if(event) //输出所有事件		
		return KEYOUT_BASE_DEF+event; //WT.EDIT 
		
	else return 0;
}
/******************************************************************************
 **
 ** Function Name:	void SysTick_Handler(void)
 ** Function : receive key input message 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
void SysTick_Handler(void)
{
	
	static uint16_t nTicks=0;
	nTicks ++ ;
	if(!(nTicks%3000)) nTicks=0; //300ms 赋初值一次

	if (( nTicks % TICKS_INTERVAL) == 0 )
	 {
		Key_Scan_Stick(); //每5ms扫键一次，读出消抖之后的按键值，以及按下的时间
		if ( nTicks % (TICKS_INTERVAL*12) == 0 ) 
			 GetAndSaveKey();//每60ms分析一次键值
	 }
}















