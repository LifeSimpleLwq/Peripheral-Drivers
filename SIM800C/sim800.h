#ifndef __SIM800_H
#define __SIM800_H

#include "SYS.H"

#define bool char
#define true 1

void SIM800_Init(void);
bool SIM800_Cmd( char len, char * reply1,char * reply2, u32 waittime);
void SIM800_Send(u8 *str,u8 length,char len,char *str1, u32 watetime);


#endif
