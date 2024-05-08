/*
 * SSD1306.c
 *
 *  Created on: Feb 18, 2024
 *      Author: nicolas
 *      Inspired by : https://github.com/afiskon/stm32-ssd1306/
 */

#include "SSD1306.h"

__SCREEN_SSD1306_HandleTypeDef hscreen1;

HAL_StatusTypeDef SCREEN_SSD1306_Init(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, I2C_HandleTypeDef *hi2c){
	SCREEN_SSD1306_Handle->hi2c = hi2c;
	SCREEN_SSD1306_Handle->i2c_addr = I2C_ADDR;

//	if(HAL_OK == HAL_I2C_IsDeviceReady(SCREEN_SSD1306_Handle->hi2c, SCREEN_SSD1306_Handle->i2c_addr, 3, 100)){
//		tx_Buffer_Size = snprintf((char *)uart2_Tx_Buffer, UART_TX_BUFFER_SIZE, "Screen connected\r\n");
//		HAL_UART_Transmit(&huart2, uart2_Tx_Buffer, tx_Buffer_Size, 10);
//	}
//	else{
//		tx_Buffer_Size = snprintf((char *)uart2_Tx_Buffer, UART_TX_BUFFER_SIZE, "Screen not connected\r\n");
//		HAL_UART_Transmit(&huart2, uart2_Tx_Buffer, tx_Buffer_Size, 10);
//	}

    // Init OLED
	SCREEN_SSD1306_Dislay_Off(SCREEN_SSD1306_Handle); //display off
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0x20); //Set Memory Addressing Mode
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0x00); // 00b,Horizontal Addressing Mode; 01b,Vertical Addressing Mode; // 10b,Page Addressing Mode (RESET); 11b,Invalid
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0xB0); //Set Page Start Address for Page Addressing Mode,0-7
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0xC8); //Set COM Output Scan Direction
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0x00); //---set low column address
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0x10); //---set high column address
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0x40); //--set start line address - CHECK
    SCREEN_SSD1306_Set_Contrat(SCREEN_SSD1306_Handle, 0xFF);
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0xA1); //--set segment re-map 0 to 127 - CHECK
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0xA8); //--set multiplex ratio(1 to 64) - CHECK
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0x3F); //
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0xD3); //-set display offset - CHECK
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0x00); //-not offset
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0xD5); //--set display clock divide ratio/oscillator frequency
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0xF0); //--set divide ratio
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0xD9); //--set pre-charge period
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0x22); //
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0xDA); //--set com pins hardware configuration - CHECK
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0x12);
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0xDB); //--set vcomh
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0x20); //0x20,0.77xVcc
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0x8D); //--set DC-DC enable
    SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0x14); //
    SCREEN_SSD1306_Dislay_On(SCREEN_SSD1306_Handle); //--turn on SSD1306 panel
    SCREEN_SSD1306_Fill(SCREEN_SSD1306_Handle, Black);
    SCREEN_SSD1306_Update_Screen(SCREEN_SSD1306_Handle);

//    SSD1306.CurrentX = 0;
//    SSD1306.CurrentY = 0;
//    SSD1306.Initialized = 1;

	return HAL_OK;
}

HAL_StatusTypeDef SCREEN_SSD1306_Send_Cmd(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, uint8_t cmd){
	uint8_t cmdBuffer[2] = {SSD1306_COMMAND, cmd};
	if(HAL_I2C_Master_Transmit(SCREEN_SSD1306_Handle->hi2c, SCREEN_SSD1306_Handle->i2c_addr, cmdBuffer, 2, 100) == HAL_OK){
		return HAL_OK;
	}
	else{
		return HAL_ERROR;
	}
}

