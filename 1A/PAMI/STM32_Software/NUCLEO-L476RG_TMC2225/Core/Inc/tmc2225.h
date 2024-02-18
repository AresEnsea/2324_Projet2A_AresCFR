/*
 * tmc2225.h
 *
 *  Created on: Feb 8, 2024
 *      Author: nicolas
 */

#ifndef INC_TMC2225_H_
#define INC_TMC2225_H_

#include "main.h"
#include "tim.h"

typedef struct __TMC2225_HandleTypeDef
{
	TIM_HandleTypeDef *htim;
	uint8_t channel;
} __TMC2225_HandleTypeDef;

extern __TMC2225_HandleTypeDef TMC2225_motor_Left;
extern __TMC2225_HandleTypeDef TMC2225_motor_Right;

void TMC2225_Init(__TMC2225_HandleTypeDef *TMC2225_Handle, TIM_HandleTypeDef *htim, uint8_t channel);
void TMC2225_Start(__TMC2225_HandleTypeDef *TMC2225_Handle);

#endif /* INC_TMC2225_H_ */
