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
#include "math.h"
#include "outputdata.h"
#include "cmd_process.h"
#include "cmd_queue.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ADCTIMES 	1536		//ADC采样次数
#define FFT_LENGTH  1024 		//FFT长度

#define NUM 1536 //�???????轮采样点�???????
#define BLOCK_SIZE 128 //计算�???????次FIR
#define FIR_order 26 //滤波器阶�???????
#define FIR_Len 26+1 //滤波器系数个�???????
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

extern arm_rfft_fast_instance_f32 FFT;
extern arm_fir_instance_f32 FIR;

extern arm_pid_instance_f32 CPID;

extern float32_t Voltage_12[ADCTIMES];
extern float32_t Current_12[ADCTIMES];

float32_t Voltage_12_RMS[ADCTIMES];
float32_t Current_12_RMS[ADCTIMES];

extern float32_t Voltage_12_FIR_out[ADCTIMES];
extern float32_t Current_12_FIR_out[ADCTIMES];

extern float32_t Voltage_12_FFT_in[FFT_LENGTH];
extern float32_t Current_12_FFT_in[FFT_LENGTH];

extern float32_t Voltage_12_FFT_out[FFT_LENGTH];
extern float32_t Current_12_FFT_out[FFT_LENGTH];

float32_t   Current_Arg;
float32_t   Voltage_Arg;

extern float32_t   PHD[11];
extern uint8_t PHDtimes;

extern double CurrentSet;

extern float32_t VoltageReal;
extern float32_t CurrentReal;
extern uint32_t Freq;

extern int16_t PWM;

uint32_t tick;

double Cpid_error;

int times=0;

int flagnum=0;

extern float OutData[4];

extern uint8_t Mode;
extern uint8_t frame;

