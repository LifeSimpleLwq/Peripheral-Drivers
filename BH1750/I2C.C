#include "I2C.h"

/**
  * @brief  主函数
  * @param  void
  * @retval None
  */
void SDA_IN(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  /*Configure GPIO pin : PtPin */

  GPIO_InitStruct.Pin = BSP_I2CSDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BSP_I2CSDA_GPIO_Port, &GPIO_InitStruct);
}

/**
  * @brief  主函数
  * @param  void
  * @retval None
  */
void SDA_OUT(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  /*Configure GPIO pin : PtPin */

  GPIO_InitStruct.Pin = BSP_I2CSDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
  * @brief  IIC初始化
  * @param  void
  * @retval None
  */
void IIC_Init(void)
{
}

/**
  * @brief  产生IIC起始信号
  * @param  void
  * @retval None
  */
void IIC_Start(void)
{
	SDA_OUT();

	HAL_GPIO_WritePin(BSP_I2CSDA_GPIO_Port, BSP_I2CSDA_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BSP_I2CSCL_GPIO_Port, BSP_I2CSCL_Pin, GPIO_PIN_SET);

	BSP_Delay_us(5);
	HAL_GPIO_WritePin(BSP_I2CSDA_GPIO_Port, BSP_I2CSDA_Pin, GPIO_PIN_RESET);
	//START:when CLK is high,DATA change form high to low 
	BSP_Delay_us(5);
	HAL_GPIO_WritePin(BSP_I2CSCL_GPIO_Port, BSP_I2CSCL_Pin, GPIO_PIN_RESET);
	//钳住I2C总线，准备发送或接收数据 
}

/**
  * @brief  产生IIC停止信号
  * @param  void
  * @retval None
  */
void IIC_Stop(void)
{
	HAL_GPIO_WritePin(BSP_I2CSDA_GPIO_Port, BSP_I2CSDA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BSP_I2CSCL_GPIO_Port, BSP_I2CSCL_Pin, GPIO_PIN_RESET);
	//START:when CLK is high,DATA change form high to low 

	BSP_Delay_us(5);
	HAL_GPIO_WritePin(BSP_I2CSDA_GPIO_Port, BSP_I2CSDA_Pin, GPIO_PIN_SET);
	BSP_Delay_us(5);
	HAL_GPIO_WritePin(BSP_I2CSCL_GPIO_Port, BSP_I2CSCL_Pin, GPIO_PIN_SET);
	//钳住I2C总线，准备发送或接收数据  	
}

/**
  * @brief  产生ACK应答
  * @param  void
  * @retval None
  */
void IIC_Ack(void)
{
	HAL_GPIO_WritePin(BSP_I2CSCL_GPIO_Port, BSP_I2CSCL_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BSP_I2CSDA_GPIO_Port, BSP_I2CSDA_Pin, GPIO_PIN_RESET);

	BSP_Delay_us(5);
	HAL_GPIO_WritePin(BSP_I2CSCL_GPIO_Port, BSP_I2CSCL_Pin, GPIO_PIN_SET);
	BSP_Delay_us(5);
	HAL_GPIO_WritePin(BSP_I2CSCL_GPIO_Port, BSP_I2CSCL_Pin, GPIO_PIN_RESET);
}

/**
  * @brief  不产生ACK应答
  * @param  void
  * @retval None
  */
void IIC_NAck(void)
{
	HAL_GPIO_WritePin(BSP_I2CSCL_GPIO_Port, BSP_I2CSCL_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BSP_I2CSDA_GPIO_Port, BSP_I2CSDA_Pin, GPIO_PIN_SET);

	BSP_Delay_us(5);
	HAL_GPIO_WritePin(BSP_I2CSCL_GPIO_Port, BSP_I2CSCL_Pin, GPIO_PIN_SET);
	BSP_Delay_us(5);
	HAL_GPIO_WritePin(BSP_I2CSCL_GPIO_Port, BSP_I2CSCL_Pin, GPIO_PIN_RESET);
}

/**
  * @brief  等待应答信号到来
  * @param  void
  * @retval 1，接收应答失败  or   0，接收应答成功
  */  
u8 IIC_Wait_Ack(void)
{
//	u8 ucErrTime=0;
	SDA_IN();
	//SDA设置为输入

	HAL_GPIO_WritePin(BSP_I2CSDA_GPIO_Port, BSP_I2CSDA_Pin, GPIO_PIN_SET);
	BSP_Delay_us(4);
	HAL_GPIO_WritePin(BSP_I2CSCL_GPIO_Port, BSP_I2CSCL_Pin, GPIO_PIN_SET);
	BSP_Delay_us(4);

//	while(HAL_GPIO_ReadPin(BSP_I2CSDA_GPIO_Port, BSP_I2CSDA_Pin))
//	{
//		ucErrTime++;
//		if(ucErrTime>250)
//		{
//			IIC_Stop();
//			return 1;
//		}
//	}

	HAL_GPIO_WritePin(BSP_I2CSCL_GPIO_Port, BSP_I2CSCL_Pin, GPIO_PIN_RESET);
	//时钟输出0
	SDA_OUT();
	return 0;
}

/**
  * @brief  IIC发送一个字节
  * @param  void
  * @retval 1，有应答	or 	0，无应答			  
  */ 
void IIC_Send_Byte(u8 txd)
{
	u8 t;

	for(t=0;t<8;t++)
	{
		if (((txd&0x80)>>7) != 0)
		{
			HAL_GPIO_WritePin(BSP_I2CSDA_GPIO_Port, BSP_I2CSDA_Pin, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(BSP_I2CSDA_GPIO_Port, BSP_I2CSDA_Pin, GPIO_PIN_RESET);
		}
		txd<<=1;
		BSP_Delay_us(5);
		HAL_GPIO_WritePin(BSP_I2CSCL_GPIO_Port, BSP_I2CSCL_Pin, GPIO_PIN_SET);
		BSP_Delay_us(5);
		HAL_GPIO_WritePin(BSP_I2CSCL_GPIO_Port, BSP_I2CSCL_Pin, GPIO_PIN_RESET);
		BSP_Delay_us(5);
	}
	IIC_Wait_Ack();
}

/**
  * @brief  读1个字节
  * @note  ack=1时，发送ACK，ack=0，发送nACK
  * @retval 1，有应答	or 	0，无应答			  
  */   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	unsigned char bit;

	SDA_IN();
	//SDA设置为输入

	HAL_GPIO_WritePin(BSP_I2CSDA_GPIO_Port, BSP_I2CSDA_Pin, GPIO_PIN_SET);
	for(i=0;i<8;i++ )
	{
		receive<<=1;
		HAL_GPIO_WritePin(BSP_I2CSCL_GPIO_Port, BSP_I2CSCL_Pin, GPIO_PIN_SET);

		BSP_Delay_us(5);

		if(HAL_GPIO_ReadPin(BSP_I2CSDA_GPIO_Port, BSP_I2CSDA_Pin) != 0)
			bit = 0X01;
		else
			bit = 0x00;

		receive |= bit;

		HAL_GPIO_WritePin(BSP_I2CSCL_GPIO_Port, BSP_I2CSCL_Pin, GPIO_PIN_RESET);
		BSP_Delay_us(5);
	}
	SDA_OUT();

	return receive;
}


