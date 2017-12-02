#ifndef __HT1381A_H
#define __HT1381A_H

#include "BSP/sys.h"

#define delay()		{_nop_();_nop_();_nop_();_nop_();_nop_();}

void Read_Data(void);
void Write_Data(void);
void HT1381_Init(void);

void Write_Byte(uint8 Addr, uint8 Data);
uint8 Read_Byte(uint8 Addr);

#endif
