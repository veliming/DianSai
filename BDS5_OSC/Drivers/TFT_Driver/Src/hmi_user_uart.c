/************************************��Ȩ����********************************************
**                             ���ݴ�ʹ��Ƽ����޹�˾
**                             http://www.gz-dc.com
**-----------------------------------�ļ���Ϣ--------------------------------------------
** �ļ�����:   hmi_user_uart.c
** �޸�ʱ��:   2011-05-18
** �ļ�˵��:   �û�MCU��������������
** ����֧�֣�  Tel: 020-82186683  Email: hmi@gz-dc.com Web:www.gz-dc.com
--------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------
                                  ʹ�ñض�
   hmi_user_uart.c�еĴ��ڷ��ͽ��պ�����3�����������ڳ�ʼ��Uartinti()������1���ֽ�SendChar()��
   �����ַ���SendStrings().����ֲ������ƽ̨����Ҫ�޸ĵײ��
   ��������,����ֹ�޸ĺ������ƣ������޷���HMI������(hmi_driver.c)ƥ�䡣
--------------------------------------------------------------------------------------



----------------------------------------------------------------------------------------
                          1. ����STM32ƽ̨��������
----------------------------------------------------------------------------------------*/
#include "main.h"
#include "hmi_user_uart.h"
#include "hmi_driver.h"
#include "cmd_queue.h"
#include "cmd_process.h"
#include "obase.h"
#include "usart.h"
/****************************************************************************
* ��    �ƣ� UartInit()
* ��    �ܣ� ���ڳ�ʼ��
* ��ڲ����� ��
* ���ڲ����� ��
****************************************************************************/


#define CMD_HEAD 0XEE  //֡ͷ
#define CMD_TAIL 0XFFFCFFFF //֡β

u8 Tx_pos = 0,Txing_pos = 0;     //��ǰ����
u8 sendStatus = 0; //����״̬
u8 RxBuffer;
u8 *TxBuffer;

Tx_STACK Tx_stack = {0};  //���Ͷ���

void TFT_Init(void)
{
    //HAL_UART_Receive_IT(&huart1, &RxBuffer, 1);//ʹ�ܽ����ж�
    queue_reset();
}
void Param_Update(void) //��ȡ��ǰ�²���
{
    qsize size = queue_find_cmd(cmd_buffer,CMD_MAX_SIZE);
    if(size)
    {
        //TODO:����ָ��
        ProcessMessage((PCTRL_MSG)cmd_buffer, size);//ָ���
        LED1_T;
    }
}

//PUSH:
//   0(��) ->  ֡ͷ  ->   pos ����
//                   ->   state -> 1
//                   ->   size ++
//                   ->  _data װ��
//          -> �������ݣ������ܣ�
//          -> ֡β�������ܣ�
//   1(ת����) -> ֡ͷ -> pos ++
//                    -> state(��һ��) -> 1
//                    -> size(��һ��)++
//					  -> _dataװ��  (pos++ �����µ��øú��� )
//            -> ���� -> pos _____
//                    -> state ____
//                    -> size++
//                    -> dataװ��
//            -> ����+ ����
//                    -> pos_____
//					  -> state_____
//                    -> size = MAX
//					  -> data����λ�ȴ�֡β
//			  -> ֡β -> pos _____
//                    -> state -> 2
//                    -> size++
//                    -> dataװ��
//                    -> dataװ��
//  2(װ�����) -> ֡ͷ -> (pos++ �����µ��øú���)
//             -> ��������(������)
//             -> ֡β(������)
//OUT:
//  ����д��ʱ������
//  �Զ�ɨ��
//  ����������С����С
//  �ж����ж��Ƿ����� �ټ�С��ȥ
//
//  DMA�ж�
//
//  ɨ��
// SEND_SATUS���������ݲ�����

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
				if(size<Tx_MAX_SIZE)  //����Ҳ����������
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
	//Tx_stack_push(t);
	//HAL_UART_Transmit_DMA(&huart2, t, 1);
	USART2->DR = t;
	//USART2->DR = (t & (uint16_t)0x01FF);
    //while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TXE) == RESET);
    //while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) == RESET);

}
