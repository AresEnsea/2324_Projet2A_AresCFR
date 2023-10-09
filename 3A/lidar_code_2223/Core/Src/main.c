/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "platform_specific.h"
#include "stm32g0xx.h"
#include <string.h>
#include "VL53L1X_api.h"
#include "math.h"

#include "trameUart.h"
#include "testUART.h"
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
 I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint16_t LEDS[16]= {};

/* ----- UART variables, only useful for Serial communication ----- */

extern char Uart_RXBuffer[80];	/* Buffer for continuous RX */
#ifdef USER
extern char UartComm_RXBuffer[80];
#endif
extern int UART_Active;		/* Flag to see if UART is active */
extern int UART_Ready;		/* Flag new command available   */
extern size_t Uart_RxIndex;

/* ----- VL53L1X variables ----- */

uint16_t Dev_init = 0x52;		/* I2C address of device 1 */
float    LidarAngle[NumOfZonesPerSensor*NumOfTOFSensors];
uint16_t LidarDistance[NumOfZonesPerSensor*NumOfTOFSensors];
uint32_t TimeStamp[NumOfZonesPerSensor*NumOfTOFSensors];
//uint16_t Devs[9] = {0x62, 0x64, 0x66, 0x68, 0x6A, 0x6C, 0x6E, 0x70, 0x72};
uint16_t Devs[16] = {0x62, 0x64, 0x66, 0x68, 0x6A, 0x6C, 0x6E, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7A, 0x7C, 0x7E, 0x80};
uint16_t Distance;
uint16_t SignalRate;
uint16_t SpadNb;
uint16_t AmbientRate;
uint16_t SignalPerSpad;
uint16_t AmbientPerSpad;
uint8_t RangeStatus;
uint16_t RangeCounter = 0;
#define Calibrate
/*
#ifdef Calibrate
int16_t  OffsetCal[NumOfTOFSensors*NumOfZonesPerSensor] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0
		};
#else
int16_t  OffsetCal[NumOfTOFSensors * NumOfZonesPerSensor] = {
 -40, -44, -29, -24, -21, -18, -14, -15, -14, -13, -17, -22, -32,
 -28, -17, -21, -24, -11, -12, -12,  -9, -11, -26, -25, -36, -38,
 -36, -46, -26, -24, -20, -16, -17, -14, -11, -18, -17, -26, -37,
 -43, -31, -21, -25, -20,  -8, -12, -12, -13, -20, -27, -26, -38,
 -51, -41, -36, -24, -22, -21, -19, -16, -17, -22, -32, -41, -52,
 -44, -38, -26, -26, -29, -17,  -8, -11, -20, -20, -28, -34, -40,
 -50, -41, -37, -39, -23, -11, -21, -18, -20, -18, -23, -34, -48,
 -50, -41, -29, -28, -20, -16, -10, -16, -22, -25, -22, -45, -41,
 -43, -40, -25, -27, -16, -21, -14,  -9, -28, -39, -40, -46, -55
};*/
#ifdef Calibrate
int16_t  OffsetCal[NumOfTOFSensors*NumOfZonesPerSensor] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0
		};
#else
int16_t  OffsetCal[NumOfTOFSensors * NumOfZonesPerSensor] = {
-40, -44, -29, -24, -21, -18, -14, -15, -14, -13, -17, -22, -32,
-28, -17, -21, -24, -11, -12, -12,  -9, -11, -26, -25, -36, -38,
-36, -46, -26, -24, -20, -16, -17, -14, -11, -18, -17, -26, -37,
-43, -31, -21, -25, -20,  -8, -12, -12, -13, -20, -27, -26, -38,
-51, -41, -36, -24, -22, -21, -19, -16, -17, -22, -32, -41, -52,
-44, -38, -26, -26, -29, -17,  -8, -11, -20, -20, -28, -34, -40,
-50, -41, -37, -39, -23, -11, -21, -18, -20, -18, -23, -34, -48,
-50, -41, -29, -28, -20, -16, -10, -16, -22, -25, -22, -45, -41,
-43, -40, -25, -27, -16, -21, -14,  -9, -28, -39, -40, -46, -55
};

