/*
 * button.c
 *
 *  Created on: May 6, 2024
 *      Author: nicolas
 */
#include "button.h"

__Buttons_HandleTypeDef buttons;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	BTN_Pushed(GPIO_Pin);
}

void BTN_Pushed(uint16_t GPIO_Pin){
	buttons.pushed = 1;
	if(GPIO_Pin == ENC_BTN_Pin) buttons.button = BTN_ENC;
	if(GPIO_Pin == USR_BTN_0_Pin) buttons.button = BTN_0;
	if(GPIO_Pin == USR_BTN_1_Pin) buttons.button = BTN_1;
	if(GPIO_Pin == USR_BTN_2_Pin) buttons.button = BTN_2;
}

