/*
 * ydlidar_x4.h
 *
 *  Created on: Feb 14, 2024
 *      Author: nicolas
 */

#ifndef INC_YDLIDAR_X4_H_
#define INC_YDLIDAR_X4_H_

#include "main.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>

#define CMD_PREFIX						0xA5
#define CMD_START_SCAN  				0x60
#define CMD_STOP_SCAN 	 				0x65
#define CMD_GET_DEVICE_INFO				0x90
#define CMD_GET_HEALTH_STATUS 			0x91
#define CMD_SOFT_RESTART 				0x80

#define HEADER_SIZE 					7
#define DEVICE_INFORMATION_PAYLOAD_SIZE	20
#define HEALTH_STATUS_PAYLOAD_SIZE		3
#define SCAN_CONTENT_HEADER_SIZE		10

#define LAST_DATA_BUFFER_SIZE			10

#define LIDAR_BAUDRATE 					128000

#define RX_BUFFER_SIZE					1

typedef enum {
	IDLE,
	STOP,
	START_SYNC_CONTENT_HEADER,
	START_WAIT_CONTENT,
} YDLIDAR_State;

typedef struct YDLIDAR_Scan_Response{
	uint8_t 	id_data;
	uint8_t		packet_header[2];
	uint8_t		package_type;
	uint8_t 	sample_quantity;
	uint16_t 	start_angle;
	uint16_t 	end_angle;
	uint16_t 	check_code;
	uint8_t 	buffer_data[80];
	float 		distance[360];
}YDLIDAR_Scan_Response;

typedef struct __YDLIDAR_X4_HandleTypeDef
{
	UART_HandleTypeDef *huart;
	YDLIDAR_State state;
	uint8_t model;
	uint8_t firmware_major;
	uint8_t firmware_minor;
	uint8_t hardware;
	uint8_t	serial_number[16];
	uint8_t health_status;
	uint8_t health_error_code[2];
	uint8_t rx_buffer[RX_BUFFER_SIZE];
	YDLIDAR_Scan_Response scan_response;
	uint8_t newData;
	int trame_id;
} __YDLIDAR_X4_HandleTypeDef;

typedef struct YDLIDAR_header_response{
	uint8_t		start_sign[2];
	uint32_t	content_size;
	uint8_t 	mode;
	uint8_t 	type_code;
}YDLIDAR_header_response;



extern __YDLIDAR_X4_HandleTypeDef hlidar;

HAL_StatusTypeDef YDLIDAR_X4_Send_Cmd(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle, uint8_t cmd);
HAL_StatusTypeDef YDLIDAR_X4_Init(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle, UART_HandleTypeDef *huart);
HAL_StatusTypeDef YDLIDAR_X4_Get_Device_Informations(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle);
HAL_StatusTypeDef YDLIDAR_X4_Print_Device_Informations(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle);
HAL_StatusTypeDef YDLIDAR_X4_Get_Health_Status(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle);
HAL_StatusTypeDef YDLIDAR_X4_Print_Health_Status(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle);
HAL_StatusTypeDef YDLIDAR_X4_Start_Scan(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle);
HAL_StatusTypeDef YDLIDAR_X4_Soft_Reboot(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle);
HAL_StatusTypeDef YDLIDAR_X4_Compute_Payload(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle);
HAL_StatusTypeDef YDLIDAR_X4_State_Machine(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle);

#endif /* INC_YDLIDAR_X4_H_ */
