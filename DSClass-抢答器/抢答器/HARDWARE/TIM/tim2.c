#include "tim2.h"
#include "stdlib.h"
#include "stdio.h"
#include "lcd.h"

//一个定时器3的中断函数   计数频率为10k

void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
	//初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设置重载值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //初始化TIM
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能TIM3中断
 
	//配置中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;  //?????0?
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //????3?
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ?????
	NVIC_Init(&NVIC_InitStructure);  //???NVIC???
 
 
	TIM_Cmd(TIM2, ENABLE);  //??TIMx					 
}




extern u32 count;
//中断服务函数
void TIM2_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否？
		{
			extern u32 count;
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx更新中断标志 
			
			count+=1;
			//LCD_ShowxNum(50,50,count,200,24,0);
			//LCD_ShowNum(50,50,count,200,24);
			//LCD_ShowString(200,450,84,24,24,"aaaa");
		}
}