HAL_StatusTypeDef SCREEN_SSD1306_Send_Data(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, uint8_t* data, size_t size){
	//if(HAL_I2C_Mem_Write(SCREEN_SSD1306_Handle->hi2c, SCREEN_SSD1306_Handle->i2c_addr, SSD1306_DATA, 1, data, size, 100)){
	HAL_I2C_Mem_Write(SCREEN_SSD1306_Handle->hi2c, SCREEN_SSD1306_Handle->i2c_addr, SSD1306_DATA, 1, data, size, 100);
	//HAL_I2C_Mem_Write_DMA(SCREEN_SSD1306_Handle->hi2c, SCREEN_SSD1306_Handle->i2c_addr, SSD1306_DATA, 1, data, size);
//	if(HAL_I2C_Mem_Write_DMA(SCREEN_SSD1306_Handle->hi2c, SCREEN_SSD1306_Handle->i2c_addr, SSD1306_DATA, 1, data, size)){
//		return HAL_OK;
//	}
//	else{
//		return HAL_ERROR;
//	}

//	HAL_I2C_Mem_Write_DMA(SCREEN_SSD1306_Handle->hi2c, SCREEN_SSD1306_Handle->i2c_addr, SSD1306_DATA, 1, data, size);
}

HAL_StatusTypeDef SCREEN_SSD1306_Dislay_On(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle){
	return SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0xAF);
}

HAL_StatusTypeDef SCREEN_SSD1306_Dislay_Off(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle){
	return SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0xAE);
}

HAL_StatusTypeDef SCREEN_SSD1306_Set_Contrat(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, uint8_t value){
	SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, SSD1306_CONTRAST_REG);
	SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, value);
}



HAL_StatusTypeDef SCREEN_SSD1306_Fill(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, SSD1306_COLOR color){
    memset(SCREEN_SSD1306_Handle->buffer, (color == Black) ? 0x00 : 0xFF, SSD1306_BUFFER_SIZE);
    return HAL_OK;
}

HAL_StatusTypeDef SCREEN_SSD1306_Update_Screen(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle){
	SCREEN_SSD1306_Send_Cmd(SCREEN_SSD1306_Handle, 0xB0);
	return SCREEN_SSD1306_Send_Data(SCREEN_SSD1306_Handle, SCREEN_SSD1306_Handle->buffer, SSD1306_BUFFER_SIZE);
}

HAL_StatusTypeDef SCREEN_SSD1306_Draw_Pixel(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, uint8_t x, uint8_t y, SSD1306_COLOR color) {
    if(x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT) {
        return HAL_ERROR;
    }

    // Draw in the right color
    if(color == White) {
    	SCREEN_SSD1306_Handle->buffer[x + (y / 8) * SCREEN_WIDTH] |= 1 << (y % 8);
    } else {
    	SCREEN_SSD1306_Handle->buffer[x + (y / 8) * SCREEN_WIDTH] &= ~(1 << (y % 8));
    }
}

char SCREEN_SSD1306_Write_Char(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, char ch, FontDef Font, SSD1306_COLOR color) {
    uint32_t i, b, j;

    // Check if character is valid
    if (ch < 32 || ch > 126)
        return 0;

    // Check remaining space on current line
    if (SCREEN_WIDTH < (SCREEN_SSD1306_Handle->CurrentX + Font.FontWidth) ||
    		SCREEN_HEIGHT < (SCREEN_SSD1306_Handle->CurrentY + Font.FontHeight))
    {
        // Not enough space on current line
        return 0;
    }

    // Use the font to write
    for(i = 0; i < Font.FontHeight; i++) {
        b = Font.data[(ch - 32) * Font.FontHeight + i];
        for(j = 0; j < Font.FontWidth; j++) {
            if((b << j) & 0x8000)  {
            	SCREEN_SSD1306_Draw_Pixel(SCREEN_SSD1306_Handle, SCREEN_SSD1306_Handle->CurrentX + j, SCREEN_SSD1306_Handle->CurrentY + i, (SSD1306_COLOR) color);
            } else {
            	SCREEN_SSD1306_Draw_Pixel(SCREEN_SSD1306_Handle, SCREEN_SSD1306_Handle->CurrentX + j, SCREEN_SSD1306_Handle->CurrentY + i, (SSD1306_COLOR)!color);
            }
        }
    }

    // The current space is now taken
    SCREEN_SSD1306_Handle->CurrentX += Font.FontWidth;

    // Return written char for validation
    return ch;
}


