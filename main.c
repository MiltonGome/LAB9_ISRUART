/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
uint8_t BTN1 = 0;
uint8_t BTN2 = 0;
uint8_t lecPot1 = 0;
uint8_t lecPot2 = 0;
uint8_t buffer[2];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void mostrarDigito(int numero);
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  if(BTN1 == 1){
	  	     BTN1 = 0;
	  	     HAL_UART_Receive(&huart1, buffer, 1, 1000); // Solo 2 bytes
	  	     lecPot1 = buffer[0];
	  	 }

	  	 if(BTN2 == 1){
	  		 BTN2 = 0;
	  	     HAL_UART_Receive(&huart1, buffer, 1, 1000);
	  	     lecPot2 = buffer[1];
	  	 }

	  	 HAL_GPIO_WritePin(DISP1_GPIO_Port, DISP1_Pin, 1);
	  	 HAL_GPIO_WritePin(DISP2_GPIO_Port, DISP2_Pin, 0);
	  	 mostrarDigito(lecPot1);
	  	 HAL_Delay(5);

	  	 HAL_GPIO_WritePin(DISP1_GPIO_Port, DISP1_Pin, 0);
	  	 HAL_GPIO_WritePin(DISP2_GPIO_Port, DISP2_Pin, 1);
	  	 mostrarDigito(lecPot2);
	  	 HAL_Delay(5);

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, A_Pin|B_Pin|C_Pin|E_Pin
                          |F_Pin|G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DISP1_Pin|DISP2_Pin|D_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : A_Pin B_Pin C_Pin E_Pin
                           F_Pin G_Pin */
  GPIO_InitStruct.Pin = A_Pin|B_Pin|C_Pin|E_Pin
                          |F_Pin|G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : DISP1_Pin DISP2_Pin D_Pin */
  GPIO_InitStruct.Pin = DISP1_Pin|DISP2_Pin|D_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN1_Pin BTN2_Pin */
  GPIO_InitStruct.Pin = BTN1_Pin|BTN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    if(GPIO_Pin == BTN1_Pin) {  // Verifica si la interrupción es por BTN1
        if(HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin) == GPIO_PIN_RESET) {
            BTN1 = 1;
        }
    }
    if(GPIO_Pin == BTN2_Pin) {  // Verifica si la interrupción es por BTN2
        if(HAL_GPIO_ReadPin(BTN2_GPIO_Port, BTN2_Pin) == GPIO_PIN_RESET) {
            BTN1 = 2;
        }
    }
}


void mostrarDigito(int numero){
	switch(numero){
		case 0:
			 HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 1);
			 HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 1);
			 HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 1);
			 HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 1);
			 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
			 HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 1);
			 HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 0);
			 break;
		case 1:
			 HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 0);
			 HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 1);
			 HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 1);
			 HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 0);
			 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
			 HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 0);
			 HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 0);
			 break;
		case 2:
			 HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 1);
			 HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 1);
			 HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 0);
			 HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 1);
			 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
			 HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 0);
			 HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 1);
			 break;
		case 3:
			 HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 1);
			 HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 1);
			 HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 1);
			 HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 1);
			 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
			 HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 0);
			 HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 1);
			 break;
		case 4:
			 HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 0);
			 HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 1);
			 HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 1);
			 HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 0);
			 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
			 HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 1);
			 HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 1);
			 break;
		case 5:
			 HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 1);
			 HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 0);
			 HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 1);
			 HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 1);
			 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
			 HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 1);
			 HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 1);
			 break;
		case 6:
			 HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 1);
			 HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 0);
			 HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 1);
			 HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 1);
			 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
			 HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 1);
			 HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 1);
			 break;
		case 7:
			 HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 1);
			 HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 1);
			 HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 1);
			 HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 0);
			 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
			 HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 0);
			 HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 0);
			 break;
		case 8:
			 HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 1);
			 HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 1);
			 HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 1);
			 HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 1);
			 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
			 HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 1);
			 HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 1);
			 break;
		case 9:
			 HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 1);
			 HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 1);
			 HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 1);
			 HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 0);
			 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
			 HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 1);
			 HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 1);
			 break;
		case 10:
			 HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 1);
			 HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 1);
			 HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 1);
			 HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 0);
			 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
			 HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 1);
			 HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 1);
			 break;
		case 11:
			 HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 0);
			 HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 0);
			 HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 1);
			 HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 1);
			 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
			 HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 1);
			 HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 1);
			 break;
		case 12:
			 HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 1);
			 HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 0);
			 HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 0);
			 HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 0);
			 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
			 HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 1);
			 HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 1);
			 break;
		case 13:
			 HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 0);
			 HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 1);
			 HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 1);
			 HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 1);
			 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
			 HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 0);
			 HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 1);
			 break;
		case 14:
			 HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 1);
			 HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 0);
			 HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 0);
			 HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 1);
			 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
			 HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 1);
			 HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 1);
			 break;
		case 15:
			 HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 1);
			 HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 0);
			 HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 0);
			 HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 0);
			 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
			 HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 1);
			 HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 1);
			 break;
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