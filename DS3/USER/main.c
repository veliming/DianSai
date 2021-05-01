#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "24cxx.h"
#include "w25qxx.h"
#include "touch.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "exti.h"
 extern void LCD_Show_CH_Font24(u16 x,u16 y,u8 index);

 int main(void)
 {	 		    
	delay_init();	    	 
	 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);	 	
 	LED_Init();			     //LED¶Ë¿Ú³õÊ¼»¯
	LCD_Init();	
	KEY_Init();
	EXTIX_Init();	 
 	tp_dev.init(); 
	 u8 GREENON=0;
	 u8 REDON=0;
	 u8 MODE=0;
  static u8 key_up=1;

	 while(1){

					}
				}
