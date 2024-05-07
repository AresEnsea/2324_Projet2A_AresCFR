/*
 * SSD1306.h
 *
 *  Created on: Feb 18, 2024
 *      Author: nicolas
 */

#ifndef INC_SSD1306_H_
#define INC_SSD1306_H_

#include "main.h"
#include "usart.h"
#include "i2c.h"
#include <string.h>
#include <stdio.h>
#include "SSD1306_fonts.h"
#include "strategy.h"

#define I2C_ADDR 				0x78
#define I2C_ADDR_ALT			0x7A
#define SCREEN_HEIGHT			64
#define SCREEN_WIDTH			128
#define SSD1306_BUFFER_SIZE 	SCREEN_HEIGHT*SCREEN_WIDTH/8

#define SSD1306_COMMAND 		0x00
#define SSD1306_DATA 			0x40

#define SSD1306_CONTRAST_REG	0x81


typedef enum {
    Black = 0x00, // Black color, no pixel
    White = 0x01  // Pixel is set. Color depends on OLED
} SSD1306_COLOR;

typedef enum {
    SSD1306_OK = 0x00,
    SSD1306_ERR = 0x01  // Generic error.
} SSD1306_Error_t;


typedef struct __SCREEN_SSD1306_HandleTypeDef
{
	I2C_HandleTypeDef *hi2c;
	uint8_t i2c_addr;
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint8_t Initialized;
    uint8_t DisplayOn;
    uint8_t textBuffer[32];
    uint8_t buffer[SSD1306_BUFFER_SIZE];
} __SCREEN_SSD1306_HandleTypeDef;

extern __SCREEN_SSD1306_HandleTypeDef hscreen1;

HAL_StatusTypeDef SCREEN_SSD1306_Init(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef SCREEN_SSD1306_Send_Cmd(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, uint8_t cmd);
HAL_StatusTypeDef SCREEN_SSD1306_Send_Data(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, uint8_t* data, size_t size);
HAL_StatusTypeDef SCREEN_SSD1306_Set_Contrat(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, uint8_t value);
HAL_StatusTypeDef SCREEN_SSD1306_Fill(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, SSD1306_COLOR);
HAL_StatusTypeDef SCREEN_SSD1306_Update_Screen(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle);
HAL_StatusTypeDef SCREEN_SSD1306_Draw_Pixel(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, uint8_t x, uint8_t y, SSD1306_COLOR color);
char SCREEN_SSD1306_Write_Char(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, char ch, FontDef Font, SSD1306_COLOR color);
char SCREEN_SSD1306_Write_String(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, char* str, FontDef Font, SSD1306_COLOR color);
HAL_StatusTypeDef SCREEN_SSD1306_Dislay_On(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle);
HAL_StatusTypeDef SCREEN_SSD1306_Dislay_Off(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle);
void SCREEN_SSD1306_Fill_String(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, char* str, FontDef Font, SSD1306_COLOR color);
void SCREEN_SSD1306_Set_Position(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, uint8_t x, uint8_t y);
HAL_StatusTypeDef SCREEN_SSD1306_State_Machine(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle);
void SCREEN_SSD1306_Print_Info(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, uint32_t time_1, uint32_t time_2,	float v_battery, int idx_angle_min_distance, float min_distance, __STRATEGY_HandleTypeDef actual_strategy);

#endif /* INC_SSD1306_H_ */
