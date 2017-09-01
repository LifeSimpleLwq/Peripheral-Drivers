#ifndef __SYS_H
#define __SYS_H

#include "stm32f1xx_hal.h"
#include "usart.h"
#include "tim.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;


#include "BSP_Ranging.h"

void BSP_Delay_us(uint32_t nus);

#endif 
