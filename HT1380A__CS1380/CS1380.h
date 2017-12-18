#ifndef __CS1380_H
#define __CS1380_H

#include "BSP/sys.h"

void week_Calc(void);
uint8 days_Calc(void);

void Read_Data(void);
void Write_Data(void);
void CS1380_Init(void);

void Write_Byte(uint8 Addr, uint8 Data);
uint8 Read_Byte(uint8 Addr);

#endif

