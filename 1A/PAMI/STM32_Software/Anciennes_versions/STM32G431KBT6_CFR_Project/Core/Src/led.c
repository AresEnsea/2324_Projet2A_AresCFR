/*
 * led.c
 *
 *  Created on: May 6, 2024
 *      Author: nicolas
 */
#include "led.h"

void LED_set_value(uint8_t value){
	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, (value>>0) & 0x01);
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, (value>>1) & 0x01);
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, (value>>2) & 0x01);
}