char SCREEN_SSD1306_Write_String(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, char* str, FontDef Font, SSD1306_COLOR color) {
    while (*str) {
        if (SCREEN_SSD1306_Write_Char(SCREEN_SSD1306_Handle, *str, Font, color) != *str) {
            // Char could not be written
            return *str;
        }
        str++;
    }

    // Everything ok
    return *str;
}

void SCREEN_SSD1306_Fill_String(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, char* str, FontDef Font, SSD1306_COLOR color) {
	SCREEN_SSD1306_Fill(&hscreen1, Black);
	SCREEN_SSD1306_Set_Position(&hscreen1, 0, 0);
	SCREEN_SSD1306_Write_String(&hscreen1, str, Font, color);
	SCREEN_SSD1306_Update_Screen(&hscreen1);
}

void SCREEN_SSD1306_Set_Position(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle, uint8_t x, uint8_t y){
	SCREEN_SSD1306_Handle->CurrentX = x;
	SCREEN_SSD1306_Handle->CurrentY = y;
}


HAL_StatusTypeDef SCREEN_SSD1306_State_Machine(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle){

	return HAL_OK;
}

void SCREEN_SSD1306_Print_Info(__SCREEN_SSD1306_HandleTypeDef *SCREEN_SSD1306_Handle,
		uint32_t time_1, uint32_t time_2, float v_battery,
		int idx_angle_min_distance, float min_distance,
		__STRATEGY_HandleTypeDef actual_strategy){
	SCREEN_SSD1306_Fill(SCREEN_SSD1306_Handle, Black);

	// Line 1
	snprintf(SCREEN_SSD1306_Handle->textBuffer, 19, "%3d.%d %3d.%d  %1.2fV ", time_1/10, time_1%10, time_2/10, time_2%10, v_battery);
	SCREEN_SSD1306_Set_Position(SCREEN_SSD1306_Handle, 0, 0);
	SCREEN_SSD1306_Write_String(SCREEN_SSD1306_Handle, SCREEN_SSD1306_Handle->textBuffer, Font_7x10, White);

	// Line 2
	snprintf(SCREEN_SSD1306_Handle->textBuffer, 19, "%3d deg : %3.1f mm", idx_angle_min_distance-180, min_distance);
	SCREEN_SSD1306_Set_Position(SCREEN_SSD1306_Handle, 0, 12);
	SCREEN_SSD1306_Write_String(SCREEN_SSD1306_Handle, SCREEN_SSD1306_Handle->textBuffer, Font_7x10, White);

	// Line 3
//	snprintf(SCREEN_SSD1306_Handle->textBuffer, 19, "Speed {%3d,%3d}", actual_strategy.action[actual_strategy.action_id].speed_Motor_Left, actual_strategy.action[actual_strategy.action_id].speed_Motor_Right);
//	SCREEN_SSD1306_Set_Position(SCREEN_SSD1306_Handle, 0, 24);
//	SCREEN_SSD1306_Write_String(SCREEN_SSD1306_Handle, SCREEN_SSD1306_Handle->textBuffer, Font_7x10, White);

	// Line 4
	snprintf(SCREEN_SSD1306_Handle->textBuffer, 12, "S %s | A %2d", actual_strategy.name, actual_strategy.action_id);
	SCREEN_SSD1306_Set_Position(SCREEN_SSD1306_Handle, 0, 36);
	SCREEN_SSD1306_Write_String(SCREEN_SSD1306_Handle, SCREEN_SSD1306_Handle->textBuffer, Font_11x18, White);

	SCREEN_SSD1306_Update_Screen(SCREEN_SSD1306_Handle);


}



