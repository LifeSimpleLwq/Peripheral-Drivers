#include "BSP/ht1381a.h"

unsigned char Read1380(unsigned char raddr);
void Write1380(unsigned char waddr,unsigned char wdat);

void HT1381_Init(void)
{
	Write1380(0x8e,0);	
	Write1380(0x80,0);

	Write_Data();	
}

/**
  * @brief Read_Data
  * @note  
  * @retval NONE
  */
void Read_Data(void)
{
	uint8 sdasd = 0x03;

//	HT1381_Init();
	sdasd = Read1380(0x81);
	UART1_SendData(sdasd);
	sdasd = Read1380(0x83);
	UART1_SendData(sdasd);

//	Read_Byte(0x83,&numLcd.min);
//	Read_Byte(0x85,&numLcd.hour);
//
//	Read_Byte(0x87,&numLcd.day);
//	Read_Byte(0x89,&numLcd.month);
//	Read_Byte(0x8B,&numLcd.week);	
//	Read_Byte(0x8D,&numLcd.year);
}

/**
  * @brief Write_Data
  * @note  
  * @retval NONE
  */
void Write_Data(void)
{
	 Write1380(0x80,50);//初始化时间 30秒，BCD码：30/10*16+30%10=48
     Write1380(0x82,89);//初始化时间 59分，BCD码：59/10*16+59%10=89
     Write1380(0x84,35);//初始化时间 23时，BCD码：23/10*16+23%10=35
     Write1380(0x86,49);//初始化时间 31日，BCD码：31/10*16+31%10=49
     Write1380(0x88,6);//初始化时间星期6，BCD码：6/10*16+6%10=6
     Write1380(0x8a,18);//初始化时间 12月，BCD码：12/10*16+12%10=18
     Write1380(0x8c,17);//初始化时间 11年，BCD码：11/10*16+11%10=17
//	 Write_Byte(0x8C,numLcd.year);
//	 Write_Byte(0x8A,numLcd.week);
//	 Write_Byte(0x88,numLcd.month);
//	 Write_Byte(0x86,numLcd.day);
//
//	 Write_Byte(0x84,numLcd.hour);
//	 Write_Byte(0x82,numLcd.min);
//	 Write_Byte(0x80,numLcd.second);
}

unsigned char Read1380(unsigned char raddr)
{
        unsigned char i,rdat=0;

        rst=1;//使能
        for(i=0;i<8;i++) //写地址命令字节
        {
               io=(raddr&0x01)?1:0;
               sclk=1;//上升沿写数据
			   delay();
			   delay();

               sclk=0;
               raddr>>=1;//右移取下一位
			   delay();
			   delay();
        }
		P1MODL = 0XA2;
        for(i=0;i<8;i++)//读数据
        {
               sclk=1;//上升沿读数据
               rdat>>=1;//右移一位 			   
               if(io==1) rdat|=0x80;//从低位开始读取放入变量
               //else rdat|=0x00;//如果是0，可以不作处理
               sclk=0;
			   delay();
			   delay();
        }
        rst=0;//禁止
	    P1MODL = 0XAA;
         return rdat;
}

//写数据函数:
void Write1380(unsigned char waddr,unsigned char wdat)
{
        unsigned char i;
        rst=1;//使能
        for(i=0;i<8;i++)
        {
               io=(waddr&0x01)?1:0;//先写地址，从低位开始写
               sclk=1;//上升沿写数据
			   delay();
			   delay();

               sclk=0;
               waddr>>=1;//右移取下一位
			   delay();
			   delay();
        }
        for(i=0;i<8;i++)
        {
               io=(wdat&0x01)?1:0;//写数据，从低位开始写
               sclk=1;//上升沿写数据
			   delay();
			   delay();

               sclk=0;
               wdat>>=1;//右移取下一位
			   delay();
        }
        rst=0;//禁止
}

///**
//  * @brief  Read_Byte
//  * @note  	读取一个byte
//  * @retval NONE
//  */
//uint8 Read_Byte(uint8 Addr)
//{
//	uint8 i,Data = 0;
//
//	CE = 1;
//	for (i = 8; i > 0; i--)
//	{	
//		SDA = (Addr & 0x01)?1:0;
//		SCLK = 1;
//		delay();		
//
//		Addr >>= 1;
//		SCLK = 0;
//		delay();
//	}
//	for (i = 8; i > 0; i--)
//	{
//		SCLK = 1;
//		Data >>= 1;
//		delay();
//
//		SCLK = 0;	
//		if (SDA == 1)  Data |= 0X80;
//		delay();
//	}
//	CE = 0;
//
//	return Data;
//}
//
///**
//  * @brief  Write_Byte
//  * @note  	读取一个byte
//  * @retval NONE
//  */
//void Write_Byte(uint8 Addr, uint8 Data)
//{
//	uint8 i;
//			
//	CE = 1;
//	for (i = 8; i > 0; i--)
//	{		
//		SDA = (Addr & 0x01)?1:0;
//		SCLK = 1;
//		delay();
//
//		Addr >>= 1;
//		SCLK = 0;
//		delay();
//	}
//
//	for (i = 8; i > 0; i--)
//	{
//		SDA = (Data & 0x01)?1:0;
//		SCLK = 1;
//		delay();	
//
//		Data >>= 1;
//		SCLK = 0;
//		delay();	
//	}
//	CE = 0;	
//}


