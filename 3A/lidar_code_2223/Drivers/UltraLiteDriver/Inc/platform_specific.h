
#ifndef _PLATFORM_SPECIFIC_H_
#define _PLATFORM_SPECIFIC_H_

#pragma once


#include "stm32g0xx.h"
#include <stm32g0xx_nucleo.h>



#define InputBufferSize 512 /* Max size sent by a user from UART */
#define I2cExpAddr0 ((int)(0x43*2))
#define I2cExpAddr1 ((int)(0x42*2))
#define GPMR    0x10
#define GPSR    0x12
#define GPDR    0x14
#define XNUCLEO53L1_DEV_LEFT     0
#define XNUCLEO53L1_DEV_CENTER   1
#define XNUCLEO53L1_DEV_RIGHT    2
#define MAX_VL53L1X_SENSORS		 3
#define ARRAY_SIZE(a)  (sizeof(a) / sizeof(a[0]))
#define MSG_START "VL53L1X sensor detected\n\0"
#define MSG_OK "ok\n\0"
#define MSG_UNKNOWN_CMD "Unknown command\n\0"
#define MSG_WRONG_VALUE "Warning: Wrong value sent\n\0"
int SensorState(void);

void GPIO_Expander_Init(void);
int _ExpandersSetAllIO(void);
int _ExpanderRd(int I2cExpAddr, int index, uint8_t *data, int n_data);
int _ExpanderWR(int I2cExpAddr, int index, uint8_t *data, int n_data);
uint8_t Sensor_Reset(uint8_t DevNo, uint8_t state);

void I2C_Init(void);
void UART_Init(void);
void UART_Reboot(size_t *Uart_RxIndex, int *UartActive, int *UART_Ready,
		 char *Uart_RXBuffer);
void UART_Print(const char *msg);
void UART_CheckError(uint16_t status);
void UART_GetCommandFromUser(uint16_t dev, char *Buffer);
void DMA1_Stream6_IRQHandler(void);
void USART2_IRQHandler(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

void Peek(uint16_t dev, uint16_t Register);
void Peek16(uint16_t dev, uint16_t Register);
void _I2cFailRecover(void);

#endif
