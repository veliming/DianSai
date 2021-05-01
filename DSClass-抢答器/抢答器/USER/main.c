#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "Chinese.h"
#include "touch.h"
#include "tim2.h"
#include "exti.h"
#include "beep.h"
//extern u8 CH_Title[];
/************************************************
 ALIENTEK��ӢSTM32������ʵ��13
 TFTLCD��ʾʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
//count�Ǽ���ֵ   ����Ϊ1ms���ж����һ������һ��
u32 count;
u8 P1,P2,P3,st;
u8 Start(){
			BEEP=!BEEP;
			delay_ms(100);
		BEEP=!BEEP;
	u8 printchar[8];
	//����ѡ�ֵ�״ֵ̬   0��ʾδ���°���   1��ʾ��һ�����°���   2��ʾ�ǵ�һ�����°���
	P1=0;
	P2=0;
	P3=0;
	count=0;
	st=0;
	LCD_Fill(188,300,292,332,WHITE);
	Index_Redbutton();
	BACK_COLOR=WHITE;
	POINT_COLOR=BLUE;
	TIM2_Int_Init(99,719);  //ʱ�����Ƶ��1k
	while(1){			
		sprintf(printchar,"%.3fs",count*1.0/1000);
		if(count<=5000){
			//�������ѡ�ֶ�δ����  �򲻶�ˢ�±���ʱ��
			if(!(P1||P2||P3)){
				LCD_ShowString(196,200,120,24,24,printchar);
			}
			//���ѡ��1û����   ��ˢ��ѡ��1ʱ��   ��������ֹͣˢ��
			if(P1==0){
				LCD_ShowString(42,450,120,24,24,printchar);
			}
			//���ѡ��1�ǵ�һ�����µ�    ���ѡ��һ���
				if(P1==1){
				Index_Red(196,200,292,224);
				Index_Red(42,450,138,424);
				}
			
			if(P2==0){
				LCD_ShowString(196,450,120,24,24,printchar);
			}
			if(P2==1){
				Index_Red(196,200,292,224);
				Index_Red(196,450,292,424);
			}
			
			if(P3==0){
				LCD_ShowString(350,450,120,24,24,printchar);
			}
			if(P3==1){
				Index_Red(196,200,292,224);
				Index_Red(350,450,446,424);
			}
			
			delay_ms(1);
			if(P1==1&&P2==1&&P3==1){
				Index_Button();
				return 0;
			}
		}
		else
		{BACK_COLOR=WHITE;
			POINT_COLOR=RED;
							LCD_ShowString(196,200,120,24,24,"5.000s");
			LCD_ShowString(42,450,120,24,24,"5.000s");
			LCD_ShowString(196,450,120,24,24,"5.000s");
			LCD_ShowString(350,450,120,24,24,"5.000s");
			POINT_COLOR=BLACK;
			BACK_COLOR=RED;
			LCD_Show_Ch_Font64(110,643,4,Button_64);
	LCD_Show_Ch_Font64(180,643,5,Button_64);
	LCD_Show_Ch_Font64(250,643,8,Button_64);
	LCD_Show_Ch_Font64(320,643,9,Button_64);
	}
}
	}


 int main(void)
 {	 
	 st=1;
 	u8 x=0;
	u8 lcd_id[12];			//���LCD ID�ַ���
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();
	TP_Init();
	BEEP_Init();
	EXTIX_Init();
	Index_Title();
	Index_Button();
	Index_Player(0);
  while(1) 
	{		 
		tp_dev.scan(0);
		delay_ms(10);
		tp_dev.scan(0);
		if(tp_dev.sta&0x80){
			//�����������   ��ʼ��ʱ
			delay_ms(10);
			if(tp_dev.sta&0x80){
			if(tp_dev.x[0]<408&&tp_dev.x[0]>72&&tp_dev.y[0]<750&&tp_dev.y[0]>600){
					Start();
					//�����־λ
					tp_dev.sta=0;
				}
			}
		}
	} 
}
 