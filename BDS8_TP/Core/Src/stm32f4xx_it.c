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
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ADCTIMES 	3		//ADC采样次数or序列个数
#define ADDR_AT24C02_Write 0xA0
#define ADDR_AT24C02_Read 0xA1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */


extern arm_pid_instance_f32 DCPID;
extern I2C_HandleTypeDef hi2c1;

extern uint16_t ADC1_Value[6];/*电池电压电流DCDC电压*4*/
extern uint16_t ADC2_Value[ADCTIMES];
extern uint16_t ADC3_Value[8];/**/

extern int16_t PHASE[1];/*存储相位*/
int16_t PHASE_Order=0;


uint16_t ADC3_Value_mem1[8];/**/
uint16_t ADC3_Value_mem2[8];/**/

float32_t   Current_Arg;
float32_t   Voltage_Arg;


extern double VSet;

extern float32_t BT_VReal;
extern float32_t BT_CReal;
extern float32_t BT_PReal_La;
extern float32_t BT_PReal;
extern float32_t DC_VReal;
extern float32_t PW_VReal;
extern float32_t PW_CReal_1;
extern float32_t PW_CReal_2;

extern float32_t DCVSet;

extern float32_t Freq;

extern int16_t PWM;

volatile int32_t tick;//按键时刻
volatile int32_t A_tick;//a1时刻
volatile int32_t Ala_tick;//a1上一个时�??????
volatile int32_t B_tick;//b1时刻
volatile int32_t Mppt_tick;//mppt延时时刻
int8_t ADCflag=0;

double DCpid_error;


extern float OutData[4];


extern uint8_t Mode;
extern uint8_t frame;

extern const float COSA[];
extern const float COSB[];
extern const float COSC[];

uint16_t COSNum=0;
uint16_t coserror=0;
float32_t COSNul=0.0;
uint16_t ARR=5600-1;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
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
  //if(	(((TIM5->CNT-A_tick)%20000-20000)>=-40)&&(((TIM5->CNT-A_tick)%20000-20000)<=40)&&ADCflag==0	)
  //{
  Ala_tick=A_tick;
  A_tick=TIM5->CNT;
  ADCflag=1;
  //}
  //HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief This function handles EXTI line2 interrupt.
  */
