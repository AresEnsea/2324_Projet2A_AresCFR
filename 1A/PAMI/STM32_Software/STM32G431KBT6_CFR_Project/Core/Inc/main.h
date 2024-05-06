/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED1_Pin GPIO_PIN_0
#define LED1_GPIO_Port GPIOF
#define LED2_Pin GPIO_PIN_1
#define LED2_GPIO_Port GPIOF
#define ADC_BATT_Pin GPIO_PIN_0
#define ADC_BATT_GPIO_Port GPIOA
#define USR_BTN_0_Pin GPIO_PIN_1
#define USR_BTN_0_GPIO_Port GPIOA
#define USR_BTN_0_EXTI_IRQn EXTI1_IRQn
#define RPI_TX_Pin GPIO_PIN_2
#define RPI_TX_GPIO_Port GPIOA
#define RPI_RX_Pin GPIO_PIN_3
#define RPI_RX_GPIO_Port GPIOA
#define DIR_MOTOR_R_Pin GPIO_PIN_4
#define DIR_MOTOR_R_GPIO_Port GPIOA
#define PWM_MOTOR_R_Pin GPIO_PIN_5
#define PWM_MOTOR_R_GPIO_Port GPIOA
#define PWM_MOTOR_L_Pin GPIO_PIN_6
#define PWM_MOTOR_L_GPIO_Port GPIOA
#define DIR_MOTOR_L_Pin GPIO_PIN_7
#define DIR_MOTOR_L_GPIO_Port GPIOA
#define ENC_BTN_Pin GPIO_PIN_0
#define ENC_BTN_GPIO_Port GPIOB
#define ENC_BTN_EXTI_IRQn EXTI0_IRQn
#define TIM1_CH1_ENC_Pin GPIO_PIN_8
#define TIM1_CH1_ENC_GPIO_Port GPIOA
#define TIM1_CH2_ENC_Pin GPIO_PIN_9
#define TIM1_CH2_ENC_GPIO_Port GPIOA
#define LIDAR_RX_Pin GPIO_PIN_10
#define LIDAR_RX_GPIO_Port GPIOA
#define USR_BTN_2_Pin GPIO_PIN_11
#define USR_BTN_2_GPIO_Port GPIOA
#define USR_BTN_2_EXTI_IRQn EXTI15_10_IRQn
#define USR_BTN_1_Pin GPIO_PIN_12
#define USR_BTN_1_GPIO_Port GPIOA
#define USR_BTN_1_EXTI_IRQn EXTI15_10_IRQn
#define I2C_SCL_OLED_Pin GPIO_PIN_15
#define I2C_SCL_OLED_GPIO_Port GPIOA
#define VCP_TX_Pin GPIO_PIN_3
#define VCP_TX_GPIO_Port GPIOB
#define VCP_RX_Pin GPIO_PIN_4
#define VCP_RX_GPIO_Port GPIOB
#define LIDAR_TX_Pin GPIO_PIN_6
#define LIDAR_TX_GPIO_Port GPIOB
#define I2C_SDA_OLED_Pin GPIO_PIN_7
#define I2C_SDA_OLED_GPIO_Port GPIOB
#define LED0_Pin GPIO_PIN_8
#define LED0_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
