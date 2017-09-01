#include "BSP_Main.h"
#include "BSP_Ranging.h"

/**
  * @brief  Ö÷º¯Êý
  * @param  void
  * @retval None
  */
void BSP_Main(void)
{
	printf("STM32F103C8T6 HAL_Project\r\n");
	printf("By£ºSimple\r\n");
	printf("Date£º8/30/2017\r\n");
	
	while(1)
	{
		Ranging_Text();
		HAL_Delay(1000);
	}
}



