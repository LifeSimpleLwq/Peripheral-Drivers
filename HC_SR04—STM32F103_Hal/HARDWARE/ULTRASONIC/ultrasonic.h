#ifndef _ultrasonic_H
#define _ultrasonic_H
#include"sys.h"



//------------------------------------------------------------ÒÆÖ²ÐÞ¸ÄÇø-----------------------------------------------------------------------

#define ULTRA_PORT	GPIOB
#define ULTRA_CLK       RCC_APB2Periph_GPIOB
#define ULTRA_TRIG			GPIO_Pin_5
#define ULTRA_ECHO			GPIO_Pin_6

#define TRIG_Send  PBout(5)
#define ECHO_Reci  PBin(6)


//---------------------------------------------------------------------------------------------------------------------------------------------
void Ultran_Init(void);
void Ultra_Ranging(float *p);




#endif

