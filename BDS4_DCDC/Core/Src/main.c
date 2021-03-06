/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "obase.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
enum
{
	Manual=1, AutoCharge, AutoDischarge
} MainMode;

enum
{
	VoltageRegulation=1, CurrentRegulator, Control
} SubMode;

typedef struct PID
{
  float kp;
  float ki;
  float kd;
  float ek;     //当前误差
  float ek_1;   //上一次误??????
  float ek_2;   //上上??????次误??????
  float limit;  //限幅
  float res;  //限幅
}PID;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ADCTIMES 	100		//ADC采样次数
#define PIDTIME 	1		//ADC采样次数
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;
DMA_HandleTypeDef hdma_adc1;
DMA_HandleTypeDef hdma_adc2;
DMA_HandleTypeDef hdma_adc3;

TIM_HandleTypeDef htim3;

SRAM_HandleTypeDef hsram1;

/* USER CODE BEGIN PV */

float ToV1=8.2;
float ToV2=11.76;
float ToC=1.77;

uint32_t Voltage_Behind=0;
uint32_t Voltage_Front=0;
uint32_t Current=0;


uint16_t Voltage_Behind_DMA[ADCTIMES];
uint16_t Voltage_Front_DMA[ADCTIMES];
uint16_t Current_DMA[ADCTIMES];

float Target=0;
float Encoder=0;

uint32_t t=0;//延迟变化

uint8_t var = 0;//循环变量

uint8_t pressdown = 0;//长按监测

uint16_t Pwm = 420;//pwm计数懂得?????

uint8_t flag = 0;//s初次状�?�指??????