#endif
uint16_t   zone_center[]={247,239,231,223,215,207,199,191,183,175,167,159,151, 247, 239, 231, 223, 215};
// Timing Budget Options:  15, 20, 33, 50, 100, 200, 500
uint16_t TimingBudget = 50;

uint16_t current_zone=0;
char BigBuff[4000];
char VL53L1X_BUFFER[60];	/* Create a buffer to get data */
char SmallBuff[17];
char FloatBuff[40];

uint16_t ActiveCaptors = 0xFFFF;
uint16_t FailedBoot = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM6_Init(void);
/* USER CODE BEGIN PFP */
void PlotPolarData(uint8_t SensorNum, uint8_t CurrentZone, uint8_t NumOfZones, uint16_t Distance);
void TurnOnSensor(uint8_t SensorNum);
void ResetAllSensors(void);
void ResetAndInitializeAllSensors(void);
void SystemClock_Config(void);
void SendAllMesurements(uint32_t TotalTime);
void SendOneROIMesurement(uint32_t TotalTime, uint8_t selectedZone);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t dataRead;
void ResetAndInitializeAllSensors(void)
{
	uint8_t i,counter, Sensor, error = 0;
	uint8_t Bootstate = 0;
	int16_t Offset;
	ResetAllSensors();
	HAL_Delay(10);
	for (i = 0; i < NumOfTOFSensors; i++)
	{
		FailedBoot = i;
		TurnOnSensor(i);
		HAL_Delay(60);
		error += VL53L1X_BootState(Dev_init, &Bootstate);
		while (Bootstate != 0x03 && counter < 10)
		{
			//ITM_Port32(31) = Bootstate;
			HAL_Delay(60);
			error += VL53L1X_BootState(Dev_init, &Bootstate);
			counter++;
		}
		counter = 0;
		VL53L1X_SensorInit(Dev_init);	/* Initialize sensor  */HAL_Delay(1);
		VL53L1X_SetI2CAddress(Dev_init, Devs[i]);HAL_Delay(1);	/* Change i2c address Left is now 0x62 and Dev1 */
		dataRead = ReadRegister8(Devs[i], 0x10f);HAL_Delay(1);
		dataRead = ReadRegister8(Devs[i], 0x110);
	}
	UART_Print("All Chips booted\n");

	for (Sensor = 0; Sensor < NumOfTOFSensors; Sensor++)
	{
		VL53L1X_SetDistanceMode(Devs[Sensor], 1);
		VL53L1X_SetTimingBudgetInMs(Devs[Sensor], TimingBudget);
		VL53L1X_SetInterMeasurementInMs(Devs[Sensor], TimingBudget);
		VL53L1X_SetROI(Devs[Sensor], WidthOfSPADsPerZone, 6);
		WriteRegister8(Devs[Sensor], ROI_CONFIG__USER_ROI_CENTRE_SPAD, zone_center[0] - 0);
		error = VL53L1X_GetOffset(Devs[Sensor], &Offset);
		VL53L1X_SetOffset(Devs[Sensor], Offset + 40);
	}
	for (Sensor = 0; Sensor < NumOfTOFSensors; Sensor++)
	{
		if((ActiveCaptors>>Sensor)&1){
			VL53L1X_StartRanging(Devs[Sensor]);
		}
		HAL_Delay(1);
	}
	if (ActiveCaptors != 0xFFFF)
	{
		UART_Print("Not all captors were initialized\r\n");
	}

}

float OldAngle;
double SystemAngle;
void PlotPolarData(uint8_t SensorNum, uint8_t CurrentZone, uint8_t NumOfZones, uint16_t Distance)
{
	double PartZoneAngle;

	float CorrectedDistance = 0;

	if (Distance > 60000)
	{
		Distance = 0;
	}
	PartZoneAngle = (StartingZoneAngle + ZoneFOVChangePerStep*CurrentZone) - (HorizontalFOVofSensor / 2.0);
	SystemAngle = -80 + 20.0*SensorNum + PartZoneAngle;
	CorrectedDistance = pow(pow(RadarCircleRadius,2) + pow(Distance, 2) - (2 * RadarCircleRadius * Distance * cos((180 - PartZoneAngle)/(180) * Pi)), 0.5);
	if (CorrectedDistance < 55)
	{
		CorrectedDistance = 55;
	}
	LidarAngle[SensorNum*13+CurrentZone] = SystemAngle;
	LidarDistance[SensorNum*13+CurrentZone] = (uint16_t)CorrectedDistance;
}

