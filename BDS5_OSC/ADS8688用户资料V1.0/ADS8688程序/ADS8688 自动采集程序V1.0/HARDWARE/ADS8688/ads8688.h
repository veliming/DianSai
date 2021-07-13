#ifndef __ADS8688_H
#define __ADS8688_H	 
#include "sys.h"
#include "stm32f10x.h"
/*************************************************************************************************************/
//����Ĵ��� 
#define NO_OP			0x0000 /*��ѡ��ģʽ�¼�������  
													���豸�����ڼ佫SDI����������Ϊ�͵�ƽ���൱��������16λд��0�������������ѡ���ģʽ��STDBY��PWR_DN��AUTO_RST��MAN_Ch_n���½����豸������
													������ģʽ�£��豸����ѭ����Ĵ�������ַ01h��3Ch���������õ���ͬ���á�*/
#define STDBY			0x8200 /*����ģʽ   
													����֧�ֵ͹��Ĵ���ģʽ��STDBY�����ڸ�ģʽ�£������ֵ�·�ϵ硣
													�ڲ���׼��ѹԴ�ͻ�����δ�ϵ磬���˳�STDBYģʽʱ��������20 ��s��Ϊ�����ӵ硣�˳�STDBYģʽʱ������Ĵ������ḴλΪĬ��ֵ��*/
#define PWR_DN  	0x8300/*����ģʽ��PWR_DN��
													����֧��Ӳ�����������ģʽ��PWR_DN�����ڸ�ģʽ�£������ڲ���·�������磬�����ڲ���׼��ѹԴ�ͻ�������
													����豸���ڲ��ο�ģʽ�����У�REFSEL = 0�������˳�PWR_DNģʽ���豸�ӵ粢ת����ѡģ������ͨ��������Ҫ15 ms��ʱ�䡣
													�豸��Ӳ����Դģʽ��RST / PD�����룩������˵����
													Ӳ�����������ģʽ֮�����Ҫ�������ڣ����豸��Ӳ�����绽��ʱ������Ĵ���������ΪĬ��ֵ�����ǵ��豸���������ʱ������Ĵ�������ǰ���ûᱣ�����硣*/
#define RST				0x8500/*���ó���Ĵ�����RST��
													����֧��Ӳ���������λ��RST��ģʽ���ڸ�ģʽ�£����г���Ĵ�������λΪ��Ĭ��ֵ��Ҳ����ʹ��Ӳ�����Ž��豸����RSTģʽ*/
#define AUTO_RST	0xA000/*�Զ�ͨ������
													�Զ�ɨ������ģ���ŵ��ϵ������źš��Զ�ɨ���ͨ�����п��ɳ���Ĵ����е��Զ�ɨ��˳����ƼĴ�����01h��02h�����ã�����ĳ���Ĵ���ӳ�䲿�֡�
													�ڴ�ģʽ�£��豸����������ѭ��ͨ����ѡͨ���������ͨ����ʼ��ת������Ĵ�����ѡ�������ͨ����
													������ɺ��豸���ص�����Ĵ����е���ͼ���ͨ�������ظ������С�ͨ�����ó���Ĵ����ķ�Χѡ��Ĵ��������������Զ�ɨ��������ÿ��ͨ���������ѹ��Χ��*/
#define MAN_CH_0	0xC000/**/
#define MAN_CH_1	0xC400/**/
#define MAN_CH_2	0xC800/**/
#define MAN_CH_3	0xCC00/**/
#define MAN_CH_4	0xD000/**/
#define MAN_CH_5	0xD400/**/
#define MAN_CH_6	0xD800/**/
#define MAN_CH_7	0xDC00/*�ֶ�ͨ��nѡ��MAN_Ch_n��
												ͨ�����ֶ�ͨ��nɨ��ģʽ��MAN_Ch_n���н��в��������Զ��豸���б����ת���ض���ģ������ͨ����ͨ��������Ĵ�����д����Ч���ֶ�ͨ��nѡ�����MAN_Ch_n������ɸñ��*/
#define MAN_AUX		0XE000/*AUXͨ��*/

//����Ĵ���
#define AUTO_SEQ_EN	0x01	/*�Զ�ɨ������ʹ�ܼĴ���
													�üĴ���ѡ�񵥸�ͨ������AUTO_RSTģʽ�½������� 
													�üĴ�����Ĭ��ֵΪFFh������ζ����Ĭ������������ͨ�����������Զ�ɨ�������С�*/
#define CH_PD				0x02	/*ͨ������Ĵ���
													�üĴ����رյ�AUTO_RSTģʽ�²������ĵ���ͨ���ĵ�Դ�� �üĴ�����Ĭ��ֵΪ00h������ζ����Ĭ������������ͨ�������ϵ硣*/																
#define F_S					0X03	/*��������ѡ����ƼĴ���
													�üĴ����е�λ���������þջ����������豸ID��������SDO�ϵ����λ��ʽ��*/
							
