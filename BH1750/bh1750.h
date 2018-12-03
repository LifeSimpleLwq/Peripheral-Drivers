#ifndef __BH1750_H__
#define __BH1750_H__

#include "SYS.h"

#define	  SlaveAddress   0x46
//定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
//ALT  ADDRESS引脚接地时地址为0xA6，接电源时地址为0x3A

u8 *mread(void);         //连续的读取内部寄存器数据

#endif

