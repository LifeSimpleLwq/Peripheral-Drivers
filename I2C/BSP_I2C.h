#ifndef __BSP_I2C_H
#define __BSP_I2C_H

#include "main.h"

#define delay_us(n)		BSP_Delay_us(n);

#ifdef _ENABLE_TEMP
//IO��������
#define SDA_IN()  		TEMP_SDA_IN()
#define SDA_OUT()		 	TEMP_SDA_OUT()

#define SDA_RESET			TEMP_SDA_RESET    		
#define SDA_SET    		TEMP_SDA_SET
#define SCL_RESET    	TEMP_SCL_RESET	
#define SCL_SET 			TEMP_SCL_SET

#define READ_SDA			TEMP_READ_SDA
#else 

#endif

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);								//����IIC��ʼ�ź�
void IIC_Stop(void);	  						//����IICֹͣ�ź�
void IIC_Send_Byte(uint8 txd);			//IIC����һ���ֽ�
void IIC_Ack(void);									//IIC����ACK�ź�
void IIC_NAck(void);								//IIC������ACK�ź�


uint8 IIC_Read_Byte(uint8 ack);			//IIC��ȡһ���ֽ�
uint8 IIC_Wait_Ack(void); 					//IIC�ȴ�ACK�ź�

void IIC_Write_One_Byte(uint8 daddr,uint8 addr,uint8 data);
uint8 IIC_Read_One_Byte(uint8 daddr,uint8 addr);	

#endif
















