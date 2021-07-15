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
#define LED0_Pin GPIO_PIN_8
#define LED0_GPIO_Port GPIOF
#define LED1_Pin GPIO_PIN_9
#define LED1_GPIO_Port GPIOF
#define LED2_Pin GPIO_PIN_10
#define LED2_GPIO_Port GPIOF
#define LCD5110SDIN_Pin GPIO_PIN_12
#define LCD5110SDIN_GPIO_Port GPIOD
#define LCD5110SCE_Pin GPIO_PIN_13
#define LCD5110SCE_GPIO_Port GPIOD
#define LCD5110SCLK_Pin GPIO_PIN_2
#define LCD5110SCLK_GPIO_Port GPIOG
#define LCD5110RESET_Pin GPIO_PIN_3
#define LCD5110RESET_GPIO_Port GPIOG
#define LCD5110DC_Pin GPIO_PIN_9
#define LCD5110DC_GPIO_Port GPIOA
#define LCD5110GND_Pin GPIO_PIN_10
#define LCD5110GND_GPIO_Port GPIOA
#define ROW3_Pin GPIO_PIN_4
#define ROW3_GPIO_Port GPIOB
#define ROW3_EXTI_IRQn EXTI4_IRQn
#define ROW4_Pin GPIO_PIN_5
#define ROW4_GPIO_Port GPIOB
#define ROW4_EXTI_IRQn EXTI9_5_IRQn
#define COL1_Pin GPIO_PIN_6
#define COL1_GPIO_Port GPIOB
#define COL2_Pin GPIO_PIN_7
#define COL2_GPIO_Port GPIOB
#define COL3_Pin GPIO_PIN_8
#define COL3_GPIO_Port GPIOB
#define COL4_Pin GPIO_PIN_9
#define COL4_GPIO_Port GPIOB
#define ROW1_Pin GPIO_PIN_0
#define ROW1_GPIO_Port GPIOE
#define ROW1_EXTI_IRQn EXTI0_IRQn
#define ROW2_Pin GPIO_PIN_1
#define ROW2_GPIO_Port GPIOE
#define ROW2_EXTI_IRQn EXTI1_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