//PID
static PID pid;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_FSMC_Init(void);
static void MX_TIM3_Init(void);
static void MX_ADC2_Init(void);
static void MX_ADC3_Init(void);
/* USER CODE BEGIN PFP */
void SubDisplay(uint8_t i,uint16_t c);
void MainDisplay(uint8_t i,uint16_t c);
void PwmDisplay(uint16_t dp_pwm,uint16_t c);
void UnDisplay();
void PID_Init(int i);
float PID_Increase(int Encoder,int Target);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_FSMC_Init();
  MX_TIM3_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  /* USER CODE BEGIN 2 */
  LCD_Init();
  tp_dev.init();
  POINT_COLOR=RED;
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_ADC_Start_DMA(&hadc3, (uint32_t*)&Voltage_Front_DMA[0], ADCTIMES);
  HAL_ADC_Start_DMA(&hadc2, (uint32_t*)&Voltage_Behind_DMA[0], ADCTIMES);
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&Current_DMA[0], ADCTIMES);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);


  LCD_ShowString(15,90,48,16,16,(uint8_t*)"MAIN^");
  LCD_ShowString(15,135,48,16,16,(uint8_t*)"SUB>");


  MainMode=Manual;
  SubMode=Control;
  MainDisplay(1,GREEN);
  MainDisplay(2,YELLOW);
  MainDisplay(3,YELLOW);
  SubDisplay(1,YELLOW);
  SubDisplay(2,YELLOW);
  PwmDisplay(Pwm,YELLOW);
  LCD_ShowString(15,160,90,16,16,(uint8_t*)">Vf: >To");
  LCD_ShowString(15,200,90,16,16,(uint8_t*)">Vb: >To");
  LCD_ShowString(15,240,90,16,16,(uint8_t*)">C:  >To");
  LCD_ShowString(15,280,90,16,16,(uint8_t*)">Pwm: ");
  LCD_DrawLine(0,155,320,155);

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


	  //DAC采集

		HAL_Delay(10);
		for (var = 0,Voltage_Front = 0; var < ADCTIMES; ++var) {
				Voltage_Front += Voltage_Front_DMA[var];
		}
			Voltage_Front /= ADCTIMES;
			LCD_ShowNum(90,163,Voltage_Front,4,16);

		HAL_Delay(10);
		for (var = 0,Voltage_Behind = 0; var < ADCTIMES; ++var) {
				Voltage_Behind += Voltage_Behind_DMA[var];
		}
			Voltage_Behind /= ADCTIMES;
			LCD_ShowNum(90,203,Voltage_Behind,4,16);

		HAL_Delay(10);
		for (var = 0,Current = 0; var < ADCTIMES; ++var) {
				Current += Current_DMA[var];
		}
			Current /= ADCTIMES;
			LCD_ShowNum(90,243,Current,4,16);




		//模式切换
	  tp_dev.scan(0);
	  //LCD_DrawPoint(tp_dev.x[0],tp_dev.y[0]);//触控测试
	  if(tp_dev.sta & TP_PRES_DOWN)
	  {

		  if(tp_dev.x[0]>15&&tp_dev.y[0]>15&&tp_dev.x[0]<75&&tp_dev.y[0]<75){
			  MainMode=Manual;
			  SubMode=Control;
			  MainDisplay(1,GREEN);
			  MainDisplay(2,YELLOW);
			  MainDisplay(3,YELLOW);
			  SubDisplay(1,YELLOW);
			  SubDisplay(2,YELLOW);
		  }
		  else if(tp_dev.x[0]>90&&tp_dev.y[0]>15&&tp_dev.x[0]<150&&tp_dev.y[0]<75){
			  MainMode=AutoCharge;
			  flag=0;
			  MainDisplay(1,YELLOW);
			  MainDisplay(2,GREEN);
			  MainDisplay(3,YELLOW);
			  SubDisplay(1,GRAY);
			  SubDisplay(2,GRAY);
		  }
		  else if(tp_dev.x[0]>165&&tp_dev.y[0]>15&&tp_dev.x[0]<225&&tp_dev.y[0]<75){
			  MainMode=AutoDischarge;
			  flag=0;
			  MainDisplay(1,YELLOW);
			  MainDisplay(2,YELLOW);
			  MainDisplay(3,GREEN);
			  SubDisplay(1,GRAY);
			  SubDisplay(2,GRAY);
		  }
		  else if(MainMode==Manual&&pressdown==0&&tp_dev.x[0]>90&&tp_dev.y[0]>90&&tp_dev.x[0]<150&&tp_dev.y[0]<150){
			  if(SubMode==VoltageRegulation)
			  {
				  SubMode=Control;
				  SubDisplay(1,YELLOW);
				  SubDisplay(2,YELLOW);
			  }
			  else
			  {
				  SubMode=VoltageRegulation;
				  flag=0;
				  SubDisplay(1,GREEN);
				  SubDisplay(2,YELLOW);
			  }
		  }
		  else if(MainMode==Manual&&pressdown==0&&tp_dev.x[0]>165&&tp_dev.y[0]>90&&tp_dev.x[0]<225&&tp_dev.y[0]<150){
			  if(SubMode==CurrentRegulator)
			  {
				  SubMode=Control;
				  SubDisplay(1,YELLOW);
				  SubDisplay(2,YELLOW);
			  }
			  else
			  {
				  SubMode=CurrentRegulator;
				  flag=0;
				  SubDisplay(1,YELLOW);
				  SubDisplay(2,GREEN);
			  }
		  }
		  else if(MainMode==Manual&&SubMode==Control&&tp_dev.x[0]>75&&tp_dev.y[0]>265&&tp_dev.x[0]<240&&tp_dev.y[0]<285)
		  {
			  if(tp_dev.x[0]>225) Pwm=840;
			  else if(tp_dev.x[0]<90) Pwm=0;
			  else Pwm = 840.0*((tp_dev.x[0]-90.0)/135.0);
			  TIM3->CCR1 = Pwm;//手动修改pwm占空??????

		  }

		  pressdown=1;

	  }else {pressdown=0;}


	  //Pwm显示
	  if(MainMode==Manual&&SubMode==Control&&(pressdown==0))
	  	{
		  PwmDisplay(Pwm,YELLOW);
		  BACK_COLOR=YELLOW;
		  LCD_ShowNum(100,283,Pwm*100/840,3,16);
		  BACK_COLOR=WHITE;
	  	}
	  else if(MainMode==Manual&&SubMode==Control&&tp_dev.x[0]>75&&tp_dev.y[0]>265&&tp_dev.x[0]<240&&tp_dev.y[0]<285)
	  	 {
		  PwmDisplay(Pwm,GREEN);
		  BACK_COLOR=GREEN;
		  LCD_ShowNum(100,283,Pwm*100/840,3,16);
		  BACK_COLOR=WHITE;
	  	 }
	  else if(MainMode!=Manual||SubMode!=Control)
	  	 {
		  PwmDisplay(Pwm,GRAY);
		  BACK_COLOR=GRAY;
		  LCD_ShowNum(100,283,Pwm*100/840,3,16);
		  BACK_COLOR=WHITE;
	  	 }
	  else{

	  	  }

	  //分模式控??????(PID)
	  if(MainMode==Manual&&SubMode==VoltageRegulation)
	  {
		  if(Current<(((ToC)/3.3)*4096))
		  {
			  PID_Init(1);
			  if(flag==0){Pwm=420;flag=1;}
			  Encoder=Voltage_Behind;
			  Target=(((ToV1/4)/3.3)*4096);
			  Pwm += PID_Increase(Encoder,Target);
			  if(Pwm>835)Pwm=835;
			  else if(Pwm<0)Pwm=0;
			  else{};
			  TIM3->CCR1 = Pwm;//PID改pwm
		  }
		  else
		  {
			  PID_Init(2);
			  if(flag==0){Pwm=420;flag=1;}
			  Encoder=Current;
			  Target=(((ToC)/3.3)*4096);
			  Pwm += PID_Increase(Encoder,Target);
			  if(Pwm>835)Pwm=835;
			  else if(Pwm<0)Pwm=0;
			  else{};
			  TIM3->CCR1 = Pwm;//PID改pwm
		  }
	  }

	  else if(MainMode==Manual&&SubMode==CurrentRegulator)
	  {
		  if(Voltage_Behind>(((ToV1/4)/3.3)*4096))
		  {
			  PID_Init(2);
			  if(flag==0){Pwm=420;flag=1;}
			  Encoder=Current;
			  Target=(((ToC)/3.3)*4096);
			  Pwm += PID_Increase(Encoder,Target);
			  if(Pwm>835)Pwm=835;
			  else if(Pwm<0)Pwm=0;
			  else{};
			  TIM3->CCR1 = Pwm;//PID改pwm
		  }
		  else
		  {

		  }
	  }

	  else if(MainMode==AutoCharge)
	  {
		  if(Current>340)//????????
		  {

			  if(Voltage_Behind<(((ToV1/4)/3.3)*4096))//横流
			  {
				  MainDisplay(2,GREEN);
				  PID_Init(2);
				  if(flag==0){Pwm=420;flag=1;}
				  Encoder=Current;
				  Target=(((ToC)/3.3)*4096);
				  Pwm += PID_Increase(Encoder,Target);
				  if(Pwm>835)Pwm=835;
				  else if(Pwm<0)Pwm=0;
				  else{};
				  TIM3->CCR1 = Pwm;//PID改pwm
			  }
			  else if(Voltage_Behind>(((ToV1/4)/3.3)*4096))//恒压
			  {
				  MainDisplay(2,CYAN);
				  PID_Init(1);
				  if(flag==0){Pwm=420;flag=1;}
				  Encoder=Voltage_Behind;
				  Target=(((ToV1/4)/3.3)*4096);
				  Pwm += PID_Increase(Encoder,Target);
				  if(Pwm>835)Pwm=835;
				  else if(Pwm<0)Pwm=0;
				  else{};
				  TIM3->CCR1 = Pwm;//PID改pwm
			  }
		  }
		  else if(Current<340&&Voltage_Behind>(((ToV1/4)/3.3)*4096))
		  {//冲完
			  MainDisplay(2,BLUE);
		  }


	  }

	  else if(MainMode==AutoDischarge)
	  {
		  if(1)
		  {
			  PID_Init(1);
			  if(flag==0){Pwm=840;flag=1;}
			  Encoder=Voltage_Front;
			  Target=(((ToV2/4)/3.3)*4096);
			  Pwm -= PID_Increase(Encoder,Target);
			  if(Pwm>835)Pwm=835;
			  else if(Pwm<420)Pwm=420;
			  else{};
			  TIM3->CCR1 = Pwm;//PID改pwm
		  }
	  }





  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enables the Clock Security System
  */
  HAL_RCC_EnableCSS();
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_TRGO;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.ScanConvMode = DISABLE;
  hadc2.Init.ContinuousConvMode = ENABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc2.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_TRGO;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DMAContinuousRequests = ENABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.ScanConvMode = DISABLE;
  hadc3.Init.ContinuousConvMode = ENABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc3.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_TRGO;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DMAContinuousRequests = ENABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 5-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 840-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 420;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_ENABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
  /* DMA2_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TCS_GPIO_Port, TCS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, LED0_Pin|LED1_Pin|LED2_Pin|TDIN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, TCLK_Pin|LCD_BL_Pin|IIC_SCL_Pin|IIC_SDA_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : KEY0_Pin KEY1_Pin KEY2_Pin */
  GPIO_InitStruct.Pin = KEY0_Pin|KEY1_Pin|KEY2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : TCS_Pin */
  GPIO_InitStruct.Pin = TCS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TCS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED0_Pin LED1_Pin LED2_Pin */
  GPIO_InitStruct.Pin = LED0_Pin|LED1_Pin|LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : TCLK_Pin IIC_SCL_Pin IIC_SDA_Pin */
  GPIO_InitStruct.Pin = TCLK_Pin|IIC_SCL_Pin|IIC_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PEN_Pin DOUT_Pin */
  GPIO_InitStruct.Pin = PEN_Pin|DOUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : TDIN_Pin */
  GPIO_InitStruct.Pin = TDIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(TDIN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_BL_Pin */
  GPIO_InitStruct.Pin = LCD_BL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(LCD_BL_GPIO_Port, &GPIO_InitStruct);

}

