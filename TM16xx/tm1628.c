#include "BSP/Drives/tm1628.h"

/**
  * @brief ReadByte_1628
  * @note  读取一个数据, TM1628  450KHz, 低位先发
  * @retval NONE
  */
void ReadByte_1628(uint8 *Data)
{
	uint8 i,tmp = 0;
	*Data = 0;
	for(i = 0; i < 8; i++)
	{
		CLK = 0;
		_nop_();	 //  延时，等待电平稳定
		_nop_();
		tmp = DIO?1<<i:0;
		CLK = 1;
		*Data += tmp;
		_nop_();	
	}
}

/**
  * @brief Read_1628
  * @note  Data 按键保存，len 读取按键个数
  * @retval NONE
  */
void Read_1628(uint8 *Data,uint8 len)
{	
	STB = 0;
	WriteByte_1628(0x42); 	// 读按键

	DIO = 1;
	_nop_();
	while(len--)
	{
		ReadByte_1628(&Data[len]);
	}

	STB = 1;			
}

/**
  * @brief WriteByte_1628
  * @note  写入一个数据, TM1628  450KHz, 低位先发
  * @retval NONE
  */
void WriteByte_1628(uint8 Data)
{
	uint8 i;
	
	for (i = 8; i > 0; i--)
	{	
		CLK = 0;							
		DIO = (Data & 0x01)?1:0;	
		CLK = 1;
		Data >>= 1;
		_nop_();	
	}
}

/**
  * @brief Write_1628
  * @note  Data为0时，只发送addr
  * @retval NONE
  */
void Write_1628(uint8 addr,uint8 Data)
{
	STB = 0;
	WriteByte_1628(addr);
	if (Data != 0)	WriteByte_1628(Data);
	STB = 1;		
}




