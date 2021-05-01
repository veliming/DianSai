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
#include "dac.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "touch.h"
#include "24l01.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
u8 TP_CHECK(u16 x0, u16 y0, u16 x1, u16 y1);
void DAC_VAL_Change(void);
void AMP_MUL_Change(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern uint8_t DAC_STA;
extern uint8_t DAC_FRE;
extern uint16_t DAC_VAL;
extern uint32_t TimeOffset;
extern uint16_t Wavetable[];
extern uint16_t Sin[];
extern uint16_t pressTime;
uint8_t presStatus = 0;
uint8_t Check_flag=0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  // PRE_AMP_MUL = AMP_MUL;
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
  MX_DAC_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_FSMC_Init();
  MX_TIM3_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  DAC_VAL_Change();
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim3);
  HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
  HAL_DAC_Start(&hdac, DAC_CHANNEL_2);
  HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 1750);
  HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, ((DAC_FRE/40))*4095);
  delay_init(168);
  LCD_Init();
	tp_dev.init();

  POINT_COLOR = RED;
  //     (28,40)                     (68,40)                                      (192,40)    (202,44)
  //       (32,48) - (44,49)                    DAC_FRE    ()                          (196,48)    +     (208,49)
  //                   (48,56)                                 (172,56)                     (203,52)   (212,56)
  LCD_ShowString(68, 40, 104, 16, 16, (uint8_t *)"DAC_FRE:  KHz");
  LCD_Fill(28,60,48,76,GRAY);
  LCD_Fill(32,68,44,69,GREEN);
  LCD_Fill(192,60,212,76,GRAY);
  LCD_Fill(196,68,208,69,RED);
  LCD_Fill(202,64,203,72,RED);
  // LCD_ShowxNum(132,40,12,2,16,0);

  //閺勫墽銇氭潏鎾冲毉楠炲懎瀹虫穱鈩冧紖
  LCD_ShowString(64, 90, 112, 16, 16, (uint8_t *)"DAC_VAL:    mV");
  LCD_Fill(28,110,48,126,GRAY);
  LCD_Fill(32,118,44,119,GREEN);
  LCD_Fill(192,110,212,126,GRAY);
  LCD_Fill(196,118,208,119,RED);
  LCD_Fill(202,114,203,122,RED);
  // LCD_ShowxNum(128,90,1122,4,16,0);

  LCD_Fill(40,140,200,170,GREEN);
  LCD_ShowString(72, 147, 168, 163, 16, (uint8_t *)"Start Detect");

  POINT_COLOR = GRAY;
  LCD_DrawRectangle(48,110,192,126);
  LCD_DrawRectangle(48,60,192,76);
  POINT_COLOR = RED;
	LCD_Fill(48, 110,DAC_VAL*144.0/600.0+48.0, 126,GRAY);
	LCD_Fill(DAC_VAL/600.0*144.0+48.0, 111,190, 125,WHITE);

	LCD_Fill(48, 60,DAC_FRE*144.0/40.0+48.0,76,GRAY);
	LCD_Fill(DAC_FRE/40.0*144.0+48.0,61,190, 75,WHITE);
	LCD_ShowString(70,190,200,16,16,(uint8_t *)"NRF24L01 Error");
  // HAL_UART_Receive_IT(&huart1,RxBuf,sizeof(RxBuf));
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		if(Check_flag==0&&NRF24L01_Check()==0)
		{
			LCD_Fill(65,190,309,200+16,WHITE);
			LCD_ShowString(70,190,200,16,16,(uint8_t *)"NRF24L01 OK");
			Check_flag=1;
			NRF24L01_TX_Mode();
		}

    tp_dev.scan(0);

    if (tp_dev.sta & TP_PRES_DOWN)
    {
      presStatus = 1;
      if (pressTime++ == 0 || (pressTime > 10 && pressTime%20 == 0))
      {
			if(TP_CHECK(48,110,192,126))
			{DAC_VAL=600.0*((tp_dev.x[0]-48.0)/144.0);
			LCD_Fill(48, 110,tp_dev.x[0], 126,GRAY);
			LCD_Fill(tp_dev.x[0], 111,190, 125,WHITE);
			DAC_VAL_Change();
			}

			if(TP_CHECK(48,60,192,76))
			{DAC_FRE=40.0*((tp_dev.x[0]-48.0)/144.0);
			LCD_Fill(48, 60,tp_dev.x[0], 76,GRAY);
			LCD_Fill(tp_dev.x[0], 61,192, 75,WHITE);
			}

        if(TP_CHECK(28,60,48,76)){
        	DAC_FRE = DAC_FRE==1?1:DAC_FRE-1;
        	LCD_Fill(48, 60,DAC_FRE*144.0/40.0+49.0,76,GRAY);
        	LCD_Fill(DAC_FRE/40.0*144.0+47.0,61,190, 75,WHITE);
        }

        if(TP_CHECK(192,60,212,76)) {
        	DAC_FRE = DAC_FRE==40?40:DAC_FRE+1;
        	LCD_Fill(48, 60,DAC_FRE*144.0/40.0+49.0,76,GRAY);
        	LCD_Fill(DAC_FRE/40.0*144.0+47.0,61,190, 75,WHITE);
        }

        if(TP_CHECK(28,110,48,126)) {
          DAC_VAL = DAC_VAL==0?0:DAC_VAL-1;
          DAC_VAL_Change();
			LCD_Fill(48, 110,DAC_VAL*144.0/600.0+49.0, 126,GRAY);
			LCD_Fill(DAC_VAL/600.0*144.0+47.0, 111,190, 125,WHITE);
        }

        if(TP_CHECK(192,110,212,126)) {
        	DAC_VAL = DAC_VAL==600?600:DAC_VAL+1;
        	DAC_VAL_Change();
			LCD_Fill(48, 110,DAC_VAL*144.0/600.0+49.0, 126,GRAY);
			LCD_Fill(DAC_VAL/600.0*144.0+47.0, 111,190, 125,WHITE);
        }
        if(TP_CHECK(40,140,200,170)) {
          if(DAC_STA) {
            LCD_Fill(40,140,200,170,GREEN);
            LCD_ShowString(72, 147, 168, 163, 16, (uint8_t *)"Sweep Start");
          }else {
            POINT_COLOR = GREEN;
            LCD_Fill(40,140,200,170,RED);
            LCD_ShowString(76, 147, 164, 163, 16, (uint8_t *)"Sweep Stop");
            POINT_COLOR = RED;
          }
					DAC_STA = !DAC_STA;
        }
      }
    }
    else {
      presStatus = 0;
      pressTime = 0;
    }

    LCD_ShowxNum(132,40,DAC_FRE,2,16,0);
    LCD_ShowxNum(128,90,DAC_VAL*5,4,16,0);
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
}

/* USER CODE BEGIN 4 */
u8 TP_CHECK(u16 x0, u16 y0, u16 x1, u16 y1)
{
	return (tp_dev.x[0] > x0 && tp_dev.y[0] > y0 && tp_dev.x[0] < x1 && tp_dev.y[0] < y1);
}
void DAC_VAL_Change(void) {
  uint16_t i;
	uint16_t * Wavetable_p = Wavetable;
  for(i=0;i<5000;i++) {
		*(Wavetable_p++) = ((int32_t)Sin[i]-2028)*DAC_VAL/600+2028;
  }
}
// void AMP_MUL_Change(void) {
//   uint16_t i;
//   for(i=0;i<10;i++) {
//     Wavetable[i] = ((int32_t)Sin[i]-2028)*DAC_VAL*AMP_MUL/1000+2028;
//   }
// }
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
