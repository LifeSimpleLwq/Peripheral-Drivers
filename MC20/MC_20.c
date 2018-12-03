#include "mc_20.h"



// TCP ע��ATָ��
uint8_t AT[] = "+++";
uint8_t AT1[] = "AT";
uint8_t AT_CPIN[] = "AT+CPIN?";  
uint8_t AT_CREG[] = "AT+CREG?";	 
uint8_t AT_CSQ[] = "AT+CSQ";		
uint8_t AT_CGATT[] = "AT+CGATT?"; 
uint8_t AT_QIDEACT[] = "AT+QIDEACT";	
uint8_t AT_QIDNSIP[] = "AT+QIDNSIP=0";
uint8_t AT_QIFGCNT[] = "AT+QIFGCNT=0";
uint8_t	AT_QIMODE[] = "AT+QIMODE=1";
uint8_t	AT_QITCFG[] = "AT+QITCFG=4,5,100,1";
uint8_t AT_IP[] = "AT+QIOPEN=\"TCP\",\"120.25.214.208\",\"8002\"";
uint8_t Enter[] =  {0X0d,0X0a};

char buf[60];		// ��ʼ��ָ�������

uint8_t heartbeat[14] = {0x0F,		// ������
											0x31,0x32,0x33,0x34,0x35,0x36,
											0x00,0x00,0x00,0x00,0x00,0x01,
											0x02};	
uint8_t Parking_State[19] = {0x0A,		// ��λ״̬
												0x31,0x32,0x33,0x34,0x35,0x36,
												0x00,0x00,0x00,0x00,0x00,0x01,
												0x02,
												0x04,0x10,0x00,0x10,0x01};

u8 Read_compare[11]= {0x00,0x00,0x00,0x00,0x00,0x01,		// �������ݱȽ�
										0x20,0x00,0x20,0x01,0x02};

u8 Read_State[19];		// ����������������
u8 Read_Data[18];			// ״̬���Ľ�����
								
u8 Flash_Data[3] = {0x00,0x01,0x00};			// ���浽flash
	 			
/**
  * @brief  MC20_heartbeat
	* @note   ����MC20��������led״̬
  * @retval NONE
  */										
void MC20_heartbeat(void)
{
	HAL_UART_Transmit(&huart2,(uint8_t *)heartbeat,14,0xffff);  // ����������	
	HAL_UART_Transmit(&huart2,(uint8_t *)Parking_State,19,0xffff);  // ���͵�ǰ��λ״̬
}

/**
  * @brief  Uart2Data_Handle
	* @note   �������״ָ̬��
  * @param  len���������ݳ���
  * @retval 0 �������� or 1 �ɹ�����
  */
u8 MC20_DataHandle(u8 len)
{
	u8 i;
	for(i = 6; i < 10; i++)						
		Read_Data[i] = Read_Data[i+8];		// ɾ��Ŀ���ַ
	
	for(i = 0; i < 9; i++)			
		if (Read_Data[i] != Read_compare[i]) return 0; 	 // �ж�Ŀ���ַ��������Ƿ�һ��
	
	if (Read_Data[9] == Parking_State[18]) return 0;	//  ��ǰһ״̬�Ƿ�һ��
	
	if (Read_Data[9] == Read_compare[9])   // �ж��Ƿ�
	{
		LED_Sign = 0;
		Parking_State[18] = Read_Data[9];
		HAL_UART_Transmit(&huart2,(uint8_t *)Parking_State,19,0xffff);  // ���͵�ǰ��λ״̬
		Motor=1;
	}
	if (Read_Data[9] == Read_compare[10])		// �жϽ����Ƿ�Ϊ
	{
		LED_Sign = 1;
		Parking_State[18] = Read_Data[9];
		HAL_UART_Transmit(&huart2,(uint8_t *)Parking_State,19,0xffff);  // ���͵�ǰ��λ״̬
		Motor=2;
	}
	
//	for(i = 0; i < 10; i++)
//		printf("%x ",Read_Data[i]);   // ����ʹ�ã�������յ�������
	
	return 1;
}

/**
  * @brief  MC20_Init
	* @note   MC20_��ʼ��
  * @retval NONE
  */
