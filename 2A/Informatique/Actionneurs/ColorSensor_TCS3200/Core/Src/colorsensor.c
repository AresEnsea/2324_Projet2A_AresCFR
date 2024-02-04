/**
  ******************************************************************************
  * @file           : colorsensor.c
  * @brief          : Functions for the color sensor TCS3200
  * @author         : Ousmane THIONGANE
  ******************************************************************************
  */

#include "colorsensor.h"

extern TIM_HandleTypeDef htim2;

#define NUM_MEASUREMENTS 100

//Allows turning on or off the lighting LEDs
void ledToggle(int state){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, state);
}

//Frequency dividers mode to control output frequency power
void frequencyScaling(int mode) {
    switch (mode) {
        case 0: //Power down
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
            break;

        case 1: //2% Power
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
            break;

        case 2: //20% Power
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
            break;

        case 3: //100% Power
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
            break;

        default:
            break;
    }
}

//FIlter color selection
void photodiodeType(int color) {
    switch (color) {
        case 0: //Clear (no filter)
        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
            break;

        case 1: //Red filter
        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
            break;

        case 2: //Green filter
        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
            break;

        case 3: //Blue filter
        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
            break;

        default:
            break;
    }
}

//Reading the duration of a rising edge
//Increasing the variable NUM_MEASUREMENTS allows averaging over multiple rising edges
int readColorValue(void) {
    uint32_t totalCounter = 0;

    for (int i = 0; i < NUM_MEASUREMENTS; ++i) {
        __HAL_TIM_SET_COUNTER(&htim2, 0);

        while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_RESET){}
        HAL_TIM_Base_Start(&htim2);
        while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_SET){}
        HAL_TIM_Base_Stop(&htim2);

        totalCounter += __HAL_TIM_GET_COUNTER(&htim2);
    }

    int averageCounter = totalCounter / NUM_MEASUREMENTS;

    return averageCounter;
}

