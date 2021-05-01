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
 ALIENTEK精英STM32开发板实验13
 TFTLCD显示实验  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
//count是计数值   周期为1ms的中断溢出一次增加一次
u32 count;
u8 P1,P2,P3,st;
u8 Start(){
			BEEP=!BEEP;
			delay_ms(100);
		BEEP=!BEEP;
	u8 printchar[8];
	//三个选手的状态值   0表示未按下按键   1表示第一个按下按键   2表示非第一个按下按键
	P1=0;
	P2=0;
	P3=0;
	count=0;
	st=0;
	LCD_Fill(188,300,292,332,WHITE);
	Index_Redbutton();
	BACK_COLOR=WHITE;
	POINT_COLOR=BLUE;
	TIM2_Int_Init(99,719);  //时钟溢出频率1k
	while(1){			
		sprintf(printchar,"%.3fs",count*1.0/1000);
		if(count<=5000){
			//如果三个选手都未按下  则不断刷新标题时间
			if(!(P1||P2||P3)){
				LCD_ShowString(196,200,120,24,24,printchar);
			}
			//如果选手1没按下   则刷新选手1时间   按下了则停止刷新
			if(P1==0){
				LCD_ShowString(42,450,120,24,24,printchar);
			}
			//如果选手1是第一个按下的    则把选手一标红
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
	u8 lcd_id[12];			//存放LCD ID字符串
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化
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
			//检测点击触摸屏   开始计时
			delay_ms(10);
			if(tp_dev.sta&0x80){
			if(tp_dev.x[0]<408&&tp_dev.x[0]>72&&tp_dev.y[0]<750&&tp_dev.y[0]>600){
					Start();
					//清除标志位
					tp_dev.sta=0;
				}
			}
		}
	} 
}
 