void TurnOnSensor(uint8_t SensorNum)
{
	switch (SensorNum)
	{
		case 0:
			// GPIO PC2
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
			break;
		case 1:
			// GPIO PC15
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
			break;
		case 2:
			// GPIO PC12
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);
			break;
		case 3:
			// GPIO PB9
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
			break;
		case 4:
			// GPIO PB6
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
			break;
		case 5:
			// GPIO PB3
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
			break;
		case 6:
			// GPIO PD2
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
			break;
		case 7:
			// GPIO PC9
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
			break;
		case 8:
			// GPIO PA12
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
			break;
		case 9:
			// GPIO PC7
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
			break;
		case 10:
			// GPIO PA8
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
			break;
		case 11:
			// GPIO PB13
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
			break;
		case 12:
			// GPIO PB10
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
			break;
		case 13:
			// GPIO PB0
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
			break;
		case 14:
			// GPIO PA7
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
			break;
		case 15:
			// GPIO PA4
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
			break;


	}
}

void ResetAllSensors(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);  // Capt 0
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET); // Capt 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);  // Capt 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);  // Capt 3

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);  // Capt 4
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);  // Capt 5
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);  // Capt 6
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);  // Capt 7

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET); // Capt 8
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);  // Capt 9
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);  // Capt 10
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET); // Capt 11

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET); // Capt 12
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);  // Capt 13
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);  // Capt 14
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);  // Capt 15
}

void SendAllMesurements(uint32_t TotalTime){
	UART_Send_Mesures(LidarDistance , NumOfZonesPerSensor + 1 , TotalTime);

	/*
	for(uint16_t x=0; x <NumOfZonesPerSensor*NumOfTOFSensors; x++){
		snprintf(FloatBuff, sizeof(FloatBuff), "%f", LidarAngle[x]);
		snprintf(SmallBuff, sizeof(SmallBuff), " ; %d", LidarDistance[x]);
		snprintf(BigBuff, sizeof(BigBuff), " ; %ld\n\r", TimeStamp[x]);
		UART_Print(FloatBuff);
		UART_Print(SmallBuff);
		UART_Print(BigBuff);


	}*/
	setInactiveCaptors(0);
	setActiveCaptors(1);
}

