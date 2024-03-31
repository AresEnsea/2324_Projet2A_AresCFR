/*
 * tmc2225.c
 *
 *  Created on: Feb 8, 2024
 *      Author: nicolas
 */
#include "tmc2225.h"

__TMC2225_HandleTypeDef TMC2225_motor_Left;
__TMC2225_HandleTypeDef TMC2225_motor_Right;

TIM_HandleTypeDef *htim;
uint8_t channel;

void TMC2225_Init(__TMC2225_HandleTypeDef *TMC2225_Handle, TIM_HandleTypeDef *htim, uint8_t channel){
	TMC2225_Handle->htim = htim;
	TMC2225_Handle->channel = channel;
}


void TMC2225_Start(__TMC2225_HandleTypeDef *TMC2225_Handle){
	HAL_TIM_PWM_Start(TMC2225_Handle->htim, TMC2225_Handle->channel);
}
