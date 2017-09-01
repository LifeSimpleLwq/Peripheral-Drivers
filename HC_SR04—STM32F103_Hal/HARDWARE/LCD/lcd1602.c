#include "LCD1602.h"	
#include "delay.h"
/************************************************************************************************
@f_name: void LCD1602_InitPort(void)
@brief:	 初始化硬件端口配置
@param:	 None
@return: None
************************************************************************************************/
void LCD1602_InitPort(void)
{  	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(LCD1602_GPIOCLK | RCC_APB2Periph_AFIO, ENABLE);	
		
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);    //把调试设置普通IO口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_CMD; 		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 	// 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 	// 输出的最大频率为50HZ
	GPIO_Init(LCD1602_GPIO, &GPIO_InitStructure);   		// 初始化GPIOB端口	   //配置1602液晶数据端口


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_DAT;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	 	// 开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 	// 输出的最大频率为50HZ
	GPIO_Init(LCD1602_GPIO, &GPIO_InitStructure);   				// 初始化GPIOB端口

	GPIO_Write(LCD1602_GPIO,0xffff);  //将GPIOB 16个端口全部置为高电  
}	
/************************************************************************************************
@f_name: void NOP(void)
@brief:	 延时函数
@param:	 None
@return: None
************************************************************************************************/ 
void NOP(void)
{ u16 i; for(i=0; i<100; i++);} 
/************************************************************************************************
@f_name: u8 lcd1602_bz(void)
@brief:	 测试LCD忙碌状态
@param:	 None
@return: 1：忙    0：闲
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
@brief:	 写入指令数据到LCD
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
@brief:	 写入数据到LCD
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
@brief:	 设置显示位置
@param:	 u8 pos显示位置		u8 row显示第几排
@return: None
************************************************************************************************/		
void lcd1602_pos(u8 pos,u8 row)
{
	switch(row)
	{
		case 1:lcd1602_wcmd(0x80|pos);break;  //DDRAM数据首行地址80H,次行地址0xc0	
		case 2:lcd1602_wcmd(0xc0|pos);break;  
		default:lcd1602_wcmd(0x80|pos); 	
	}
}
/************************************************************************************************
@f_name: void lcd1602_clr(void)
@brief:	 清屏
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
@brief:	 液晶初始化
@param:	 None
@return: None
************************************************************************************************/	
void lcd1602_init(void)		   
{                       
	lcd1602_wcmd(0x38);          //16*2显示，5*7点阵，8位数据
	delay_ms(5);
	lcd1602_wcmd(0x0c);          //显示开，关光标
	delay_ms(5);
	lcd1602_wcmd(0x06);          //移动光标
	delay_ms(5);
	lcd1602_wcmd(0x01);          //清除LCD的显示内容
	delay_ms(5);
}
/************************************************************************************************
@f_name: void strdis(u8 *p)	 
@brief:	 写字符串
@param:	 u8 *p 字符串首地址
@return: None
************************************************************************************************/
void strdis(u8 *p)	  
{			  					
	while(*p!='\0')			    // 判断是否为结束符
	lcd1602_wdat(*(p++));	   // 写入要显示的内容
}
	
	 
