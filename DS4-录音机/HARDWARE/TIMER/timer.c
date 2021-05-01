#include "timer.h"
#include "led.h"
#include "adc.h"
#include "dac.h"
#include "lcd.h"
#include "delay.h"
#include "w25qxx.h"
#include "spi.h"
#include "touch.h"
#include <stdio.h>

void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}

extern u8 vol;
extern u8 mode;
extern u8 audionum;// ��Ƶ���
extern u32 wcount,rcount;
extern u8 Audiois[5];

u32 firstblock;   //�׵�ַ
u16 sample;   //����ֵ
u8 storage[1];    //�洢ֵ
u8 isstart=0;   //�Ƿ�ʼ   0 û�п�ʼ   1��ʼ

//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
		
		switch(mode)
		{
			
			case 1:	//¼��ģʽ
				if(wcount==0)
					{
				BACK_COLOR=WHITE;
				LCD_ShowString(150,250,200,24,24,"reseting...,wait");
									for(u8 i=50;i>0;i--){
											LCD_Draw_Circle(60, 600, i);
												POINT_COLOR=GRAY;
											LCD_Draw_Circle(240, 600, i);
												POINT_COLOR=GRAY;
											LCD_Draw_Circle(420, 600, i);
												POINT_COLOR=GRAY;
											}
									POINT_COLOR=BLACK;
					for(u8 i=0;i<24;i++)
				{
					W25QXX_Erase_Block((24*65536*audionum+0x010000*i)/4096);//�����
				}
					LCD_Fill(150,250,350,280,WHITE);
									for(u8 i=50;i>0;i--){
											LCD_Draw_Circle(60, 600, i);
												POINT_COLOR=GRAY;
											LCD_Draw_Circle(240, 600, i);
												POINT_COLOR=GRAY;
											LCD_Draw_Circle(420, 600, i);
												POINT_COLOR=BLACK;
											}				
					LCD_ShowString(150,250,200,24,24,"recording...");
					}
			
				sample=Get_Adc(ADC_Channel_1);
				storage[0]=(u8)(sample>>4);
				//DAC_SetChannel1Data(DAC_Align_12b_R,sample); //��һ������
				W25QXX_Write_NoCheck(storage,0x180000*audionum+wcount,1);//�ڶ�������
				//W25QXX_Read(storage,0x180000*audionum+wcount,1);
				//DAC_SetChannel1Data(DAC_Align_12b_R,storage[0]*16);
				wcount++;
				if(wcount>=200000)
					{
						mode=0;
						LED0=1;
						LED1=1;
						wcount=0;
						LCD_Fill(150,250,350,280,WHITE);
						LCD_ShowString(150,250,200,24,24,"fininshed...");
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
												for(u8 i=50;i>0;i--){
											LCD_Draw_Circle(60, 600, i);
												POINT_COLOR=BLUE;
											LCD_Draw_Circle(240, 600, i);
												POINT_COLOR=GREEN;
											LCD_Draw_Circle(420, 600, i);
												POINT_COLOR=BLACK;
											}		
						TIM_Cmd(TIM3, DISABLE);
					}
				break;
			
			
			case 2: //����ģʽ
				if(rcount==0)
					{
					LCD_ShowString(150,250,200,24,24,"playing...");
					}
				W25QXX_Read(storage,0x180000*audionum+rcount,1);
				DAC_SetChannel1Data(DAC_Align_12b_R,(storage[0]*16)*vol/100.0);
				rcount++;
				if(rcount>=200000)
					{
						mode=0;
						LED0=1;
						LED1=1;
						rcount=0;
						LCD_Fill(150,250,350,280,WHITE);
						LCD_ShowString(150,250,200,24,24,"fininshed...");
												for(u8 i=50;i>0;i--){
											LCD_Draw_Circle(60, 600, i);
												POINT_COLOR=BLUE;
											LCD_Draw_Circle(240, 600, i);
												POINT_COLOR=GREEN;
											LCD_Draw_Circle(420, 600, i);
												POINT_COLOR=BLACK;
											}								
						TIM_Cmd(TIM3, DISABLE);
					}
				break;
				
				
			case 3:
				break;
			
			
			default:
				break;
		}
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIMx�����жϱ�־ 
		}
}









