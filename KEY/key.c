/**
	���ܣ�KEY-״̬�������������̰����ఴ������
	by: simpleСǿ��
	github:LifeSimpleLwq
	qq: 997950763 ����bug����ϵ���˸��ģ�Thanks
*/
#include "BSP/key.h"

static uint8 idata KeyBackup = 0;
static uint8 idata KeyNum = 0;

/**
  * @brief  KEY_Updata
  * @note   �������ʱ��<=10ms���͵�ƽ����
  * @retval NONE
  */
void KEY_Updata(void)
{
	KeyNum = 0;
	
	// �����������Ӱ���
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
		 * �˴���Ӱ�����������
		 */
	default :  KeyNum = 0;
		break;
	}
}

enum {Init1_State,Affirm1_State,Single1_State,Repeat1_State};
/**
  * @brief  KEY_Scan
  * @note   �������ʱ��<=10ms���͵�ƽ����
  * @retval NONE
  */	 
void KEY_Scan(uint8 k,uint8 n)
{	
	static uint8 Key1_StateValue;
	static uint8 Time = 0;
	uint8 Key1_Value = k,tmp = 20;		//��ȡ����1	
	KeyBackup = n;

	switch (Key1_StateValue)
	{
		case Init1_State:	//��ʼ��״̬
		{
			if(!Key1_Value)
			{
				Key1_StateValue = Affirm1_State;	//�´ν���ȷ��״̬
			}	
			else{Key1_StateValue = Init1_State;KeyBackup = 0;}	//��������ʼ��״̬
		}
		break;
		case Affirm1_State:	//ȷ��״̬
		{
			if(!Key1_Value)
			{
				Time = 0;
				Key1_StateValue = Single1_State;	//�´ν��뵥�δ���״̬ 
			}
			else{Key1_StateValue = Init1_State;KeyBackup = 0;}	//��������ʼ��״̬
		}
		break;
		case Single1_State:	//���δ���״̬
		{
			Time++;	//10ms ��һ��
			if(Key1_Value)	//��������ſ����ص���ʼ״̬
			{
				KeyNum = n;
				LcdTim = 0;		

				Key1_StateValue = Init1_State;
				KeyBackup = 0;				
			}
			else if(Time == 100)	//����ʱ�����1S
			{
				Time = 0;
				Key1_StateValue = Repeat1_State;
			} 
		}
		break;
		case Repeat1_State:	//����״̬
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



