/*
 * button.c
 *
 *  Created on: May 6, 2024
 *      Author: nicolas
 */
#include "button.h"

__Buttons_HandleTypeDef button;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	BTN_Pushed(GPIO_Pin);
}

void BTN_Pushed(uint16_t GPIO_Pin){
	button.pushed = 1;
	if(GPIO_Pin == ENC_BTN_Pin) button.name = BTN_ENC;
	if(GPIO_Pin == USR_BTN_0_Pin) button.name = BTN_0;
	if(GPIO_Pin == USR_BTN_1_Pin) button.name = BTN_1;
	if(GPIO_Pin == USR_BTN_2_Pin) button.name = BTN_2;
}

