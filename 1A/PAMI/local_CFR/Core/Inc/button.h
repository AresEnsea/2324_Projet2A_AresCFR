/*
 * button.h
 *
 *  Created on: May 6, 2024
 *      Author: nicolas
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

typedef enum {
    NO_BTN = 0x00,
	BTN_ENC = 0x01,
    BTN_0 = 0x02,
    BTN_1 = 0x03,
    BTN_2 = 0x04,
	START = 0x05
} BTN_Enum;

typedef struct __Buttons_HandleTypeDef
{
	uint8_t pushed;
	uint8_t	name;
} __Buttons_HandleTypeDef;

extern __Buttons_HandleTypeDef button;

//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void BTN_Pushed(uint16_t GPIO_Pin);

#endif /* INC_BUTTON_H_ */
