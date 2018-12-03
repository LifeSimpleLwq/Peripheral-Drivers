#ifndef __MC_20_H
#define __MC_20_H

#include "SYS.H"
#include "BSP_IO.h"
#include "BSP_Flash.h"
#include "BSP_Motor.h"


#define true 1

extern uint8_t heartbeat[14];
extern uint8_t Parking_State[19];
extern u8 Read_State[19];
extern u8 Read_Data[18];
extern u8 Flash_Data[3];

void MC20_Init(void);			//  MC20_��ʼ��
bool MC20_Cmd( char len, char * reply1,char * reply2, uint32_t waittime);		// ��ȡ����֤����ָ��
void MC20_Send(uint8_t *str,char size,char len,char *str1,uint32_t watetime);  // ����ģ���ʼ��ATָ��

void MC20_heartbeat(void);		// ����MC20��������led״̬
u8 MC20_DataHandle(u8 len);		// �������״ָ̬��

#endif







