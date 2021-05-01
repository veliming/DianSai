#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "beep.h"
#include "lcd.h"
extern u8 CH_Title[];   //�������ģ
extern u8 Button_64[];   //�������ֵ���ģ
extern u8 Player_CH[];
extern u8 st;

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   
//�ⲿ�ж�0�������
void EXTIX_Init(void)
{
 
   	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	�����˿ڳ�ʼ��

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��



   //GPIOE.3	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   //GPIOE.4	  �ж����Լ��жϳ�ʼ������  �½��ش���	//KEY0
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


   //GPIOA.0	  �ж����Լ��жϳ�ʼ������ �����ش��� PA0  WK_UP
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
}
extern u32 count;
extern u8 P1,P2,P3;
//�ⲿ�ж�0������� 
void EXTI0_IRQHandler(void)
{
	delay_ms(3);//����
	if(WK_UP==1&&st==0)	 	 //WK_UP����
	{				 
		BEEP=!BEEP;
			delay_ms(100);
		BEEP=!BEEP;
		u32 k=count;
		//���   �����������ѡ�ֶ�Ϊ����   ��˵����ѡ���ǵ�һ������   ���Ϊ1   ���ҰѸ�ѡ����ʾ����
		if(P2==0&&P3==0){
		u16 x=188;
		P1=1;
		
		POINT_COLOR=RED;
		LCD_Show_Ch_Font32(x,300,0,Player_CH);
		LCD_Show_Ch_Font32(x+36,300,1,Player_CH);
		LCD_Show_Ch_Font32(x+72,300,2,Player_CH);
		POINT_COLOR=BLUE;
		}
		//������Ϊ2
		else{P1=2;}
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
}
 

//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	delay_ms(3);//����
	if(KEY1==0&&st==0)	 //����KEY1
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
	EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}

void EXTI4_IRQHandler(void)
{
	delay_ms(3);//����
	if(KEY0==0&&st==0)	 //����KEY0
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
	EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE4�ϵ��жϱ�־λ  
}
 
