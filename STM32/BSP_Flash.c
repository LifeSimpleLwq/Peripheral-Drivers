#include "BSP_flash.h"

#define STM_SECTOR_SIZE 		1024 // �ֽ�
#define Page_SIZE 	STM_SECTOR_SIZE		// FLASHһҳ�洢�ռ��С
#define Page_Num		Page_SIZE/2			// ��2���ֽ�Ϊ��λ��ע�⣬�˴���д������ݿ���й�

// ----------------------------------- Read flash -----------------------------
/**
  * @brief  ��ȡָ����ַ����
  * @param  faddr :��ȡ�ĵ�ַ, �õ�ַ������ 4 �ı���					  
  * @retval ��ȡ������
  */
uint16_t BSP_FLASHReadHalfWord(uint32_t faddr)
{
	return *(__IO uint16_t*)faddr; 
}

/**
  * @brief  ��ָ����ַ��ʼ����ָ�����ȵ�����
  * @param  ReadAddr: ��ʼ��ַ
  * @param  pBuffer: �������ݵĻ�����
  * @param  NumToWrite: �������ݵĴ�С(��λ: ����)
  * @retval None
  */
void BSP_FLASHRead(uint32_t ReadAddr, uint16_t *pBuffer, uint16_t NumToRead)   	
{
	uint16_t i;

	for(i = 0; i < NumToRead; i++)
	{
		pBuffer[i] = BSP_FLASHReadHalfWord(ReadAddr);		// ��ȡ 2 ���ֽ�	
		ReadAddr += 2;																	// ƫ�� 2 ���ֽ�	
	}
}

// ---------------------------------- Write flash --------------------------
/**
  * @brief  ������д��, ��λ������
  * @param  WriteAddr: ��ʼ��ַ
  * @param  pBuffer: д�����ݵĻ�����
  * @param  NumToWrite: д�����ݵĴ�С(��λ: ��)
  * @retval None
  */
static void BSP_FLASHWrite_NoCheck(uint32_t WriteAddr, uint16_t *pBuffer, uint16_t NumToWrite)   
{
	uint16_t i;
	
	for(i = 0; i < NumToWrite; i++)
	{
		FLASH_ProgramHalfWord(WriteAddr, pBuffer[i]);
		WriteAddr += 2;														// ��ַ����2.	
	}  
}

/**
  * @brief  �� Flash д����(һҳд��1024�ֽ�)
  * @param  WriteAddr: ��ʼ��ַ
  * @param  pBuffer: д�����ݵĻ�����  
  * @param  NumToWrite: д�����ݵĴ�С(��λ: ��)  
  * @retval None	  
  */
