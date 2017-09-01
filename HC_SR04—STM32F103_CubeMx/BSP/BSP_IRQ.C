#include "BSP_IRQ.h"
#include "BSP_Ranging.h"

/**
  * @brief  外部中断
  * @param  GPIO_Pin
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch (GPIO_Pin)
	{
		case SR04_Echo_Pin:	Ranging_Calc(); 
												break;	
		
		default : break;
	}
}

u16 tim_num = 0;
/**
  * @brief  定时器中断
  * @param  GPIO_Pin
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		if (tim_num++ >= 2)
		{
			SR04_Sign = 1;
			tim_num = 0;
			
			HAL_TIM_Base_Stop_IT(&htim3);
			printf("没有检测到回拨\r\n");
			
		}
}

