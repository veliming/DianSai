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
 ALIENTEK ��ӢSTM32F103������ ʵ��31
 NRF24L01����ͨ��ʵ��-HAL�⺯����
 ����֧�֣�www.openedv.com
 �Ա����̣� http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
int ascii_to_integer( char *string )
{
    int value; value = 0;
    // ������ַ������ַ�ת��Ϊ���֡�
    while( *string >= '0' && *string <= '9' ){
        value *= 10;
        value += *string - '0';
        string++;
    }
    //�����飺�����������һ���������ַ�����ֹ���ѽ������Ϊ0
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
	
    HAL_Init();                    	 	//��ʼ��HAL��    
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//����ʱ��,72M
	delay_init(72);               		//��ʼ����ʱ����
	uart_init(115200);					//��ʼ������	
	LED_Init();							//��ʼ��LED	
	KEY_Init();							//��ʼ������
 	LCD_Init();           				//��ʼ��LCD FSMC�ӿ� 
	NRF24L01_Init();    		    	//��ʼ��NRF24L01 
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
		if(t==100)LCD_ShowString(10,150,230,16,16,"KEY0:RX_Mode  KEY1:TX_Mode"); //��˸��ʾ��ʾ��Ϣ
 		if(t==200)
		{	
			LCD_Fill(10,150,230,150+16,WHITE);
			t=0; 
		}
		delay_ms(5);	  
	}   
 	LCD_Fill(10,150,240,166,WHITE);//����������ʾ		  
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ	   
	if(mode==0)//RXģʽ
	{
		LCD_ShowString(30,150,200,16,16,"NRF24L01 RX_Mode");	
		LCD_ShowString(30,170,200,16,16,"Received DATA:");	
		NRF24L01_RX_Mode();		  
		while(1)
		{	  		    		    				 
			if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
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
			if(t==10000)//��Լ1s�Ӹı�һ��״̬
			{
				t=0;
				LED0=!LED0;
			} 				    
		};	
	}else//TXģʽ
	{							    
		LCD_ShowString(30,150,200,16,16,"NRF24L01 TX_Mode");	
		NRF24L01_TX_Mode();
		mode=' ';//�ӿո����ʼ  
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
				tmp_buf[32]=0;//���������		   
			}else
			{										   	
 				LCD_Fill(0,170,lcddev.width,170+16*3,WHITE);//�����ʾ			   
				LCD_ShowString(30,170,lcddev.width-1,32,16,"Send Failed "); 
			};
			LED0=!LED0;
			delay_ms(1500);				    
		}
	} 
}

