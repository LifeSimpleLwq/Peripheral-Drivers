#ifndef __DHT11_H
#define __DHT11_H 

#include "SYS.h"

//IO��������
#define DHT11_IO_IN()  { GPIOB->CRL &= 0X0FFFFFFF; \
												 GPIOB->CRL |= 8<<28; };
#define DHT11_IO_OUT() { GPIOB->CRL &= 0X0FFFFFFF; \
												 GPIOB->CRL |= 3<<28; };


u8 DHT11_Read_Data(uint8_t *temp,uint8_t *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ

u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Init(void);//��ʼ��DHT11
void DHT11_Rst(void);//��λDHT11 

void DHT11_DATA_PIN_RESET(void);
void DHT11_DATA_PIN_SET(void);


#endif















