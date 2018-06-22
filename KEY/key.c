/**
	功能：KEY-状态机按键，长按短按，多按键驱动
	by: simple小强哥
	github:LifeSimpleLwq
	qq: 997950763 存在bug请联系本人更改，Thanks
*/
#include "BSP/key.h"

static uint8 idata KeyBackup = 0;
static uint8 idata KeyNum = 0;

/**
  * @brief  KEY_Updata
  * @note   建议调用时间<=10ms，低电平按下
  * @retval NONE
  */
void KEY_Updata(void)
{
	KeyNum = 0;
	
	// 根据需求增加按键
	if (!KeyBackup || KeyBackup == 1)	
		KEY_Scan(KEY1,1);			
	if (!KeyBackup || KeyBackup == 2)	
		KEY_Scan(KEY2,2);
	if (!KeyBackup || KeyBackup == 3)	
		KEY_Scan(KEY3,3);
	if (!KeyBackup || KeyBackup == 4)	
		KEY_Scan(KEY4,4);

	switch (KeyNum)
	{
		/**
		 * 此处添加按键动作程序
		 */
	default :  KeyNum = 0;
		break;
	}
}

enum {Init1_State,Affirm1_State,Single1_State,Repeat1_State};
/**
  * @brief  KEY_Scan
  * @note   建议调用时间<=10ms，低电平按下
  * @retval NONE
  */	 
void KEY_Scan(uint8 k,uint8 n)
{	
	static uint8 Key1_StateValue;
	static uint8 Time = 0;
	uint8 Key1_Value = k,tmp = 20;		//获取按键1	
	KeyBackup = n;

	switch (Key1_StateValue)
	{
		case Init1_State:	//初始化状态
		{
			if(!Key1_Value)
			{
				Key1_StateValue = Affirm1_State;	//下次进入确认状态
			}	
			else{Key1_StateValue = Init1_State;KeyBackup = 0;}	//否则进入初始化状态
		}
		break;
		case Affirm1_State:	//确认状态
		{
			if(!Key1_Value)
			{
				Time = 0;
				Key1_StateValue = Single1_State;	//下次进入单次触发状态 
			}
			else{Key1_StateValue = Init1_State;KeyBackup = 0;}	//否则进入初始化状态
		}
		break;
		case Single1_State:	//单次触发状态
		{
			Time++;	//10ms 加一次
			if(Key1_Value)	//如果按键放开，回到初始状态
			{
				KeyNum = n;
				LcdTim = 0;		

				Key1_StateValue = Init1_State;
				KeyBackup = 0;				
			}
			else if(Time == 100)	//按下时间等于1S
			{
				Time = 0;
				Key1_StateValue = Repeat1_State;
			} 
		}
		break;
		case Repeat1_State:	//连发状态
		{
			Time++;
			if(	Column == ColumnWorkNum) 	tmp = 100;
			if(tmp == Time)
			{
				Time = 0;
				KeyNum = n;
				LcdTim = 0;
			}
			else if(Key1_Value)
			{
				Key1_StateValue = Init1_State;
				KeyBackup = 0;
			}					
		}
		break;

		default:Key1_StateValue = Init1_State; KeyBackup = 0;
		break;
	} 
}



