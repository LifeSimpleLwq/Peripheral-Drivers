#ifndef __BH1750_H__
#define __BH1750_H__

#include "SYS.h"

#define	  SlaveAddress   0x46
//����������IIC�����еĴӵ�ַ,����ALT  ADDRESS��ַ���Ų�ͬ�޸�
//ALT  ADDRESS���Žӵ�ʱ��ַΪ0xA6���ӵ�Դʱ��ַΪ0x3A

u8 *mread(void);         //�����Ķ�ȡ�ڲ��Ĵ�������

#endif