/* FSMC initialization function */
static void MX_FSMC_Init(void)
{

  /* USER CODE BEGIN FSMC_Init 0 */

  /* USER CODE END FSMC_Init 0 */

  FSMC_NORSRAM_TimingTypeDef Timing = {0};
  FSMC_NORSRAM_TimingTypeDef ExtTiming = {0};

  /* USER CODE BEGIN FSMC_Init 1 */

  /* USER CODE END FSMC_Init 1 */

  /** Perform the SRAM1 memory initialization sequence
  */
  hsram1.Instance = FSMC_NORSRAM_DEVICE;
  hsram1.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram1.Init */
  hsram1.Init.NSBank = FSMC_NORSRAM_BANK4;
  hsram1.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hsram1.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  hsram1.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram1.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  hsram1.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram1.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  hsram1.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  hsram1.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  hsram1.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  hsram1.Init.ExtendedMode = FSMC_EXTENDED_MODE_ENABLE;
  hsram1.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram1.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
  hsram1.Init.PageSize = FSMC_PAGE_SIZE_NONE;
  /* Timing */
  Timing.AddressSetupTime = 15;
  Timing.AddressHoldTime = 15;
  Timing.DataSetupTime = 60;
  Timing.BusTurnAroundDuration = 0;
  Timing.CLKDivision = 16;
  Timing.DataLatency = 17;
  Timing.AccessMode = FSMC_ACCESS_MODE_A;
  /* ExtTiming */
  ExtTiming.AddressSetupTime = 9;
  ExtTiming.AddressHoldTime = 15;
  ExtTiming.DataSetupTime = 8;
  ExtTiming.BusTurnAroundDuration = 0;
  ExtTiming.CLKDivision = 16;
  ExtTiming.DataLatency = 17;
  ExtTiming.AccessMode = FSMC_ACCESS_MODE_A;

  if (HAL_SRAM_Init(&hsram1, &Timing, &ExtTiming) != HAL_OK)
  {
    Error_Handler( );
  }

  /* USER CODE BEGIN FSMC_Init 2 */

  /* USER CODE END FSMC_Init 2 */
}

