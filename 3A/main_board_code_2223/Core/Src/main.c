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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "config.h"
#include "propulsion.h"
#include "odometry.h"
#include "robot.h"
#include "bezier.h"
#include "strategy.h"
#include "serial.h"
#include "lidar.h"
#include "avoidance.h"
#include "symetry.h"
#include "control.h"
#include <stdio.h>
#include <math.h>

extern Robot robot;
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

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int _write(int file, char *ptr, int len) {
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++) {
		HAL_UART_Transmit(&huart2, (uint8_t *) ptr++, 1, HAL_MAX_DELAY);
	}
	return len;
}

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
  MX_TIM1_Init();
  MX_TIM8_Init();
  MX_TIM11_Init();
  MX_TIM3_Init();
  MX_TIM7_Init();
  MX_TIM2_Init();
  MX_TIM6_Init();
  MX_TIM4_Init();
  MX_USART2_UART_Init();
  MX_TIM5_Init();
  MX_USART6_UART_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim1);
  HAL_TIM_Base_Start(&htim3);
  HAL_TIM_Base_Start_IT(&htim5);

  HAL_UART_Receive_IT(&huart6, pData, 1);
  printf("Initializing propulsion system...");
  propulsion_initialize();
  propulsion_disableMotors();
  avoidance_initialize();
  HAL_Delay(200);
  printf(" Done.\r\n");

  //HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
  //printf("Initializing strategy...");
  Strategy* strategy;
  int curveIndex = 0;
  int onSiteActionIndex = 0;
  int onMoveActionIndex = 0;

  robot.waitingForOnSiteAction = false;
  robot.waitingForOnMoveAction = false;
  robot.team = YELLOW;
  float t = 0;

  HAL_Delay(200);
  printf(" Done.\r\n");

  //HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
  printf("Initializing lidar...");
  lidar_initialize();
  HAL_Delay(200);
  printf(" Done.\r\n");

  bool waitingForMatchStart = true;

  printf("Waiting for start...\r\n");
  pData[0] = 'o';
  int a = 0;
  while ((waitingForMatchStart == true)) {
  	  waitingForMatchStart = HAL_GPIO_ReadPin(START_GPIO_Port, START_Pin);
  	  if(wifiDataRX==0x84){
  		  waitingForMatchStart=0;
  		  strategy = strategy_initialize(7);
  		  //WifiUartTXActivation();
  	  }
  	  else if((pData[0] >= '0' && pData[0] <= '9')  && a == 0)
  	  {
  		  a = 1;
  	  	  switch(pData[0])
  	      	{
  	  	  	case '0':
  	  	  		printf("Initializing strategy...0");
  	  	  		strategy = strategy_initialize(0);
  	       	    break;
  	      	case '1':
  	      		printf("Initializing strategy...1");
  	      		strategy = strategy_initialize(1);
  	      		switchTeam(strategy);
  	            break;
  	      	case '2':
  	      		printf("Initializing strategy...2");
  	      		strategy = strategy_initialize(2);
  	      		break;
  	        case '3':
  	        	printf("Initializing strategy...3");
  	        	strategy = strategy_initialize(3);
  	        	switchTeam(strategy);
  	        	break;
  	        case '4':
  	        	printf("Initializing strategy...4");
  	        	strategy = strategy_initialize(4);
  	        	switchTeam(strategy);
  	        	break;
  	        case '5':
  	        	printf("Initializing strategy...5");
  	        	strategy = strategy_initialize(5);
  	            break;
  	        default:
  	            break;
  	      	}
  	  }
  }
  propulsion_enableMotors();

  printf("Initializing odometry...");
  Vector2 start = strategy->path[0]->p1;
  Vector2 startTangent = strategy->path[0]->p2;
  float startAngle = vector2_angle(vector2_diff(startTangent, start));
  odometry_setPosition(start.x, start.y);
  odometry_setAngle(startAngle);
  robot.measuredSpeed = 0;
  odometry_startKalman();
  HAL_Delay(200);
  printf(" Done.\r\n");

  printf("Go!\r\n");

  //odometry_setPosition(0, 0);
  //odometry_setAngle(0);

  HAL_UART_Receive_DMA(&huart4, &lidarBuf[0], 3);//HAL_UART_Receive_IT(&huart4, &lidarData, 1);
  HAL_UART_Receive_IT(&huart6, &armData, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  /*while (1) {
	  for (int i=0; i<16; i++) {
		  printf("%d ", i);
		  printf("(%d) ", lidar_timeSinceData[i]);
	  }
	  printf("\r\n");

	  if (!lidar_frontIsClear()) {
		  printf("Front stop!\r\n");
	  }
	  if (!lidar_backIsClear()) {
		  printf("Back stop!\r\n");
	  }

	  HAL_Delay(100);
  }*/

  while (onSiteActionIndex < strategy->onSiteActionsLengths[0]) {
	  uint8_t action = strategy->onSiteActions[0][onSiteActionIndex];
	  serial_send(&action, 1, 6);
	  robot.waitingForOnSiteAction = true;

	  printf("Waiting for 0xFF...\r\n");
	  printf("%d\r\n", robot.waitingForOnSiteAction);
	  while (robot.waitingForOnSiteAction) {}
	  printf("%d\r\n", robot.waitingForOnSiteAction);
	  onSiteActionIndex++;
  }

  printf("About to move...\r\n");

  while (1) {
	  if (onMoveActionIndex < strategy->onMoveActionsLengths[curveIndex]
              && !robot.waitingForOnMoveAction
			  && !robot.waitingForOnSiteAction) {
		  uint8_t action = strategy->onMoveActions[curveIndex][onMoveActionIndex];
		  serial_send(&action, 1, 6);
		  robot.waitingForOnMoveAction = true;
	  }

	  avoidance_update(t, strategy->directions[curveIndex]);

	  if (avoidanceState == PATH_CLEAR && curveIndex < strategy->length) {
		  t = propulsion_followBezier(
				  strategy->path[curveIndex],
				  strategy->directions[curveIndex],
				  strategy->speeds[curveIndex],
				  strategy->speeds[curveIndex+1],
				  false
		  );
	  } else if (avoidanceState == PATH_OBSTRUCTED) {
		  propulsion_setSpeeds(0, 0, 0);
	  } else if (avoidanceState == BACKTRACKING) {
		  t = propulsion_followBezier(
				  strategy->path[curveIndex],
				  strategy->directions[curveIndex],
				  strategy->speeds[curveIndex],
				  strategy->speeds[curveIndex+1],
				  true
		  );
	  }

	  if (t > 0.99 && !robot.waitingForOnMoveAction) {
	      curveIndex = (curveIndex + 1);// % strategy->length;
	      onSiteActionIndex = 0;
	      while (onSiteActionIndex < strategy->onSiteActionsLengths[curveIndex]) {
	    	  uint8_t action = strategy->onSiteActions[curveIndex][onSiteActionIndex];
	    	  serial_send(&action, 1, 6);
	    	  robot.waitingForOnSiteAction = true;

	    	  while (robot.waitingForOnSiteAction) {
	    		  propulsion_setSpeeds(0, 0, 0);
	    	  }
	    	  onSiteActionIndex++;
	      }
	      onMoveActionIndex = 0;
	  }

	  if (curveIndex == strategy->length) {
		  break;
	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }

  propulsion_disableMotors();
  printf("Finished.\r\n");

  while (1) {

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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
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
  printf("A runtime error occurred.\r\n");
  while (1) {
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
