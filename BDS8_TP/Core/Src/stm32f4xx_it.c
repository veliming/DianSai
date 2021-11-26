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
//#include "outputdata.h"
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

extern uint32_t ADC_Value1[10];/*电池电压电流DCDC电压*4*/
extern uint32_t ADC_Value3[10];/*电池电压电流DCDC电压*4*/

extern int16_t PHASE[1];/*存储相位*/
int16_t PHASE_Order=0;

extern float32_t DCVSet;

extern int16_t PWM;

volatile uint32_t tick;//按键时刻
volatile uint32_t A_tick;//a1时刻//
volatile uint32_t Ala_tick;//a1上一个时�????????????????//
volatile uint32_t B_tick;//b1时刻//
volatile uint32_t Retrig_tick;//b1时刻//


uint8_t Notrig=0;//判断是否正确触发 标志0没有触发 1不知  2错误触发//
uint8_t Trig_Ok=0;//稳定后不在判断是否正确触�??????????????????//
uint8_t Trig1_level=1;// 触发前相�????????????????//
uint8_t trigon=0;

double DCpid_error;
double DC_VReal;
double DC_VSet=36.0;

extern uint8_t Mode;

extern const float COSA[];
extern const float COSB[];
extern const float COSC[];
extern const float COSS[];
extern const float COSS2[];

