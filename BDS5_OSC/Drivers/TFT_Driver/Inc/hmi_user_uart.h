#ifndef _USER_UART__
#define _USER_UART__

#include "stm32f4xx_it.h"     //根据用户MCU进行修改
#include "obase.h"

#define uchar    unsigned char
#define uint8    unsigned char
#define uint16   unsigned short int
#define uint32   unsigned long
#define int16    short int
#define int32    long
#define Tx_MAX_CMD  20     //接收指令最大个数
#define Tx_MAX_SIZE 4000   //接收指令最大宽度

typedef struct _Tx_STACK
{
	u16 _size[Tx_MAX_CMD];              //目前长度
	u8  _state[Tx_MAX_CMD];             //0:空 1:载入中 2:装载完成(超载+帧尾) 3:发送完毕
	u8  _data[Tx_MAX_CMD][Tx_MAX_SIZE];	//队列数据缓存区
}Tx_STACK;

extern u8* TxBuffer;
extern u8 Txing_pos;
/****************************************************************************
* 名    称： UartInit()
* 功    能： 串口初始化
* 入口参数： 无
* 出口参数： 无
****************************************************************************/
void TFT_Init(void);
void Param_Update(void);
/*****************************************************************
* 名    称： SendChar()
* 功    能： 发送1个字节
* 入口参数： t  发送的字节
* 出口参数： 无
 *****************************************************************/
void  SendChar(uchar t);
u16 Tx_stack_find_cmd(u8 **buffer);

#endif
