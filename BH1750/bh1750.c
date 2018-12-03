#include "BH1750.h"
#include "I2C.h"

static u8 BUF[8];		//接收数据缓存区

/**
  * @brief  发送读取指令
  * @param  REG_Address ： 读取指令
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
  * @brief  读取一次光照强度
  * @param  void
  * @retval None
  */
u8 *mread(void)
{
	u8 i;

	Single_Write_BH1750(0x01);
	Single_Write_BH1750(0x10);

	HAL_Delay(180);

	IIC_Start();	//起始信号

	IIC_Send_Byte(SlaveAddress+1);		//发送设备地址+读信号
	

	for (i=0; i<3; i++)		//连续读取6个地址数据，存储中BUF
	{
		BUF[i] = IIC_Read_Byte(1);		//BUF[0]存储0x32地址中的数据
		
		if (i < 2)
			IIC_Ack();		//发送nACK
		else
			IIC_NAck();		//发送ACK	
	}

	IIC_Stop();		//停止信号
	
	HAL_Delay(5);

	return BUF;
}