void MC20_Init(void)
{
	HAL_UART_Transmit(&huart2, (uint8_t *)AT,sizeof(AT)-1,0xffff);	//�˳�͸��ģʽ������ģ�黹����͸��ģʽ��
	HAL_Delay(1000);
	
	MC20_Send(AT1,sizeof(AT1)-1,9,"OK",100); 		// ����ģ���Ƿ�����
	
	MC20_Send(AT_CPIN,sizeof(AT_CPIN)-1,31,"READY",100);	 	// �����Ƿ����SIM��

	MC20_Send(AT_CREG,sizeof(AT_CREG)-1,29,"OK",100);		// ��ѯ����ע��״̬

	MC20_Send(AT_CSQ,sizeof(AT_CSQ)-1,27,"OK",100);	 	// �ź�����

	MC20_Send(AT_CGATT,sizeof(AT_CGATT)-1,29,"1",1000);	 // GPRS����״̬

	MC20_Send(AT_QIDEACT,sizeof(AT_QIDEACT)-1,23,"OK",100);	// �ر�GPRS/CSD PDP����
	
	MC20_Send(AT_QIDNSIP,sizeof(AT_QIDNSIP)-1,19,"OK",100);	// ����ʹ��IP��ַ����

	MC20_Send(AT_QIFGCNT,sizeof(AT_QIFGCNT)-1,19,"OK",100);	// ����ǰ�ó���
	
	MC20_Send(AT_QIMODE,sizeof(AT_QIMODE)-1,18,"OK",100);	 // ����TCPIPӦ��ģʽΪ͸��ģʽ
	
	MC20_Send(AT_QITCFG,sizeof(AT_QITCFG)-1,26,"OK",100);	 // ����͸������ģʽ����

	
	HAL_UART_Transmit(&huart2, (uint8_t *)AT_IP,sizeof(AT_IP)-1,0xffff);	//��������
	HAL_UART_Transmit(&huart2, (uint8_t *)Enter,sizeof(Enter),0xffff);  // ���ͻس�����  
	HAL_UART_Receive (&huart2, (uint8_t *)buf, 55, 0xffff);			// ����MC_20������Ϣ
	HAL_UART_Transmit(&huart1, (uint8_t *)buf, 55, 0xffff);   // ����ʹ�ã��������ݵ�����
	HAL_Delay(2000);
	
	printf("\r\nMC20C SET OK!\r\n");
}

/**
  * @brief  MC20_Send
	* @note   ��ģ�鷢��ATָ��,��ȡ��������ʱ�������·���ָ��
  * @param 	str: ATָ��		size��ATָ���
  * @param 	len: ������Ϣ����
  * @param 	str1���ڴ�����Ӧ��ΪNULL������Ӧ
  * @param 	waittime���ȴ���Ӧ��ʱ��
  * @retval NONE
  */
void MC20_Send(uint8_t *str,char size,char len,char *str1,uint32_t watetime)
{
	do{	 
		HAL_UART_Transmit(&huart2, (uint8_t *)str,size,0xffff);
		HAL_UART_Transmit(&huart2, (uint8_t *)Enter,sizeof(Enter),0xffff);   // ���ͻس�����
	}while(!MC20_Cmd(len,str1,NULL,watetime));
}

/**
  * @brief  MC20_Cmd
	* @note   ��ȡ����֤����ָ��
  * @param 	len: ������Ϣ����
  * @param 	reply1��reply2���ڴ�����Ӧ��ΪNULL������Ӧ������Ϊ���߼���ϵ
  * @param 	waittime���ȴ���Ӧ��ʱ��
  * @retval 1��ָ��ͳɹ� or  0��ָ���ʧ��
  */
bool MC20_Cmd( char len, char * reply1,char * reply2, uint32_t waittime)
{
	if ( ( reply1 == 0 ) && ( reply2 == 0 ) )                      //����Ҫ��������
		return true;

	HAL_UART_Receive(&huart2, (uint8_t *)buf, len, 0xffff);	
	HAL_Delay ( waittime );                  //��ʱ
	
	HAL_UART_Transmit ( &huart1, (uint8_t *)buf, len, 0xffff);   // ����ʹ�ã��������ݵ�����
  
	if ( ( reply1 != 0 ) && ( reply2 != 0 ) )
		return ( ( uint8_t ) strstr ( buf, reply1 ) || 
						 ( uint8_t ) strstr ( buf, reply2 ) ); 
 	
	else if ( reply1 != 0 )
		return ( ( uint8_t ) strstr ( buf, reply1 ) );
	
	else
		return ( ( uint8_t ) strstr ( buf, reply2 ) );
}








