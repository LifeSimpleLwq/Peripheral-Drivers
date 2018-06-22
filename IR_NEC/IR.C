#include "BSP/IR.h"

#define 	Tim2_100us	Fclk/1000/2/10	//  Fclk/1000/2 = 1ms	2个指令周期
#define		TH2_TMP		(65536-Tim2_100us)/256
#define		TL2_TMP		(65536-Tim2_100us)%256

static uint16 IR_conunt = 0;  // 计时器
static uint8 IR_time[33];	
static uint8 IR_data[4];
bit conunt_ok = 0,decode_ok = 0,IR_TMP = 1,long_flag = 0; 	 

/**
  * @brief  IR_Check
  * @note   IR状态改变时判断接收情况
  * @retval NONE
  */
void IR_Check(void)
{
	if (IR_TMP != IR)		
	{	
		IR_TMP = IR;
		if (IR)
		{		
			if (conunt_ok) 
			{
				IR_decode();
				conunt_ok = 0;	
				long_flag = 0;		
			}
			if (decode_ok)
			{
				if (long_flag)	
				{
					long_flag = 0;
					IR_conunt = 0;
					IR_decode();
				}											
			}	   		
		}
		else 
		{
			TR2 = 1;
			EX0_ISR();		
		}
	}
	
	if ( IR_conunt > 1500 ) 	
	{
		decode_ok = 0;
		IR_conunt = 0;
		UART1_SendData(0x66);
		TR2 = 0;		
	}	
}

/**
  * @brief  EX0_ISR
  * @note   IR 下降沿时保存一个周期时间
  * @retval NONE
  */
void EX0_ISR(void)
{
	static uint8 num = 0;
	static bit start_flag = 0;
		
	if(!start_flag)		start_flag = 1;
	else if(start_flag)
	{
		if(IR_conunt >= 90 && IR_conunt < 160)		// 判断是否为9.5ms+4.5ms引导码
		{	
			num = 0;
			long_flag = 1;
		}

		IR_time[num] = IR_conunt;
		num++;
		if(33 == num)
		{
			num = 0;
			start_flag = 0;			// 第一次中断标志位
			conunt_ok = 1;			// 红外码接收完毕
		}
	}

	IR_conunt = 0;
}

/**
  * @brief  IR_decode
  * @note   IR Read data handle
  * @retval NONE
  */
void IR_decode(void)
{
	uint8 IR_byte;
	uint8 i = 0,j = 0;
	uint8 num = 1;

	for(i = 0; i < 4; i++)
	{
		IR_data[i] = 0;
		for(j = 0; j < 8; j++)
		{
			if(IR_time[num] > 18)	IR_byte |= 0x80;	// 低位在前

			if(j < 7)	IR_byte >>= 1;
			num++;			
		}
		IR_data[i] = IR_byte;
		IR_byte = 0x00;	
	}

	if(IR_data[2] == ~IR_data[3])
	{
		decode_ok = 1;
		UART1_SendData(IR_data[2]);
	}
}

/**
  * @brief  IR_Init
  * @note   TIM2 init 100us
  * @retval NONE
  */
void IR_Init(void)
{	
	TH2 = TH2_TMP;	
	TL2 = TL2_TMP;
	ET2 = 1;
	TR2 = 1;	
} 

/**
  * @brief  TIMER2_int
  * @note   TIM2 interrupt 100us
  * @retval NONE
  */
void TIMER2_int(void) interrupt 5
{
	IR_conunt++;

	TH2 = TH2_TMP;
	TL2 = TL2_TMP;
	TF2 = 0;			//clear interrupt flag
}


















