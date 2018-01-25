#ifndef __KEY_H__
#define	__KEY_H__

#define 	Init1_State 	0
#define 	Affirm1_State 	1
#define		Single1_State	2
#define		Repeat1_State	3

extern uint8 idata KeyBackup;

void KEY_Updata(void); 	
void KEY_Scan(uint8 k,uint8 n);

#endif
