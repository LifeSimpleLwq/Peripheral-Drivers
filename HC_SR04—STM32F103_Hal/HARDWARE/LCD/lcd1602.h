#ifndef __LCD1602_H
#define __LCD1602_H		
#include "sys.h"


//�ܽŶ��壬��ֲ�޸���
//************************************************************************************************
#define RS  GPIO_Pin_3        
#define RW  GPIO_Pin_4 
#define EN  GPIO_Pin_5 

#define LCD1602_GPIO       GPIOB 
#define LCD1602_GPIOCLK    RCC_APB2Periph_GPIOB
#define	GPIO_Pin_DAT	   GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14| GPIO_Pin_15 
#define	GPIO_Pin_CMD	   GPIO_Pin_3| GPIO_Pin_4 |GPIO_Pin_5
#define	GPIO_BUSY  		   GPIO_Pin_15

#define LCD1602WriteData(x)    {GPIOB->BSRR = x<<8 & 0xff00;GPIOB->BRR = ((~x)<<8) & 0xff00;}
#define BUSY        			GPIO_ReadInputDataBit(LCD1602_GPIO,GPIO_BUSY)

#define    LCD_RS(x)  x ? GPIO_SetBits(LCD1602_GPIO, RS): GPIO_ResetBits(LCD1602_GPIO, RS)
#define    LCD_RW(x)  x ? GPIO_SetBits(LCD1602_GPIO, RW): GPIO_ResetBits(LCD1602_GPIO, RW)
#define    LCD_EN(x)  x ? GPIO_SetBits(LCD1602_GPIO, EN): GPIO_ResetBits(LCD1602_GPIO, EN)

u8 lcd1602_bz(void);         //����Ƿ�æ
void NOP(void);				//��ʱ����
void lcd1602_init(void);	//Һ����ʼ��
void lcd1602_pos(u8 pos,u8 row);  //������ʾλ��
void lcd1602_wdat(u8 dat);		  //д����
void lcd1602_wcmd(u8 cmd);		  //дָ��

void LCD1602_InitPort(void);	 //�˿ڳ�ʼ��
void lcd1602_clr(void);			 //����
void strdis(u8 *p);              //д�ַ���
//*************************************************************************************************
#endif


