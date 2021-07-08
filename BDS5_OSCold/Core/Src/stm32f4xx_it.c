/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ADS8688.h"
#include "usart.h"
#include "hmi_user_uart.h"
//#include "dac.h"
#include "spi.h"
#include "obase.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
extern uint16_t chufazhuangtai;
//全局变量
extern int count_caiyang,count_pinlv;      //定时器计数器
//水平刻度     0�??????????????????1ms档位     1,10ms档位       2,100ms档位
extern uint8_t shuiping_scale;
//水平刻度对应的分�??????????????????
extern int fenpin_count[3];
//采样总时间（�??????????????????大计数器计数值）
extern int max_count[3];
//采样到的�??????????????????
extern uint16_t ch1_values[500],ch2_values[500];
//两个通道采样到的点的�??????????????????大�?�和�??????????????????小�??
extern uint16_t ch1_max,ch2_max,ch1_min,ch2_min;
//触发电平
extern uint16_t chufa_volts;
//触发模式   0上升沿触�??????????????????    1下降沿触�??????????????????
extern uint8_t chufa_mode;
//触发通道  0,�??????????????????通道   1，二通道
extern uint8_t chufa_ch;
//两个通道的合计�??  （用来测量平均�?�）

//�??????????????些暂存�??
int xiabiao;
uint16_t ad_temp;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern ADS8688 ads;
extern uint16_t ads_data[2];
extern float volt1[400];
extern float volt2[400];
extern uint8_t rxbuf[2][4];
extern uint16_t ads_data[2];
extern uint8_t txbuf[2];
extern uint16_t trigger_volt;
uint8_t CH=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//收到的指�?????
extern uint8_t R_alldata[256];   //指令完整内容
extern uint8_t R_onedata;    //指令单元
extern uint16_t R_place;         //接收指令的位�?????
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim3;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */
extern uint16_t ch1_maxdata,ch1_mindata;

extern uint16_t ch2_maxdata,ch2_mindata;

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  HAL_RCC_NMI_IRQHandler();
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 stream6 global interrupt.
  */
void DMA1_Stream6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream6_IRQn 0 */

  /* USER CODE END DMA1_Stream6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_tx);
  /* USER CODE BEGIN DMA1_Stream6_IRQn 1 */
  huart2.gState=HAL_UART_STATE_READY;

  /* USER CODE END DMA1_Stream6_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */
  ADS_Read_All_Raw(&ads, ads_data);
  ch1_values[count_caiyang] = ads_data[0];
  ch2_values[count_caiyang] = ads_data[1];

  if(ads_data[0]>ch1_maxdata)ch1_maxdata=ads_data[0];
  if(ads_data[0]>ch2_maxdata)ch2_maxdata=ads_data[1];
  if(ads_data[0]<ch1_mindata)ch1_mindata=ads_data[0];
  if(ads_data[0]<ch2_mindata)ch2_mindata=ads_data[1];

  if(chufazhuangtai && ch1_values[count_caiyang]>32768 && ch1_values[count_caiyang-1]<32768)
  {
	  count_caiyang=0;
	  chufazhuangtai=0;
	  ch1_maxdata=0;
	  ch1_mindata=65535;
	  ch2_maxdata=0;
	  ch2_mindata=65535;
  }


  if(++count_caiyang>=402)
  {
	  HAL_TIM_Base_Stop_IT(&htim3);
	  count_caiyang=0;
	  FinishCount();
  }


//
//
//  ADS_Read_All_Raw(&ads, ads_data);
//      HAL_UART_Transmit(&huart2, ads_data, 4, 5);
//      HAL_UART_Transmit(&huart2, "\0", 1, 5);

//        //先判断预分频系数和count，看此次中断是否�?????????????要采�?????????????
//        if(count_caiyang%fenpin_count[shuiping_scale]==0)
//        {
//      	  ADS_Read_All_Raw(&ads, ads_data);
//      	  xiabiao = count_caiyang/fenpin_count[shuiping_scale];
//      	  ch1_values[xiabiao] = ads_data[0];
//      	  ch2_values[xiabiao] = ads_data[1];
//      	  if(ch1_values[xiabiao]=ch1_values)
//        }
//        //判断是否结束采样
//        if(++count_caiyang>=max_count[shuiping_scale])
//        {
//      	  HAL_TIM_Base_Stop_IT(&htim3);
//      	  count_caiyang=0;
//      	  FinishCount();
//        }


  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
