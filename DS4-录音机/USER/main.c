#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 	 
#include "dac.h"
#include "adc.h"
#include "usmart.h"
#include "w25qxx.h"
#include "touch.h"
#include "timer.h"
#include "exti.h"
#include "ui.h"
/************************************************

************************************************/

u32 wcount=0,rcount=0;   //写采样数和读采样数
u8 audionum=0;//音频编号
				u8 a[1];//临时编码
//u8 Audiois[5];   //各个音频有无存入   0无  1为有
u8 vol=100;
u8 mode;
int main(){
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	KEY_Init();			  //初始化按键程序
	EXTIX_Init();			// 中断
 	LED_Init();			     //LED端口初始化
	LCD_Init();			 	 //LCD初始化
	usmart_dev.init(72);	//初始化USMART	
 	Adc_Init();		  		//ADC初始化
	Dac1_Init();				//DAC初始化
	TP_Init();
	W25QXX_Init();
	//TIM3_Int_Init(100-1,72-1);
	
	
	
			Face_index();
	while(1)
		{
			tp_dev.scan(0);
			if(tp_dev.sta&0x80){
			if(tp_dev.x[0]<135&&tp_dev.x[0]>75&&tp_dev.y[0]<200&&tp_dev.y[0]>140)audionum=0;
			if(tp_dev.x[0]<225&&tp_dev.x[0]>165&&tp_dev.y[0]<200&&tp_dev.y[0]>140)audionum=1;
			if(tp_dev.x[0]<315&&tp_dev.x[0]>255&&tp_dev.y[0]<200&&tp_dev.y[0]>140)audionum=2;
			if(tp_dev.x[0]<405&&tp_dev.x[0]>345&&tp_dev.y[0]<200&&tp_dev.y[0]>140)audionum=3;
			Face_indexsc();
			if(tp_dev.x[0]<421&&tp_dev.x[0]>60&&tp_dev.y[0]<450&&tp_dev.y[0]>400)
			{vol=100.0*((tp_dev.x[0]-60.0)/360.0);
			LCD_Fill(60, 400,tp_dev.x[0], 450,BLACK);
			LCD_Fill(tp_dev.x[0], 401,419, 449,WHITE);
			}
				
					tp_dev.sta=0;
				}
			
			if(wcount!=0){
			LCD_Fill(60 + wcount * 360 / 200000, 300, 60 + wcount * 360 / 200000, 350,BLACK);}
			if(rcount!=0){
			LCD_Fill(60 + rcount * 360 / 200000, 300, 60 + rcount * 360 / 200000, 350,BLACK);}
			if(rcount!=0){
			LCD_Fill(60 + rcount * 360 / 200000, 300, 60 + rcount * 360 / 200000, 350,BLACK);}
			}

		}
	
	