//��ͨ����Χѡ��Ĵ���	Ĭ��ֵΪ00h		 				
#define CHIR_0		0x05/**/
#define CHIR_1		0x06/**/
#define CHIR_2		0x07/**/
#define CHIR_3		0x08/**/
#define CHIR_4		0x09/**/
#define CHIR_5		0x0A/**/
#define CHIR_6		0x0B/**/
#define CHIR_7		0x0C/**/

#define CMD_READ	0x3F	/*����ض��Ĵ���
												�üĴ��������û���ȡ�豸�Ĳ���ģʽ�� ִ�д�������豸�������ǰһ������֡��ִ�е������֡�
												�й�����Ĵ�����������Ϣ��ǰ8λ�а��������Һ�8λΪ0��*/
												
/*************************************************************************************************************/
#define CH7_EN  0X80
#define CH6_EN  0X40
#define CH5_EN  0X20
#define CH4_EN  0X10
#define CH3_EN  0X08
#define CH2_EN  0X04
#define CH1_EN  0X02
#define CH0_EN  0X01

#define REF 4096
//���뷶Χ
#define ADS8688_IR_N2_5V    0x00  //��2.5*ref  ref=4.096V  ��10.24V
#define ADS8688_IR_N1_25V   0x01  //��1.25*ref    ��5.12V
#define ADS8688_IR_N0_625V  0x02  //��0.625*ref   ��2.56V

#define ADS8688_IR_2_5V   	0x05  //0-2.5*ref      0-10.24V
#define ADS8688_IR_1_25V    0x06  //0-1.25*ref     0-5.12V

#define CONST_N2_5V_LSB_mV  	2.5*2*REF/65535
#define CONST_N1_25V_LSB_mV  	1.25*2*REF/65535
#define CONST_N0_625V_LSB_mV  0.625*2*REF/65535
#define CONST_2_5V_LSB_mV  		2.5*REF/65535
#define CONST_1_25V_LSB_mV 	 	1.25*REF/65535


#define SDI_H			GPIO_SetBits(GPIOC,GPIO_Pin_8)      //����ͨ����������
#define RST_H			GPIO_SetBits(GPIOC,GPIO_Pin_9)     //��λ
#define DAISY_H		GPIO_SetBits(GPIOC,GPIO_Pin_10) //�Ծջ���ģʽ���Ӵ���ͨ���ڼ����������
#define CLK_H			GPIO_SetBits(GPIOC,GPIO_Pin_12)   //����ͨ��ʱ������
#define CS_H			GPIO_SetBits(GPIOC,GPIO_Pin_13)   //Ƭѡ

#define SDI_L			GPIO_ResetBits(GPIOC,GPIO_Pin_8)
#define RST_L			GPIO_ResetBits(GPIOC,GPIO_Pin_9)  //>400ns
#define DAISY_L		GPIO_ResetBits(GPIOC,GPIO_Pin_10)
#define CLK_L			GPIO_ResetBits(GPIOC,GPIO_Pin_12)
#define CS_L			GPIO_ResetBits(GPIOC,GPIO_Pin_13)

#define READ_SDO		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)

//#define SDI_H		PCout(8)=1
//#define RST_H		PCout(9)=1
//#define CLK_H		PCout(12)=1 
//#define CS_H		PCout(13)=1

//#define SDI_L		PCout(8)=0
//#define RST_L		PCout(9)=0   //>400ns
//#define CLK_L		PCout(12)=0
//#define CS_L		PCout(13)=0

////#define TLV_DATA	PCout(10) 
//#define READ_SDO		PCin(11) 

void ADS8688_IO_Init(void);	   //ADS8688 IO�ڳ�ʼ��
void ADS8688_Init(uint8_t ch_en);	   //ADS8688��ʼ��

uint8_t ADS8688_SPI_Read8Bit(void);//��8��bit����
void ADS8688_SPI_Write8Bit(uint8_t com);//д8��bit����

void ADS8688_WriteCmd(uint16_t cmd);//дADS8688����Ĵ���

void SOFT_RESET(void);//�����λ
void AUTO_RST_Mode(void);//�Զ�ɨ��ģʽ
void MAN_CH_Mode(uint16_t ch);//�ֶ�ģʽ

uint8_t ADS8688_ReadReg(uint8_t addr);//��ָ���ļĴ���
void ADS8688_WriteReg(uint8_t addr,uint8_t data);//дָ���ļĴ���

void Set_Auto_Scan_Sequence(uint8_t seq);//�����Զ�ɨ������ͨ��
void Set_CH_Range(uint8_t ch,uint8_t range);//����ָ��ͨ��������Χ
	
u16 Get_MAN_CH_Mode_Data(void);//��ȡ�ֶ�ģʽADֵ
void Get_AUTO_RST_Mode_Data(uint16_t* outputdata, uint8_t chnum);//��ȡ�Զ�ɨ��ģʽADֵ





#endif















