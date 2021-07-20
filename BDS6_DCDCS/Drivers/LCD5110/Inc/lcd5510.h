#ifndef __LCD5510_H
#define __LCD5510_H	

#include "obase.h"
#include "main.h"
#include "stm32f4xx_hal_gpio.h"





#define sce0      HAL_GPIO_WritePin(LCD5110SCE_GPIO_Port,LCD5110RESET_Pin,GPIO_PIN_RESET) //片选
#define res0      HAL_GPIO_WritePin(LCD5110RESET_GPIO_Port,LCD5110RESET_Pin,GPIO_PIN_RESET)  //复位,0复位
#define dc0       HAL_GPIO_WritePin(LCD5110DC_GPIO_Port, LCD5110DC_Pin,GPIO_PIN_RESET)   //1写数据，0写指令
#define sdin0     HAL_GPIO_WritePin(LCD5110SDIN_GPIO_Port, LCD5110SDIN_Pin,GPIO_PIN_RESET)   //数据
#define sclk0     HAL_GPIO_WritePin(LCD5110SCLK_GPIO_Port,LCD5110SCLK_Pin,GPIO_PIN_RESET)   //时钟
//#define backled0  HAL_GPIO_WritePin(LCD5110LED_GPIO_Port, LCD5110LED_Pin,GPIO_PIN_RESET)   //背光

#define sce1      HAL_GPIO_WritePin(LCD5110SCE_GPIO_Port,LCD5110RESET_Pin,GPIO_PIN_SET);  //片选
#define res1      HAL_GPIO_WritePin(LCD5110RESET_GPIO_Port,LCD5110RESET_Pin,GPIO_PIN_SET)  //复位,0复位
#define dc1       HAL_GPIO_WritePin(LCD5110DC_GPIO_Port, LCD5110DC_Pin,GPIO_PIN_SET)   //1写数据，0写指令
#define sdin1     HAL_GPIO_WritePin(LCD5110SDIN_GPIO_Port, LCD5110SDIN_Pin,GPIO_PIN_SET)  //数据
#define sclk1     HAL_GPIO_WritePin(LCD5110SCLK_GPIO_Port,LCD5110SCLK_Pin,GPIO_PIN_SET)   //时钟
//#define backled1  HAL_GPIO_WritePin(LCD5110LED_GPIO_Port, LCD5110LED_Pin,GPIO_PIN_SET)   //背光

extern const unsigned char  font6x8[][6];
extern const unsigned char shuzi[];
extern const unsigned char han[];
/*row:�� page:ҳ dd:�ַ�*/


void LCD_write_byte(unsigned char dt, unsigned char command);                         //名称: 使用SPI接口写数据到LCD
void LCD_init(void);                                                                  //名称: 5110LCD初始化函数
void LCD_set_XY(unsigned char X, unsigned char Y);                                    //名称: 设置坐标函数
void LCD_clear(void);                                                                 //名称: LCD清屏函数
void LCD_write_char(unsigned char c);                                                 //名称: 显示英文字符
void LCD_write_String(unsigned char X,unsigned char Y,char *s);                       //名称: 英文字符串显示函数
void LCD_write_shu(unsigned char row, unsigned char page,unsigned char c);            //名称: 写一个字符到LCD函数（8*16点阵）
void LCD_write_hanzi(unsigned char row, unsigned char page,unsigned char c);          //名称: 写一个汉字到LCD函数
void LCD_write_wenzi(unsigned char row, unsigned char page,unsigned char c);

#endif

