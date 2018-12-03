#ifndef __DHT11_H
#define __DHT11_H 

#include "SYS.h"

//IO方向设置
#define DHT11_IO_IN()  { GPIOB->CRL &= 0X0FFFFFFF; \
												 GPIOB->CRL |= 8<<28; };
#define DHT11_IO_OUT() { GPIOB->CRL &= 0X0FFFFFFF; \
												 GPIOB->CRL |= 3<<28; };


u8 DHT11_Read_Data(uint8_t *temp,uint8_t *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位

u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Init(void);//初始化DHT11
void DHT11_Rst(void);//复位DHT11 

void DHT11_DATA_PIN_RESET(void);
void DHT11_DATA_PIN_SET(void);


#endif















