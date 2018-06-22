#include "BSP/sys.h"


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




