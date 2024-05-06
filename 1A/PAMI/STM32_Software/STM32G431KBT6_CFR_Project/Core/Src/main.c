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
#include "adc.h"
#include "i2c.h"
#include "usart.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SSD1306.h"
#include "led.h"
#include "encodeur.h"
#include "button.h"
#include "ydlidar_x4.h"
#include "stepper.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ANGLE_MIN 120
#define ANGLE_MAX 240
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
SSD1306_COLOR screen_color = White;
uint8_t it_enc;
uint8_t it_lidar;
uint8_t it_time;
uint32_t time_100ms = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
	uint8_t led = 0;
	uint32_t encValue;
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
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_LPUART1_UART_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
	tx_Buffer_Size = snprintf((char *)vcp_Tx_Buffer, UART_TX_BUFFER_SIZE, "ENSEA CFR PAMI v0.1\r\n");
	HAL_UART_Transmit(&huart2, vcp_Tx_Buffer, tx_Buffer_Size, 10);


	// Init SCREEN OLED
	if(HAL_OK == SCREEN_SSD1306_Init(&hscreen1, &hi2c1)){
		tx_Buffer_Size = snprintf((char *)vcp_Tx_Buffer, UART_TX_BUFFER_SIZE, "Screen Init Done\r\n");
		HAL_UART_Transmit(&huart2, vcp_Tx_Buffer, tx_Buffer_Size, 10);
		SCREEN_SSD1306_Write_String(&hscreen1, "ENSEA CFR", Font_11x18, screen_color);
		hscreen1.CurrentX = 0;
		hscreen1.CurrentY = 18;
		SCREEN_SSD1306_Write_String(&hscreen1, "Code v0.1", Font_11x18, screen_color);
		SCREEN_SSD1306_Update_Screen(&hscreen1);
	}
	else{
		tx_Buffer_Size = snprintf((char *)vcp_Tx_Buffer, UART_TX_BUFFER_SIZE, "Screen Init Error\r\n");
		HAL_UART_Transmit(&huart2, vcp_Tx_Buffer, tx_Buffer_Size, 10);
	}

	// Init Encodeur
	ENCODEUR_Init(&henc1, &htim1);
	//Bug de l'encodeur, une des 2 pins de réagit pas comme il faudrait... à changer ?!

	// Init Stepper
	Stepper_Init(&hstepperLeft, &htim3, TIM_CHANNEL_1, DIR_MOTOR_L_GPIO_Port, DIR_MOTOR_L_Pin, SET);
	Stepper_Init(&hstepperRight, &htim2, TIM_CHANNEL_1, DIR_MOTOR_R_GPIO_Port, DIR_MOTOR_R_Pin, RESET);

	Stepper_Set_Speed(&hstepperLeft, 20, 0);
	Stepper_Set_Speed(&hstepperRight, 5, 0);


	// Init Lidar
	YDLIDAR_X4_Init(&hlidar, &huart1);
	// voir du fichier usart.c pour gestion de l'interruption

	// Init Time
	HAL_TIM_Base_Start_IT(&htim7);




  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
		if(hlidar.newData){
			YDLIDAR_X4_Compute_Payload(&hlidar);
			float min_distance = 10000;
			int idx_angle_min_distance;
			for(int idx_angle=ANGLE_MIN; idx_angle<ANGLE_MAX; idx_angle++){
				if((10 < hlidar.scan_response.distance[idx_angle]) &&
						(hlidar.scan_response.distance[idx_angle] < min_distance)){
					idx_angle_min_distance = idx_angle;
					min_distance = hlidar.scan_response.distance[idx_angle];
				}
			}
//			sprintf(hscreen1.textBuffer, "%3d | %4.2f", idx_angle_min_distance-180, min_distance);
//			SCREEN_SSD1306_Fill_String(&hscreen1, hscreen1.textBuffer, Font_11x18, screen_color);
			if(min_distance < 200){
				LED_set_value(7);
				Stepper_Stop(&hstepperLeft);
				Stepper_Stop(&hstepperRight);
			}
			else{
				LED_set_value(0);
			}

			hlidar.newData = 0;
		}

		if(button.pushed){
			switch(button.name){
			case BTN_0:
				SCREEN_SSD1306_Fill_String(&hscreen1, "Button 0", Font_11x18, screen_color);
				// add code here
				break;
			case BTN_1:
				SCREEN_SSD1306_Fill_String(&hscreen1, "Button 1", Font_11x18, screen_color);
				// add code here
				break;
			case BTN_2:
				SCREEN_SSD1306_Fill_String(&hscreen1, "Button 2", Font_11x18, screen_color);
				// add code here
				break;
			case BTN_ENC:
				SCREEN_SSD1306_Fill_String(&hscreen1, "Button Enc", Font_11x18, screen_color);
				// add code here
				break;
			default:

			}
		}
		else if(henc1.it){
//			sprintf(hscreen1.textBuffer,"%6d\r\n",henc1.value);
//			SCREEN_SSD1306_Fill_String(&hscreen1, hscreen1.textBuffer, Font_11x18, screen_color);
//			henc1.it = 0;
		}
		else if(it_time){
			sprintf(hscreen1.textBuffer, "%3d.%d", time_100ms/10, time_100ms%10);
			SCREEN_SSD1306_Fill_String(&hscreen1, hscreen1.textBuffer, Font_11x18, screen_color);
			if(time_100ms > 200){
				Stepper_Stop(&hstepperLeft);
				Stepper_Stop(&hstepperRight);
			}
			else if(time_100ms > 100){
				Stepper_Start(&hstepperLeft);
				Stepper_Start(&hstepperRight);
			}
			it_time = 0;
		}
//		LED_set_value(led++);
//		led %= 8;
//		HAL_Delay(10);


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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  if (htim->Instance == TIM7) {
	  time_100ms++;
	  it_time = 1;
  }
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
