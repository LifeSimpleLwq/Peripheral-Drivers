#include "BSP/sys.h"

/**
  *  该文件为8位机使用
  */

/**
  * @brief  ClearXRAM
  * @param  清除RAM
  * @retval None
  */
void ClearXRAM(void)
{
	uint8 xdata * data l_p_ucXdata;
	uint16 i;
	l_p_ucXdata = 0xff00;
	for(i = 0;i < 256;i++)
	{
		*(l_p_ucXdata++) = 0x00;	
	}
}

/**
  * @brief  delay_ms
  * @param  延时函数，具体根据MCU频率测定
  * @retval None
  */
void delay_ms(uint16 y)
{
	uint16 x;
	while(y--)
	{
		for (x = 0; x < 500; x++)
			_nop_(); // 2.1us
		CLRWDT = 1;		//clear watchdog
	}
}




