#ifndef	_LCD5110_H_
#define	_LCD5110_H_
#include "sys.h"
#include"FONT.H"


#define RST    GPIO_Pin_3        
#define CE     GPIO_Pin_4 
#define DC     GPIO_Pin_5 
#define DIN    GPIO_Pin_6        
#define CLK    GPIO_Pin_7 
//#define LIGHT  


#define LCD5110_GPIO       GPIOB 
#define LCD5110_GPIOCLK    RCC_APB2Periph_GPIOB
#define	GPIO_Pin_DAT	   GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7  

#define    LCD_RST(x)  x ? GPIO_SetBits(LCD5110_GPIO, RST): GPIO_ResetBits(LCD5110_GPIO, RST)
#define    LCD_CE(x)   x ? GPIO_SetBits(LCD5110_GPIO, CE) : GPIO_ResetBits(LCD5110_GPIO, CE)
#define    LCD_DC(x)   x ? GPIO_SetBits(LCD5110_GPIO, DC) : GPIO_ResetBits(LCD5110_GPIO, DC)     
#define    LCD_DIN(x)  x ? GPIO_SetBits(LCD5110_GPIO, DIN): GPIO_ResetBits(LCD5110_GPIO, DIN) 
#define    LCD_CLK(x)  x ? GPIO_SetBits(LCD5110_GPIO, CLK): GPIO_ResetBits(LCD5110_GPIO, CLK) 



void LCD5110_PortInit(void);
void LCD5110Wbyte(u8 dt, u8 command);
void LCD5110SetPos(u8 x, u8 y);
void LCD5110Clear(void);
void LCD5110WriteNum(u8 row, u8 page,u8 c) ;
void LCD_write_hanzi(u8 row, u8 page,u8 c) ;
void LCD5110_Init(void);




 #endif
