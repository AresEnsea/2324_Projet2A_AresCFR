/*
 * encodeur.h
 *
 *  Created on: May 6, 2024
 *      Author: nicolas
 */

#ifndef INC_ENCODEUR_H_
#define INC_ENCODEUR_H_

#include "main.h"
#include "tim.h"

typedef struct __ENC_HandleTypeDef
{
	TIM_HandleTypeDef *htim;
	uint8_t it;
	uint32_t channel;
	uint32_t value;
} __ENC_HandleTypeDef;

extern __ENC_HandleTypeDef henc1;

void ENCODEUR_Init(__ENC_HandleTypeDef *henc, TIM_HandleTypeDef *htim);

#endif /* INC_ENCODEUR_H_ */
