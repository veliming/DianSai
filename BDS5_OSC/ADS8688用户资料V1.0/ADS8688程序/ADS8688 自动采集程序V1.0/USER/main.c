/**********************************************************
                       ��������
���������ѧϰʹ�ã�δ��������ɣ��������������κ���;										 
���ܣ�ADS8688��16λAD 8ͨ���Զ�ɨ��ɼ�   ʹ��оƬ�ڲ���׼4.096V 
			��ʾ��12864cog
�ӿڣ��ӿ������ads8688.h  ��ֱ�����ӱ������ذ�TLV5608�ӿ�
ʱ�䣺2020/12/13
�汾��0.2
���ߣ���������
������������ֻ��ģ�鹦����֤���Ա���ٲ���ģ��û���
			�������������֤�������б��.��������MCU��FPGAʵ�ָ��ٲɼ���������
			
			��ѡ������Ϊ˫����ʱ��0V��Ӧ32767�����V=(ADCֵ-32767)*����/65535��������Ϊ������ʱ���������ȥ32767��

������������뵽�Ա��꣬�������ӽ߳�Ϊ������ ^_^
https://kvdz.taobao.com

**********************************************************/
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "wdg.h"
#include "usb_lib.h"
#include "math.h"
#include "hw_config.h"
#include "string.h"
#include "stdlib.h"
#include "lcd.h"
#include "ads8688.h"
/**********************************************************
* �������� ---> USB����/�Ͽ�
* ��ڲ��� ---> usb_sw��USB����/�رտ��ơ�0���ر�
*                                         1����
* ������ֵ ---> none
* ����˵�� ---> none
**********************************************************/	   
void USB_Port_Set(u8 usb_sw)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);    //ʹ��PORTAʱ��
		   	 
	if(usb_sw)	_SetCNTR(_GetCNTR()&(~(1<<1)));//�˳��ϵ�ģʽ
	else
	{	  
		_SetCNTR(_GetCNTR()|(1<<1));  // �ϵ�ģʽ
		GPIOA->CRH &= 0XFFF00FFF;
		GPIOA->CRH |= 0X00033000;
		PAout(12) = 0;	    		  
	}
}
 
void display(void)
{	
	LCD_Show_CEStr(0,0,"I1");
	LCD_Show_CEStr(64,0,"I2");
	LCD_Show_CEStr(0,2,"I3");
	LCD_Show_CEStr(64,2,"I4");
	LCD_Show_CEStr(0,4,"I5");
	LCD_Show_CEStr(64,4,"I6");
	LCD_Show_CEStr(0,6,"I7");
	LCD_Show_CEStr(64,6,"I8");
	LCD_Refresh_Gram();
}	
int main(void)
{
	uint8_t i=0;
	char showLcd[30];
	char infoBackPC[64];
	uint16_t value[8];

	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
	uart_init(9600);   //���ڳ�ʼ��
	key_init();//������ʼ��
	initial_lcd();//Һ����ʼ��
	LCD_Clear();
	LCD_Show_CEStr(10,0,"ADS8688-16bit");//ADS8688 16λadc
	LCD_Show_CEStr(40,2,"Auto");//�Զ�
	LCD_Show_CEStr(40,4,"Unit:1mV");//��λ
	LCD_Refresh_Gram();
	delay_ms(1000);
	USB_Port_Set(0); 	//USB�ȶϿ�
	delay_ms(600);
	USB_Port_Set(1);	//USB�ٴ�����
	USB_Config();
	LCD_Clear();
	
	ADS8688_Init(CH0_EN|CH1_EN|CH2_EN|CH3_EN|CH4_EN|CH5_EN|CH6_EN|CH7_EN);//ADS8688��ʼ��
  Set_CH_Range(CHIR_0,ADS8688_IR_N2_5V);
  Set_CH_Range(CHIR_1,ADS8688_IR_N2_5V);
  Set_CH_Range(CHIR_2,ADS8688_IR_N2_5V);
  Set_CH_Range(CHIR_3,ADS8688_IR_N2_5V);
  Set_CH_Range(CHIR_4,ADS8688_IR_N2_5V);
  Set_CH_Range(CHIR_5,ADS8688_IR_N2_5V);
  Set_CH_Range(CHIR_6,ADS8688_IR_N2_5V);
  Set_CH_Range(CHIR_7,ADS8688_IR_N2_5V);//����ͨ�����뷶Χ����10.24V   ��2.5*ref  ref=4.096V  
  AUTO_RST_Mode();//�����Զ�ɨ��ģʽ
	display();
  while(1)
  {
		delay_ms(10);
    Get_AUTO_RST_Mode_Data(value,8);//�Զ�ɨ��ģʽ���Զ�ɨ�貢ת��8ͨ�������ݴ���value������
		for(i = 0; i < 4; i++) //��ʾ
		{
			sprintf(showLcd, "%06d", (int16_t)((value[i*2]-32767)*CONST_N2_5V_LSB_mV));//������ΧΪ����Ҫ��ȥ32767
			LCD_ShowString(0,16 , i*16, (const u8*)showLcd);
			
			sprintf(showLcd, "%06d", (int16_t)((value[i*2+1]-32767)*CONST_N2_5V_LSB_mV));	
			LCD_ShowString(0,80 , i*16, (const u8*)showLcd);
		}
		LCD_Refresh_Gram();
		for(i = 0; i < 4; i++)//����
		{
			sprintf(infoBackPC, "AIN%d=%06dmV  AIN%d=%06dmV\r\n",i*2+1,(int16_t)((value[i*2]-32767)*CONST_N2_5V_LSB_mV),i*2+2,(int16_t)((value[i*2+1]-32767)*CONST_N2_5V_LSB_mV));			
			USB_TxWrite((uint8_t*)infoBackPC, strlen(infoBackPC)); //usb����
			printf("%s",infoBackPC);  //���ڷ���	
		}
		USB_TxWrite("\r\n", 2); //usb����
		printf("\r\n");  //���ڷ���			
  }		
}

 












 
 
 
 
 
 
 
