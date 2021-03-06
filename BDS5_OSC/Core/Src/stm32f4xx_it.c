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
#include "spi.h"
#include "obase.h"
#include "string.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

uint8_t ADS_CH=0;

//uint8_t rxbuf[2][2] = {0};
//uint8_t txbuf[2] = {0x00, 0x00};

extern ADS8688 ads;
extern uint16_t ads_data[2];

extern uint8_t CH0_ON;
extern uint8_t CH1_ON;
extern uint8_t TriggerCH;
extern uint8_t TriggerMODE;
extern uint8_t TrigFlag;
extern uint16_t TrigValue;
extern uint16_t TrigPosit;

extern uint8_t CHdata0[400];
extern uint8_t CHdata1[400];

extern uint16_t savedata0[2000];
extern uint16_t savedata1[2000];

extern uint8_t savedata0_8[2000];
extern uint8_t savedata1_8[2000];

uint8_t saveflag;

extern uint16_t savenum;

extern uint8_t CH0_num[828];
extern uint8_t CH1_num[414];

extern uint8_t ProcessOn;
extern uint8_t SendOn;

extern uint16_t AmpRate;

extern uint16_t ch1max;
extern uint16_t ch1min;
extern uint16_t ch1vpp;
extern uint32_t ch1avg;
extern uint16_t ch0max;
extern uint16_t ch0min;
extern uint16_t ch0vpp;
extern uint32_t ch0avg;

uint16_t TrigPosit_tu;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_spi3_rx;
extern DMA_HandleTypeDef hdma_spi3_tx;
extern DMA_HandleTypeDef hdma_tim2_ch1;
extern DMA_HandleTypeDef hdma_tim5_ch1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */

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
  * @brief This function handles DMA1 stream0 global interrupt.
  */
void DMA1_Stream0_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream0_IRQn 0 */

  /* USER CODE END DMA1_Stream0_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_spi3_rx);
  /* USER CODE BEGIN DMA1_Stream0_IRQn 1 */

  /* USER CODE END DMA1_Stream0_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream2 global interrupt.
  */
void DMA1_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream2_IRQn 0 */

  /* USER CODE END DMA1_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_tim5_ch1);
  /* USER CODE BEGIN DMA1_Stream2_IRQn 1 */

  /* USER CODE END DMA1_Stream2_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream5 global interrupt.
  */
void DMA1_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream5_IRQn 0 */

  /* USER CODE END DMA1_Stream5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_tim2_ch1);
  /* USER CODE BEGIN DMA1_Stream5_IRQn 1 */

  /* USER CODE END DMA1_Stream5_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream6 global interrupt.
  */
void DMA1_Stream6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream6_IRQn 0 */

  /* USER CODE END DMA1_Stream6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_tx);
  /* USER CODE BEGIN DMA1_Stream6_IRQn 1 */

  /* USER CODE END DMA1_Stream6_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
	  FinishCount();
  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */
  if(ProcessOn==0&&SendOn==1)
  {

  if(CH0_ON==1&&CH1_ON==0)
  {
	  HAL_UART_Transmit_DMA(&huart2, (uint8_t*)&CH0_num[0], 414);
  }
  else if(CH0_ON==0&&CH1_ON==1)
  {
	  HAL_UART_Transmit_DMA(&huart2, (uint8_t*)&CH1_num[0], 414);
  }
  else if(CH0_ON==1&&CH1_ON==1)
  {
	  memcpy(CH0_num+414*sizeof(uint8_t),CH1_num,sizeof(CH1_num));
	 HAL_UART_Transmit_DMA(&huart2, (uint8_t*)&CH0_num[0] , 828);
  }
  else{}

 	ProcessOn=0;
	SendOn=0;
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim4);
  }



  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */

  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */
  if(ProcessOn==0&&SendOn==0)
  {


	  //????????????
	  ADS_Read_All_Raw(&ads, ads_data);
	  if(ads_data[0]>(32767/AmpRate+32767))
	  {
		  savedata0[savenum]=65535;
	  }
	  else if(ads_data[0]<-32767/AmpRate+32767)
	  {
		  savedata0[savenum]=0;
	  }
	  else {savedata0[savenum]=(ads_data[0]-32767)*AmpRate+32767;}


	  if(ads_data[1]>32767/AmpRate+32767)
	  {
		  savedata1[savenum]=65535;
	  }
	  else if(ads_data[1]<-32767/AmpRate+32767)
	  {
		  savedata1[savenum]=0;
	  }
	  else {savedata1[savenum]=(ads_data[1]-32767)*AmpRate+32767;}
	  savenum++;
	  if(savenum>2000)
	  {
		  savenum=0;
		  ProcessOn=1;
		  HAL_TIM_Base_Stop_IT(&htim4);
	  }
  }
  /* USER CODE END TIM4_IRQn 1 */
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

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream7 global interrupt.
  */
