#include "sim800.h"

u8 AT[] = "+++";
u8 AT_CREG[] = "AT+CREG?";
u8 ATE0[] = "ATE0";
u8 AT_CIPCLOSE[] = "AT+CIPCLOSE=1";
u8 AT_CIPSHUT[] = "AT+CIPSHUT";
u8 AT_CGDCONT[] = "AT+CGDCONT=1,\"IP\",\"3GNET\"";
u8 AT_CGATT[] = "AT+CGATT=1";
u8 AT_CIPCSGP[] = "AT+CIPCSGP=1";
u8 AT_CIPMUX[] = "AT+CIPMUX=0";
u8 AT_CIPHEAD[] = "AT+CIPHEAD=1";
u8 AT_CIPMODE[] = "AT+CIPMODE=1";
u8 AT_CIPCCFG[] = "AT+CIPCCFG=4,5,200,1";
//u8 AT_IP[] = "AT+CIPSTART=\"TCP\",\"120.55.82.235\",8002";
u8 AT_IP[] = "AT+CIPSTART=\"TCP\",\"120.25.214.208\",8002";

u8 a[] =  {0X0d,0X0a};
char buf[80];

void SIM800_Init(void)
{
	HAL_Delay(4000);
	HAL_UART_Transmit(&huart3, (u8 *)AT,sizeof(AT)-1,0xffff);	//�˳�͸��ģʽ������ģ�黹����͸��ģʽ��
	HAL_Delay(1000);
	
	SIM800_Send(ATE0,sizeof(ATE0)-1,6,"OK",100);	// ȡ������
	HAL_Delay(800);
	
	SIM800_Send(AT_CREG,sizeof(AT_CREG)-1,20,"1",300);	// ���ע���Ƿ�ɹ�
	
	HAL_UART_Transmit(&huart3, (u8 *)AT_CIPCLOSE,sizeof(AT_CIPCLOSE)-1,0xffff);	//�ر�����
	HAL_Delay(500);
	
	SIM800_Send(AT_CIPSHUT,sizeof(AT_CIPSHUT)-1,9,"SHU",100);	//�ر��ƶ�����

	SIM800_Send(AT_CGDCONT,sizeof(AT_CGDCONT)-1,6,"OK",100);	 //����PDP������,��������Э��,��������Ϣ

	SIM800_Send(AT_CGATT,sizeof(AT_CGATT)-1,6,"OK",100);	 //����GPRSҵ��

	SIM800_Send(AT_CIPCSGP,sizeof(AT_CIPCSGP)-1,6,"OK",100);	 //����ΪGPRS����ģʽ

	SIM800_Send(AT_CIPMUX,sizeof(AT_CIPMUX)-1,6,"OK",100);	//����Ϊ��·����
	
	SIM800_Send(AT_CIPHEAD,sizeof(AT_CIPHEAD)-1,6,"OK",100);	//���ý���������ʾIPͷ(�����ж�������Դ,���ڵ�·������Ч)

	SIM800_Send(AT_CIPMODE,sizeof(AT_CIPMODE)-1,6,"OK",100);	//��͸������
	HAL_Delay(300);
	
	//��������
	HAL_UART_Transmit(&huart3, (u8 *)AT_IP,sizeof(AT_IP)-1,0xffff);
	HAL_UART_Transmit(&huart3, (u8 *)a,sizeof(a),0xffff);
	printf("SIM800C SET OK!\r\n");
}

// sim800 Send AT
void SIM800_Send(u8 *str,u8 length,char len,char *str1,uint32_t watetime)
{
	do{	 
		HAL_UART_Transmit(&huart3, (u8 *)str,length,0xffff);
		HAL_UART_Transmit(&huart3, (u8 *)a,sizeof(a),0xffff);
	}while(!SIM800_Cmd(len,str1,NULL,watetime));
}

/*
 * ��������SIM800_Cmd
 * ����  ����WF-ESP8266ģ�鷢��ATָ��
 * ����  ��len: ���ճ���
 *         reply1��reply2���ڴ�����Ӧ��ΪNULL������Ӧ������Ϊ���߼���ϵ
 *         waittime���ȴ���Ӧ��ʱ��
 * ����  : 1��ָ��ͳɹ�
 *         0��ָ���ʧ��
 * ����  �����ⲿ����
 */
bool SIM800_Cmd( char len, char * reply1,char * reply2, uint32_t waittime)
{
	if ( ( reply1 == 0 ) && ( reply2 == 0 ) )                      //����Ҫ��������
		return true;

	HAL_UART_Receive(&huart3, (u8 *)buf, len, 0xffff);	
	HAL_Delay ( waittime );                  //��ʱ
	
	HAL_UART_Transmit ( &huart1, (u8 *)buf, len, 0xffff);   // ����ʹ�ã��������ݵ�����
  
	if ( ( reply1 != 0 ) && ( reply2 != 0 ) )
		return ( ( u8 ) strstr ( buf, reply1 ) || 
						 ( u8 ) strstr ( buf, reply2 ) ); 
 	
	else if ( reply1 != 0 )
		return ( ( u8 ) strstr ( buf, reply1 ) );
	
	else
		return ( ( u8 ) strstr ( buf, reply2 ) );
}









