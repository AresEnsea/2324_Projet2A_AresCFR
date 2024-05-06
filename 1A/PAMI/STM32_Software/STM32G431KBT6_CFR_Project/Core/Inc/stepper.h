/*
 * stepper.h
 *
 *  Created on: May 6, 2024
 *      Author: nicolas
 */

#ifndef INC_STEPPER_H_
#define INC_STEPPER_H_

#include "main.h"
#include "tim.h"
#include "gpio.h"

typedef struct __Stepper_HandleTypeDef
{
	TIM_HandleTypeDef *htim;
	uint8_t channel;
	GPIO_TypeDef *gpioPort;
	uint16_t gpioPin;
	uint8_t invRotation;
	GPIO_PinState direction;
	int32_t speed;
} __Stepper_HandleTypeDef;

extern __Stepper_HandleTypeDef hstepperLeft;
extern __Stepper_HandleTypeDef hstepperRight;

void Stepper_Init(__Stepper_HandleTypeDef *hstepper, TIM_HandleTypeDef *htim,
		uint8_t channel, GPIO_TypeDef *gpioPort, uint16_t gpioPin, uint8_t invRotation);
void Stepper_Start(__Stepper_HandleTypeDef *hstepper);
void Stepper_Stop(__Stepper_HandleTypeDef *hstepper);
void Stepper_Set_Speed(__Stepper_HandleTypeDef *hstepper, uint32_t speed, uint8_t dir);

#endif /* INC_STEPPER_H_ */
