#ifndef _USER_UART__
#define _USER_UART__

#define uchar    unsigned char
#define uint8    unsigned char
#define uint16   unsigned short int
#define uint32   unsigned long
#define int16    short int
#define int32    long
#include "stm32f4xx_it.h"     //根据用户MCU进行修改
#include "obase.h"

void TFT_Init(u8* buf);

void Param_Update(void);

void SendChar(uchar t);

#endif