extern uint8_t recive[128];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern DMA_HandleTypeDef hdma_tim5_ch1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart3;
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
							if((CurrentSet-0.1)<0.0)
							{
								CurrentSet=0.0;
							}
							else{
								CurrentSet-=0.1;
							}
							goto END;

						}
						case 7:
						{
							while(PEin(0)==0){}
							if((CurrentSet-0.02)<0.0)
							{
								CurrentSet=0.0;
							}
							else
							{
								CurrentSet-=0.02;
							}
							goto END;


						}
						case 8:
						{
							while(PEin(0)==0){}
							if((CurrentSet+0.02)>30.0)
							{
								CurrentSet=30.0;
							}
							else
							{
								CurrentSet+=0.02;
							}
							goto END;
						}
						case 9:
						{
							while(PEin(0)==0){}
							if((CurrentSet+0.1)>30.0)
							{
								CurrentSet=30.0;
							}
							else
							{
								CurrentSet+=0.1;
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

		if(Mode==1){

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
					if((PWM-160)<0)
					{
						PWM=0;
						TIM3->CCR1 = PWM;
					}
					else
					{
						PWM-=160;
						TIM3->CCR1 = PWM;
					}
					goto END;
				}
				case 7:
				{
					while(PEin(1)==0){}
					if((PWM-32)<0)
					{
						PWM=0;
						TIM3->CCR1 = PWM;
					}
					else
					{
						PWM-=32;
						TIM3->CCR1 = PWM;
					}
					goto END;


				}
				case 8:
				{
					while(PEin(1)==0){}
					if((PWM+32)>3200)
					{
						PWM=2;
						TIM3->CCR1 = PWM;
					}
					else
					{
						PWM+=32;
						TIM3->CCR1 = PWM;
					}
					goto END;


				}
				case 9:
				{
					while(PEin(1)==0){}
					if((PWM+160)>3200)
					{
						PWM=3200;
						TIM3->CCR1 = PWM;
					}
					else
					{
						PWM+=160;
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
					Mode=0;
					PWM=0;
					TIM3->CCR1 = PWM;
					goto END;

				}
				case 7:
				{
					while(PBin(4)==0){}
					Mode=1;
					PWM=0;
					TIM3->CCR1 = PWM;
					goto END;
				}
				case 8:
				{
					while(PBin(4)==0){}
					frame=0;
					goto END;
				}
				case 9:
				{
					while(PBin(4)==0){}
					frame=1;
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
  /* USER CODE END EXTI4_IRQn 1 */
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
  * @brief This function handles ADC1, ADC2 and ADC3 global interrupts.
  */
void ADC_IRQHandler(void)
{
  /* USER CODE BEGIN ADC_IRQn 0 */

  /* USER CODE END ADC_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc1);
  HAL_ADC_IRQHandler(&hadc2);
  /* USER CODE BEGIN ADC_IRQn 1 */

  /* USER CODE END ADC_IRQn 1 */
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


					goto END;
				}
				case 7:
				{
					while(PBin(5)==0)


					goto END;
				}
				case 8:
				{
					while(PBin(5)==0)


					goto END;
				}
				case 9:
				{
					while(PBin(5)==0)


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
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  HAL_ADC_Start(&hadc1);
  HAL_ADC_PollForConversion(&hadc1, 5);
  HAL_ADC_Start(&hadc2);
  HAL_ADC_PollForConversion(&hadc2, 5);

  Current_12[times] = HAL_ADC_GetValue(&hadc1);
  Voltage_12[times] = HAL_ADC_GetValue(&hadc2);
  times++;
  if(times==1536)
  {
	  HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
	  times=0;

//	  for (int var = 0; var < 1024; ++var)
//	  {
//		  OutData[0]=Current_12[var];
//		  OutData[1]=Voltage_12[var];
//		  OutPut_Data();
//	  }

	  arm_offset_f32(Current_12, -2048.0,Current_12_RMS,1536);
	  arm_offset_f32(Voltage_12, -2048.0,Voltage_12_RMS,1536);

	  arm_scale_f32(Current_12_RMS,0.00161132,Current_12_RMS,1536);
	  arm_scale_f32(Voltage_12_RMS,0.00161132,Voltage_12_RMS,1536);

	  arm_rms_f32(Current_12_RMS,1536,&CurrentReal);
	  arm_rms_f32(Voltage_12_RMS,1536,&VoltageReal);

	  CurrentReal/=2.0;
	  VoltageReal/=2.0;


	  if(Mode==0)
	  {
		  Cpid_error = CurrentSet - CurrentReal;
		  PWM += arm_pid_f32(&CPID, Cpid_error);
		  if(PWM>2880)
		  {
			  PWM=2880;
			  TIM3->CCR1 = 2880;
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
	  else{}




//	  for (int var = 0; var < 1024; ++var)
//	  {
//		  OutData[0]=Current_12_RMS[var]*100;
//		  OutData[1]=Voltage_12_RMS[var]*100;
//		  OutPut_Data();
//	  }

	  for (int var = 0; var < 12; ++var)
	  {
		  arm_fir_f32(&FIR, Current_12 + (var * BLOCK_SIZE), Current_12_FIR_out + (var * BLOCK_SIZE),BLOCK_SIZE);
	  }
	  for (int var = 0; var < 12; ++var)
	  {
		  arm_fir_f32(&FIR, Voltage_12 + (var * BLOCK_SIZE), Voltage_12_FIR_out + (var * BLOCK_SIZE),BLOCK_SIZE);
	  }

//	  for (int var = 0; var < 1536; ++var)
//	  {
//		  OutData[0]=Current_12_FIR_out[var];
//		  OutData[1]=Voltage_12_FIR_out[var];
//		  OutPut_Data();
//	  }

	  for (int var = 64; var < 1536; ++var)
	  {
		  if(Voltage_12_FIR_out[var-1]>2047&&Voltage_12_FIR_out[var]<2047)
		  {
			  memcpy(Current_12_FFT_in,Current_12_FIR_out+var,1024*sizeof(float32_t));
			  memcpy(Voltage_12_FFT_in,Voltage_12_FIR_out+var,1024*sizeof(float32_t));
			  break;
		  }


	  }

//	  	  for (int var = 0; var < 1024; ++var)
//	  	  {
//	  		  OutData[0]=Current_12_FFT_in[var];
//	  		  OutData[1]=Voltage_12_FFT_in[var];
//	  		  OutPut_Data();
//	  	  }

	  arm_rfft_fast_f32(&FFT, Current_12_FFT_in, Current_12_FFT_out, 0);
	  arm_rfft_fast_f32(&FFT, Voltage_12_FFT_in, Voltage_12_FFT_out, 0);

//	  for (int var = 0; var < 1024; ++var)
//	  {
//		  OutData[0]=Current_12_FFT_out[var];
//		  OutData[1]=Voltage_12_FFT_out[var];
//		  OutPut_Data();
//	  }

	  Current_Arg=atan2(Current_12_FFT_out[9],Current_12_FFT_out[8]);
	  Voltage_Arg=atan2(Voltage_12_FFT_out[9],Voltage_12_FFT_out[8]);


	  PHD[PHDtimes]=Voltage_Arg-Current_Arg;
	  PHDtimes++;
	  if(PHDtimes>9)
	  {
		  PHDtimes=0;
		  arm_mean_f32(PHD, 10, &PHD[10]);
	  }

  }

  /* USER CODE END TIM2_IRQn 1 */
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
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */

  /* USER CODE END USART3_IRQn 0 */
  HAL_UART_IRQHandler(&huart3);
  /* USER CODE BEGIN USART3_IRQn 1 */
  HAL_UART_Receive_IT(&huart3, recive, 1);
  /* USER CODE END USART3_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
