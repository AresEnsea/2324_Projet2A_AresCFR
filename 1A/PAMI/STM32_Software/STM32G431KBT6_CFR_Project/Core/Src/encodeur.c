/*
 * encodeur.c
 *
 *  Created on: May 6, 2024
 *      Author: nicolas
 */

#include "encodeur.h"

__ENC_HandleTypeDef henc1;

void ENCODEUR_Init(__ENC_HandleTypeDef *henc, TIM_HandleTypeDef *htim){
	henc->htim = htim;
	henc->channel = TIM_CHANNEL_ALL;
	HAL_TIM_Encoder_Start(htim, henc->channel);
}

uint32_t ENCODEUR_Get_Value(__ENC_HandleTypeDef *henc){
	henc->value = __HAL_TIM_GET_COUNTER(henc->htim);
	return henc->value;
}
