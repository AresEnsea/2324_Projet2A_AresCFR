/*
 Copyright (c) 2017, STMicroelectronics - All Rights Reserved

 This file is part of VL53L1 Core and is dual licensed,
 either 'STMicroelectronics
 Proprietary license'
 or 'BSD 3-clause "New" or "Revised" License' , at your option.

*******************************************************************************

 'STMicroelectronics Proprietary license'

*******************************************************************************

 License terms: STMicroelectronics Proprietary in accordance with licensing
 terms at www.st.com/sla0081

 STMicroelectronics confidential
 Reproduction and Communication of this document is strictly prohibited unless
 specifically authorized in writing by STMicroelectronics.


*******************************************************************************

 Alternatively, VL53L1 Core may be distributed under the terms of
 'BSD 3-clause "New" or "Revised" License', in which case the following
 provisions apply instead of the ones mentioned above :

*******************************************************************************

 License terms: BSD 3-clause "New" or "Revised" License.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 3. Neither the name of the copyright holder nor the names of its contributors
 may be used to endorse or promote products derived from this software
 without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


*******************************************************************************

*/

#include "platform.h"
#include "platform_specific.h"

extern I2C_HANDLE;	/* Handle for VL53L1X I2C COM */
extern SERIAL_UART;	/* Handle for Serial UART COM */
extern DMA_HANDLE;	/* Handle for Serial DMA */

#define I2C_TIME_OUT_BASE   10
#define I2C_TIME_OUT_BYTE   1

uint32_t ReadRegister32(uint16_t dev, uint16_t RegisterAdress)
{
	uint8_t Status;
	uint8_t data_write[2];
	uint8_t data_read[4];

	data_write[0] = (RegisterAdress >> 8) & 0xFF;
	data_write[1] = RegisterAdress & 0xFF;
	Status = HAL_I2C_Master_Transmit(&I2C_HANDLE, dev, data_write, 2, 100);
	Status += HAL_I2C_Master_Receive(&I2C_HANDLE, dev, data_read, 4, 100);
	if (Status)
	{
		_I2cFailRecover();
	}
	return ((data_read[0] << 24) | (data_read[1]<<16) | (data_read[2]<<8)| (data_read[3]));
}

uint16_t ReadRegister16(uint16_t dev, uint16_t RegisterAdress)
{
	uint8_t Status;
	uint8_t data_write[2];
	uint8_t data_read[2];

	data_write[0] = (RegisterAdress >> 8) & 0xFF;
	data_write[1] = RegisterAdress & 0xFF;
	Status = HAL_I2C_Master_Transmit(&I2C_HANDLE, dev, data_write, 2, 100);
	Status += HAL_I2C_Master_Receive(&I2C_HANDLE, dev, data_read, 2, 100);
	if (Status)
	{
		_I2cFailRecover();
	}
	return (data_read[0] << 8) | (data_read[1]);
}

uint8_t ReadRegister8(uint16_t dev, uint16_t RegisterAdress)
{
	uint8_t Status;
	uint8_t data_write[2];
	uint8_t data_read[1];

	data_write[0] = (RegisterAdress >> 8) & 0xFF;
	data_write[1] = RegisterAdress & 0xFF;
	Status = HAL_I2C_Master_Transmit(&I2C_HANDLE, dev, data_write, 2, 100);
	Status += HAL_I2C_Master_Receive(&I2C_HANDLE, dev, data_read, 1, 100);
	if (Status)
	{
		_I2cFailRecover();
	}
	return data_read[0];
}

void WriteRegister8(uint16_t dev, uint16_t RegisterAdress, uint8_t value)
{
	uint8_t Status;
	uint8_t data_write[3];

	data_write[0] = (RegisterAdress >> 8) & 0xFF;
	data_write[1] = RegisterAdress & 0xFF;
	data_write[2] = value & 0xFF;
	Status = HAL_I2C_Master_Transmit(&I2C_HANDLE, dev, data_write, 3, 100);
	if (Status)
	{
		_I2cFailRecover();
	}
}

void WriteRegister16(uint16_t dev, uint16_t RegisterAdress, uint16_t value)
{
	uint8_t Status;
	uint8_t data_write[4];

	data_write[0] = (RegisterAdress >> 8) & 0xFF;
	data_write[1] = RegisterAdress & 0xFF;
	data_write[2] = (value >> 8) & 0xFF;
	data_write[3] = value & 0xFF;
	Status = HAL_I2C_Master_Transmit(&I2C_HANDLE, dev, data_write, 4, 100);
	if (Status)
	{
		_I2cFailRecover();
	}
}

void WriteRegister32(uint16_t dev, uint16_t RegisterAdress, uint32_t value)
{
	uint8_t Status;
	uint8_t data_write[6];

	data_write[0] = (RegisterAdress >> 8) & 0xFF;
	data_write[1] = RegisterAdress & 0xFF;
	data_write[2] = (value >> 24) & 0xFF;
	data_write[3] = (value >> 16) & 0xFF;
	data_write[4] = (value >> 8) & 0xFF;
	data_write[5] = value & 0xFF;
	Status = HAL_I2C_Master_Transmit(&I2C_HANDLE, dev, data_write, 6, 100);
	if (Status)
	{
		_I2cFailRecover();
	}
}

