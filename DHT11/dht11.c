#include "dht11.h"

/**
  * @brief  ��λDHT11
  * @param  void
  * @retval None
  */
void DHT11_Rst(void)	   
{                 
	DHT11_IO_OUT(); 	//SET OUTPUT
	DHT11_DATA_PIN_RESET(); 	//����DQ
	HAL_Delay(20);    	//��������18ms
	DHT11_DATA_PIN_SET(); 	//DQ=1 
	BSP_Delay_us(30);     	//��������20~40us
}

/**
  * @brief  �ȴ�DHT11�Ļ�Ӧ
  * @param  void
  * @retval 1:δ��⵽DHT11�Ĵ��� or 0:����
  */
u8 DHT11_Check(void) 	   
{   
	u8 retry=0;
	DHT11_IO_IN();	//SET INPUT	 
	
	while (HAL_GPIO_ReadPin(DHT11_DQ_GPIO_Port,DHT11_DQ_Pin) && retry<100)//DHT11������40~80us
	{
		retry++;
		BSP_Delay_us(1);
	};	 
	
	if(retry>=100) return 1;
	else retry=0;
	
	while ((!HAL_GPIO_ReadPin(DHT11_DQ_GPIO_Port,DHT11_DQ_Pin)) && retry<100)//DHT11���ͺ���ٴ�����40~80us
	{
		retry++;
		BSP_Delay_us(1);
	};
	
	if(retry>=100) return 1;	    
	return 0;
}

/**
  * @brief  ��DHT11��ȡһ��λ
  * @param  void
  * @retval 1/0
  */
u8 DHT11_Read_Bit(void) 			 
{
 	u8 retry=0;
	
	while(HAL_GPIO_ReadPin(DHT11_DQ_GPIO_Port,DHT11_DQ_Pin) && retry<100)//�ȴ���Ϊ�͵�ƽ
	{
		retry++;
		BSP_Delay_us(1);
	}
	
	retry=0;
	while(!HAL_GPIO_ReadPin(DHT11_DQ_GPIO_Port,DHT11_DQ_Pin) && retry<100)//�ȴ���ߵ�ƽ
	{
		retry++;
		BSP_Delay_us(1);
	}
	
	BSP_Delay_us(40);//�ȴ�40us
	
	if(HAL_GPIO_ReadPin(DHT11_DQ_GPIO_Port,DHT11_DQ_Pin)) return 1;
	else return 0;		   
}

/**
  * @brief  ��DHT11��ȡһ���ֽ�
  * @param  void
  * @retval ����������
  */
u8 DHT11_Read_Byte(void)    
{        
	u8 i,dat;
	dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit();
	}						    
	return dat;
}

/**
  * @brief  ��DHT11��ȡһ������
  * @param  temp:�¶�ֵ(��Χ:0~50��)
	* @param	humi:ʪ��ֵ(��Χ:20%~90%)
  * @retval 0,���� or 1,��ȡʧ��
  */
u8 DHT11_Read_Data(u8 *temp,u8 *humi)    
{        
 	u8 buf[5];
	u8 i;
	
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)//��ȡ40λ����
		{
			buf[i] = DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humi = buf[0];
			*temp = buf[2];
		}
	}else return 1;
	
	return 0;	    
}

/**
  * @brief  ��ʼ��DHT11��IO�� DQ ͬʱ���DHT11�Ĵ���
  * @note  temp:�¶�ֵ(��Χ:0~50��)
					 humi:ʪ��ֵ(��Χ:20%~90%)
  * @retval 1:������ or 0:����    	 
  */
void DHT11_Init(void)
{	 
	DHT11_DATA_PIN_SET();//PB7 �����
						
	DHT11_Rst();  //��λDHT11
	while( DHT11_Check() );//�ȴ�DHT11�Ļ�Ӧ
	
} 

/**
  * @brief  DHT11��������
	* @param	void
  * @retval NONE
  */
void DHT11_DATA_PIN_SET(void)
{
	HAL_GPIO_WritePin(DHT11_DQ_GPIO_Port,DHT11_DQ_Pin,GPIO_PIN_SET);
}

/**
  * @brief  DHT11��������
	* @param	void
  * @retval NONE
  */
void DHT11_DATA_PIN_RESET(void)
{
	HAL_GPIO_WritePin(DHT11_DQ_GPIO_Port,DHT11_DQ_Pin,GPIO_PIN_RESET); 
} 











