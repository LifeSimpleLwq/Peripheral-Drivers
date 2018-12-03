#include "BSP_I2C.h"

/**
  * @brief  ����IIC��ʼ�ź�
  * @param  void  
  * @retval void
  */
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	SDA_SET;	  	  
	SCL_SET;
	delay_us(4);
 	SDA_RESET;		//START:when CLK is high,DATA change form high to low 
	delay_us(4);	
	SCL_RESET;		//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  

/**
  * @brief  ����IICֹͣ�ź�
  * @param  void  
  * @retval void
  */
void IIC_Stop(void)
{
	SDA_OUT();	//sda�����
	SCL_RESET;
	SDA_RESET;	//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	SCL_SET; 
	SDA_SET;		//����I2C���߽����ź�
	delay_us(4);							   	
}

/**
  * @brief  �ȴ�Ӧ���źŵ���
  * @param  void  
  * @retval 1������Ӧ��ʧ��
			0������Ӧ��ɹ�
  */      
uint8 IIC_Wait_Ack(void)
{
	uint8 ucErrTime = 0;
	SDA_IN();      //SDA����Ϊ����  
	
	SDA_SET;
	delay_us(1);	   
	SCL_SET;
	delay_us(1);	
		
	while (READ_SDA)
	{
		ucErrTime++;
		delay_us(1);
		
		if (ucErrTime > 25)
		{
			IIC_Stop();
			return 1;
		}
	}
	
	SCL_RESET;		//ʱ�����0 	   
	return 0;  
} 

/**
  * @brief  ����ACKӦ��
  * @param  void  
  * @retval void
  */
void IIC_Ack(void)
{
	SCL_RESET;
	SDA_OUT();
	SDA_RESET;
	delay_us(2);
	SCL_SET;
	delay_us(2);
	SCL_RESET;
}

/**
  * @brief 	������ACKӦ��		
  * @param  void  
  * @retval void
  */   
void IIC_NAck(void)
{
	SCL_RESET;
	SDA_OUT();
	SDA_SET;
	delay_us(2);
	SCL_SET;
	delay_us(2);
	SCL_RESET;
}					

/**
  * @brief 	IIC����һ���ֽ�,���شӻ�����Ӧ��  (��λ�ȷ�)
  * @param  void  
  * @retval 1����Ӧ��
						0����Ӧ��			
  */	  
void IIC_Send_Byte(uint8 txd)
{                        
	uint8 t;   
	
	SDA_OUT(); 	    
	SCL_RESET;	//����ʱ�ӿ�ʼ���ݴ���
	
	for (t = 0; t < 8; t++)
	{              
		if (( txd & 0x80) >> 7)
			SDA_SET;
		else
			SDA_RESET;
		
		txd <<= 1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		SCL_SET;
		delay_us(2); 
		SCL_RESET;	
		delay_us(2);
	}	 
} 

/**
  * @brief 	��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   		
  * @param  void  
  * @retval void
  */	    
uint8 IIC_Read_Byte(uint8 ack)
{
	uint8 i,receive = 0;
	
	SDA_IN();//SDA����Ϊ����
	
  for (i = 0; i < 8; i++ )
	{
    SCL_RESET; 
    delay_us(2);
		SCL_SET;
    receive <<= 1;
		
    if (READ_SDA)	receive++; 
		
		delay_us(1); 
  }					
	
	if (!ack)
			IIC_NAck();//����nACK
	else
			IIC_Ack(); //����ACK   
	
	return receive;
}









