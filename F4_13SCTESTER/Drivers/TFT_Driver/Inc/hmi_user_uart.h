#ifndef _USER_UART__
#define _USER_UART__

#include "stm32f4xx_it.h"     //根据用户MCU进行修改
#include "base.h"
#define uchar    unsigned char
#define uint8    unsigned char
#define uint16   unsigned short int
#define uint32   unsigned long
#define int16    short int
#define int32    long

void TFT_Init(void);

void Param_Update(void);

void SendChar(uchar t);

#endif