uint16_t COSNum=0;//波表进度
float32_t COSNul=0.0;//限制三相幅度
float32_t COSCom=0;//三相三次谐波补偿幅度
extern float32_t COSCom2;//三相五次谐波补偿幅度
extern int16_t COSCom2_plus;//三相五次谐波补偿相位
uint16_t COSCom2_Num;//三相五次谐波补偿相位后位�???????
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
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */

  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  if(Notrig==0)//第一次对�??????????????????//
  {
    Ala_tick=A_tick;
    A_tick=TIM5->CNT;
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    Notrig=1;
  }

  else if(Trig_Ok==0&&Notrig==2)//下一次重对相//
  {
  	if((TIM5->CNT-Retrig_tick)>8000)
  	{
  	  Ala_tick=A_tick;
  	  A_tick=TIM5->CNT;
  	  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
  		Notrig=1;
  	}
  }

  else if
	(
			//数字康过零干�??????????????????//
			((TIM5->CNT-A_tick)>=17500)&&
					(
							(((int32_t)((TIM5->CNT-A_tick)%20000)>=0)&&((int32_t)((TIM5->CNT-A_tick)%20000)<=200))
							||(((int32_t)((TIM5->CNT-A_tick)%20000)>=19800)&&((int32_t)((TIM5->CNT-A_tick)%20000)<=20000))
					)
	)
  {
  	trigon=1;
  Ala_tick=A_tick;
  A_tick=TIM5->CNT;
  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
  }
  /* USER CODE END EXTI4_IRQn 1 */
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
  COSNum++;//波表加一//

  if (COSNum==600)
  {
  	COSNum=0;
	}//波表清零//

  if (COSCom2_Num==600)
  {
  	COSCom2_Num=0;
	}//波表清零//

  if(COSNum+COSCom2_plus>=600)
  {
  	COSCom2_Num=COSNum+COSCom2_plus-600;
  }
  else if(COSNum+COSCom2_plus<0)
  {
  	COSCom2_Num=600+COSNum+COSCom2_plus;
  }
  else
  {
  	COSCom2_Num=COSNum+COSCom2_plus;
  }

  TIM2->CCR2=(COSA[COSNum]*COSNul-COSS[COSNum]*COSCom-COSS2[COSCom2_Num]*COSCom2+1.0)*(TIM2->ARR-1)/2.0;//超前 Pa1//PF4//
  TIM2->CCR4=(COSB[COSNum]*COSNul-COSS[COSNum]*COSCom-COSS2[COSCom2_Num]*COSCom2+1.0)*(TIM2->ARR-1)/2.0;//正确 pa3//PF6//
  TIM2->CCR1=(COSC[COSNum]*COSNul-COSS[COSNum]*COSCom-COSS2[COSCom2_Num]*COSCom2+1.0)*(TIM2->ARR-1)/2.0;//滞后 pa5//PF8//






  if (((TIM5->CNT-A_tick)>=PHASE[0])&&trigon==1)
  {
  	trigon=0;
  	COSNum=0;
	}//波表清零//

  if(Trig_Ok==0)//判断是否正确触发//
  {
    if((TIM5->CNT-A_tick)>17400&&(TIM5->CNT-A_tick)<17600)
    {
    	if(HAL_GPIO_ReadPin(Trig1_GPIO_Port, Trig1_Pin)==1)
    	{
    		Notrig=2;
    		Retrig_tick=TIM5->CNT;
    	}
    }
  }
  if((TIM5->CNT-A_tick)>20000*3)
  {
  	Notrig=0;
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
  DC_VReal=0;

	for (int var = 0; var < 10; ++var) {
		DC_VReal+=1.2*((ADC_Value3[var])*1.0/(ADC_Value1[var])*1.0)*15.0;//缩小倍数
	}
	DC_VReal/=10;

		switch (Mode) {
			case 0:
			{
				if((A_tick-B_tick)>3300)//测量相序//
				{
					PHASE_Order=0;
				}
				if((A_tick-B_tick)<-3300)
				{
					PHASE_Order=1;
				}
				if(COSNul<=0.85)//逐步加到90%//
				{
					COSNul+=0.01;
				}

				else
				{
					//Trig_Ok=1;
					Mode=1;
				}
				break;
			}
			case 1:
			{
    		DCpid_error = DC_VSet - DC_VReal;
    		PWM += arm_pid_f32(&DCPID, DCpid_error);
    		if(PWM>((TIM2->ARR-1))*0.95)
    		{
    			PWM=(TIM2->ARR-1)*0.95;
    			TIM2->CCR3 = (TIM2->ARR-1)*0.95;
    		}
    		else if(PWM<(TIM2->ARR-1)*0.1)
    		{
    			PWM=(TIM2->ARR-1)*0.1;
    			TIM2->CCR3 = (TIM2->ARR-1)*0.1;
    		}
    		else
    		{
    			TIM2->CCR3 = PWM;
    		}
    		break;
			}
			default:
				break;
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
									PHASE[0]-=50;
									HAL_I2C_Mem_Write(&hi2c1, ADDR_AT24C02_Write, 0, I2C_MEMADD_SIZE_16BIT,(uint8_t*)(&(PHASE[0])),8, 1000);
									//
									goto END1;
								}
								case 2:
								{
									while(HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin)==0){}
									PHASE[0]-=10;
									HAL_I2C_Mem_Write(&hi2c1, ADDR_AT24C02_Write, 0, I2C_MEMADD_SIZE_16BIT,(uint8_t*)(&(PHASE[0])),8, 1000);
									//
									goto END1;
								}
								case 3:
								{
									while(HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin)==0){}
									PHASE[0]+=10;
									HAL_I2C_Mem_Write(&hi2c1, ADDR_AT24C02_Write, 0, I2C_MEMADD_SIZE_16BIT,(uint8_t*)(&(PHASE[0])),8, 1000);
									//
									goto END1;
								}
								case 4:
								{
									while(HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin)==0){}
									PHASE[0]+=50;
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
									HAL_GPIO_TogglePin(LOCK_GPIO_Port, LOCK_Pin);
									goto END2;
								}
								case 2:
								{
									while(HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin)==0){}
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
									COSCom2_plus++;
									goto END3;
								}
								case 2:
								{
									while(HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin)==0){}
									//
									COSCom2_plus--;
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
										COSCom2+=0.1;
										goto END4;
									}
									case 2:
									{
										while(HAL_GPIO_ReadPin(ROW4_GPIO_Port, ROW4_Pin)==0){}
										//
										COSCom2+=0.01;
										goto END4;
									}
									case 3:
									{
										while(HAL_GPIO_ReadPin(ROW4_GPIO_Port, ROW4_Pin)==0){}
										//
										COSCom2-=0.01;
										goto END4;
									}
									case 4:
									{
										while(HAL_GPIO_ReadPin(ROW4_GPIO_Port, ROW4_Pin)==0){}
										//
										COSCom2-=0.1;
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
