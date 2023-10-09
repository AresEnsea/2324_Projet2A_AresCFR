/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "led.h"

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
/* USER CODE BEGIN Private defines */
#define RadarCircleRadius 						(110.0 / 2.0)
#define Pi 										3.1415
#define VHV_TIMER 								200
#define ROI_CONFIG__USER_ROI_CENTRE_SPAD		0x007F
//#define NumOfTOFSensors							9
#define NumOfTOFSensors							16
#define TotalWidthOfSPADS						16
#define WidthOfSPADsPerZone						4
#define NumOfSPADsShiftPerZone					1
#define HorizontalFOVofSensor					19.09
#define SingleSPADFOV							(HorizontalFOVofSensor/TotalWidthOfSPADS)
#define NumOfZonesPerSensor						(((TotalWidthOfSPADS - WidthOfSPADsPerZone) / NumOfSPADsShiftPerZone) + 1)
#define StartingZoneAngle						(WidthOfSPADsPerZone / 2 * SingleSPADFOV)
#define ZoneFOVChangePerStep					(SingleSPADFOV * NumOfSPADsShiftPerZone)

#define MaxInterestDistance						5000

#define ITM_Port32(n) (*((volatile unsigned long *)(0xE0000000+4*n)))
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
