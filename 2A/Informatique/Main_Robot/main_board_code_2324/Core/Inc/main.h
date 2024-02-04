/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
int ___io_putchar(int ch);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define L_MOTOR_EN_Pin GPIO_PIN_0
#define L_MOTOR_EN_GPIO_Port GPIOC
#define R_MOTOR_EN_Pin GPIO_PIN_1
#define R_MOTOR_EN_GPIO_Port GPIOC
#define L_MOTOR_DIR_Pin GPIO_PIN_2
#define L_MOTOR_DIR_GPIO_Port GPIOC
#define GREEN_LED_Pin GPIO_PIN_5
#define GREEN_LED_GPIO_Port GPIOA
#define L_ENCODER_A_Pin GPIO_PIN_6
#define L_ENCODER_A_GPIO_Port GPIOA
#define L_ENCODER_B_Pin GPIO_PIN_7
#define L_ENCODER_B_GPIO_Port GPIOA
#define WIFI_Pin GPIO_PIN_0
#define WIFI_GPIO_Port GPIOB
#define START_Pin GPIO_PIN_8
#define START_GPIO_Port GPIOC
#define R_ENCODER_A_Pin GPIO_PIN_8
#define R_ENCODER_A_GPIO_Port GPIOA
#define R_ENCODER_B_Pin GPIO_PIN_9
#define R_ENCODER_B_GPIO_Port GPIOA
#define R_MOTOR_DIR_Pin GPIO_PIN_11
#define R_MOTOR_DIR_GPIO_Port GPIOC
#define TEAM_LED_Pin GPIO_PIN_8
#define TEAM_LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
