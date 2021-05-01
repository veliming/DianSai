#include "led.h"
#include "lcd.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "exti.h"
#include "timer.h"
#include "w25qxx.h"
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

extern u8 mode;
extern u8 audionum;
extern u32 rcount;
extern u32 wcount;
u8 TEST[1];
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
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
}

//�ⲿ�ж�0������� 
void EXTI0_IRQHandler(void)
{

	delay_ms(100);//����
	if(WK_UP==1)	 	 //WK_UP����
	{				 
		switch(mode)
		{
			case 0:
				mode=1;
				LED0=0;
				LED1=1;
				wcount=0;			
				LCD_Fill(150,250,450,280,WHITE);
				LCD_Fill(61,301,419,349,WHITE);			
				TIM3_Int_Init(100-1,72-1);
				TIM_Cmd(TIM3, ENABLE);
			break;
			
			case 1:
				mode=0;
				LED0=1;
				LED1=1;
				wcount=0;
				LCD_Fill(150,250,450,280,WHITE);
				LCD_Fill(61,301,419,349,WHITE);
				TIM_Cmd(TIM3, DISABLE);
				for(u8 i=50;i>0;i--){
	LCD_Draw_Circle(60, 600, i);
		POINT_COLOR=BLUE;
	LCD_Draw_Circle(240, 600, i);
		POINT_COLOR=GREEN;
	LCD_Draw_Circle(420, 600, i);
		POINT_COLOR=BLACK;
	}
							extern u8 a[];//�鿴�ĸ���¼��
			LCD_Fill(75,200,405,220,WHITE);
			for(u8 audionum=0;audionum<4;audionum++)
			{
			W25QXX_Read(a,0x180000*audionum,1);
				if(a[0]!=255){
					switch(audionum)
					{
						case 0:LCD_Fill(75,200,135,220,RED);break;
						case 1:LCD_Fill(165,200,225,220,RED);break;
						case 2:LCD_Fill(255,200,315,220,RED);break;
						case 3:LCD_Fill(345,200,405,220,RED);break;							
					}
				}
			}
			break;		

			case 2:		
			break;
			
			default:
				break;
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
}
 

//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY1==0)	 //����KEY1
	{				 
		switch(mode)
		{
			case 0:
				mode=2;
				LED0=1;
				LED1=0;
				rcount=0;	
				LCD_Fill(150,250,450,280,WHITE);
				LCD_Fill(61,301,419,349,WHITE);			
				TIM3_Int_Init(100-1,72-1);
				TIM_Cmd(TIM3, ENABLE);
				for(u8 i=50;i>0;i--){
	LCD_Draw_Circle(60, 600, i);
		POINT_COLOR=BLUE;
	LCD_Draw_Circle(240, 600, i);
		POINT_COLOR=GRAY;
	LCD_Draw_Circle(420, 600, i);
		POINT_COLOR=GRAY;
	}
				POINT_COLOR=BLACK;
			break;
			
			case 1:
			break;		

			case 2:
				mode=0;
				LED0=1;
				LED1=1;
				rcount=0;
				LCD_Fill(150,250,450,280,WHITE);
				LCD_Fill(61,301,419,349,WHITE);
				TIM_Cmd(TIM3, DISABLE);		
	for(u8 i=50;i>0;i--){
	LCD_Draw_Circle(60, 600, i);
		POINT_COLOR=BLUE;
	LCD_Draw_Circle(240, 600, i);
		POINT_COLOR=GREEN;
	LCD_Draw_Circle(420, 600, i);
		POINT_COLOR=BLACK;
	}			
	
	

			break;
			
			case 3:
				break;
			
			default:
				break;
		}
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}

void EXTI4_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY0==0)	 //����KEY0
	{
				switch(mode)
		{
			case 0:
				mode=3;
				LED0=0;
				LED1=0;
				for(u8 i=50;i>0;i--){
	LCD_Draw_Circle(60, 600, i);
		POINT_COLOR=GRAY;
	LCD_Draw_Circle(240, 600, i);
		POINT_COLOR=GRAY;
	LCD_Draw_Circle(420, 600, i);
		POINT_COLOR=GRAY;
	}
				POINT_COLOR=BLACK;
			LCD_ShowString(150,250,300,24,24,"Eraseing,touch not");
					for(audionum=0;audionum<4;audionum++)
		{
			for(u8 i=0;i<24;i++)
		{
			W25QXX_Erase_Block((24*65536*audionum+0x010000*i)/4096);//�����
		}
		}
		LCD_Fill(150,250,450,280,WHITE);
		LCD_ShowString(150,250,200,24,24,"success");
				mode=0;
				LED0=1;
				LED1=1;
			for(u8 i=50;i>0;i--){
	LCD_Draw_Circle(60, 600, i);
		POINT_COLOR=BLUE;
	LCD_Draw_Circle(240, 600, i);
		POINT_COLOR=GREEN;
	LCD_Draw_Circle(420, 600, i);
		POINT_COLOR=BLACK;
	}
										extern u8 a[];//�鿴�ĸ���¼��
			LCD_Fill(75,200,405,220,WHITE);
			for(u8 audionum=0;audionum<4;audionum++)
			{
			W25QXX_Read(a,0x180000*audionum,1);
				if(a[0]!=255){
					switch(audionum)
					{
						case 0:LCD_Fill(75,200,135,220,RED);break;
						case 1:LCD_Fill(165,200,225,220,RED);break;
						case 2:LCD_Fill(255,200,315,220,RED);break;
						case 3:LCD_Fill(345,200,405,220,RED);break;							
					}
				}
			}
			break;
			
			case 1:
			break;		

			case 2:		
			break;
			
			case 3:
			break;
			
			default:
				break;
		}

	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE4�ϵ��жϱ�־λ  
}
 
