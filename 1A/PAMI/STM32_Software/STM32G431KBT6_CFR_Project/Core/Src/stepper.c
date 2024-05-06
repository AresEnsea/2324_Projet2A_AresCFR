/*
 * stepper.c
 *
 *  Created on: May 6, 2024
 *      Author: nicolas
 */

#include "stepper.h"
#include "tim.h"
__Stepper_HandleTypeDef hstepperLeft;
__Stepper_HandleTypeDef hstepperRight;

void Stepper_Init(__Stepper_HandleTypeDef *hstepper, TIM_HandleTypeDef *htim,
		uint8_t channel, GPIO_TypeDef *gpioPort, uint16_t gpioPin, uint8_t invRotation){
	hstepper->htim = htim;
	hstepper->channel = channel;
	hstepper->gpioPort = gpioPort;
	hstepper->gpioPin = gpioPin;
	hstepper->invRotation = invRotation;
}

void Stepper_Start(__Stepper_HandleTypeDef *hstepper){
	HAL_TIM_PWM_Start(hstepper->htim, hstepper->channel);
}

void Stepper_Stop(__Stepper_HandleTypeDef *hstepper){
	HAL_TIM_PWM_Stop(hstepper->htim, hstepper->channel);
}

void Stepper_Set_Speed(__Stepper_HandleTypeDef *hstepper, uint32_t speed, uint8_t dir){
	hstepper->speed = speed;
	hstepper->direction = dir;
	__HAL_TIM_SET_PRESCALER(hstepper->htim, 170/hstepper->speed);

	HAL_GPIO_WritePin(hstepper->gpioPort, hstepper->gpioPin,
			(hstepper->invRotation == 0) ? hstepper->direction : (1 - hstepper->direction));
}


