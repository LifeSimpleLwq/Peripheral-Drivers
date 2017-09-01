#ifndef __BSP_RANGING_H
#define __BSP_RANGING_H

#include "SYS.H"

extern u8 SR04_Sign;

#define SR04_Trig_SET()			HAL_GPIO_WritePin(SR04_Trig_GPIO_Port,SR04_Trig_Pin,GPIO_PIN_SET);
#define SR04_Trig_RESET()		HAL_GPIO_WritePin(SR04_Trig_GPIO_Port,SR04_Trig_Pin,GPIO_PIN_RESET);
#define SR04_Echo_Check()		HAL_GPIO_ReadPin(SR04_Echo_GPIO_Port,SR04_Echo_Pin);

#define Delay_us(n)					BSP_Delay_us(n);



void Ranging_Text(void);
void Ranging_Calc(void);

#endif 


