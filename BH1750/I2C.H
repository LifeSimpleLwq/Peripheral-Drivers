#ifndef __I2C_H__
#define __I2C_H__

#include "SYS.H"

void IIC_Start(void);
void IIC_Stop(void);
u8 IIC_Wait_Ack(void);
void IIC_Send_Byte(u8 txd);
void IIC_NAck(void);
void IIC_Ack(void);
u8 IIC_Read_Byte(unsigned char ack);

#endif
