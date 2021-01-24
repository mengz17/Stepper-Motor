/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */
int i = 0; // counter
int direction = 1; // Clockwise
int mode = 1; // Full Step
int L_press = 1;
int R_press = 1;
int pre; //prescalar
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */

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
	BSP_LCD_GLASS_Init();
	BSP_JOY_Init(JOY_MODE_EXTI);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	if (HAL_TIM_Base_Start_IT(&htim3) != HAL_OK)
	{
		Error_Handler();
	}	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
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

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 799;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 5728;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

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
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LEDR_GPIO_Port, LEDR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, OUT_A_Pin|OUT_B_Pin|OUT_C_Pin|OUT_D_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LEDR_Pin */
  GPIO_InitStruct.Pin = LEDR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LEDR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : OUT_A_Pin OUT_B_Pin OUT_C_Pin OUT_D_Pin */
  GPIO_InitStruct.Pin = OUT_A_Pin|OUT_B_Pin|OUT_C_Pin|OUT_D_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if ((*htim).Instance==TIM3){
		if (mode == 1 && direction == 1){ //Full Step, Clockwise
			if (i == 0){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_SET);
			}
			else if (i == 1){		
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_RESET);
			}
			else if (i == 2){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_RESET);
			}
			else if (i == 3){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_SET);
			}
			i++;
			
			if (i == 4){
				i = 0;
			}
		}
		else if (mode == 1 && direction == 2){ // Full step, Counter-clockwise
			if (i == 0){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_SET);
			}
			else if (i == 1){		
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_RESET);
			}
			else if (i == 2){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_RESET);
			}
			else if (i == 3){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_SET);
			}
			i++;
			
			if (i == 4){
				i = 0;
			}
		}
		
		else if (mode == 2 && direction == 1){ // Half step, Clockwise
			if (i == 0){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_SET);
			}
			else if (i == 1){		
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_RESET);
			}
			else if (i == 2){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_RESET);
			}
			else if (i == 3){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_RESET);
			}
			else if (i == 4){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_RESET);
			}
			else if (i == 5){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_RESET);
			}
			else if (i == 6){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_SET);
			}
			else if (i == 7){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_SET);
			}
			i++;
			
			if (i == 8){
				i = 0;
			}
		}
		
		else if (mode == 2 && direction == 2){ // Half step, Counter-Clockwise
			if (i == 0){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_SET);
			}
			else if (i == 1){		
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_SET);
			}
			else if (i == 2){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_RESET);
			}
			else if (i == 3){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_RESET);
			}
			else if (i == 4){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_RESET);
			}
			else if (i == 5){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_RESET);
			}
			else if (i == 6){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_RESET);
			}
			else if (i == 7){
				HAL_GPIO_WritePin(GPIOE, OUT_A_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE, OUT_B_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_C_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOE, OUT_D_Pin,GPIO_PIN_SET);
			}
			i++;
			
			if (i == 8){
				i = 0;
			}
		}	
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_1 && L_press == 1)
	{
		mode = 2;  // Change to Half step mode
		BSP_LCD_GLASS_Clear();
		BSP_LCD_GLASS_DisplayString((uint8_t*)"HALF");
		pre = 399; // Change prescaler to fit Half step mode
		__HAL_TIM_SET_PRESCALER(&htim3,pre);
		L_press++;
	}
	
	else if(GPIO_Pin == GPIO_PIN_1 && L_press == 2)
	{
		mode = 1;  // Change to Full step mode
		BSP_LCD_GLASS_Clear();
		BSP_LCD_GLASS_DisplayString((uint8_t*)"FULL");
		pre = 799; // Change prescaler to fit Full step mode
		__HAL_TIM_SET_PRESCALER(&htim3,pre);
		L_press--;
	}
	
	else if(GPIO_Pin == GPIO_PIN_2 && R_press == 1)
	{
		direction = 2; // Change to Counter-Clockwise
		BSP_LCD_GLASS_Clear();
		BSP_LCD_GLASS_DisplayString((uint8_t*)"CC");
		R_press++;
	}
	
	else if(GPIO_Pin == GPIO_PIN_2 && R_press == 2)
	{
		direction = 1; // Change to Clockwise
		BSP_LCD_GLASS_Clear();
		BSP_LCD_GLASS_DisplayString((uint8_t*)"CL");
		R_press--;
	}
	
	else if(GPIO_Pin == GPIO_PIN_3)
	{
		BSP_LCD_GLASS_Clear();
		BSP_LCD_GLASS_DisplayString((uint8_t*)"UP");
		pre -= 100; // Make prescaler smaller, hence frequency larger
		__HAL_TIM_SET_PRESCALER(&htim3,pre);
	}
	else if(GPIO_Pin == GPIO_PIN_5)
	{
		BSP_LCD_GLASS_Clear();
		BSP_LCD_GLASS_DisplayString((uint8_t*)"DOWN");
		pre += 100; // Make prescaler larger, hence frequency smaller
		__HAL_TIM_SET_PRESCALER(&htim3,pre);
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
