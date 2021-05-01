#include "tim2.h"
#include "stdlib.h"
#include "stdio.h"
#include "lcd.h"

//һ����ʱ��3���жϺ���   ����Ƶ��Ϊ10k

void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	
	//��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //��������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //��ʼ��TIM
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��TIM3�ж�
 
	//�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;  //?????0?
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //????3?
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ?????
	NVIC_Init(&NVIC_InitStructure);  //???NVIC???
 
 
	TIM_Cmd(TIM2, ENABLE);  //??TIMx					 
}




extern u32 count;
//�жϷ�����
void TIM2_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
			extern u32 count;
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
			
			count+=1;
			//LCD_ShowxNum(50,50,count,200,24,0);
			//LCD_ShowNum(50,50,count,200,24);
			//LCD_ShowString(200,450,84,24,24,"aaaa");
		}
}





