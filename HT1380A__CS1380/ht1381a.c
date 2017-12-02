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
	 Write1380(0x80,50);//��ʼ��ʱ�� 30�룬BCD�룺30/10*16+30%10=48
     Write1380(0x82,89);//��ʼ��ʱ�� 59�֣�BCD�룺59/10*16+59%10=89
     Write1380(0x84,35);//��ʼ��ʱ�� 23ʱ��BCD�룺23/10*16+23%10=35
     Write1380(0x86,49);//��ʼ��ʱ�� 31�գ�BCD�룺31/10*16+31%10=49
     Write1380(0x88,6);//��ʼ��ʱ������6��BCD�룺6/10*16+6%10=6
     Write1380(0x8a,18);//��ʼ��ʱ�� 12�£�BCD�룺12/10*16+12%10=18
     Write1380(0x8c,17);//��ʼ��ʱ�� 11�꣬BCD�룺11/10*16+11%10=17
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

        rst=1;//ʹ��
        for(i=0;i<8;i++) //д��ַ�����ֽ�
        {
               io=(raddr&0x01)?1:0;
               sclk=1;//������д����
			   delay();
			   delay();

               sclk=0;
               raddr>>=1;//����ȡ��һλ
			   delay();
			   delay();
        }
		P1MODL = 0XA2;
        for(i=0;i<8;i++)//������
        {
               sclk=1;//�����ض�����
               rdat>>=1;//����һλ 			   
               if(io==1) rdat|=0x80;//�ӵ�λ��ʼ��ȡ�������
               //else rdat|=0x00;//�����0�����Բ�������
               sclk=0;
			   delay();
			   delay();
        }
        rst=0;//��ֹ
	    P1MODL = 0XAA;
         return rdat;
}

//д���ݺ���:
void Write1380(unsigned char waddr,unsigned char wdat)
{
        unsigned char i;
        rst=1;//ʹ��
        for(i=0;i<8;i++)
        {
               io=(waddr&0x01)?1:0;//��д��ַ���ӵ�λ��ʼд
               sclk=1;//������д����
			   delay();
			   delay();

               sclk=0;
               waddr>>=1;//����ȡ��һλ
			   delay();
			   delay();
        }
        for(i=0;i<8;i++)
        {
               io=(wdat&0x01)?1:0;//д���ݣ��ӵ�λ��ʼд
               sclk=1;//������д����
			   delay();
			   delay();

               sclk=0;
               wdat>>=1;//����ȡ��һλ
			   delay();
        }
        rst=0;//��ֹ
}

///**
//  * @brief  Read_Byte
//  * @note  	��ȡһ��byte
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
//  * @note  	��ȡһ��byte
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


