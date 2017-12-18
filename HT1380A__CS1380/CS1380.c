#include "BSP/cs1380.h"

/**
	功能：HT1381A/CS1380/HT1380A驱动
	by: simple小强哥
	github:LifeSimpleLwq
	qq: 997950763 存在bug请练习本人更改，thanks
*/

/**
  * @brief  Data_Calc
  * @note   该IC不会根据日期自动调整星期，需手动调整
  * @retval NONE
  */
void week_Calc(void)
{
	int y;
	char m,d,w;
	
	y = numLcdTemp.year/16*10 + numLcdTemp.year%16;
	m = numLcdTemp.month/16*10 + numLcdTemp.month%16;
	d = numLcdTemp.day/16*10 + numLcdTemp.day%16;	

	if (m==1 || m==2)
	{
		m = (m==1?13:14);
		y--;
	}	
	w = (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400+1)%7;
	
	if (!w)	w = 7;
	numLcdTemp.week = w;
}



/**
  * @brief  Data_Calc
  * @retval NONE
  */
uint8 days_Calc(void)
{
	uint8 days,year;
	year = numLcdTemp.year/16*10 + numLcdTemp.year%16;
	switch (numLcdTemp.month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:days = 0x31; break;
		
		case 2: 
				if (((year%4 == 0) && (year%100 != 0)) || (year%400 == 0))	days = 0x29;
				else  days = 0x28;  break;
		case 4:
		case 6:
		case 9:
		case 11: days = 0x30;break;
		default: days = 0x32;break;
	}
	return days;
}


/**
  * @brief  cs1380_Init
  *	@note	时钟IC初始化
  * @retval NONE
  */
void CS1380_Init(void)
{
	Write_Byte(0x8e,0);	  	// 失能写保护
	Write_Byte(0x80,0);	  	// 使能晶振
	Write_Byte(0x8e,0x80);	// 使能写保护
}

/**
  * @brief	Read_Data
  *	@note	读取时钟数据
  * @retval NONE
  */
void Read_Data(void)
{
	numLcd.second = Read_Byte(0x81);
	numLcd.min	  = Read_Byte(0x83);
	numLcd.hour	  = Read_Byte(0x85);

	numLcd.day	  = Read_Byte(0x87);
	numLcd.month  = Read_Byte(0x89);
	numLcd.week	  = Read_Byte(0x8B);
	numLcd.year   = Read_Byte(0x8D);

	if (!SetMode)	   // 非设置模式
	{
		numLcdTemp.second = numLcd.second;	
		numLcdTemp.min = numLcd.min;
		numLcdTemp.hour = numLcd.hour;
		
		numLcdTemp.day = numLcd.day;
		numLcdTemp.month = numLcd.month;
		numLcdTemp.week = numLcd.week;
		numLcdTemp.year = numLcd.year;
	}
}

/**
  * @brief  Write_Data
  * @retval NONE
  */
void Write_Data(void)
{	
	Write_Byte(0x8e,0);	  // 失能写保护
	Write_Byte(0x8C,numLcdTemp.year);
	Write_Byte(0x8A,numLcdTemp.week);
	Write_Byte(0x88,numLcdTemp.month);
	Write_Byte(0x86,numLcdTemp.day);
	
	Write_Byte(0x84,numLcdTemp.hour);
	Write_Byte(0x82,numLcdTemp.min);
	Write_Byte(0x80,numLcdTemp.second);
	Write_Byte(0x8e,0x80);	  // 使能写保护
}


/**
  * @brief  Read_Byte
  * @retval NONE
  */
uint8 Read_Byte(uint8 Addr)
{
	uint8 i,Data = 0;

	CE = 1;
	for (i = 8; i > 0; i--)
	{	
		SDA = (Addr & 0x01)?1:0;
		SCLK = 1;
			
		Addr >>= 1;
		SCLK = 0;
	}
	P1MODH = 0x22;
	for (i = 8; i > 0; i--)
	{
		SCLK = 1;
		Data >>= 1;
		if (SDA == 1)  Data |= 0X80;

		SCLK = 0;	
	}
	CE = 0;
	P1MODH = 0xA2;
	return Data;
}

/**
  * @brief  Write_Byte
  * @retval NONE
  */
void Write_Byte(uint8 Addr, uint8 Data)
{
	uint8 i;
			
	CE = 1;
	for (i = 8; i > 0; i--)
	{		
		SDA = (Addr & 0x01)?1:0;
		SCLK = 1;

		Addr >>= 1;
		SCLK = 0;		
	}

	for (i = 8; i > 0; i--)
	{
		SDA = (Data & 0x01)?1:0;
		SCLK = 1;
	
		Data >>= 1;
		SCLK = 0;	
	}
	CE = 0;	
}


