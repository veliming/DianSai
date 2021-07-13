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
#include "base.h"
#include "usart.h"

u8 RxBuffer;

void TFT_Init(void)
{
    HAL_UART_Receive_IT(&huart1, &RxBuffer, 1);//ʹ�ܽ����ж�
    queue_reset();
}
void Param_Update(void) //��ȡ��ǰ�²���
{
    qsize size = queue_find_cmd(cmd_buffer,CMD_MAX_SIZE);
    if(size)
    {
        //TODO:����ָ��
    	LED1_T;
        ProcessMessage((PCTRL_MSG)cmd_buffer, size);//ָ���
        LED1_T;
    }
}

void  SendChar(uchar t)
{
	USART1->DR = (t & (uint16_t)0x01FF);
    while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TXE) == RESET);
    while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) == RESET);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    huart1.RxState = HAL_UART_STATE_READY;
	__HAL_UNLOCK(&huart1);
	queue_push(RxBuffer);
	Param_Update();//�ж����洦����ָ��
	HAL_UART_Receive_IT(&huart1, &RxBuffer, 1);
  }
}
