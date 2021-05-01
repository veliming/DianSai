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
#include "eval.h"
 extern void LCD_Show_CH_Font24(u16 x,u16 y,u8 index);
/************************************************
 ALIENTEK精英STM32开发板实验26
 触摸屏 实验    
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
typedef struct
{
    char *s;
    uint32_t (*p)(uint32_t,uint32_t);
} calc_t;

uint32_t my_add(uint32_t a, uint32_t b) {return a+b;}
uint32_t my_sub(uint32_t a, uint32_t b) {return a-b;}
uint32_t my_mul(uint32_t a, uint32_t b) {return a*b;}
uint32_t my_div(uint32_t a, uint32_t b) {return a/b;}
uint32_t my_mod(uint32_t a, uint32_t b) {return a%b;}
uint32_t my_and(uint32_t a, uint32_t b) {return a&b;}
uint32_t my_or (uint32_t a, uint32_t b) {return a|b;}
uint32_t my_xor(uint32_t a, uint32_t b) {return a^b;}
uint32_t my_lsh(uint32_t a, uint32_t b) {return a<<b;}
uint32_t my_rsh(uint32_t a, uint32_t b) {return a>>b;}
    const calc_t CALC_EXP[] = {{"%d+%d",my_add},
                               {"%d-%d",my_sub},
                               {"%d*%d",my_mul},
                               {"%d/%d",my_div},
                               {"%d%%d",my_mod},
                               {"%d&%d",my_and},
                               {"%d|%d",my_or },
                               {"%d^%d",my_xor},
                               {"%d<<%d",my_lsh},
                               {"%d>>%d",my_rsh}};
        double sum1;		
				char sum;
void USART2_GetPacket(char *s)
{
	char str[200]=0;
        uint32_t t;	
	        uint32_t flag=1;
        uint32_t i;											 
    uint32_t a, b;										 
    uint32_t err = 1;
	
	for(t=0;t<USART_REC_LEN;t++)
			{
				if(USART_RX_BUF[t]=='+'||USART_RX_BUF[t]=='-'||USART_RX_BUF[t]=='*'||USART_RX_BUF[t]=='/'||USART_RX_BUF[t]=='%'||USART_RX_BUF[t]=='&'||USART_RX_BUF[t]=='|')
				{
			//		printf("%c\n\r",USART_RX_BUF[t]);
			//		printf("%u\n\r",t);
					flag=0;
				}
				else {}
			}
	
	
	
      if(flag==0)
	{
	
    for (i = 0; i < sizeof(CALC_EXP)/sizeof(CALC_EXP[0]); i++)
    {

        if (2 == sscanf(s, CALC_EXP[i].s, &a, &b))
        {
            printf(CALC_EXP[i].s, a, b);
            printf("=%d\r\n",CALC_EXP[i].p(a,b));
						if(i==0){LCD_ShowString(150,525,200,24,24,"+");}
						else if(i==1){LCD_ShowString(150,525,200,24,24,"-");}
						else if(i==2){LCD_ShowString(150,525,200,24,24,"*");}
						else if(i==3){LCD_ShowString(150,525,200,24,24,"/");}
						else if(i==4){LCD_ShowString(150,525,200,24,24,"%");}
						else if(i==5){LCD_ShowString(150,525,200,24,24,"&");}
						else if(i==6){LCD_ShowString(150,525,200,24,24,"|");}
						else if(i==7){LCD_ShowString(150,525,200,24,24,"^");}
						else if(i==8){LCD_ShowString(150,525,200,24,24,"<<");}
						else if(i==9){LCD_ShowString(150,525,200,24,24,">>");}
						else {LCD_ShowString(150,525,200,24,24," ");}
					LCD_ShowNum(50,525,a,7,24);
					LCD_ShowNum(180,525,b,7,24);
					sprintf((char *)str,"%d\r\n",CALC_EXP[i].p(a,b));
					LCD_ShowString(330,525,200,24,24,str);
					LCD_ShowString(300,525,200,24,24,"=");
					a=' ';
					b=' ';
            err = 0;
						USART_RX_STA=0;
            break;
        }
    }
    
    if (err)
    {
        printf("error command!\r\n");
    }
}
	else if ( atof(USART_RX_BUF)==0)
	{        printf("error command!\r\n");}
	else {
		char str[200] = 0;
		sum1=eval((char *)USART_RX_BUF);
		printf("%f\r\n",sum1+1);
		sprintf((char *)str,"%f\r\n",sum1+1);
		LCD_ShowString(300,300,200,24,24,str);
		printf("%f\r\n",sum1-1);
		sprintf((char *)str,"%f\r\n",sum1-1);
		LCD_ShowString(300,250,200,24,24,str);
		//printf("LCD_ShowString(300,300,200,24,24,str);%f\r\n",sum1-1);
		//sum=(atof(USART_RX_BUF))+1;
					//LCD_ShowString(240,300,(atof(USART_RX_BUF))-1,10,24);
							//LCD_ShowString(300,300,200,24,24,&sum);
		}

}

 int main(void)
 {	 		    
	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化
	LCD_Init();	
	KEY_Init();	 	
 	tp_dev.init(); 
  static u8 key_up=1;//按键按松开标志
	 u8 REDON=0;
	 u8 GREENON=0; 
	 RESETONE:
	 USART_RX_BUF[0]=0;
	LCD_Clear(WHITE);
	POINT_COLOR=RED;
	BACK_COLOR=GRAY;
	LCD_Fill(50,700,190,750,GRAY);//填充单色
	LCD_ShowString(100,713,200,24,24,"PRO");
	LCD_Fill(290,700,430,750,GRAY);//填充单色
	LCD_ShowString(340,713,200,24,24,"HOME");
	LCD_Fill(120,80,360,200,GRAY);//填充单色	
							LCD_Show_CH_Font24(200,125,8);
							LCD_Show_CH_Font24(220,125,9);
							LCD_Show_CH_Font24(240,125,10);
							LCD_Show_CH_Font24(260,125,11);
	LCD_Fill(120,280,360,400,GRAY);//填充单色
							LCD_Show_CH_Font24(200,325,12);
							LCD_Show_CH_Font24(220,325,13);
							LCD_Show_CH_Font24(240,325,14);
							LCD_Show_CH_Font24(260,325,15);
	LCD_Fill(120,480,360,600,GRAY);//填充单色
							LCD_Show_CH_Font24(200,525,16);
							LCD_Show_CH_Font24(220,525,17);
							LCD_Show_CH_Font24(240,525,18);
							LCD_Show_CH_Font24(260,525,19);
	BACK_COLOR=WHITE;

	 while(1){
		 
		 					 tp_dev.scan(0); 
	if((key_up&&(tp_dev.sta&0x80))||USART_RX_STA&0x8000)
	{
		delay_ms(10);//去抖动 
		key_up=0;	 
		 					if((tp_dev.x[0]>120&&tp_dev.y[0]>80&&tp_dev.x[0]<360&&tp_dev.y[0]<200)||('m'==USART_RX_BUF[0]))
					{
						goto NUMBERONE;
					}
						else	if((tp_dev.x[0]>120&&tp_dev.y[0]>280&&tp_dev.x[0]<360&&tp_dev.y[0]<400)||('l'==USART_RX_BUF[0]))
					{
						goto LEDONE;
					}
						else	if((tp_dev.x[0]>120&&tp_dev.y[0]>480&&tp_dev.x[0]<360&&tp_dev.y[0]<600)||('u'==USART_RX_BUF[0]))
					{
						goto USARTONE;
					}
					 else if((tp_dev.x[0]>50&&tp_dev.y[0]>700&&tp_dev.x[0]<190&&tp_dev.y[0]<750)||('p'==USART_RX_BUF[0]))
					{
						goto PROONE;
					}
					 else if((tp_dev.x[0]>290&&tp_dev.y[0]>700&&tp_dev.x[0]<430&&tp_dev.y[0]<750)||('h'==USART_RX_BUF[0]))
					{
						//printf("%s",USART_RX_BUF);
						goto RESETONE;
					}
					USART_RX_STA=0;
	}
	else if(((tp_dev.sta&TP_PRES_DOWN)==0)&&(USART_RX_STA==0))
		key_up=1;
			}
					
					NUMBERONE:{
						USART_RX_BUF[0]=0;
						LCD_Clear(WHITE);
						BACK_COLOR=GRAY;
						LCD_Fill(50,700,190,750,GRAY);//填充单色
						LCD_ShowString(100,713,200,24,24,"PRO");
						LCD_Fill(290,700,430,750,GRAY);//填充单色
						LCD_ShowString(340,713,200,24,24,"HOME");		
						BACK_COLOR=WHITE;		
						LCD_DrawRectangle(50,40,210,160);
						POINT_COLOR=RED;
						LCD_ShowString(60,50,200,24,24,"201921111363");	
						LCD_ShowString(60,90,200,24,24,"ZHAOXUDONG");	
						LCD_ShowString(60,130,200,24,24,"3.1415926");
						printf("201921111363\r\nZHAODUDONG\r\n3.1415926");
						while(1){

						tp_dev.scan(0);
							
	if((key_up&&(tp_dev.sta&0x80))||USART_RX_STA&0x8000)
	{
		delay_ms(10);//去抖动 
		key_up=0;		
					if((tp_dev.x[0]>50&&tp_dev.y[0]>700&&tp_dev.x[0]<190&&tp_dev.y[0]<750)||('p'==USART_RX_BUF[0]))
					{
						goto PROONE;
					}
					else if((tp_dev.x[0]>290&&tp_dev.y[0]>700&&tp_dev.x[0]<430&&tp_dev.y[0]<750)||('h'==USART_RX_BUF[0]))
					{
						goto RESETONE;
					}
					USART_RX_STA=0;					
	}
	else if(((tp_dev.sta&TP_PRES_DOWN)==0)&&USART_RX_STA==0)
		key_up=1; 							
						}
					}
					
					
					
					
					
					LEDONE:{
						USART_RX_BUF[0]=0;
					LCD_Clear(WHITE);
						BACK_COLOR=WHITE;
						LCD_ShowString(200,90,200,24,24,"LEDONE");
						LCD_ShowString(90,340,200,24,24,"REDLED");
						LCD_DrawRectangle(210,300,60,180);
						BACK_COLOR=GRAY;
						LCD_Fill(50,700,190,750,GRAY);//填充单色
						LCD_ShowString(100,713,200,24,24,"PRO");
						LCD_Fill(290,700,430,750,GRAY);//填充单色
						LCD_ShowString(340,713,200,24,24,"HOME");
						BACK_COLOR=WHITE;

						POINT_COLOR=GREEN;
						LCD_DrawRectangle(270,300,420,180);
						LCD_ShowString(300,340,200,24,24,"GREENLED");
						POINT_COLOR=RED;
						//static u8 key_up=1;//按键按松开标志
						while(1){

					 tp_dev.scan(0);			
	if((key_up&&(tp_dev.sta&0x80))||USART_RX_STA&0x8000)
	{
		delay_ms(10);//去抖动 
		key_up=0;
					if((tp_dev.x[0]>60&&tp_dev.y[0]>180&&tp_dev.x[0]<210&&tp_dev.y[0]<300)||('1'==USART_RX_BUF[0]))
					{
						USART_RX_BUF[0]=0;
						if(REDON==0){
						LCD_Fill(60,180,210,300,RED);
							LED0=!LED0;
						REDON=1;}
						else {LCD_Fill(60,180,210,300,WHITE);
							LCD_DrawRectangle(210,300,60,180);
							LED0=!LED0;
						REDON=0;}
					}		
					else if((tp_dev.x[0]>270&&tp_dev.y[0]>180&&tp_dev.x[0]<420&&tp_dev.y[0]<300)||('2'==USART_RX_BUF[0]))
					{
						USART_RX_BUF[0]=0;
						if(GREENON==0){
						LCD_Fill(270,180,420,300,GREEN);
							LED1=!LED1;
						GREENON=1;}
						else {LCD_Fill(270,180,420,300,WHITE);
							POINT_COLOR=GREEN;
							LCD_DrawRectangle(270,300,420,180);
							LED1=!LED1;
							POINT_COLOR=RED;
						GREENON=0;}
					}					
					else if((tp_dev.x[0]>50&&tp_dev.y[0]>700&&tp_dev.x[0]<190&&tp_dev.y[0]<750)||('p'==USART_RX_BUF[0]))
					{
						goto PROONE;
					}
					else if((tp_dev.x[0]>290&&tp_dev.y[0]>700&&tp_dev.x[0]<430&&tp_dev.y[0]<750)||('h'==USART_RX_BUF[0]))
					{
						goto RESETONE;
					}
					USART_RX_STA=0;					
	}
	else if(((tp_dev.sta&TP_PRES_DOWN)==0)&&USART_RX_STA==0)
		key_up=1; 	
						}
					}
					
										
					
					USARTONE:{
						USART_RX_BUF[0]=0;

					LCD_Clear(WHITE);
						LCD_Show_CH_Font24(100,300,20);
						LCD_Show_CH_Font24(120,300,21);
						LCD_Show_CH_Font24(140,300,22);
						LCD_Show_CH_Font24(160,300,23);
							BACK_COLOR=GRAY;
					LCD_Fill(50,700,190,750,GRAY);//填充单色
					LCD_ShowString(100,713,200,24,24,"PRO");
					LCD_Fill(290,700,430,750,GRAY);//填充单色
					LCD_ShowString(340,713,200,24,24,"HOME");
							BACK_COLOR=WHITE;
					LCD_ShowString(60,90,200,24,24,"USART");
					u8 *Res;
					u8 t;
						while(1){		
			if(USART_RX_STA&0x8000)
	{
		delay_ms(10);//去抖动 
		key_up=0;
					if('p'==USART_RX_BUF[0])
					{
						goto PROONE;
					}
					else if('h'==USART_RX_BUF[0])
					{
						goto RESETONE;
					}
					Res =USART_RX_BUF;
					USART2_GetPacket(("%s",Res));
					printf("\r\n");//插入换行
					//USART_RX_BUF=0;
								for(t=0;t<USART_REC_LEN;t++)
			{
				USART_RX_BUF[t]=' ';
			}
					USART_RX_STA=0;				
	}
	else if(((tp_dev.sta&TP_PRES_DOWN)==0)&&USART_RX_STA==0)
		key_up=1; 				
		
		
		
					tp_dev.scan(0);			
	if((key_up&&(tp_dev.sta&0x80)))
	{
		delay_ms(10);//去抖动 
		key_up=0;
					if((tp_dev.x[0]>50&&tp_dev.y[0]>700&&tp_dev.x[0]<190&&tp_dev.y[0]<750))
					{
						goto PROONE;
					}
					else if((tp_dev.x[0]>290&&tp_dev.y[0]>700&&tp_dev.x[0]<430&&tp_dev.y[0]<750))
					{
						goto RESETONE;
					}			
	}
	else if(((tp_dev.sta&TP_PRES_DOWN)==0))
		key_up=1; 					
						}
					}
					
					
					
					PROONE:{
						printf("%s",USART_RX_BUF);
						USART_RX_BUF[0]=0;
						printf("%s",USART_RX_BUF);
					LCD_Clear(WHITE);
					BACK_COLOR=GRAY;
					LCD_Fill(50,700,190,750,GRAY);//填充单色
					LCD_ShowString(100,713,200,24,24,"PRO");
					LCD_Fill(290,700,430,750,GRAY);//填充单色
					LCD_ShowString(340,713,200,24,24,"HOME");
					BACK_COLOR=WHITE;
					LCD_ShowString(60,90,200,24,24,"PRO");	
						LCD_Show_CH_Font24(30,300,0);
						LCD_Show_CH_Font24(60,300,1);
						LCD_Show_CH_Font24(90,300,2);
						LCD_Show_CH_Font24(120,300,3);
						LCD_Show_CH_Font24(150,300,4);
						LCD_Show_CH_Font24(180,300,5);
						LCD_Show_CH_Font24(210,300,6);
						LCD_Show_CH_Font24(240,300,7);
						while(1){

					tp_dev.scan(0);		
	if((key_up&&(tp_dev.sta&0x80))||(USART_RX_STA&0x8000))
	{
		delay_ms(10);//去抖动 
		key_up=0;		
		printf("%s",USART_RX_BUF);
					if((tp_dev.x[0]>50&&tp_dev.y[0]>700&&tp_dev.x[0]<190&&tp_dev.y[0]<750)||('p'==USART_RX_BUF[0]))
					{
						goto PROONE;
					}
					else if((tp_dev.x[0]>290&&tp_dev.y[0]>700&&tp_dev.x[0]<430&&tp_dev.y[0]<750)||('h'==USART_RX_BUF[0]))
					{
						goto RESETONE;
					}
					USART_RX_STA=0;					
	}
	else if(((tp_dev.sta&TP_PRES_DOWN)==0)&&USART_RX_STA==0)
		key_up=1; 								
						}
					}					
	 }
