/************************************版权申明********************************************
**                             广州大彩光电科技有限公司
**                             http://www.gz-dc.com
**-----------------------------------文件信息--------------------------------------------
** 文件名称:   hmi_user_uart.c
** 修改时间:   2011-05-18
** 文件说明:   用户MCU串口驱动函数库
** 技术支持：  Tel: 020-82186683  Email: hmi@gz-dc.com Web:www.gz-dc.com
--------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------
                                  使用必读
   hmi_user_uart.c中的串口发送接收函数共3个函数：串口初始化Uartinti()、发送1个字节SendChar()、
   发送字符串SendStrings().若移植到其他平台，需要修改底层寄
   存器设置,但禁止修改函数名称，否则无法与HMI驱动库(hmi_driver.c)匹配。
--------------------------------------------------------------------------------------



----------------------------------------------------------------------------------------
                          1. 基于STM32平台串口驱动
----------------------------------------------------------------------------------------*/
#include "main.h"
#include "hmi_user_uart.h"
#include "hmi_driver.h"
#include "cmd_queue.h"
#include "cmd_process.h"
#include "base.h"
#include "usart.h"
/****************************************************************************
* 名    称： UartInit()
* 功    能： 串口初始化
* 入口参数： 无
* 出口参数： 无
****************************************************************************/


#define CMD_HEAD 0XEE  //帧头
#define CMD_TAIL 0XFFFCFFFF //帧尾

u8 Tx_pos = 0,Txing_pos = 0;     //当前条数
u8 sendStatus = 0; //发送状态
u8 RxBuffer;
u8 *TxBuffer;

Tx_STACK Tx_stack = {0};  //发送队列

void TFT_Init(void)
{
    HAL_UART_Receive_IT(&huart1, &RxBuffer, 1);//使能接收中断
    queue_reset();
}
void Param_Update(void) //获取当前新参数
{
    qsize size = queue_find_cmd(cmd_buffer,CMD_MAX_SIZE);
    if(size)
    {
        //TODO:两条指令
        ProcessMessage((PCTRL_MSG)cmd_buffer, size);//指令处理
        LED1_T;
    }
}

//PUSH:
//   0(空) ->  帧头  ->   pos 不变
//                   ->   state -> 1
//                   ->   size ++
//                   ->  _data 装入
//          -> 正常数据（不可能）
//          -> 帧尾（不可能）
//   1(转载中) -> 帧头 -> pos ++
//                    -> state(下一个) -> 1
//                    -> size(下一个)++
//					  -> _data装入  (pos++ 再重新调用该函数 )
//            -> 正常 -> pos _____
//                    -> state ____
//                    -> size++
//                    -> data装入
//            -> 正常+ 超额
//                    -> pos_____
//					  -> state_____
//                    -> size = MAX
//					  -> data后三位等待帧尾
//			  -> 帧尾 -> pos _____
//                    -> state -> 2
//                    -> size++
//                    -> data装入
//                    -> data装入
//  2(装载完成) -> 帧头 -> (pos++ 再重新调用该函数)
//             -> 正常数据(不可能)
//             -> 帧尾(不可能)
//OUT:
//  正在写入时不打扰
//  自动扫描
//  传输结束后减小到最小
//  中断先判断是否淦完 再减小回去
//
//  DMA中断
//
//  扫描
// SEND_SATUS非正常数据不处理

void Tx_stack_reset(void)
{
	u16 i;

	for(i=0;i<Tx_MAX_CMD;i++)Tx_stack._size[i] = Tx_stack._state[i] = 0;
}

void Tx_stack_push(u8 _data)
{
	if(Tx_pos != Tx_MAX_CMD) {
		if(Tx_stack._state[Tx_pos] == 0)
		{
			if(_data == CMD_HEAD)
			{
				Tx_stack._state[Tx_pos]   = 1;
				Tx_stack._size[Tx_pos]    = 1;
				Tx_stack._data[Tx_pos][0] = CMD_HEAD;
			}
		}
		else if(Tx_stack._state[Tx_pos] == 1)
		{
			u16 size = Tx_stack._size[Tx_pos];
			u8  *p =  (Tx_stack._data[Tx_pos] + Tx_stack._size[Tx_pos]);
			if(_data == CMD_HEAD)
			{
				Tx_pos++;
				Tx_stack_push(_data);
				return;
			}
			else if(((*(u32*)(p-3)<<8 & 0xffffff00) | _data) == CMD_TAIL)
			{
				Tx_stack._state[Tx_pos]   = 2;
				if(size<Tx_MAX_SIZE)  //超载也能输入数据
				{
					Tx_stack._data[Tx_pos][size] = 0xff;
					Tx_stack._size[Tx_pos]++;
				}
				//*(Tx_STACK._data[Tx_pos] + size - 4) = CMD_TAIL;
			}
			else if(size==Tx_MAX_SIZE)
			{
				*(u32*)(p-4) = (*(u32*)(p-3) << 8 & 0xffffff00) |_data;
			}
			else
			{
				Tx_stack._data[Tx_pos][Tx_stack._size[Tx_pos]++] = _data;
			}
		}
		else if(Tx_stack._state[Tx_pos] == 2 || Tx_stack._state[Tx_pos] == 3)
		{
			if(_data == CMD_HEAD)
			{
				Tx_pos++;
				Tx_stack_push(_data);
				return;
			}
		}
	}
}

u16 Tx_stack_find_cmd(u8 **buffer)
{
	while(Tx_stack._state[Tx_pos] == 3)
	{
		Tx_stack._state[Tx_pos] = 0;
		Tx_stack._size[Tx_pos]  = 0;
		if(Tx_pos==0)break;
		else Tx_pos--;
	}
	if(Tx_stack._state[Tx_pos] == 2)
	{
		*buffer = (u8*)(Tx_stack._data[Tx_pos]);
		return Tx_stack._size[Tx_pos];
	}
	return 0;
}

void  SendChar(uchar t)
{
	Tx_stack_push(t);
	/*
	USART1->DR = (t & (uint16_t)0x01FF);
    while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TXE) == RESET);
    while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) == RESET);
    */
}

