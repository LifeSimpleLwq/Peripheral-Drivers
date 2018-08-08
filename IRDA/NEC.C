#include "BSP/IRDA_PIN.h"

#define 	Tim2_100us	Fclk/1000/2/10	//  Fclk/1000/2 = 1ms	2个指令周期
#define		TH2_TMP		(65536-Tim2_100us)/256
#define		TL2_TMP		(65536-Tim2_100us)%256

static uint16 IRDA_conunt = 0;  // 计时器
static uint8 IRDA_time[33];	
static uint8 IRDA_data[4];
bit fCount_ok = 0,fDecode_ok = 0,IRDA_TMP = 1,fLong = 0; 	 

/**
  * @brief  IRDA_Check
  * @note   IRDA_PIN状态改变时判断接收情况
  * @retval NONE
  */
void IRDA_Check(void)
{
	if (IRDA_TMP != IRDA_PIN)		
	{	
		IRDA_TMP = IRDA_PIN;
		if (IRDA_PIN)
		{		
			if (fCount_ok) 
			{
				IRDA_decode();
				fCount_ok = 0;	
				fLong = 0;		
			}
			if (fDecode_ok)
			{
				if (fLong)	
				{
					fLong = 0;
					IRDA_conunt = 0;
					IRDA_decode();
				}											
			}	   		
		}
		else 
		{
			TR2 = 1;
			EX0_ISR();		
		}
	}
	
	if ( IRDA_conunt > 1500 ) 	
	{
		fDecode_ok = 0;
		IRDA_conunt = 0;
		UART1_SendData(0x66);
		TR2 = 0;		
	}	
}

/**
  * @brief  EX0_ISR
  * @note   IRDA_PIN 下降沿时保存一个周期时间
  * @retval NONE
  */
void EX0_ISR(void)
{
	static uint8 num = 0;
	static bit start_flag = 0;
		
	if(!start_flag)		start_flag = 1;
	else if(start_flag)
	{
		if(IRDA_conunt >= 90 && IRDA_conunt < 160)		// 判断是否为9.5ms+4.5ms引导码
		{	
			num = 0;
			fLong = 1;
		}

		IRDA_time[num] = IRDA_conunt;
		num++;
		if(33 == num)
		{
			num = 0;
			start_flag = 0;			// 第一次中断标志位
			fCount_ok = 1;			// 红外码接收完毕
		}
	}

	IRDA_conunt = 0;
}

/**
  * @brief  IRDA_decode
  * @note   IRDA_PIN Read data handle
  * @retval NONE
  */
void IRDA_decode(void)
{
	uint8 IR_byte;
	uint8 i = 0,j = 0;
	uint8 num = 1;

	for(i = 0; i < 4; i++)
	{
		IRDA_data[i] = 0;
		for(j = 0; j < 8; j++)
		{
			if(IRDA_time[num] > 18)	IR_byte |= 0x80;	// 低位在前

			if(j < 7)	IR_byte >>= 1;
			num++;			
		}
		IRDA_data[i] = IR_byte;
		IR_byte = 0x00;	
	}

	if(IRDA_data[2] == ~IRDA_data[3])
	{
		fDecode_ok = 1;
		UART1_SendData(IRDA_data[2]);
	}
}

/**
  * @brief  IRDA_Init
  * @note   TIM2 init 100us
  * @retval NONE
  */
void IRDA_Init(void)
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
	IRDA_conunt++;

	TH2 = TH2_TMP;
	TL2 = TL2_TMP;
	TF2 = 0;			//clear interrupt flag
}


















