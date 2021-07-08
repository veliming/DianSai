#ifndef _CMD_PROCESS_H
#define _CMD_PROCESS_H
#include "hmi_driver.h"
#include "base.h"

#define NOTIFY_TOUCH_PRESS       0X01   //触摸屏按下通知
#define NOTIFY_TOUCH_RELEASE     0X03  //触摸屏松开通知
#define NOTIFY_WRITE_FLASH_OK    0X0C  //写FLASH成功
#define NOTIFY_WRITE_FLASH_FAILD 0X0D  //写FLASH失败
#define NOTIFY_READ_FLASH_OK     0X0B  //读FLASH成功
#define NOTIFY_READ_FLASH_FAILD  0X0F  //读FLASH失败
#define NOTIFY_MENU              0X14  //菜单事件通知
#define NOTIFY_TIMER             0X43  //定时器超时通知
#define NOTIFY_CONTROL           0XB1  //控件更新通知
#define NOTIFY_READ_RTC          0XF7  //读取RTC时间
#define MSG_GET_CURRENT_SCREEN   0X01  //画面ID变化通知
#define MSG_GET_DATA             0X11  //控件数据通知

#define PTR2U16(PTR) ((((uint8 *)(PTR))[0]<<8)|((uint8 *)(PTR))[1])  //从缓冲区取16位数据
#define PTR2U32(PTR) ((((uint8 *)(PTR))[0]<<24)|(((uint8 *)(PTR))[1]<<16)|(((uint8 *)(PTR))[2]<<8)|((uint8 *)(PTR))[3])  //从缓冲区取32位数据


enum CtrlType
{
	kCtrlUnknown=0x0,
	kCtrlButton=0x10,  //按钮
	kCtrlText,  //文本
	kCtrlProgress,  //进度条
	kCtrlSlider,    //滑动条
	kCtrlMeter,  //仪表
	kCtrlDropList, //下拉列表
	kCtrlAnimation, //动画
	kCtrlRTC, //时间显示
	kCtrlGraph, //曲线图控件
	kCtrlTable, //表格控件
	kCtrlMenu,//菜单控件
	kCtrlSelector,//选择控件
	kCtrlQRCode,//二维码
};

#pragma pack(push)
#pragma pack(1)	//按字节对齐

typedef struct
{
	uint8    cmd_head;  //帧头

	uint8    cmd_type;  //命令类型(UPDATE_CONTROL)	
	uint8    ctrl_msg;   //CtrlMsgType-指示消息的类型
	uint16   screen_id;  //产生消息的画面ID
	uint16   control_id;  //产生消息的控件ID
	uint8    control_type; //控件类型

	uint8    param[10];//可变长度参数，最多10个字节

	uint8    cmd_tail[4];   //帧尾
}CTRL_MSG,*PCTRL_MSG;

#pragma pack(pop)


extern uint8 cmd_buffer[CMD_MAX_SIZE];//指令缓存

void SetTFTText(uint16 screen_id,uint16 control_id,char* buffer,...);

void SetTextValueInt32(uint16 screen_id, uint16 control_id,int32 value);

void SetTextValueFloat(uint16 screen_id, uint16 control_id,float value);

void ProcessMessage( PCTRL_MSG msg, uint16 size);

void NotifyScreen(uint16 screen_id,void* userdata);

void NotifyTouchXY(uint8 press,uint16 x,uint16 y,void* userdata);

void NotifyButton(uint16 screen_id, uint16 control_id, uint8  state,void* userdata);

void NotifyText(uint16 screen_id, uint16 control_id, uint8 *str,void* userdata);

void NotifyProgress(uint16 screen_id, uint16 control_id, uint32 value,void* userdata);

void NotifySlider(uint16 screen_id, uint16 control_id, uint32 value,void* userdata);

void NotifyMeter(uint16 screen_id, uint16 control_id, uint32 value,void* userdata);

void NotifyMenu(uint16 screen_id, uint16 control_id, uint8  item, uint8  state,void* userdata);

void NotifySelector(uint16 screen_id, uint16 control_id, uint8  item,void* userdata);

void NotifyTimer(uint16 screen_id, uint16 control_id,void* userdata);

void NotifyReadFlash(uint8 status,uint8 *_data,uint16 length,void* userdata);

void NotifyWriteFlash(uint8 status,void* userdata);

void NotifyReadRTC(uint8 year,uint8 month,uint8 week,uint8 day,uint8 hour,uint8 minute,uint8 second,void* userdata);

#endif
