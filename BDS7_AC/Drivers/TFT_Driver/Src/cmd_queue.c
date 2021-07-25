#include "cmd_queue.h"
#include "obase.h"

#define CMD_HEAD 0XEE  //帧头
#define CMD_TAIL 0XFFFCFFFF //帧尾
#define CMD_IPD  0X50442C //IPD

typedef struct _QUEUE
{
	qsize _head; //队列头
	qsize _tail;  //队列尾
	qdata _data[QUEUE_MAX_SIZE];	//队列数据缓存区
}QUEUE;

static QUEUE que = {0};  //指令队列
static uint32 cmd_state = 0;  //队列帧尾检测状态
static qsize cmd_pos = 0;  //当前指令指针位置

extern u8 IPD;

void queue_reset()
{
	que._head = que._tail = 0;
	cmd_pos = cmd_state = 0;
}

void queue_push(qdata _data)
{
	qsize pos = (que._head+1)%QUEUE_MAX_SIZE;
	if(pos!=que._tail)//非满状态
	{
		que._data[que._head] = _data;
		que._head = pos;
	}
}

//从队列中取一个数据
static void queue_pop(qdata* _data)
{
	if(que._tail!=que._head)//非空状态
	{
		*_data = que._data[que._tail];
		que._tail = (que._tail+1)%QUEUE_MAX_SIZE;
	}
}

//获取队列中有效数据个数
static qsize queue_size()
{
	return ((que._head+QUEUE_MAX_SIZE-que._tail)%QUEUE_MAX_SIZE);
}

qsize queue_find_cmd(qdata *buffer,qsize buf_len)
{
	qsize cmd_size = 0;
	qdata _data = 0;
	while(queue_size()>0)
	{
		//取一个数据
		queue_pop(&_data);

		if(cmd_pos==0&&_data!=CMD_HEAD)//指令第一个字节必须是帧头，否则跳过
		    continue;

		if(cmd_pos<buf_len)//防止缓冲区溢出
			buffer[cmd_pos++] = _data;

		cmd_state = ((cmd_state<<8)|_data);//拼接最后4个字节，组成一个32位整数

		if(cmd_state==CMD_IPD)
		{
			IPD = _data-0x30;
		}
		//最后4个字节与帧尾匹配，得到完整帧
		if(cmd_state==CMD_TAIL)
		{
			cmd_size = cmd_pos; //指令字节长度
			cmd_state = 0;  //重新检测帧尾巴
			cmd_pos = 0; //复位指令指针

#if(CRC16_ENABLE)
			//去掉指令头尾EE，尾FFFCFFFF共计5个字节，只计算数据部分CRC
			if(!CheckCRC16(buffer+1,cmd_size-5))//CRC校验
				return 0;

			cmd_size -= 2;//去掉CRC16（2字节）
#endif

			return cmd_size;
		}
	}

	return 0;//没有形成完整的一帧
}