void SendOneROIMesurement(uint32_t TotalTime, uint8_t selectedZone){
	UART_Send_Mesures(LidarDistance , selectedZone, TotalTime);

	/*
	for(uint16_t x=0; x <NumOfZonesPerSensor*NumOfTOFSensors; x++){
		snprintf(FloatBuff, sizeof(FloatBuff), "%f", LidarAngle[x]);
		snprintf(SmallBuff, sizeof(SmallBuff), " ; %d", LidarDistance[x]);
		snprintf(BigBuff, sizeof(BigBuff), " ; %ld\n\r", TimeStamp[x]);
		UART_Print(FloatBuff);
		UART_Print(SmallBuff);
		UART_Print(BigBuff);


	}*/
	setInactiveCaptors(0);
	setActiveCaptors(1);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	VL53L1X_ERROR error = 0;
	uint32_t i=0;
	uint8_t Zone, Sensor, Timeout;

	uint32_t TimeStart, TimeEnd, TotalTime, CurrentTime;
	uint8_t Sensorcheck;
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
  MX_I2C1_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  ResetAndInitializeAllSensors();
  LEDs_init();
  HAL_TIM_Base_Start_IT(&htim6);
/*
  tests();
  LEDs_init();
  while(1){

  }*/
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  	error = 0;
		TimeStart = HAL_GetTick();
		Timeout = 0;
		for(Zone = 0; Zone < NumOfZonesPerSensor; Zone++)
		{
			for (Sensor=0; Sensor < NumOfTOFSensors ; Sensor++)
			{
				if((ActiveCaptors>>Sensor)&1)
					WriteRegister8(Devs[Sensor], ROI_CONFIG__USER_ROI_CENTRE_SPAD, zone_center[Zone+1] - 0);
			}
			i=i+1;
			for (Sensor=0; Sensor < NumOfTOFSensors ; Sensor++)
			{
				if((ActiveCaptors>>Sensor)&1){
					error = VL53L1X_CheckForDataReady(Devs[Sensor], &Sensorcheck);
					while ((Sensorcheck == 0) && (Timeout == 0))
					{
						HAL_Delay(1);
						CurrentTime = HAL_GetTick();
						if (CurrentTime > (TimeStart + (NumOfZonesPerSensor + 1) * TimingBudget * 2))
						{
							Timeout = 1;
							Sensor = NumOfTOFSensors;
							Zone = NumOfZonesPerSensor;
						}
						else
						{
							error += VL53L1X_CheckForDataReady(Devs[Sensor], &Sensorcheck);
						}
					}


				if (Timeout == 0)
				{
					WriteRegister8(Devs[Sensor], ROI_CONFIG__USER_ROI_CENTRE_SPAD, zone_center[Zone+1] - 0);
					TimeStamp[Sensor*13+ Zone] = HAL_GetTick();
					VL53L1X_ClearInterrupt(Devs[Sensor]);

					error += VL53L1X_GetDistance(Devs[Sensor], &Distance);
					error += VL53L1X_GetRangeStatus(Devs[Sensor], &RangeStatus);
					if ((RangeStatus== 0) || (RangeStatus == 7))
					{
						if (Distance > 60000)
						{
							Distance = 0;
							PlotPolarData(Sensor, Zone, 13, 0);
						}
						else
						{
							Distance = Distance + OffsetCal[Sensor*13 + Zone];
							if (Distance > 60000)
							{
								Distance = 0;
							}
							PlotPolarData(Sensor, Zone, 13, Distance);
						}
					}
					else
					{
						PlotPolarData(Sensor, Zone, 13, 4000);
					}
				}
				}
			}
			toggleInactiveCaptors();
			if(Timeout != 1){
				TimeEnd = HAL_GetTick();;
				TotalTime = (TimeEnd - TimeStart);
				SendOneROIMesurement(TotalTime, Zone);
			}
		}
		if (Timeout == 1)
		{
			ResetAndInitializeAllSensors();
			Timeout = 0;
			//UART_Print("Reset Performed\n");
		}
		else
		{
			HAL_Delay(TimingBudget);
			TimeEnd = HAL_GetTick();;
			TotalTime = (TimeEnd - TimeStart);
			//snprintf(BigBuff, sizeof(BigBuff), "Time: %ld\n", TotalTime);
			//UART_Print(BigBuff);
			//SendAllMesurements(TotalTime);
		}
		if (error !=0)
		{
			UART_Print("Some Errors seen\n");
		}
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00602173;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */
  I2C_Init();
  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 3999;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 65535;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

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
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT|UART_ADVFEATURE_DMADISABLEONERROR_INIT;
  huart2.AdvancedInit.OverrunDisable = UART_ADVFEATURE_OVERRUN_DISABLE;
  huart2.AdvancedInit.DMADisableonRxError = UART_ADVFEATURE_DMA_DISABLEONRXERROR;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */
  UART_Init();
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_15|GPIO_PIN_0
                          |GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_7
                          |GPIO_PIN_9|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8|GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC12 PC13 PC15 PC0
                           PC2 PC3 PC4 PC7
                           PC9 PC10 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_15|GPIO_PIN_0
                          |GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_7
                          |GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 PA7 PA8
                           PA11 PA12 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB10 PB11
                           PB13 PB14 PB3 PB4
                           PB6 PB7 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD8 PD0 PD2 PD3 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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