void BSP_FLASHWrite(uint32_t WriteAddr, uint16_t *pBuffer, uint16_t NumToWrite)	
{	
	uint32_t secpos;		// ������ַ
	
	uint32_t offaddr;
	
	uint16_t Numsize;	

	uint16_t secoff;		// ������ƫ�Ƶ�ַ(16λ����)
	
	uint16_t secremain;	// ������ʣ���ַ(16λ����)
	
 	uint16_t i;  
	
	uint16_t BSP_FLASHBUF[Page_Num];	
	

	if(WriteAddr < FLASH_BASE || (WriteAddr >= (FLASH_BASE + STM_SECTOR_SIZE * STM32_FLASH_SIZE)))
		return;		// �Ƿ���ַ  
	
	Numsize = NumToWrite;  // д���ֽ� 
	
	// ����д��ĳ���  
	offaddr = WriteAddr - FLASH_BASE;  	// ʵ��ƫ�Ƶ�ַ. 
	
	secpos = offaddr / Page_SIZE;    					// ������ַ 	
	
	secoff = (offaddr % Page_SIZE) / 2;   		// �������ڵ�ƫ��( 2���ֽ�Ϊ������λ. )	
	
	secremain = Page_Num - secoff;		  			// ����ʣ��ռ��С
	

	if(Numsize <= secremain)	secremain = Numsize;  // �����ڸ�������Χ
	
	FLASH_Unlock();		// ����
	
	while(1) 
	{
		// ������������������
		BSP_FLASHRead (secpos * Page_SIZE + FLASH_BASE, BSP_FLASHBUF, Page_Num);				

		for (i = 0; i < secremain; i++)		// У������	
		{
			if (BSP_FLASHBUF[secoff + i] != 0xFFFF)
				break;		// ��Ҫ����			
		}

		if (i < secremain)		// ��Ҫ����			
		{
			FLASH_ErasePage(secpos * Page_SIZE + FLASH_BASE); 	// �����������
			printf("Erase\r\n");
		
			for (i = 0; i < secremain; i++)
			{
				BSP_FLASHBUF[i + secoff] = pBuffer[i]; 
			}
			
			BSP_FLASHWrite_NoCheck(secpos * Page_SIZE + FLASH_BASE, BSP_FLASHBUF, Page_Num);  // д���������� 	
		}
		else
		{
			BSP_FLASHWrite_NoCheck(WriteAddr, pBuffer, secremain);
		}

		// д�Ѿ������˵�,ֱ��д������ʣ������.
		if(Numsize == secremain)
			break;		// д�������
		else				// д��δ����		
		{
			secpos++;  		// ������ַ��1  
			
			secoff = 0;  	// ƫ��λ��Ϊ0 	 
			
			pBuffer += secremain;					// ָ��ƫ��
			
			WriteAddr += secremain * 2;		// д��ַƫ��	   
			
			Numsize -= secremain;					// �ֽ�(16λ)���ݼ�
			
			if(Numsize > (Page_Num))
				secremain = Page_Num;				// ��һ����������д����	
			else
				secremain = Numsize;					// ��һ����������д����	
		}	 
	}
	
	FLASH_Lock();	// ����
}



// ---------------------------- Init ----------------------------------
/**
  *	@brief  ���ع�ѡ�������ز��֣��ظ��������Σ����ɲ���flashд���Ƿ�ɹ�
	* @note 	�ϵ�ʱ����ȡflash����
  * @retval None
  */
void BSP_Flash_Init(void)
{
	uint16 flag = 0;
	uint16 Write_Buf;
	
	flag = BSP_FLASHReadHalfWord(DATA_ADDR);
	
	if (flag == 0xffff)		// �����ϵ�
	{
		printf("\r\n");
		printf("----- One Download -----\r\n");
		printf("\r\n");
		
		flag = 0x5555;
		BSP_FLASHWrite(DATA_ADDR, &flag, 1);
		
		// У��
		flag = BSP_FLASHReadHalfWord(DATA_ADDR);

		if (flag == 0x5555)		printf("Write flash success!\r\n");
		else 		printf("Write flash fail!\r\n");
		
		// Add save flash data , write flash
		
		Write_Buf  = BSP_FLASHReadHalfWord(DATA_ADDR + 2);
		Write_Buf &= 0xff00;
		
#if (MOTOR_VERSION == 1)	
		AdcAddValue = 50;
		Write_Buf += AdcAddValue;			
#endif 
#if (MOTOR_VERSION == 2) 
		AdcAddValue = 20;
		Write_Buf += AdcAddValue;	
#endif 				

		BSP_FLASHWrite(DATA_ADDR + 2, &Write_Buf, 1);	
	}
	else 	
	{
		Write_Buf  = BSP_FLASHReadHalfWord(DATA_ADDR + 2);	
		AdcAddValue = Write_Buf;
	}
	printf("AdcAddValue = %d\r\n\r\n",AdcAddValue);
		
	flag = FLAG_FIRMWARE;
	BSP_FLASHWrite(OTA_FLAG_ADDR, &flag, 1);
	flag = BSP_FLASHReadHalfWord(OTA_FLAG_ADDR);
	printf("flag = %x\r\n",flag);
}