void WaitMs(uint32_t TimeMs)
{
	HAL_Delay(TimeMs);
}

extern char Uart_RXBuffer[];

uint8_t _I2CBuffer[256];




VL53L1_Error VL53L1_WrByte(uint16_t Dev, uint16_t index, uint8_t data)
{
	uint8_t Status;
	uint8_t data_write[3];

	data_write[0] = (index >> 8) & 0xFF;
	data_write[1] = index & 0xFF;
	data_write[2] = data & 0xFF;
	Status = HAL_I2C_Master_Transmit(&I2C_HANDLE, Dev, data_write, 3, 100);
	if (Status)
	{
		_I2cFailRecover();
	}
	return Status;
}

VL53L1_Error VL53L1_WrWord(uint16_t Dev, uint16_t index, uint16_t data)
{
	uint8_t Status;
	uint8_t data_write[4];

	data_write[0] = (index >> 8) & 0xFF;
	data_write[1] = index & 0xFF;
	data_write[2] = (data >> 8) & 0xFF;
	data_write[3] = data & 0xFF;
	Status = HAL_I2C_Master_Transmit(&I2C_HANDLE, Dev, data_write, 4, 100);
	if (Status)
	{
		_I2cFailRecover();
	}
	return Status;
}

VL53L1_Error VL53L1_WrDWord(uint16_t Dev, uint16_t index, uint32_t data)
{
	uint8_t Status;
	uint8_t data_write[6];

	data_write[0] = (index >> 8) & 0xFF;
	data_write[1] = index & 0xFF;
	data_write[2] = (data >> 24) & 0xFF;
	data_write[3] = (data >> 16) & 0xFF;
	data_write[4] = (data >> 8) & 0xFF;
	data_write[5] = data & 0xFF;
	Status = HAL_I2C_Master_Transmit(&I2C_HANDLE, Dev, data_write, 6, 100);
	if (Status)
	{
		_I2cFailRecover();
	}
	return Status;
}

VL53L1_Error VL53L1_UpdateByte(uint16_t Dev, uint16_t index, uint8_t AndData, uint8_t OrData) {

    VL53L1_Error Status = VL53L1_ERROR_NONE;
    uint8_t data;
	//Status = VL53L1_ReadMulti(Dev, index, &data, 1);
    data = ReadRegister8(Dev, index);
    data = (data & AndData) | OrData;
    VL53L1_WrByte(Dev, index, data);
    //Status += VL53L1_WriteMulti(Dev, index, &data, 1);
    return Status;
}

VL53L1_Error VL53L1_RdByte(uint16_t Dev, uint16_t index, uint8_t *data)
{
	*data = ReadRegister8(Dev, index);
	return 0;
}

VL53L1_Error VL53L1_RdWord(uint16_t Dev, uint16_t index, uint16_t *data)
{

	*data = ReadRegister16(Dev, index);
	return 0;
}

VL53L1_Error VL53L1_RdDWord(uint16_t Dev, uint16_t index, uint32_t *data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;

    *data = ReadRegister32(Dev, index);
	//Status = VL53L1_ReadMulti(Dev, index, (uint8_t *) data, 4);
	//*data = ntohl(*data);
	return Status;
}

VL53L1_Error VL53L1_GetTickCount(uint32_t *ptick_count_ms){

    /* Returns current tick count in [ms] */

	VL53L1_Error status  = VL53L1_ERROR_NONE;

	//*ptick_count_ms = timeGetTime();
	*ptick_count_ms = 0;



	return status;
}


#define trace_print(level, ...) \
	_LOG_TRACE_PRINT(VL53L1_TRACE_MODULE_PLATFORM, \
	level, VL53L1_TRACE_FUNCTION_NONE, ##__VA_ARGS__)

#define trace_i2c(...) \
	_LOG_TRACE_PRINT(VL53L1_TRACE_MODULE_NONE, \
	VL53L1_TRACE_LEVEL_NONE, VL53L1_TRACE_FUNCTION_I2C, ##__VA_ARGS__)



VL53L1_Error VL53L1_GetTimerFrequency(int32_t *ptimer_freq_hz){

	*ptimer_freq_hz = 0;
	trace_print(VL53L1_TRACE_LEVEL_INFO, "VL53L1_GetTimerFrequency: Freq : %dHz\n", *ptimer_freq_hz);
	return VL53L1_ERROR_NONE;
}


VL53L1_Error VL53L1_WaitMs( int32_t wait_ms){

	HAL_Delay(wait_ms);
    return VL53L1_ERROR_NONE;
}

VL53L1_Error VL53L1_WaitUs( int32_t wait_us){

	HAL_Delay(wait_us/1000);
    return VL53L1_ERROR_NONE;
}


