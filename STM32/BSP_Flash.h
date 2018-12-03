#ifndef __BSP_FLASH_H__
#define __BSP_FLASH_H__

#include "main.h"

/*
 *	FLASH����ʹ�ü���˵��
 *	1������MCU���� STM32_FLASH_SIZE ��С���������Ŀ��ܵ���д��ʧ��
 *	2������ Flash_Text���в��������ܷ��д���ݡ�
 */
#define STM32_FLASH_SIZE 		128			// ��ѡSTM32��FLASH������С(��λΪK)
																		// STM32F105RB����ֻ��128k��ʵ����256k

// ----------------------------- addr ---------------------------------
//#define OTA_FLAG_ADDR		 		FLASH_BASE + 1024 * 14			// OTA����־λ
#define OTA_ADDR						FLASH_BASE + 1024 * 15			// OTA����־λ
#define DATA_ADDR				 		FLASH_BASE + 1024 * 120			// ע��Flash��С
#define OTA_FLAG_ADDR				FLASH_BASE + 1024 * 122

// ----------------------------- function --------------------------------
void BSP_FLASHWrite(uint32_t WriteAddr, uint16_t *pBuffer, uint16_t NumToWrite);

void BSP_FLASHRead(uint32_t ReadAddr, uint16_t *pBuffer, uint16_t NumToRead);
uint16_t BSP_FLASHReadHalfWord(uint32_t faddr);
	
void BSP_Flash_Init(void);


#endif

