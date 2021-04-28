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
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void LEDTask_App(void *pvParameters);
void LBtnTask_App(void *pvParameters);
void TaskMonitor_App(void *pvParameters);
void Task_App(void *pvParameters);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
QueueHandle_t xQueue1;
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  xTaskCreate(LEDTask_App,"LEDTask",128,(void *) NULL,1,NULL);
  xTaskCreate(LBtnTask_App,"LBtnTask",128,(void *) NULL,1,NULL);
  xTaskCreate(TaskMonitor_App,"Monitor",128,(void *) NULL,2,NULL);
  xTaskCreate(Task_App,"Task_App",128,(void *) NULL,14,NULL);
  xQueue1 = xQueueCreate(2,sizeof(int));
  vTaskStartScheduler();
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, Green_LED_Pin|Red_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Blue_Button_Pin */
  GPIO_InitStruct.Pin = Blue_Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Blue_Button_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Green_LED_Pin Red_LED_Pin */
  GPIO_InitStruct.Pin = Green_LED_Pin|Red_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void LEDTask_App(void *pvParameters)
{
	  int Change_state_flag = 0; // It's for change state.
	  int BRW;  // It's for break while with "state" .
	  int message;
	  for(;;){
		  BRW = 1;
		  message = 0;
		  if(Change_state_flag){
			  while(BRW){
				  HAL_GPIO_WritePin(Green_LED_GPIO_Port,GPIO_PIN_12,GPIO_PIN_RESET); //Close the green LED
				  HAL_GPIO_WritePin(Red_LED_GPIO_Port,GPIO_PIN_14,GPIO_PIN_SET);
				  xQueueReceive(xQueue1,&message,1000);
				  //cc =uxQueueSpacesAvailable(xQueue1);
				  if(message){ // When a message is received from the queue
					  BRW = 0; // break while
					  Change_state_flag = 0; // Set change status flag
					  HAL_GPIO_WritePin(Red_LED_GPIO_Port,GPIO_PIN_14,GPIO_PIN_RESET);
					  break;
				  }
				  HAL_GPIO_WritePin(Red_LED_GPIO_Port,GPIO_PIN_14,GPIO_PIN_RESET);
				  xQueueReceive( xQueue1,&message,1000);
				  //cc =uxQueueSpacesAvailable(xQueue1);
				  if(message){
					  BRW = 0;
					  Change_state_flag = 0;
					  break;
				  }
			}
		  }else{
			  while(BRW){
				  HAL_GPIO_WritePin(Red_LED_GPIO_Port,GPIO_PIN_14,GPIO_PIN_RESET);
				  HAL_GPIO_WritePin(Green_LED_GPIO_Port,GPIO_PIN_12,GPIO_PIN_SET);
				  xQueueReceive( xQueue1,&message,500);
				  //cc =uxQueueSpacesAvailable(xQueue1);
				  if(message){
					  BRW = 0;
					  Change_state_flag = 1;
					  HAL_GPIO_WritePin(Green_LED_GPIO_Port,GPIO_PIN_12,GPIO_PIN_RESET);
					  break;
				  }
				  HAL_GPIO_WritePin(Green_LED_GPIO_Port,GPIO_PIN_12,GPIO_PIN_RESET);
				  HAL_GPIO_WritePin(Red_LED_GPIO_Port,GPIO_PIN_14,GPIO_PIN_SET);
				  xQueueReceive( xQueue1,&message,500);
				  //cc =uxQueueSpacesAvailable(xQueue1);
				  if(message){
					  BRW = 0;
					  Change_state_flag = 1;
					  HAL_GPIO_WritePin(Red_LED_GPIO_Port,GPIO_PIN_14,GPIO_PIN_RESET);
				  }

			  }
	  /* USER CODE END 5 */
		  }
	  }
}
/* USER CODE BEGIN Header_LBtnTask_App */
/**
* @brief Function implementing the LBtnTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LBtnTask_App */
void LBtnTask_App(void *pvParameters)
{
	  /* USER CODE BEGIN LBtnTask_App */
	  /* Infinite loop */
	  uint8_t curr_state,prev_state = 0; //State for the button，Used to solve edge detection.
	  int message = 1;
	  for(;;)
	  {
		  curr_state = HAL_GPIO_ReadPin(Blue_Button_GPIO_Port,GPIO_PIN_0);
		  if((curr_state == 1) && (prev_state == 0)){
//		  if(HAL_GPIO_ReadPin(Blue_Button_GPIO_Port,GPIO_PIN_0)){
			  xQueueSend(xQueue1,&message, 0);
		 }
		  prev_state = curr_state;
	  }
	  /* USER CODE END LBtnTask_App */
}

void TaskMonitor_App(void *pvParameters){
	uint8_t i = 100;
	  for(;;)
	  {
		  	Taskmonitor();
		  	i +=  1;
		  	vTaskDelay(i);
	  }
	  /* USER CODE END LBtnTask_App */
}

void Task_App(void *pvParameters){

	  for(;;)
	  {
		  	vTaskDelay(15000);
	  }
	  /* USER CODE END LBtnTask_App */
}
/* USER CODE END 4 */

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
