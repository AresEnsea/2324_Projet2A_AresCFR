#ifndef _SERIAL_
#define _SERIAL_

#include "usart.h"
#include "gpio.h"
#include "robot.h"
#include "lidar.h"
#include "lidarReading.h"
#include <stdio.h>

extern uint8_t lidarData;
extern uint8_t globalUSARTchange;
extern uint8_t wifiDataRX;
extern uint8_t wifiDataTX;
extern uint8_t armData;
extern uint8_t pData[1];

extern uint8_t lidarBuf[3000];
extern uint16_t bufferIndex;
extern uint8_t DataAcquiered;

void parser32(uint32_t *ptr);
int serial_send(uint8_t *ptr, int len, int uartPort);
void WifiUartTXActivation();
void WifiUartTXDeactivation();

#endif
