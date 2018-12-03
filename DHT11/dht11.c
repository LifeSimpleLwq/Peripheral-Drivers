#include "dht11.h"

/**
  * @brief  复位DHT11
  * @param  void
  * @retval None
  */
void DHT11_Rst(void)	   
{                 
	DHT11_IO_OUT(); 	//SET OUTPUT
	DHT11_DATA_PIN_RESET(); 	//拉低DQ
	HAL_Delay(20);    	//拉低至少18ms
	DHT11_DATA_PIN_SET(); 	//DQ=1 
	BSP_Delay_us(30);     	//主机拉高20~40us
}

/**
  * @brief  等待DHT11的回应
  * @param  void
  * @retval 1:未检测到DHT11的存在 or 0:存在
  */
u8 DHT11_Check(void) 	   
{   
	u8 retry=0;
	DHT11_IO_IN();	//SET INPUT	 
	
	while (HAL_GPIO_ReadPin(DHT11_DQ_GPIO_Port,DHT11_DQ_Pin) && retry<100)//DHT11会拉低40~80us
	{
		retry++;
		BSP_Delay_us(1);
	};	 
	
	if(retry>=100) return 1;
	else retry=0;
	
	while ((!HAL_GPIO_ReadPin(DHT11_DQ_GPIO_Port,DHT11_DQ_Pin)) && retry<100)//DHT11拉低后会再次拉高40~80us
	{
		retry++;
		BSP_Delay_us(1);
	};
	
	if(retry>=100) return 1;	    
	return 0;
}

/**
  * @brief  从DHT11读取一个位
  * @param  void
  * @retval 1/0
  */
u8 DHT11_Read_Bit(void) 			 
{
 	u8 retry=0;
	
	while(HAL_GPIO_ReadPin(DHT11_DQ_GPIO_Port,DHT11_DQ_Pin) && retry<100)//等待变为低电平
	{
		retry++;
		BSP_Delay_us(1);
	}
	
	retry=0;
	while(!HAL_GPIO_ReadPin(DHT11_DQ_GPIO_Port,DHT11_DQ_Pin) && retry<100)//等待变高电平
	{
		retry++;
		BSP_Delay_us(1);
	}
	
	BSP_Delay_us(40);//等待40us
	
	if(HAL_GPIO_ReadPin(DHT11_DQ_GPIO_Port,DHT11_DQ_Pin)) return 1;
	else return 0;		   
}

/**
  * @brief  从DHT11读取一个字节
  * @param  void
  * @retval 读到的数据
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
  * @brief  从DHT11读取一次数据
  * @param  temp:温度值(范围:0~50°)
	* @param	humi:湿度值(范围:20%~90%)
  * @retval 0,正常 or 1,读取失败
  */
u8 DHT11_Read_Data(u8 *temp,u8 *humi)    
{        
 	u8 buf[5];
	u8 i;
	
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)//读取40位数据
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
  * @brief  初始化DHT11的IO口 DQ 同时检测DHT11的存在
  * @note  temp:温度值(范围:0~50°)
					 humi:湿度值(范围:20%~90%)
  * @retval 1:不存在 or 0:存在    	 
  */
void DHT11_Init(void)
{	 
	DHT11_DATA_PIN_SET();//PB7 输出高
						
	DHT11_Rst();  //复位DHT11
	while( DHT11_Check() );//等待DHT11的回应
	
} 

/**
  * @brief  DHT11引脚拉高
	* @param	void
  * @retval NONE
  */
void DHT11_DATA_PIN_SET(void)
{
	HAL_GPIO_WritePin(DHT11_DQ_GPIO_Port,DHT11_DQ_Pin,GPIO_PIN_SET);
}

/**
  * @brief  DHT11引脚拉低
	* @param	void
  * @retval NONE
  */
void DHT11_DATA_PIN_RESET(void)
{
	HAL_GPIO_WritePin(DHT11_DQ_GPIO_Port,DHT11_DQ_Pin,GPIO_PIN_RESET); 
} 











