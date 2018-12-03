#include "mc_20.h"



// TCP 注册AT指令
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

char buf[60];		// 初始化指令接收器

uint8_t heartbeat[14] = {0x0F,		// 心跳包
											0x31,0x32,0x33,0x34,0x35,0x36,
											0x00,0x00,0x00,0x00,0x00,0x01,
											0x02};	
uint8_t Parking_State[19] = {0x0A,		// 车位状态
												0x31,0x32,0x33,0x34,0x35,0x36,
												0x00,0x00,0x00,0x00,0x00,0x01,
												0x02,
												0x04,0x10,0x00,0x10,0x01};

u8 Read_compare[11]= {0x00,0x00,0x00,0x00,0x00,0x01,		// 接收数据比较
										0x20,0x00,0x20,0x01,0x02};

u8 Read_State[19];		// 心跳包反馈接收器
u8 Read_Data[18];			// 状态更改接收器
								
u8 Flash_Data[3] = {0x00,0x01,0x00};			// 保存到flash
	 			
/**
  * @brief  MC20_heartbeat
	* @note   发送MC20心跳包、led状态
  * @retval NONE
  */										
void MC20_heartbeat(void)
{
	HAL_UART_Transmit(&huart2,(uint8_t *)heartbeat,14,0xffff);  // 发送心跳包	
	HAL_UART_Transmit(&huart2,(uint8_t *)Parking_State,19,0xffff);  // 发送当前车位状态
}

/**
  * @brief  Uart2Data_Handle
	* @note   处理更改状态指令
  * @param  len：接收数据长度
  * @retval 0 错误数据 or 1 成功更改
  */
u8 MC20_DataHandle(u8 len)
{
	u8 i;
	for(i = 6; i < 10; i++)						
		Read_Data[i] = Read_Data[i+8];		// 删除目标地址
	
	for(i = 0; i < 9; i++)			
		if (Read_Data[i] != Read_compare[i]) return 0; 	 // 判断目标地址与操作符是否一致
	
	if (Read_Data[9] == Parking_State[18]) return 0;	//  与前一状态是否一样
	
	if (Read_Data[9] == Read_compare[9])   // 判断是否
	{
		LED_Sign = 0;
		Parking_State[18] = Read_Data[9];
		HAL_UART_Transmit(&huart2,(uint8_t *)Parking_State,19,0xffff);  // 发送当前车位状态
		Motor=1;
	}
	if (Read_Data[9] == Read_compare[10])		// 判断接收是否为
	{
		LED_Sign = 1;
		Parking_State[18] = Read_Data[9];
		HAL_UART_Transmit(&huart2,(uint8_t *)Parking_State,19,0xffff);  // 发送当前车位状态
		Motor=2;
	}
	
//	for(i = 0; i < 10; i++)
//		printf("%x ",Read_Data[i]);   // 调试使用，输出接收到的数据
	
	return 1;
}

/**
  * @brief  MC20_Init
	* @note   MC20_初始化
  * @retval NONE
  */
void MC20_Init(void)
{
	HAL_UART_Transmit(&huart2, (uint8_t *)AT,sizeof(AT)-1,0xffff);	//退出透传模式，避免模块还处于透传模式中
	HAL_Delay(1000);
	
	MC20_Send(AT1,sizeof(AT1)-1,9,"OK",100); 		// 测试模块是否正常
	
	MC20_Send(AT_CPIN,sizeof(AT_CPIN)-1,31,"READY",100);	 	// 测试是否存在SIM卡

	MC20_Send(AT_CREG,sizeof(AT_CREG)-1,29,"OK",100);		// 查询网络注册状态

	MC20_Send(AT_CSQ,sizeof(AT_CSQ)-1,27,"OK",100);	 	// 信号质量

	MC20_Send(AT_CGATT,sizeof(AT_CGATT)-1,29,"1",1000);	 // GPRS符着状态

	MC20_Send(AT_QIDEACT,sizeof(AT_QIDEACT)-1,23,"OK",100);	// 关闭GPRS/CSD PDP场景
	
	MC20_Send(AT_QIDNSIP,sizeof(AT_QIDNSIP)-1,19,"OK",100);	// 配置使用IP地址链接

	MC20_Send(AT_QIFGCNT,sizeof(AT_QIFGCNT)-1,19,"OK",100);	// 配置前置场景
	
	MC20_Send(AT_QIMODE,sizeof(AT_QIMODE)-1,18,"OK",100);	 // 配置TCPIP应用模式为透传模式
	
	MC20_Send(AT_QITCFG,sizeof(AT_QITCFG)-1,26,"OK",100);	 // 配置透传传输模式参数

	
	HAL_UART_Transmit(&huart2, (uint8_t *)AT_IP,sizeof(AT_IP)-1,0xffff);	//建立连接
	HAL_UART_Transmit(&huart2, (uint8_t *)Enter,sizeof(Enter),0xffff);  // 发送回车换行  
	HAL_UART_Receive (&huart2, (uint8_t *)buf, 55, 0xffff);			// 接收MC_20返回信息
	HAL_UART_Transmit(&huart1, (uint8_t *)buf, 55, 0xffff);   // 测试使用，发送数据到串口
	HAL_Delay(2000);
	
	printf("\r\nMC20C SET OK!\r\n");
}

/**
  * @brief  MC20_Send
	* @note   对模块发送AT指令,读取不到反馈时，会重新发送指令
  * @param 	str: AT指令		size：AT指令长度
  * @param 	len: 反馈信息长度
  * @param 	str1：期待的响应，为NULL表不需响应
  * @param 	waittime，等待响应的时间
  * @retval NONE
  */
void MC20_Send(uint8_t *str,char size,char len,char *str1,uint32_t watetime)
{
	do{	 
		HAL_UART_Transmit(&huart2, (uint8_t *)str,size,0xffff);
		HAL_UART_Transmit(&huart2, (uint8_t *)Enter,sizeof(Enter),0xffff);   // 发送回车换行
	}while(!MC20_Cmd(len,str1,NULL,watetime));
}

/**
  * @brief  MC20_Cmd
	* @note   读取、验证反馈指令
  * @param 	len: 反馈信息长度
  * @param 	reply1，reply2，期待的响应，为NULL表不需响应，两者为或逻辑关系
  * @param 	waittime，等待响应的时间
  * @retval 1，指令发送成功 or  0，指令发送失败
  */
bool MC20_Cmd( char len, char * reply1,char * reply2, uint32_t waittime)
{
	if ( ( reply1 == 0 ) && ( reply2 == 0 ) )                      //不需要接收数据
		return true;

	HAL_UART_Receive(&huart2, (uint8_t *)buf, len, 0xffff);	
	HAL_Delay ( waittime );                  //延时
	
	HAL_UART_Transmit ( &huart1, (uint8_t *)buf, len, 0xffff);   // 测试使用，发送数据到串口
  
	if ( ( reply1 != 0 ) && ( reply2 != 0 ) )
		return ( ( uint8_t ) strstr ( buf, reply1 ) || 
						 ( uint8_t ) strstr ( buf, reply2 ) ); 
 	
	else if ( reply1 != 0 )
		return ( ( uint8_t ) strstr ( buf, reply1 ) );
	
	else
		return ( ( uint8_t ) strstr ( buf, reply2 ) );
}








