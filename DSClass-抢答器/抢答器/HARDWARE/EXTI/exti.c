#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "beep.h"
#include "lcd.h"
extern u8 CH_Title[];   //标题的字模
extern u8 Button_64[];   //按键汉字的字模
extern u8 Player_CH[];
extern u8 st;

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK精英STM32开发板
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   
//外部中断0服务程序
void EXTIX_Init(void)
{
 
   	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	按键端口初始化

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟



   //GPIOE.3	  中断线以及中断初始化配置 下降沿触发 //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOE.4	  中断线以及中断初始化配置  下降沿触发	//KEY0
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


   //GPIOA.0	  中断线以及中断初始化配置 上升沿触发 PA0  WK_UP
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
}
extern u32 count;
extern u8 P1,P2,P3;
//外部中断0服务程序 
void EXTI0_IRQHandler(void)
{
	delay_ms(3);//消抖
	if(WK_UP==1&&st==0)	 	 //WK_UP按键
	{				 
		BEEP=!BEEP;
			delay_ms(100);
		BEEP=!BEEP;
		u32 k=count;
		//如果   如果其他两个选手都为按下   则说明此选手是第一个按下   标记为1   并且把该选手显示出来
		if(P2==0&&P3==0){
		u16 x=188;
		P1=1;
		
		POINT_COLOR=RED;
		LCD_Show_Ch_Font32(x,300,0,Player_CH);
		LCD_Show_Ch_Font32(x+36,300,1,Player_CH);
		LCD_Show_Ch_Font32(x+72,300,2,Player_CH);
		POINT_COLOR=BLUE;
		}
		//否则标记为2
		else{P1=2;}
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
}
 

//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	delay_ms(3);//消抖
	if(KEY1==0&&st==0)	 //按键KEY1
	{				 
		//LED1=!LED1;
				BEEP=!BEEP;
			delay_ms(100);
		BEEP=!BEEP;
		if(P1==0&&P3==0){
		u16 x=188;
		P2=1;
		
		POINT_COLOR=RED;
		LCD_Show_Ch_Font32(x,300,0,Player_CH);
		LCD_Show_Ch_Font32(x+36,300,1,Player_CH);
		LCD_Show_Ch_Font32(x+72,300,3,Player_CH);
		
		POINT_COLOR=BLUE;
		}
		else{P2=2;}
	}	 
	EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}

void EXTI4_IRQHandler(void)
{
	delay_ms(3);//消抖
	if(KEY0==0&&st==0)	 //按键KEY0
	{
		//LED0=!LED0;
		//LED1=!LED1; 
		BEEP=!BEEP;
			delay_ms(100);
		BEEP=!BEEP;
		if(P1==0&&P2==0){
		u16 x=188;
		P3=1;
		
		POINT_COLOR=RED;
		LCD_Show_Ch_Font32(x,300,0,Player_CH);
		LCD_Show_Ch_Font32(x+36,300,1,Player_CH);
		LCD_Show_Ch_Font32(x+72,300,4,Player_CH);
		POINT_COLOR=BLUE;
		}
		else{P3=2;}
	}
	EXTI_ClearITPendingBit(EXTI_Line4);  //清除LINE4上的中断标志位  
}
 
