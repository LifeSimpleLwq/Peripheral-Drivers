#include "BSP_Ranging.h"

u8 SR04_Sign = 0;

/**
  * @brief  测量一次距离
  * @param  void
  * @retval None
  */
void Ranging_Text(void)
{
		SR04_Sign = 0;
		
		SR04_Trig_RESET();
		SR04_Trig_SET();
		Delay_us(10);
		SR04_Trig_RESET();
		
		//HAL_TIM_Base_Start_IT(&htim3);
		while( !( HAL_GPIO_ReadPin(SR04_Echo_GPIO_Port,SR04_Echo_Pin) ) )
		{
			//printf("pin = %d SR04_Sign = %d\r\n",HAL_GPIO_ReadPin(SR04_Echo_GPIO_Port,SR04_Echo_Pin),SR04_Sign);
		}			// 等待Echo高电平
	//	HAL_TIM_Base_Stop_IT(&htim3);
		//printf("readpin = %d SR04_Sign = %d\r\n",HAL_GPIO_ReadPin(SR04_Echo_GPIO_Port,SR04_Echo_Pin),SR04_Sign);
 	
		if (!SR04_Sign) 
		{
			htim3.Instance->CNT = 0;
			HAL_TIM_Base_Start_IT(&htim3);
			printf("start ");
		}
		else 
		{
			HAL_Delay(3000);
		}
}

/**
  * @brief  计算超声波测距距离
  * @param  void
  * @retval None
  */
void Ranging_Calc(void)
{
		u16 num ;
		HAL_TIM_Base_Stop_IT(&htim3);
		num = htim3.Instance->CNT;
		htim3.Instance->CNT = 0;
		printf("\t CNT = %d\r\n",num);
}


