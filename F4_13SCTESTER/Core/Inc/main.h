/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "base.h"

#define u32 uint32_t
#define u16 uint16_t
#define u8 uint8_t
#define s32 int32_t
#define s16 int16_t
#define s8 int8_t
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#pragma pack(push)
#pragma pack(1)	//按字节对齐
typedef struct _SVAR
{
  u8  WIFI     ;   //WIFI状态是否开启
  u8  CH_SELECT;   //当前所选通道 0 1 2 3
  u8  TG_SOURCE;   //触发源 1-CH1 2-CH2
  u8  TG_MODE;     //触发模式 1-上升沿触发，2-下降沿触发，3-电平触发
  u8  RUN;         //是否STOP
  u8  AUTO;        //是否AUTO
  u8  COUPE;       //耦合方式 0-直流 1-交流
  u16 TG_VAL;      //触发电平
  float VREF;      //ADS参考电压
  float VCC;       //STM32参考电压
  float COMPENSATE;//频率补偿
}SVAR;
#pragma pack(pop)
extern SVAR Svar;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY0_Pin GPIO_PIN_2
#define KEY0_GPIO_Port GPIOE
#define KEY1_Pin GPIO_PIN_3
#define KEY1_GPIO_Port GPIOE
#define KEY2_Pin GPIO_PIN_4
#define KEY2_GPIO_Port GPIOE
#define TCS_Pin GPIO_PIN_13
#define TCS_GPIO_Port GPIOC
#define LED0_Pin GPIO_PIN_8
#define LED0_GPIO_Port GPIOF
#define LED1_Pin GPIO_PIN_9
#define LED1_GPIO_Port GPIOF
#define LED2_Pin GPIO_PIN_10
#define LED2_GPIO_Port GPIOF
#define TCLK_Pin GPIO_PIN_0
#define TCLK_GPIO_Port GPIOB
#define PEN_Pin GPIO_PIN_1
#define PEN_GPIO_Port GPIOB
#define DOUT_Pin GPIO_PIN_2
#define DOUT_GPIO_Port GPIOB
#define TDIN_Pin GPIO_PIN_11
#define TDIN_GPIO_Port GPIOF
#define W25Q128_CS_Pin GPIO_PIN_14
#define W25Q128_CS_GPIO_Port GPIOB
#define LCD_BL_Pin GPIO_PIN_15
#define LCD_BL_GPIO_Port GPIOB
#define TFT_UART_TX_Pin GPIO_PIN_9
#define TFT_UART_TX_GPIO_Port GPIOA
#define TFT_UART_RX_Pin GPIO_PIN_10
#define TFT_UART_RX_GPIO_Port GPIOA
#define ADS8688_CS_Pin GPIO_PIN_15
#define ADS8688_CS_GPIO_Port GPIOA
#define ADS8688_SCK_Pin GPIO_PIN_10
#define ADS8688_SCK_GPIO_Port GPIOC
#define ADS8688_MISO_Pin GPIO_PIN_11
#define ADS8688_MISO_GPIO_Port GPIOC
#define ADS8688_MOSI_Pin GPIO_PIN_12
#define ADS8688_MOSI_GPIO_Port GPIOC
#define ADS8688_GND_Pin GPIO_PIN_2
#define ADS8688_GND_GPIO_Port GPIOD
#define ADS8688_GNDD3_Pin GPIO_PIN_3
#define ADS8688_GNDD3_GPIO_Port GPIOD
#define IIC_SCL_Pin GPIO_PIN_8
#define IIC_SCL_GPIO_Port GPIOB
#define IIC_SDA_Pin GPIO_PIN_9
#define IIC_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
