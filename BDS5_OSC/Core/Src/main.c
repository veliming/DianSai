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
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ADS8688.h"
#include "stdio.h"
#include "lcd.h"
#include "string.h"
//#include "arm_math.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */



/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PI 3.14159265
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
ADS8688 ads;
uint16_t ads_data[2];

uint8_t CH0_ON=1;
uint8_t CH1_ON=1;

uint8_t TriggerCH=0;
uint8_t TriggerMODE=0;//0上升?????????

uint8_t CH0_num[828] = {0xEE,0xB1,0x35,0x00,0x00,0x00,0x01,0x00,0x01,0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFC,0xFF,0xFF,0xEE,0xB1,0x35,0x00,0x00,0x00,0x01,0x01,0x01,0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFC,0xFF,0xFF};
uint8_t CH1_num[414] = {0xEE,0xB1,0x35,0x00,0x00,0x00,0x01,0x01,0x01,0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFC,0xFF,0xFF};


uint8_t TrigFlag = 1;
uint16_t TrigValue = 32767;
uint16_t TrigPosit = 0;

int n=0;

uint8_t ProcessOn = 0;
uint8_t SendOn = 0;

uint16_t SampleRate = 20-1;

uint16_t AmpRate = 1;

uint8_t R_alldata[256];   //指令完整内容
uint8_t R_onedata;    //指令单元
uint16_t R_place=0;         //接收指令的位???????????????????

uint16_t savenum=0;

uint16_t savedata0[2000];
uint16_t savedata1[2000];

uint8_t clearch0[12]={0xEE, 0xB1 ,0x33 ,0x00 ,0x00 ,0x00 ,0x01 ,0x00 ,0xFF ,0xFC ,0xFF ,0xFF};//
uint8_t clearch1[12]={0xEE, 0xB1 ,0x33 ,0x00 ,0x00 ,0x00 ,0x01 ,0x01 ,0xFF ,0xFC ,0xFF ,0xFF};//

uint8_t trig_tft[15]={0xEE,0xB1,0x10,0x00,0x00,0x00,0x0B,0x30,0x2E,0x30,0x30,0xFF,0xFC,0xFF,0xFF};

uint16_t ch1max = 0;
uint16_t ch1min = 65535;
uint16_t ch1vpp = 0;
uint32_t ch1avg = 0;
uint16_t ch1freq = 0;
uint16_t ch0max = 0;
uint16_t ch0min = 65535;
uint16_t ch0vpp = 0;
uint32_t ch0avg = 0;
uint16_t ch0freq = 0;

uint16_t chmax = 0;
float chcha = 0;

uint16_t TrigPosit_tu=0;

uint8_t text_tft[81]={0xEE,0xB1,0x12,0x00,0x00,0x00,0x0C,
		0x00,0x05,0x30,0x2E,0x30,0x30,0x30,0x00,0x17,0x00,
		0x05,0x30,0x2E,0x30,0x30,0x30,0x00,0x18,0x00,0x05,
		0x30,0x2E,0x30,0x30,0x30,0x00,0x19,0x00,0x05,0x30,
		0x2E,0x30,0x30,0x30,0x00,0x1A,0x00,0x05,0x30,0x2E,
		0x30,0x30,0x30,0x00,0x1B,0x00,0x05,0x30,0x2E,0x30,
		0x30,0x30,0x00,0x20,0x00,0x05,0x30,0x2E,0x30,0x30,
		0x30,0x00,0x1D,0x00,0x05,0x30,0x2E,0x30,0x30,0x30,
		0xFF,0xFC,0xFF,0xFF};

uint8_t ch0_vpp_tft[5]={0xEE,0xB1,0x10,0x00,0x00};
uint8_t ch0_avg_tft[5]={0xEE,0xB1,0x10,0x00,0x00};
uint8_t ch0_freq_tft[5]={0xEE,0xB1,0x10,0x00,0x00};
uint8_t ch1_vpp_tft[5]={0xEE,0xB1,0x10,0x00,0x00};
uint8_t ch1_avg_tft[5]={0xEE,0xB1,0x10,0x00,0x00};
uint8_t ch1_freq_tft[5]={0xEE,0xB1,0x10,0x00,0x00};
uint8_t ch_cha_tft[5]={0xEE,0xB1,0x10,0x00,0x00};
uint8_t ch_boxing_tft[5]={0xEE,0xB1,0x10,0x00,0x00};

