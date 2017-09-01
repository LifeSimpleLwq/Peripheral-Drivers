#include "LCD1602.h"	
#include "delay.h"
/************************************************************************************************
@f_name: void LCD1602_InitPort(void)
@brief:	 ��ʼ��Ӳ���˿�����
@param:	 None
@return: None
************************************************************************************************/
void LCD1602_InitPort(void)
{  	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(LCD1602_GPIOCLK | RCC_APB2Periph_AFIO, ENABLE);	
		
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);    //�ѵ���������ͨIO��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_CMD; 		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 	// �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 	// ��������Ƶ��Ϊ50HZ
	GPIO_Init(LCD1602_GPIO, &GPIO_InitStructure);   		// ��ʼ��GPIOB�˿�	   //����1602Һ�����ݶ˿�


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_DAT;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	 	// ��©���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 	// ��������Ƶ��Ϊ50HZ
	GPIO_Init(LCD1602_GPIO, &GPIO_InitStructure);   				// ��ʼ��GPIOB�˿�

	GPIO_Write(LCD1602_GPIO,0xffff);  //��GPIOB 16���˿�ȫ����Ϊ�ߵ�  
}	
/************************************************************************************************
@f_name: void NOP(void)
@brief:	 ��ʱ����
@param:	 None
@return: None
************************************************************************************************/ 
void NOP(void)
{ u16 i; for(i=0; i<100; i++);} 
/************************************************************************************************
@f_name: u8 lcd1602_bz(void)
@brief:	 ����LCDæµ״̬
@param:	 None
@return: 1��æ    0����
************************************************************************************************/ 
u8 lcd1602_bz(void)
{                        
	u8 x;
	LCD_RS(0);  
	LCD_RW(1);  
	LCD_EN(1); 
	NOP();
	NOP();
	x = BUSY ;
	LCD_EN(0); 
	return x; 
}
/************************************************************************************************
@f_name: lcd1602_wcmd(int cmd)
@brief:	 д��ָ�����ݵ�LCD
@param:	 u8 cmd
@return: None
************************************************************************************************/ 
void lcd1602_wcmd(u8 cmd)
{                          
	while(lcd1602_bz());
	LCD_RS(0); 
	LCD_RW(0); 
	LCD_EN(0); 
	NOP();
	NOP(); 
	LCD1602WriteData(cmd);
	NOP();
	NOP();
	LCD_EN(1); 
	NOP();
	NOP();
	LCD_EN(0); 
}	
/************************************************************************************************
@f_name: void lcd1602_wdat(u8 dat)
@brief:	 д�����ݵ�LCD
@param:	 u8 dat
@return: None
************************************************************************************************/ 
void lcd1602_wdat(u8 dat) 
{                         
	while(lcd1602_bz());
	LCD_RS(1); //= 1;
	LCD_RW(0); //= 0;
	LCD_EN(0); //= 0;
	LCD1602WriteData(dat);
	NOP();
	NOP();
	LCD_EN(1);// = 1;
	NOP();
	NOP();
	LCD_EN(0);// = 0; 
}
/************************************************************************************************
@f_name: void lcd1602_pos(u8 pos,u8 row)
@brief:	 ������ʾλ��
@param:	 u8 pos��ʾλ��		u8 row��ʾ�ڼ���
@return: None
************************************************************************************************/		
void lcd1602_pos(u8 pos,u8 row)
{
	switch(row)
	{
		case 1:lcd1602_wcmd(0x80|pos);break;  //DDRAM�������е�ַ80H,���е�ַ0xc0	
		case 2:lcd1602_wcmd(0xc0|pos);break;  
		default:lcd1602_wcmd(0x80|pos); 	
	}
}
/************************************************************************************************
@f_name: void lcd1602_clr(void)
@brief:	 ����
@param:	 None
@return: None
************************************************************************************************/
void lcd1602_clr(void)
{
	lcd1602_wcmd(0x01);
	delay_ms(1);
} 
/************************************************************************************************
@f_name: void lcd1602_init(void)		
@brief:	 Һ����ʼ��
@param:	 None
@return: None
************************************************************************************************/	
void lcd1602_init(void)		   
{                       
	lcd1602_wcmd(0x38);          //16*2��ʾ��5*7����8λ����
	delay_ms(5);
	lcd1602_wcmd(0x0c);          //��ʾ�����ع��
	delay_ms(5);
	lcd1602_wcmd(0x06);          //�ƶ����
	delay_ms(5);
	lcd1602_wcmd(0x01);          //���LCD����ʾ����
	delay_ms(5);
}
/************************************************************************************************
@f_name: void strdis(u8 *p)	 
@brief:	 д�ַ���
@param:	 u8 *p �ַ����׵�ַ
@return: None
************************************************************************************************/
void strdis(u8 *p)	  
{			  					
	while(*p!='\0')			    // �ж��Ƿ�Ϊ������
	lcd1602_wdat(*(p++));	   // д��Ҫ��ʾ������
}
	
	 
