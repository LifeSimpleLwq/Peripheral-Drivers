#include "BSP_Main.h"
#include "BSP_Ranging.h"

/**
  * @brief  ������
  * @param  void
  * @retval None
  */
void BSP_Main(void)
{
	printf("STM32F103C8T6 HAL_Project\r\n");
	printf("By��Simple\r\n");
	printf("Date��8/30/2017\r\n");
	
	while(1)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		HAL_Delay(1000);
	}
}



