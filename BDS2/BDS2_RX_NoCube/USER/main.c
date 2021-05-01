#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "24l01.h"
#include "adc.h"
#include "string.h"
#include "stdlib.h"
/************************************************
 ALIENTEK 精英STM32F103开发板 实验31
 NRF24L01无线通信实验-HAL库函数版
 技术支持：www.openedv.com
 淘宝店铺： http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
int ascii_to_integer( char *string )
{
    int value; value = 0;
    // 逐个把字符串的字符转换为数字。
    while( *string >= '0' && *string <= '9' ){
        value *= 10;
        value += *string - '0';
        string++;
    }
    //错误检查：如杲由于遇到一个非数字字符而终止，把结果设置为0
    if( *string != '\0' )
        value = 0;
    return value;
}
int main(void)
{	
	u8 key,mode;
	u16 t=0;			 
	char tmp_buf[2];	
	int tmp_buf_num;
		 uint16_t adcx;
uint8_t send_data[50];
uint8_t Check_flag=0;
	 int ii=0;
	
    HAL_Init();                    	 	//初始化HAL库    
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//设置时钟,72M
	delay_init(72);               		//初始化延时函数
	uart_init(115200);					//初始化串口	
	LED_Init();							//初始化LED	
	KEY_Init();							//初始化按键
 	LCD_Init();           				//初始化LCD FSMC接口 
	NRF24L01_Init();    		    	//初始化NRF24L01 
	MY_ADC_Init();
   	POINT_COLOR=RED;
	while(NRF24L01_Check())
	{
		LCD_ShowString(30,130,200,16,16,(u8 *)"NRF24L01 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}
	LCD_ShowString(30,130,200,16,16,(u8 *)"NRF24L01 OK"); 	 
	
 while(1)
	{	
		key=KEY_Scan(0);
		if(key==KEY0_PRES)
		{
			mode=0;   
			break;
		}else if(key==KEY1_PRES)
		{
			mode=1;
			break;
		}
		t++;
		if(t==100)LCD_ShowString(10,150,230,16,16,"KEY0:RX_Mode  KEY1:TX_Mode"); //闪烁显示提示信息
 		if(t==200)
		{	
			LCD_Fill(10,150,230,150+16,WHITE);
			t=0; 
		}
		delay_ms(5);	  
	}   
 	LCD_Fill(10,150,240,166,WHITE);//清空上面的显示		  
 	POINT_COLOR=BLUE;//设置字体为蓝色	   
	if(mode==0)//RX模式
	{
		LCD_ShowString(30,150,200,16,16,"NRF24L01 RX_Mode");	
		LCD_ShowString(30,170,200,16,16,"Received DATA:");	
		NRF24L01_RX_Mode();		  
		while(1)
		{	  		    		    				 
			if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
			{
	 					  	  	adcx =  Get_Adc(ADC_CHANNEL_1);
				//vol=adcx/4095*3.3;
	
					tmp_buf_num= (int)tmp_buf[0];

	 							send_data[tmp_buf_num]=adcx;
				LCD_ShowString(0,220,lcddev.width-1,32,16,(uint8_t *)tmp_buf);
				LCD_ShowString(0,190,lcddev.width-1,32,16,(uint8_t *)tmp_buf_num);

				if(tmp_buf_num==40)
					
				for(ii=0;ii<40;ii++){
						//USART_SendData(USART1, tmp_buf[ii]);
					printf("%c",&tmp_buf[ii]);
			}

				   
			}else delay_us(100);	   
			t++;
			if(t==10000)//大约1s钟改变一次状态
			{
				t=0;
				LED0=!LED0;
			} 				    
		};	
	}else//TX模式
	{							    
		LCD_ShowString(30,150,200,16,16,"NRF24L01 TX_Mode");	
		NRF24L01_TX_Mode();
		mode=' ';//从空格键开始  
		while(1)
		{	  		   				 
			if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
			{
				LCD_ShowString(30,170,239,32,16,"Sended DATA:");	
				LCD_ShowString(0,190,lcddev.width-1,32,16,tmp_buf); 
				key=mode;
				for(t=0;t<32;t++)
				{
					key++;
					if(key>('~'))key=' ';
					tmp_buf[t]=key;	
				}
				mode++; 
				if(mode>'~')mode=' ';  	  
				tmp_buf[32]=0;//加入结束符		   
			}else
			{										   	
 				LCD_Fill(0,170,lcddev.width,170+16*3,WHITE);//清空显示			   
				LCD_ShowString(30,170,lcddev.width-1,32,16,"Send Failed "); 
			};
			LED0=!LED0;
			delay_ms(1500);				    
		}
	} 
}