/* USER CODE BEGIN 4 */
void MainDisplay(uint8_t i,uint16_t c)
{
	if(i==1)
	{
	LCD_Fill(15,15,75,75,c);
	}
	else if(i==2)
	{
	LCD_Fill(90,15,150,75,c);
	}
	else if(i==3)
	{
	LCD_Fill(165,15,225,75,c);
	}
	else
	{
	LCD_Fill(15,15,75,75,GRAY);
	LCD_Fill(90,15,150,75,GRAY);
	LCD_Fill(165,15,225,75,GRAY);
	}
	  LCD_ShowString(15,15,48,12,12,(uint8_t*)"MANUAL");
	  LCD_ShowString(90,15,48,12,12,(uint8_t*)"AUTO");
	  LCD_ShowString(90,27,48,12,12,(uint8_t*)"CHARGE");
	  LCD_ShowString(165,15,48,12,12,(uint8_t*)"AUTO");
	  LCD_ShowString(165,27,48,12,12,(uint8_t*)"DISCHARGE");
}

void SubDisplay(uint8_t i,uint16_t c)
{
	if(i==1)
	{
	LCD_Fill(90,90,150,150,c);
	}
	else if(i==2)
	{
	LCD_Fill(165,90,225,150,c);
	}
	else
	{
	LCD_Fill(90,90,150,150,GRAY);
	LCD_Fill(165,90,225,150,GRAY);
	}
	  LCD_ShowString(90,90,48,12,12,(uint8_t*)"VOLTAGE");
	  LCD_ShowString(90,102,48,12,12,(uint8_t*)"REGULATION");
	  LCD_ShowString(165,90,48,12,12,(uint8_t*)"CURRENT");
	  LCD_ShowString(165,102,48,12,12,(uint8_t*)"REGULATOR");
}

