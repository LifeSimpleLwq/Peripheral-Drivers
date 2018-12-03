#include "BH1750.h"
#include "I2C.h"

static u8 BUF[8];		//�������ݻ�����

/**
  * @brief  ���Ͷ�ȡָ��
  * @param  REG_Address �� ��ȡָ��
  * @retval None
  */
void Single_Write_BH1750(u8 REG_Address)
{
	IIC_Start();
	IIC_Send_Byte(SlaveAddress);
	IIC_Send_Byte(REG_Address);
	//  BH1750_SendByte(REG_data);
	IIC_Stop();
}

/**
  * @brief  ��ȡһ�ι���ǿ��
  * @param  void
  * @retval None
  */
u8 *mread(void)
{
	u8 i;

	Single_Write_BH1750(0x01);
	Single_Write_BH1750(0x10);

	HAL_Delay(180);

	IIC_Start();	//��ʼ�ź�

	IIC_Send_Byte(SlaveAddress+1);		//�����豸��ַ+���ź�
	

	for (i=0; i<3; i++)		//������ȡ6����ַ���ݣ��洢��BUF
	{
		BUF[i] = IIC_Read_Byte(1);		//BUF[0]�洢0x32��ַ�е�����
		
		if (i < 2)
			IIC_Ack();		//����nACK
		else
			IIC_NAck();		//����ACK	
	}

	IIC_Stop();		//ֹͣ�ź�
	
	HAL_Delay(5);

	return BUF;
}