void EXTI2_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_IRQn 0 */

  /* USER CODE END EXTI2_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
  /* USER CODE BEGIN EXTI2_IRQn 1 */
  //if((TIM5->CNT-A_tick)<=20040&&(TIM5->CNT-A_tick)<=19960)

    B_tick=TIM5->CNT;

  /* USER CODE END EXTI2_IRQn 1 */
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


  TIM2->CCR1=(COSA[COSNum]*COSNul+1.0)*(TIM2->ARR-1)/2.0;
  TIM2->CCR3=(COSB[COSNum]*COSNul+1.0)*(TIM2->ARR-1)/2.0;
  TIM2->CCR4=(COSC[COSNum]*COSNul+1.0)*(TIM2->ARR-1)/2.0;
  COSNum++;
  if (COSNum==600)
  {
  	COSNum=0;
	}
  if((TIM5->CNT)-A_tick>(((A_tick-Ala_tick)/8.0)-PHASE[0])&&ADCflag==1)
  {
		memcpy(ADC3_Value_mem1,ADC3_Value,16);
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		COSNum=0;
		ADCflag=2;
  }
  if((TIM5->CNT)-A_tick>((A_tick-Ala_tick)*5.0/8.0-PHASE[0])&&ADCflag==2)
  {
		memcpy(ADC3_Value_mem2,ADC3_Value,16);
		//HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
  	ADCflag=0;
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
  		BT_VReal=0.0;
  		BT_CReal=0.0;
  		DC_VReal=0.0;
  		for(int i = 0; i < 4;i++)
			{
  			BT_VReal += ADC1_Value[i]/4095.0*3.3/4.0*14.67;
			}
  		for(int i = 4; i < 8;i++)
			{
  			BT_CReal += ADC1_Value[i]/4095.0*3.3/4.0;
			}
  		for(int i = 8; i < 12;i++)
			{
  			DC_VReal += ADC1_Value[i]/4095.0*3.3/4.0*20.0;
			}

  	PW_VReal=0.0;
  	PW_CReal_1=0.0;
  	PW_CReal_2=0.0;
    for(int i = 0; i < 8;i++)
  	{
    	if (i%2==0) {
    		PW_VReal += ADC3_Value_mem1[i]/4095.0*3.3*17.9/4.0;
			}
    	else
    	{
    		PW_CReal_1 += ADC3_Value_mem1[i]/4095.0*3.3/4.0;
    		PW_CReal_2 += ADC3_Value_mem2[i]/4095.0*3.3/4.0;
    	}
  	}

		switch (Mode) {
			case 0:
			{
				//延时自动调整
				PHASE[0]=

				if((A_tick-B_tick)>3300)
				{
					PHASE_Order=0;
				}
				if((A_tick-B_tick)<-3300)
				{
					PHASE_Order=1;
				}
				if(COSNul<=0.90)
				{
					COSNul+=0.01;
				}
				else
				{
					Mode=1;
				}
				break;
			}
			case 1:
			{
    		DCpid_error = PW_VReal*2.0 - DC_VReal;
    		PWM -= arm_pid_f32(&DCPID, DCpid_error);
    		if(PWM>((TIM2->ARR-1))*0.9)
    		{
    			PWM=(TIM2->ARR-1)*0.9;
    			TIM2->CCR2 = (TIM2->ARR-1)*0.9;
    		}
    		else if(PWM<(TIM2->ARR-1)*0.1)
    		{
    			PWM=(TIM2->ARR-1)*0.1;
    			TIM2->CCR2 = (TIM2->ARR-1)*0.1;
    		}
    		else
    		{
    			TIM2->CCR2 = PWM;
    		}
    		break;
			}
			case 2:
			{
				if((HAL_GetTick()-Mppt_tick)>100)
				{
					BT_PReal_La=BT_PReal;
					BT_PReal=BT_VReal*BT_CReal;
					if(BT_PReal_La!=BT_PReal)
					{
						if(BT_PReal>BT_PReal_La)
						{
							PWM+=20;
							if(PWM>((TIM2->ARR-1)*0.9))
							{
			    			PWM=((TIM2->ARR-1)*0.9);
			    			TIM2->CCR2 = (TIM2->ARR-1)*0.9;
							}
							else
							{
								TIM2->CCR2 = PWM;
							}
						}
						else
						{
							PWM-=20;
							if(PWM<0)
							{
			    			PWM=0;
			    			TIM2->CCR2 = 0;
							}
							else
							{
								TIM2->CCR2 = PWM;
							}
						}
					}
					Mppt_tick=HAL_GetTick();
				}
			}
			case 3:
			{
				//PWM=0;
				//TIM2->CCR2 = 0;
				COSNul=0.0;
				if(PHASE_Order==0)
				{
				  TIM2->CCR1=(COSA[COSNum]*COSNul+1.0)*(TIM2->ARR-1)/2.0;
				  TIM2->CCR3=(COSB[COSNum]*COSNul+1.0)*(TIM2->ARR-1)/2.0;
				  TIM2->CCR4=(COSC[COSNum]*COSNul+1.0)*(TIM2->ARR-1)/2.0;
				}
				else
				{
				  TIM2->CCR1=(COSC[COSNum]*COSNul+1.0)*(TIM2->ARR-1)/2.0;
				  TIM2->CCR3=(COSB[COSNum]*COSNul+1.0)*(TIM2->ARR-1)/2.0;
				  TIM2->CCR4=(COSA[COSNum]*COSNul+1.0)*(TIM2->ARR-1)/2.0;
				}

			}

			default:
				break;
		}



	  //Freq=1000000.0/(A_tick-Ala_tick);
	  if((A_tick-Ala_tick)<20408&&(A_tick-Ala_tick)>19607)
	  {
//	  	if(TIM2->CNT>((((A_tick-Ala_tick)*84)/600)-1))
//	  	{
//	  		TIM2->CNT=((((A_tick-Ala_tick)*84)/600)-1);
//	  	}
	  	TIM2->ARR=(((A_tick-Ala_tick)*84)/600)-1;
	  }

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

	if((HAL_GetTick()-tick)>30)
	{
		//ROW1
			if(HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin)==0)
			{
				for(uint8_t i=1;i<5;i++)
				{
						HAL_GPIO_WritePin(COL1_GPIO_Port,COL1_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(COL2_GPIO_Port,COL2_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(COL3_GPIO_Port,COL3_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(COL4_GPIO_Port,COL4_Pin, GPIO_PIN_SET);

						switch (i) {
							case 1:
								HAL_GPIO_WritePin(COL1_GPIO_Port,COL1_Pin, GPIO_PIN_RESET);
								break;
							case 2:
								HAL_GPIO_WritePin(COL2_GPIO_Port,COL2_Pin, GPIO_PIN_RESET);
								break;
							case 3:
								HAL_GPIO_WritePin(COL3_GPIO_Port,COL3_Pin, GPIO_PIN_RESET);
								break;
							case 4:
								HAL_GPIO_WritePin(COL4_GPIO_Port,COL4_Pin, GPIO_PIN_RESET);
								break;
							default:
								break;
						}

						if(HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin)==0)
						{
							switch(i)
							{
								case 1:
								{
									while(HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin)==0){}
									PHASE[0]-=500;
									HAL_I2C_Mem_Write(&hi2c1, ADDR_AT24C02_Write, 0, I2C_MEMADD_SIZE_16BIT,(uint8_t*)(&(PHASE[0])),8, 1000);
									//
									goto END1;
								}
								case 2:
								{
									while(HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin)==0){}
									PHASE[0]-=50;
									HAL_I2C_Mem_Write(&hi2c1, ADDR_AT24C02_Write, 0, I2C_MEMADD_SIZE_16BIT,(uint8_t*)(&(PHASE[0])),8, 1000);
									//
									goto END1;
								}
								case 3:
								{
									while(HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin)==0){}
									PHASE[0]+=50;
									HAL_I2C_Mem_Write(&hi2c1, ADDR_AT24C02_Write, 0, I2C_MEMADD_SIZE_16BIT,(uint8_t*)(&(PHASE[0])),8, 1000);
									//
									goto END1;
								}
								case 4:
								{
									while(HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin)==0){}
									PHASE[0]+=500;
									HAL_I2C_Mem_Write(&hi2c1, ADDR_AT24C02_Write, 0, I2C_MEMADD_SIZE_16BIT,(uint8_t*)(&(PHASE[0])),8, 1000);
									//
									goto END1;
								}
							}
								END1:
								break;
						}
			}
				HAL_GPIO_WritePin(COL1_GPIO_Port,COL1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(COL2_GPIO_Port,COL2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(COL3_GPIO_Port,COL3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(COL4_GPIO_Port,COL4_Pin, GPIO_PIN_RESET);
  }

		//ROW2
			if(HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin)==0)
			{
				for(uint8_t i=1;i<5;i++)
				{
						HAL_GPIO_WritePin(COL1_GPIO_Port,COL1_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(COL2_GPIO_Port,COL2_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(COL3_GPIO_Port,COL3_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(COL4_GPIO_Port,COL4_Pin, GPIO_PIN_SET);

						switch (i) {
							case 1:
								HAL_GPIO_WritePin(COL1_GPIO_Port,COL1_Pin, GPIO_PIN_RESET);
								break;
							case 2:
								HAL_GPIO_WritePin(COL2_GPIO_Port,COL2_Pin, GPIO_PIN_RESET);
								break;
							case 3:
								HAL_GPIO_WritePin(COL3_GPIO_Port,COL3_Pin, GPIO_PIN_RESET);
								break;
							case 4:
								HAL_GPIO_WritePin(COL4_GPIO_Port,COL4_Pin, GPIO_PIN_RESET);
								break;
							default:
								break;
						}

						if(HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin)==0)
						{
							switch(i)
							{
								case 1:
								{
									while(HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin)==0){}
									//PWM=0;
									//TIM2->CCR2 = 0;
								  HAL_GPIO_TogglePin(SW1_GPIO_Port, SW1_Pin);
								  HAL_GPIO_TogglePin(SW2_GPIO_Port, SW2_Pin);
								  HAL_GPIO_TogglePin(SW3_GPIO_Port, SW3_Pin);
								  //Mode=3;
									//
									goto END2;
								}
								case 2:
								{
									while(HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin)==0){}
									//Mode=2;
									HAL_GPIO_TogglePin(SW4_GPIO_Port, SW4_Pin);
									HAL_GPIO_TogglePin(SW5_GPIO_Port, SW5_Pin);
									HAL_GPIO_TogglePin(SW6_GPIO_Port, SW6_Pin);
									//
									goto END2;
								}
								case 3:
								{
									while(HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin)==0){}
									//
									goto END2;
								}
								case 4:
								{
									while(HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin)==0){}
									//
									goto END2;
								}
							}
								END2:
								break;
						}
			}
				HAL_GPIO_WritePin(COL1_GPIO_Port,COL1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(COL2_GPIO_Port,COL2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(COL3_GPIO_Port,COL3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(COL4_GPIO_Port,COL4_Pin, GPIO_PIN_RESET);
  }

		//ROW3
			if(HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin)==0)
			{
				for(uint8_t i=1;i<5;i++)
				{
						HAL_GPIO_WritePin(COL1_GPIO_Port,COL1_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(COL2_GPIO_Port,COL2_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(COL3_GPIO_Port,COL3_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(COL4_GPIO_Port,COL4_Pin, GPIO_PIN_SET);

						switch (i) {
							case 1:
								HAL_GPIO_WritePin(COL1_GPIO_Port,COL1_Pin, GPIO_PIN_RESET);
								break;
							case 2:
								HAL_GPIO_WritePin(COL2_GPIO_Port,COL2_Pin, GPIO_PIN_RESET);
								break;
							case 3:
								HAL_GPIO_WritePin(COL3_GPIO_Port,COL3_Pin, GPIO_PIN_RESET);
								break;
							case 4:
								HAL_GPIO_WritePin(COL4_GPIO_Port,COL4_Pin, GPIO_PIN_RESET);
								break;
							default:
								break;
						}

						if(HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin)==0)
						{
							switch(i)
							{
								case 1:
								{
									while(HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin)==0){}
									//
									goto END3;
								}
								case 2:
								{
									while(HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin)==0){}
									//
									goto END3;
								}
								case 3:
								{
									while(HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin)==0){}
									//
									goto END3;
								}
								case 4:
								{
									while(HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin)==0){}
									//
									goto END3;
								}
							}
								END3:
								break;
						}
			}
				HAL_GPIO_WritePin(COL1_GPIO_Port,COL1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(COL2_GPIO_Port,COL2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(COL3_GPIO_Port,COL3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(COL4_GPIO_Port,COL4_Pin, GPIO_PIN_RESET);
  }

			//ROW4
				if(HAL_GPIO_ReadPin(ROW4_GPIO_Port, ROW4_Pin)==0)
				{
					for(uint8_t i=1;i<5;i++)
					{
							HAL_GPIO_WritePin(COL1_GPIO_Port,COL1_Pin, GPIO_PIN_SET);
							HAL_GPIO_WritePin(COL2_GPIO_Port,COL2_Pin, GPIO_PIN_SET);
							HAL_GPIO_WritePin(COL3_GPIO_Port,COL3_Pin, GPIO_PIN_SET);
							HAL_GPIO_WritePin(COL4_GPIO_Port,COL4_Pin, GPIO_PIN_SET);

							switch (i) {
								case 1:
									HAL_GPIO_WritePin(COL1_GPIO_Port,COL1_Pin, GPIO_PIN_RESET);
									break;
								case 2:
									HAL_GPIO_WritePin(COL2_GPIO_Port,COL2_Pin, GPIO_PIN_RESET);
									break;
								case 3:
									HAL_GPIO_WritePin(COL3_GPIO_Port,COL3_Pin, GPIO_PIN_RESET);
									break;
								case 4:
									HAL_GPIO_WritePin(COL4_GPIO_Port,COL4_Pin, GPIO_PIN_RESET);
									break;
								default:
									break;
							}

							if(HAL_GPIO_ReadPin(ROW4_GPIO_Port, ROW4_Pin)==0)
							{
								switch(i)
								{
									case 1:
									{
										while(HAL_GPIO_ReadPin(ROW4_GPIO_Port, ROW4_Pin)==0){}
										//
										goto END4;
									}
									case 2:
									{
										while(HAL_GPIO_ReadPin(ROW4_GPIO_Port, ROW4_Pin)==0){}
										//
										goto END4;
									}
									case 3:
									{
										while(HAL_GPIO_ReadPin(ROW4_GPIO_Port, ROW4_Pin)==0){}
										//
										goto END4;
									}
									case 4:
									{
										while(HAL_GPIO_ReadPin(ROW4_GPIO_Port, ROW4_Pin)==0){}
										//
										goto END4;
									}
								}
									END4:
									break;
							}
				}
					HAL_GPIO_WritePin(COL1_GPIO_Port,COL1_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(COL2_GPIO_Port,COL2_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(COL3_GPIO_Port,COL3_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(COL4_GPIO_Port,COL4_Pin, GPIO_PIN_RESET);
	  }

				tick = HAL_GetTick();
}
  /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
