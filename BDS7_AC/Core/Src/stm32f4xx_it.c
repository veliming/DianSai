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
#include "obase.h"
#include "lcd5510.h"
#include "arm_math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ADCTIMES 	50		//ADC采样次数
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern arm_pid_instance_f32 VPID;
extern arm_pid_instance_f32 CPID;

extern uint16_t Voltage_12[ADCTIMES];
extern uint16_t Current_12[ADCTIMES];

extern uint16_t Voltage_12_st[ADCTIMES];
extern uint16_t Current_12_st[ADCTIMES];

extern double VoltageSet;
extern double CurrentSet;

extern double VoltageReal;
extern double CurrentReal;

extern int16_t PWM;

extern uint8_t Mode;
extern uint8_t SubMode;

uint32_t tick;

double Vpid_error;
double Cpid_error;

uint16_t buf;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_adc2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
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
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */

  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */
  //PE0 ROW1
	if( (HAL_GetTick()-tick)>30)
	{

		for(uint8_t i=6;i<10;i++)
		{
				HAL_GPIO_WritePin(GPIOB,COL1_Pin|COL2_Pin|COL3_Pin|COL4_Pin, GPIO_PIN_SET);
				PBout(i)=0;
				if(PEin(0)==0)
				{
					switch(i)
					{
						case 6:
						{
							while(PEin(0)==0){}
							if((VoltageSet-5.0)<0.0)
							{
								VoltageSet=0.0;
							}
							else{
								VoltageSet-=5.0;
							}
							goto END;

						}
						case 7:
						{
							while(PEin(0)==0){}
							if((VoltageSet-1.0)<0.0)
							{
								VoltageSet=0.0;
							}
							else
							{
								VoltageSet-=1.0;
							}
							goto END;


						}
						case 8:
						{
							while(PEin(0)==0){}
							if((VoltageSet+1.0)>30.0)
							{
								VoltageSet=30.0;
							}
							else
							{
								VoltageSet+=1.0;
							}
							goto END;
						}
						case 9:
						{
							while(PEin(0)==0){}
							if((VoltageSet+5.0)>30.0)
							{
								VoltageSet=30.0;
							}
							else
							{
								VoltageSet+=5.0;
							}
							goto END;
						}
					}
						END:
						break;
				}
		}
	}
	HAL_GPIO_WritePin(GPIOB,COL1_Pin|COL2_Pin|COL3_Pin|COL4_Pin, GPIO_PIN_RESET);
	tick = HAL_GetTick();
  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief This function handles EXTI line1 interrupt.
  */
