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

void MC20_Init(void);			//  MC20_初始化
bool MC20_Cmd( char len, char * reply1,char * reply2, uint32_t waittime);		// 读取、验证反馈指令
void MC20_Send(uint8_t *str,char size,char len,char *str1,uint32_t watetime);  // 发送模块初始化AT指令

void MC20_heartbeat(void);		// 发送MC20心跳包、led状态
u8 MC20_DataHandle(u8 len);		// 处理更改状态指令

#endif







