
#ifndef _PLATFORM_H_
#define _PLATFORM_H_
#pragma once

#include "stm32G0xx.h"
#include "vl53l1_platform_log.h"
#include "vl53l1_types.h"
#include "vl53l1_error_codes.h"
#include <stdint.h>
#include "stm32G0xx_hal.h"




uint32_t ReadRegister32(uint16_t dev, uint16_t RegisterAdress);
uint16_t ReadRegister16(uint16_t dev, uint16_t registerAddr);
uint8_t ReadRegister8(uint16_t dev, uint16_t registerAddr);
void WriteRegister8(uint16_t dev, uint16_t registerAddr, uint8_t value);
void WriteRegister16(uint16_t dev, uint16_t RegisterAdress, uint16_t value);
void WriteRegister32(uint16_t dev, uint16_t RegisterAdress, uint32_t value);
void WaitMs(uint32_t TimeMs);



VL53L1_Error VL53L1_CommsInitialise(uint16_t pdev,uint8_t comms_type,uint16_t comms_speed_khz);

VL53L1_Error VL53L1_CommsClose(uint16_t pdev);

VL53L1_Error VL53L1_WriteMulti(uint16_t pdev,uint16_t index, uint8_t *pdata,uint32_t count);

VL53L1_Error VL53L1_ReadMulti(uint16_t pdev,uint16_t index,	uint8_t *pdata,	uint32_t count);

VL53L1_Error VL53L1_WrByte(uint16_t pdev,uint16_t index,uint8_t VL53L1_PRM_00005);

VL53L1_Error VL53L1_WrWord(uint16_t pdev,uint16_t index,uint16_t VL53L1_PRM_00005);

VL53L1_Error VL53L1_WrDWord(uint16_t pdev, uint16_t index, uint32_t VL53L1_PRM_00005);

VL53L1_Error VL53L1_RdByte(uint16_t pdev, uint16_t index,uint8_t *pdata);

VL53L1_Error VL53L1_RdWord(uint16_t pdev,	uint16_t index, uint16_t *pdata);

VL53L1_Error VL53L1_RdDWord(uint16_t pdev,	uint16_t index,	uint32_t *pdata);

VL53L1_Error VL53L1_WaitUs(int32_t wait_us);

VL53L1_Error VL53L1_WaitMs(int32_t wait_ms);

VL53L1_Error VL53L1_GetTimerFrequency(int32_t *ptimer_freq_hz);

VL53L1_Error VL53L1_GetTimerValue(int32_t *ptimer_count);

VL53L1_Error VL53L1_GpioSetMode(uint8_t pin, uint8_t mode);

VL53L1_Error VL53L1_GpioSetValue(uint8_t pin, uint8_t value);

VL53L1_Error VL53L1_GpioGetValue(uint8_t pin, uint8_t *pvalue);

VL53L1_Error VL53L1_GpioXshutdown(uint8_t value);

VL53L1_Error VL53L1_GpioCommsSelect(uint8_t value);

VL53L1_Error VL53L1_GpioPowerEnable(uint8_t value);

VL53L1_Error  VL53L1_GpioInterruptEnable(void (*function)(void), uint8_t edge_type);

VL53L1_Error  VL53L1_GpioInterruptDisable(void);

VL53L1_Error VL53L1_GetTickCount(uint32_t *ptime_ms);

#endif