float ch0_vppvolt,ch1_vppvolt;
float ch0_avgvolt,ch1_avgvolt;

uint32_t ch0_period=0,ch1_period=0;

uint8_t savedata0_8[2000];
uint8_t savedata1_8[2000];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void print(char *msg, ...);
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
  HAL_Delay(200);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI3_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_FSMC_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  MX_TIM5_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1, (uint8_t *)&R_onedata, 1);
  LCD_Init();
  tp_dev.init();
  POINT_COLOR=RED;
  ADS8688_Init(&ads, &hspi3, SPI3_CS_GPIO_Port, SPI3_CS_Pin);
  HAL_TIM_Base_Start(&htim2);
  HAL_TIM_Base_Start_IT(&htim3);
  HAL_TIM_Base_Start_IT(&htim4);
  HAL_TIM_Base_Start(&htim5);
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_1, &ch0_period, 1);
  HAL_TIM_IC_Start_DMA(&htim5, TIM_CHANNEL_1, &ch1_period, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  LCD_ShowString(160,120,200,24,24,(uint8_t*)"OSCILLOSCOPE");
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

/* USER CODE BEGIN 4 */
void FinishCount(){
	if(ch0max>ch1max)
	{
		chmax=ch0max>>8;
	}
	else{
		chmax=ch1max>>8;
	}


		n++;
	if(n>5){
		ch0_vppvolt=ch0vpp*1.0/65535.0*10.24;
		ch1_vppvolt=ch1vpp*1.0/65535.0*10.24;
		ch0_avgvolt=((ch0max*1.0+ch0min*1.0)*10.24)/(2.0*65535)-5.12;
		ch1_avgvolt=((ch1max*1.0+ch1min*1.0)*10.24)/(2.0*65535)-5.12;

		//将发送的数据填入指令


		sprintf(&ch0_vpp_tft,"%.3f",ch0_vppvolt);

		sprintf(&ch0_avg_tft,"%.3f",ch0_avgvolt);

		sprintf(&ch1_vpp_tft,"%.3f",ch1_vppvolt);

		sprintf(&ch1_avg_tft,"%.3f",ch1_avgvolt);

		sprintf(&ch0_freq_tft,"%.3f",84000000.0/ch0_period);

		sprintf(&ch1_freq_tft,"%.3f",84000000.0/ch1_period);

		chcha=atan((savedata0[TrigPosit_tu]-32767)*1.0/(savedata1[TrigPosit_tu]-32767)*1.0)*360.0/PI;

		sprintf(&ch_cha_tft,"%.3f",chcha);

		sprintf(&ch_boxing_tft,"%.3f",84000000.0/ch1_period);


		memcpy(text_tft+9,ch0_vpp_tft,sizeof(ch0_vpp_tft));
		memcpy(text_tft+18,ch0_avg_tft,sizeof(ch0_avg_tft));
		memcpy(text_tft+27,ch0_freq_tft,sizeof(ch0_freq_tft));
		memcpy(text_tft+36,ch1_vpp_tft,sizeof(ch1_vpp_tft));
		memcpy(text_tft+45,ch1_avg_tft,sizeof(ch1_avg_tft));
		memcpy(text_tft+54,ch1_freq_tft,sizeof(ch1_freq_tft));
		memcpy(text_tft+63,ch_cha_tft,sizeof(ch_cha_tft));
		memcpy(text_tft+72,ch_boxing_tft,sizeof(ch_boxing_tft));
		HAL_UART_Transmit(&huart2, text_tft,64,10);
		n=0;
	}







	ch1max = 0;
	ch1min = 65535;
	ch1vpp = 0;
	ch1avg = 0;
	ch1freq = 0;
	ch0max = 0;
	ch0min = 65535;
	ch0vpp = 0;
	ch0avg = 0;
	ch0freq = 0;


}
void Dosomething(){
	//如果按钮被按
	if(R_alldata[1]==0xB1&&R_alldata[2]==0x11&&R_alldata[3]==0x00&&R_alldata[4]==0x00&&R_alldata[5]==0x00&&R_alldata[7]==0x10&&R_alldata[8]==0x01)
	{

		if(R_alldata[6]==0x0A)
		{

			if(R_alldata[9]==0x01)
			{
				CH1_ON=1;
			}
			//关闭通道1
			if(R_alldata[9]==0x00)
			{
				CH1_ON=0;
				HAL_UART_Transmit_DMA(&huart2, (uint8_t*)&clearch1[0] , 12);
			}
		}

		if(R_alldata[6]==0x07)
		{

			//kai通道1
			if(R_alldata[9]==0x01)
			{
				CH0_ON=1;
			}
					//关闭通道0
			if(R_alldata[9]==0x00)
			{
				CH0_ON=0;
				HAL_UART_Transmit_DMA(&huart2, (uint8_t*)&clearch0[0] , 12);
			}
		}
		//触发调节通道选择按钮按下
		if(R_alldata[6]==0x0F)
		{
			//CH0触发
			if(R_alldata[9]==0x00)
			{
				TriggerCH=0;
			}
			//ch1触发
			if(R_alldata[9]==0x01)
			{
				TriggerCH=1;
			}
		}
		if(R_alldata[6]==0x21)
		{
			//上升触发
			if(R_alldata[9]==0x00)
			{
				TriggerMODE=0;
			}
			//下降触发
			if(R_alldata[9]==0x01)
			{
				TriggerMODE=1;
			}
		}



	}
	//如果滑动选择被滑???????????????????
	else if(R_alldata[1]==0xB1&&R_alldata[2]==0x11&&R_alldata[3]==0x00&&R_alldata[4]==0x00&&R_alldata[5]==0x00&&R_alldata[7]==0x1b)
	{
		//幅度调节被按???????????????????
		if(R_alldata[6]==0x03)
		{
			switch(R_alldata[8])
			{
				case 0:AmpRate=1;break;
				case 1:AmpRate=10;break;
				case 2:AmpRate=100;break;
			}
			if(AmpRate==1)sprintf(&trig_tft[7],"%.2f",(TrigValue*10.24/65535.0)-5.12);
			if(AmpRate==10)sprintf(&trig_tft[7],"%.2f",((TrigValue*10.24/65535.0)-5.12)/10.0);
			if(AmpRate==100)sprintf(&trig_tft[7],"%.2f",((TrigValue*10.24/65535.0)-5.12)/100.0);
			HAL_UART_Transmit_DMA(&huart2, (uint8_t*)&trig_tft[0] , 15);
		}
		//时间调节被按???????????????????
		if(R_alldata[6]==0x04)
		{
			switch(R_alldata[8])
			{
				case 0:SampleRate=2000-1;TIM4->PSC=1199;savenum=0;break;
				case 1:SampleRate=200-1;TIM4->PSC=119;savenum=0;break;
				case 2:SampleRate=20-1;TIM4->PSC=11;savenum=0;break;
			}
		}
	}

	//如果滑动触发电平选择器被按下
	else if(R_alldata[1]==0xB1&&R_alldata[2]==0x11&&R_alldata[3]==0x00&&R_alldata[4]==0x00&&R_alldata[5]==0x00&&R_alldata[6]==0x09&&R_alldata[7]==0x13)
	{
		TrigValue=(uint16_t)R_alldata[11]<<8;
		if(AmpRate==1)sprintf(&trig_tft[7],"%.2f",(TrigValue*10.24/65535.0)-5.12);
		if(AmpRate==10)sprintf(&trig_tft[7],"%.2f",((TrigValue*10.24/65535.0)-5.12)/10.0);
		if(AmpRate==100)sprintf(&trig_tft[7],"%.2f",((TrigValue*10.24/65535.0)-5.12)/100.0);
		HAL_UART_Transmit_DMA(&huart2, (uint8_t*)&trig_tft[0] , 15);
	}
	else{}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//UNUSED(huart);
	if(huart->Instance == USART1)
	{
		int i;
					R_alldata[R_place]=R_onedata;     //保存指令单元
				//如果指令单元为指令头
				if(R_onedata==0xEE){
					R_place++;                                      //始获取下指令????????
				}
				else if(R_place>=1)R_place++;
				//超过五个指令单元后判断是否结束指???????????????????
				if(R_place>5){
						if(R_alldata[R_place-1]==0xFF&&R_alldata[R_place-2]==0xFF&&R_alldata[R_place-3]==0xFC&&R_alldata[R_place-4]==0xFF){
							Dosomething();                            //调用指令处理函数
							for(i=0;i<=255;i++)R_alldata[i]=0;            //指令清空
							R_place=0;                                                  //指令位置
						}
					}
					R_onedata = 0;
					HAL_UART_Receive_IT(&huart1, (uint8_t *)&R_onedata, 1);
	}
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