void DMA1_Stream7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream7_IRQn 0 */

  /* USER CODE END DMA1_Stream7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_spi3_tx);
  /* USER CODE BEGIN DMA1_Stream7_IRQn 1 */

  /* USER CODE END DMA1_Stream7_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global interrupt, DAC1 and DAC2 underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */

  /* USER CODE END TIM6_DAC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

	  //????????????????????
if(ProcessOn==1)
{
for (TrigPosit = 20; TrigPosit < 2000; ++TrigPosit)
{
if(TriggerCH==0&&TriggerMODE==0)
{
	//??????
//		if(savedata0[TrigPosit+10]>TrigValue&&savedata0[TrigPosit+9]>TrigValue&&savedata0[TrigPosit+8]>TrigValue&&savedata0[TrigPosit+7]>
//			TrigValue&&savedata0[TrigPosit+6]>TrigValue&&savedata0[TrigPosit+5]>TrigValue&&savedata0[TrigPosit-10]<TrigValue&&savedata0[TrigPosit-9]<
//			TrigValue&&savedata0[TrigPosit-8]<TrigValue&&savedata0[TrigPosit-7]<TrigValue&&savedata0[TrigPosit-6]<TrigValue&&savedata0[TrigPosit-5]<
//			TrigValue)
	if(savedata0[TrigPosit+1]>TrigValue&&savedata0[TrigPosit-1]<TrigValue)
	{
		TrigPosit_tu=TrigPosit;
		for (int var = TrigPosit,i=0; var < TrigPosit+400; ++var,++i)
		{
			savedata0_8[i]=savedata0[var]>>8;
			savedata1_8[i]=savedata1[var]>>8;
			if(savedata0[var]>ch0max)ch0max=savedata0[var];
			if(savedata0[var]<ch0min)ch0min=savedata0[var];
			if(savedata1[var]>ch1max)ch1max=savedata1[var];
			if(savedata1[var]<ch1min)ch1min=savedata1[var];

		}
		memcpy(CH0_num+10,savedata0_8,400);
		memcpy(CH1_num+10,savedata1_8,400);
		break;
	}
}
else if(TriggerCH==1&&TriggerMODE==0)
{
	if(savedata1[TrigPosit+1]>TrigValue&&savedata1[TrigPosit-1]<TrigValue)
	{
		TrigPosit_tu=TrigPosit;
		for (int var = TrigPosit,i=0; var < TrigPosit+400; ++var,++i)
		{
			savedata0_8[i]=savedata0[var]>>8;
			savedata1_8[i]=savedata1[var]>>8;
			if(savedata0[var]>ch0max)ch0max=savedata0[var];
			if(savedata0[var]<ch0min)ch0min=savedata0[var];
			if(savedata1[var]>ch1max)ch1max=savedata1[var];
			if(savedata1[var]<ch1min)ch1min=savedata1[var];
		}
		memcpy(CH0_num+10*sizeof(uint8_t),savedata0_8,400*sizeof(uint8_t));
		memcpy(CH1_num+10*sizeof(uint8_t),savedata1_8,400*sizeof(uint8_t));
		break;
	}
}
else if(TriggerCH==0&&TriggerMODE==1)
{
	if(savedata0[TrigPosit+1]<TrigValue&&savedata0[TrigPosit-1]>TrigValue)
	{
		TrigPosit_tu=TrigPosit;
		for (int var = TrigPosit,i=0; var < TrigPosit+400; ++var,++i)
		{
			savedata0_8[i]=savedata0[var]>>8;
			savedata1_8[i]=savedata1[var]>>8;
			if(savedata0[var]>ch0max)ch0max=savedata0[var];
			if(savedata0[var]<ch0min)ch0min=savedata0[var];
			if(savedata1[var]>ch1max)ch1max=savedata1[var];
			if(savedata1[var]<ch1min)ch1min=savedata1[var];
		}
		memcpy(CH0_num+10*sizeof(uint8_t),savedata0_8,400*sizeof(uint8_t));
		memcpy(CH1_num+10*sizeof(uint8_t),savedata1_8,400*sizeof(uint8_t));
		break;
	}
}
else if(TriggerCH==1&&TriggerMODE==1)
{
	if(savedata1[TrigPosit+1]<TrigValue&&savedata1[TrigPosit-1]>TrigValue)
	{
		TrigPosit_tu=TrigPosit;
		for (int var = TrigPosit,i=0; var < TrigPosit+400; ++var,++i)
		{
			savedata0_8[i]=savedata0[var]>>8;
			savedata1_8[i]=savedata1[var]>>8;
			if(savedata0[var]>ch0max)ch0max=savedata0[var];
			if(savedata0[var]<ch0min)ch0min=savedata0[var];
			if(savedata1[var]>ch1max)ch1max=savedata1[var];
			if(savedata1[var]<ch1min)ch1min=savedata1[var];
		}
		memcpy(CH0_num+10*sizeof(uint8_t),savedata0_8,400*sizeof(uint8_t));
		memcpy(CH1_num+10*sizeof(uint8_t),savedata1_8,400*sizeof(uint8_t));
		break;
	}
}
if(TrigPosit==1999)
{
	for (int var = 0,i=0; var < 400; ++var,++i)
	{
		savedata0_8[i]=savedata0[var]>>8;
		savedata1_8[i]=savedata1[var]>>8;
		if(savedata0[var]>ch0max)ch0max=savedata0[var];
		if(savedata0[var]<ch0min)ch0min=savedata0[var];
		if(savedata1[var]>ch1max)ch1max=savedata1[var];
		if(savedata1[var]<ch1min)ch1min=savedata1[var];
	}
	memcpy(CH0_num+10,savedata0_8,400);
	memcpy(CH1_num+10,savedata1_8,400);
}

}
ch1vpp=ch1max-ch1min;
ch0vpp=ch0max-ch0min;
  //????????????
  ProcessOn=0;
  SendOn=1;
  HAL_TIM_Base_Stop_IT(&htim2);
}

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
