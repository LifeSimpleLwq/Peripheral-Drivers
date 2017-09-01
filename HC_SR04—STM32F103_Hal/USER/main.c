#include "LCD5110.h"
#include "ultrasonic.h"
#include "delay.h"
#include "usart.h"


/**
  * @brief  Ö÷º¯Êý
  * @param  void
  * @retval None
  */
int main()
{
	float temp;
	char DisNum[16];
	
	SystemInit();
	delay_init(72);
	//LCD5110_GPIOInit();
	Ultran_Init();
	uart_init(115200);
	
	while(1)
	{
			Ultra_Ranging(&temp);
			printf("%f\r\n",temp);
			
 			delay_ms(500);			
	}

}