void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */

  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */
  //PE1 ROW2
	if( (HAL_GetTick()-tick)>30)
	{


	for(uint8_t i=6;i<10;i++)
	{
		HAL_GPIO_WritePin(GPIOB,COL1_Pin|COL2_Pin|COL3_Pin|COL4_Pin, GPIO_PIN_SET);
		PBout(i)=0;
		if(PEin(1)==0)
		{
			switch(i)
			{
				case 6:
				{

					while(PEin(1)==0){}
					if((CurrentSet-0.5)<0)
					{
						CurrentSet=0;
					}
					else
					{
						CurrentSet-=0.2;
					}
					goto END;
				}
				case 7:
				{
					while(PEin(1)==0){}
					if((CurrentSet-0.1)<0)
					{
						CurrentSet=0;
					}
					else
					{
						CurrentSet-=0.05;
					}
					goto END;


				}
				case 8:
				{
					while(PEin(1)==0){}
					if((CurrentSet+0.1)>2)
					{
						CurrentSet=2;
					}
					else
					{
						CurrentSet+=0.05;
					}
					goto END;


				}
				case 9:
				{
					while(PEin(1)==0){}
					if((CurrentSet+0.5)>2.1)
					{
						CurrentSet=2;
					}
					else
					{
						CurrentSet+=0.2;
					}
					goto END;
				}
			}
				END:
				break;
		}
	}
	HAL_GPIO_WritePin(GPIOB,COL1_Pin|COL2_Pin|COL3_Pin|COL4_Pin, GPIO_PIN_RESET);
	tick = HAL_GetTick();
	}
  /* USER CODE END EXTI1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */

  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_IRQn 1 */
  //PB4 ROW3
	if( (HAL_GetTick()-tick)>30)
	{
		if(Mode==3){

	for(uint8_t i=6;i<10;i++)
	{
		HAL_GPIO_WritePin(GPIOB,COL1_Pin|COL2_Pin|COL3_Pin|COL4_Pin, GPIO_PIN_SET);
		PBout(i)=0;
		if(PBin(4)==0)
		{
			switch(i)
			{
				case 6:
				{
					while(PBin(4)==0){}
					if((PWM-105)<0)
					{
						PWM=0;
					}
					else
					{
						PWM-=105;
						TIM3->CCR1 = PWM;
					}
					goto END;

				}
				case 7:
				{
					while(PBin(4)==0){}
					if((PWM-21)<0)
					{
						PWM=0;
					}
					else
					{
						PWM-=21;
						TIM3->CCR1 = PWM;
					}
					goto END;
				}
				case 8:
				{
					while(PBin(4)==0){}
					if((PWM+21)>1890)
					{
						PWM=1890;
					}
					else
					{
						PWM+=21;
						TIM3->CCR1 = PWM;
					}
					goto END;
				}
				case 9:
				{
					while(PBin(4)==0){}
					if((PWM+105)>1890)
					{
						PWM=1890;
					}
					else
					{
						PWM+=105;
						TIM3->CCR1 = PWM;
					}
					goto END;
				}
			}
				END:
				break;
		}
	}
	HAL_GPIO_WritePin(GPIOB,COL1_Pin|COL2_Pin|COL3_Pin|COL4_Pin, GPIO_PIN_RESET);
	tick = HAL_GetTick();
	}
	}
  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */
  //PB5 ROW4
	if( (HAL_GetTick()-tick)>30)
	{


	for(uint8_t i=6;i<10;i++)
	{
		HAL_GPIO_WritePin(GPIOB,COL1_Pin|COL2_Pin|COL3_Pin|COL4_Pin, GPIO_PIN_SET);
		PBout(i)=0;
		if(PBin(5)==0)
		{
			switch(i)
			{
				case 6:
				{

					while(PBin(5)==0){}
					Mode=0;
					PWM=0;
					goto END;
				}
				case 7:
				{
					while(PBin(5)==0)
					Mode=1;
					PWM=0;
					goto END;
				}
				case 8:
				{
					while(PBin(5)==0)
					Mode=2;
					PWM=0;
					goto END;
				}
				case 9:
				{
					while(PBin(5)==0)
					Mode=3;
					PWM=0;
					goto END;
				}
			}
				END:
				break;
		}
	}
	HAL_GPIO_WritePin(GPIOB,COL1_Pin|COL2_Pin|COL3_Pin|COL4_Pin, GPIO_PIN_RESET);
	tick = HAL_GetTick();
	}
  /* USER CODE END EXTI9_5_IRQn 1 */
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

  CurrentReal=0;

  for(int x=0;x<16;x++)
  {
	  CurrentReal=CurrentReal+Current_12[x];
  }

  CurrentReal/=16*4096/(3.3);
  if(Mode==0)
  {
	  if(VoltageReal>VoltageSet)
	  {
		  SubMode=0;
	  }
	  else
	  {
		  if(CurrentReal>(CurrentSet*0.9))
		  {
			  SubMode=1;
		  }
		  else
		  {
			  SubMode=0;
		  }
	  }


  }



  if((Mode==0&&SubMode==1)||Mode==2)
  {

		  Cpid_error = CurrentSet - CurrentReal;
		  PWM += arm_pid_f32(&CPID, Cpid_error);

		  if(PWM>1890)
		  {
			  PWM=1890;
			  TIM3->CCR1 = 1890;
		  }
		  else if(PWM<0)
		  {
			  PWM=0;
			  TIM3->CCR1 = 0;
		  }
		  else
		  {
			  TIM3->CCR1 = PWM;
		  }

  }

  /* USER CODE END TIM4_IRQn 1 */
}

/**
  * @brief This function handles TIM5 global interrupt.
  */
void TIM5_IRQHandler(void)
{
  /* USER CODE BEGIN TIM5_IRQn 0 */

  /* USER CODE END TIM5_IRQn 0 */
  HAL_TIM_IRQHandler(&htim5);
  /* USER CODE BEGIN TIM5_IRQn 1 */
  VoltageReal=0.0;


  for(int x=0;x<ADCTIMES;x++)
  {
	  VoltageReal=VoltageReal+Voltage_12[x]/(1.0*ADCTIMES);
  }
VoltageReal/=4096/(10*3.3);





  if((Mode==0&&SubMode==0)||Mode==1)
  {

	  Vpid_error = VoltageSet - VoltageReal;
	  PWM += arm_pid_f32(&VPID, Vpid_error);


	  if(PWM>1890)
	  {
		  PWM=1890;
		  TIM3->CCR1 = 1890;
	  }
	  else if(PWM<0)
	  {
		  PWM=0;
		  TIM3->CCR1 = 0;
	  }
	  else
	  {
		  TIM3->CCR1 = PWM;
	  }
  }


  /* USER CODE END TIM5_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream0 global interrupt.
  */
void DMA2_Stream0_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream0_IRQn 0 */

  /* USER CODE END DMA2_Stream0_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA2_Stream0_IRQn 1 */

  /* USER CODE END DMA2_Stream0_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream2 global interrupt.
  */
void DMA2_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream2_IRQn 0 */

  /* USER CODE END DMA2_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc2);
  /* USER CODE BEGIN DMA2_Stream2_IRQn 1 */

  /* USER CODE END DMA2_Stream2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