void PwmDisplay(uint16_t dp_pwm,uint16_t c)
{
	if(0<=(dp_pwm)&&(dp_pwm)<=840)
	{
		uint16_t pwm_op;
		pwm_op = 90.0+135.0*(dp_pwm/840.0);
		LCD_Fill(90, 280,pwm_op, 300,c);
		LCD_Fill(pwm_op, 280,225, 300,WHITE);
		LCD_DrawRectangle(90,280,225,300);

	}
}

void UnDisplay()
{
		//LCD_Fill(90, 280,pwm_op, 300,c);
		//LCD_Fill(pwm_op, 280,225, 300,WHITE);
}

void PID_Init(int i)
{
	if(i==1)
	{
	    pid.kp = 0.18;
	    pid.ki = 0.045;
	    pid.kd = 0.0001;
	}
	else if(i==2)
	{
		pid.kp = 0.08;
		pid.ki = 0.05;
		pid.kd = 0;
	}

    pid.limit = 100;
    pid.ek = 0;
    pid.ek_1 = 0;
    pid.ek_2 = 0;
}


// 增量式PID控制
float PID_Increase(int Encoder,int Target)
{

	float pwm = 0;
	    pid.ek = Target - Encoder; // 计算当前误差
	    pwm = pid.kp*(pid.ek - pid.ek_1) + pid.ki*pid.ek +pid.kd*(pid.ek - 2*pid.ek_1 + pid.ek_2);   //增量式PID控制??????
	    pid.ek_2 = pid.ek_1; //保存上上??????次的偏差
	    pid.ek_1 = pid.ek;   //保存上一次偏??????

	    if(pwm > pid.limit)
	    {
	      pwm =  pid.limit;
	    }
	    else if(pwm < -pid.limit)
	    {
	      pwm =  -pid.limit;
	    }
	    return pwm;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
