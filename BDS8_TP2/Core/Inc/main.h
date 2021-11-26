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

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Trig2_Pin GPIO_PIN_2
#define Trig2_GPIO_Port GPIOE
#define Trig2_EXTI_IRQn EXTI2_IRQn
#define GND_Pin GPIO_PIN_5
#define GND_GPIO_Port GPIOE
#define GNDC13_Pin GPIO_PIN_13
#define GNDC13_GPIO_Port GPIOC
#define Trig1_Pin GPIO_PIN_0
#define Trig1_GPIO_Port GPIOF
#define Trig1_EXTI_IRQn EXTI0_IRQn
#define GNDF9_Pin GPIO_PIN_9
#define GNDF9_GPIO_Port GPIOF
#define GNDF10_Pin GPIO_PIN_10
#define GNDF10_GPIO_Port GPIOF
#define PW_V_Pin GPIO_PIN_2
#define PW_V_GPIO_Port GPIOC
#define GNDC3_Pin GPIO_PIN_3
#define GNDC3_GPIO_Port GPIOC
#define PW_C_Pin GPIO_PIN_0
#define PW_C_GPIO_Port GPIOA
#define DC_V_Pin GPIO_PIN_4
#define DC_V_GPIO_Port GPIOA
#define BT_V_Pin GPIO_PIN_6
#define BT_V_GPIO_Port GPIOA
#define BT_C_Pin GPIO_PIN_4
#define BT_C_GPIO_Port GPIOC
#define COL4_Pin GPIO_PIN_1
#define COL4_GPIO_Port GPIOG
#define COL3_Pin GPIO_PIN_7
#define COL3_GPIO_Port GPIOE
#define COL2_Pin GPIO_PIN_8
#define COL2_GPIO_Port GPIOE
#define COL1_Pin GPIO_PIN_9
#define COL1_GPIO_Port GPIOE
#define ROW1_Pin GPIO_PIN_10
#define ROW1_GPIO_Port GPIOE
#define ROW1_EXTI_IRQn EXTI15_10_IRQn
#define ROW2_Pin GPIO_PIN_11
#define ROW2_GPIO_Port GPIOE
#define ROW2_EXTI_IRQn EXTI15_10_IRQn
#define ROW3_Pin GPIO_PIN_12
#define ROW3_GPIO_Port GPIOE
#define ROW3_EXTI_IRQn EXTI15_10_IRQn
#define ROW4_Pin GPIO_PIN_13
#define ROW4_GPIO_Port GPIOE
#define ROW4_EXTI_IRQn EXTI15_10_IRQn
#define LCD5110RESET_Pin GPIO_PIN_14
#define LCD5110RESET_GPIO_Port GPIOE
#define LCD5110SCE_Pin GPIO_PIN_15
#define LCD5110SCE_GPIO_Port GPIOE
#define LCD5110SDIN_Pin GPIO_PIN_10
#define LCD5110SDIN_GPIO_Port GPIOB
#define LCD5110DC_Pin GPIO_PIN_11
#define LCD5110DC_GPIO_Port GPIOB
#define LCD5110SCLK_Pin GPIO_PIN_13
#define LCD5110SCLK_GPIO_Port GPIOB
#define SW1_Pin GPIO_PIN_0
#define SW1_GPIO_Port GPIOD
#define SW2_Pin GPIO_PIN_1
#define SW2_GPIO_Port GPIOD
#define SW3_Pin GPIO_PIN_2
#define SW3_GPIO_Port GPIOD
#define SW4_Pin GPIO_PIN_3
#define SW4_GPIO_Port GPIOD
#define SW5_Pin GPIO_PIN_4
#define SW5_GPIO_Port GPIOD
#define SW6_Pin GPIO_PIN_5
#define SW6_GPIO_Port GPIOD
#define LED0_Pin GPIO_PIN_13
#define LED0_GPIO_Port GPIOG
#define LED1_Pin GPIO_PIN_14
#define LED1_GPIO_Port GPIOG
#define GNDG15_Pin GPIO_PIN_15
#define GNDG15_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
