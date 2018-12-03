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
	HAL_UART_Transmit(&huart3, (u8 *)AT,sizeof(AT)-1,0xffff);	//退出透传模式，避免模块还处于透传模式中
	HAL_Delay(1000);
	
	SIM800_Send(ATE0,sizeof(ATE0)-1,6,"OK",100);	// 取消回显
	HAL_Delay(800);
	
	SIM800_Send(AT_CREG,sizeof(AT_CREG)-1,20,"1",300);	// 检查注册是否成功
	
	HAL_UART_Transmit(&huart3, (u8 *)AT_CIPCLOSE,sizeof(AT_CIPCLOSE)-1,0xffff);	//关闭连接
	HAL_Delay(500);
	
	SIM800_Send(AT_CIPSHUT,sizeof(AT_CIPSHUT)-1,9,"SHU",100);	//关闭移动场景

	SIM800_Send(AT_CGDCONT,sizeof(AT_CGDCONT)-1,6,"OK",100);	 //设置PDP上下文,互联网接协议,接入点等信息

	SIM800_Send(AT_CGATT,sizeof(AT_CGATT)-1,6,"OK",100);	 //附着GPRS业务

	SIM800_Send(AT_CIPCSGP,sizeof(AT_CIPCSGP)-1,6,"OK",100);	 //设置为GPRS连接模式

	SIM800_Send(AT_CIPMUX,sizeof(AT_CIPMUX)-1,6,"OK",100);	//设置为单路连接
	
	SIM800_Send(AT_CIPHEAD,sizeof(AT_CIPHEAD)-1,6,"OK",100);	//设置接收数据显示IP头(方便判断数据来源,仅在单路连接有效)

	SIM800_Send(AT_CIPMODE,sizeof(AT_CIPMODE)-1,6,"OK",100);	//打开透传功能
	HAL_Delay(300);
	
	//建立连接
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
 * 函数名：SIM800_Cmd
 * 描述  ：对WF-ESP8266模块发送AT指令
 * 输入  ：len: 接收长度
 *         reply1，reply2，期待的响应，为NULL表不需响应，两者为或逻辑关系
 *         waittime，等待响应的时间
 * 返回  : 1，指令发送成功
 *         0，指令发送失败
 * 调用  ：被外部调用
 */
bool SIM800_Cmd( char len, char * reply1,char * reply2, uint32_t waittime)
{
	if ( ( reply1 == 0 ) && ( reply2 == 0 ) )                      //不需要接收数据
		return true;

	HAL_UART_Receive(&huart3, (u8 *)buf, len, 0xffff);	
	HAL_Delay ( waittime );                  //延时
	
	HAL_UART_Transmit ( &huart1, (u8 *)buf, len, 0xffff);   // 测试使用，发送数据到串口
  
	if ( ( reply1 != 0 ) && ( reply2 != 0 ) )
		return ( ( u8 ) strstr ( buf, reply1 ) || 
						 ( u8 ) strstr ( buf, reply2 ) ); 
 	
	else if ( reply1 != 0 )
		return ( ( u8 ) strstr ( buf, reply1 ) );
	
	else
		return ( ( u8 ) strstr ( buf, reply2 ) );
}









