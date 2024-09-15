/*
 * ydlidar_x4.c
 *
 *  Created on: Feb 14, 2024
 *      Author: nicolas
 */
#include "ydlidar_x4.h"
//#define SERIAL_DEBUG
__YDLIDAR_X4_HandleTypeDef hlidar;

HAL_StatusTypeDef YDLIDAR_X4_Send_Cmd(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle, uint8_t cmd){
	uint8_t cmdBuffer[2] = {CMD_PREFIX, cmd};
	if(HAL_UART_Transmit(YDLIDAR_X4_Handle->huart, cmdBuffer, 2, 10) == HAL_OK){
		return HAL_OK;
	}
	else{
		return HAL_ERROR;
	}
}
HAL_StatusTypeDef YDLIDAR_X4_Init(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle, UART_HandleTypeDef *huart){
	YDLIDAR_X4_Handle->huart = huart;
	YDLIDAR_X4_Handle->state = IDLE;
	YDLIDAR_X4_Handle->trame_id = 0;
	YDLIDAR_X4_Handle->newData = 0;
	YDLIDAR_X4_Handle->scan_response.id_data = 0;

	YDLIDAR_X4_Send_Cmd(YDLIDAR_X4_Handle, CMD_SOFT_RESTART);
	HAL_Delay(20);

	YDLIDAR_X4_Get_Device_Informations(YDLIDAR_X4_Handle);
	YDLIDAR_X4_Print_Device_Informations(YDLIDAR_X4_Handle);

	YDLIDAR_X4_Get_Health_Status(YDLIDAR_X4_Handle);
	YDLIDAR_X4_Print_Health_Status(YDLIDAR_X4_Handle);
	HAL_Delay(200);

	HAL_GPIO_WritePin(OSC_TRIG_GPIO_Port, OSC_TRIG_Pin, RESET);
	YDLIDAR_X4_Start_Scan(YDLIDAR_X4_Handle);
	return HAL_OK;
}
HAL_StatusTypeDef YDLIDAR_X4_Get_Device_Informations(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle){
	YDLIDAR_header_response header;

	txBufferSize = snprintf((char *)uart2TxBuffer, UART_TX_BUFFER_SIZE, "Getting Device Informations...\r\n");
	//HAL_UART_Transmit(&huart2, uart2TxBuffer, txBufferSize, LAST_DATA_BUFFER_SIZE);

	YDLIDAR_X4_Send_Cmd(YDLIDAR_X4_Handle, CMD_STOP_SCAN);
	HAL_Delay(50);


	YDLIDAR_X4_Send_Cmd(YDLIDAR_X4_Handle, CMD_GET_DEVICE_INFO);

	HAL_UART_Abort(YDLIDAR_X4_Handle->huart); // Clean every old data in Rx Buffer

	if(HAL_UART_Receive(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, HEADER_SIZE+DEVICE_INFORMATION_PAYLOAD_SIZE, 5000) != HAL_OK){
		txBufferSize = snprintf((char *)uart2TxBuffer, UART_TX_BUFFER_SIZE, "Device not responding...\r\n");
		//HAL_UART_Transmit(&huart2, uart2TxBuffer, txBufferSize, 10);
		return HAL_ERROR;
	}

	// Get parameters from response
	header.start_sign[0] 	= YDLIDAR_X4_Handle->rx_buffer[0];
	header.start_sign[1] 	= YDLIDAR_X4_Handle->rx_buffer[1];
	header.content_size 	= (YDLIDAR_X4_Handle->rx_buffer[5] & 0x3F) << 24 |
			YDLIDAR_X4_Handle->rx_buffer[4] << 16 |
			YDLIDAR_X4_Handle->rx_buffer[3] << 8 |
			YDLIDAR_X4_Handle->rx_buffer[2];
	header.mode 			= YDLIDAR_X4_Handle->rx_buffer[5] >> 6;
	header.type_code 		= YDLIDAR_X4_Handle->rx_buffer[6];

	if(header.start_sign[0] = 0xA5 &&
			header.start_sign[1] == 0x5A &&
			header.content_size == 0x14 &&
			header.mode == 0x00 &&
			header.type_code == 0x04)
	{
		YDLIDAR_X4_Handle->model = YDLIDAR_X4_Handle->rx_buffer[HEADER_SIZE];
		YDLIDAR_X4_Handle->firmware_minor = YDLIDAR_X4_Handle->rx_buffer[HEADER_SIZE+1];
		YDLIDAR_X4_Handle->firmware_major = YDLIDAR_X4_Handle->rx_buffer[HEADER_SIZE+2];
		YDLIDAR_X4_Handle->hardware = YDLIDAR_X4_Handle->rx_buffer[HEADER_SIZE+3];
		for(int idx=0; idx<16; idx++){
			YDLIDAR_X4_Handle->serial_number[idx] = YDLIDAR_X4_Handle->rx_buffer[HEADER_SIZE+4+idx];
		}

	}
	else{
		txBufferSize = snprintf((char *)uart2TxBuffer, UART_TX_BUFFER_SIZE, "Wrong header response...\r\n");
		//HAL_UART_Transmit(&huart2, uart2TxBuffer, txBufferSize, 10);
		return HAL_ERROR;
	}

	txBufferSize = snprintf((char *)uart2TxBuffer, UART_TX_BUFFER_SIZE, "Getting Device Informations : Done !\r\n");
	//HAL_UART_Transmit(&huart2, uart2TxBuffer, txBufferSize, 10);

	return HAL_OK;
}
HAL_StatusTypeDef YDLIDAR_X4_Print_Device_Informations(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle){
	txBufferSize = snprintf((char *)uart2TxBuffer, UART_TX_BUFFER_SIZE,
			"**********************************\r\n"
			"*      Device Informations       *\r\n"
			"**********************************\r\n"
			"Model : 0x%02x\r\n"
			"Firmware : %u.%u\r\n"
			"Hardware : %u\r\n"
			"Serial Number : ",
			YDLIDAR_X4_Handle->model,
			(unsigned int)YDLIDAR_X4_Handle->firmware_major,
			(unsigned int)YDLIDAR_X4_Handle->firmware_minor,
			(unsigned int)YDLIDAR_X4_Handle->hardware);

	for(int idx = 0; idx<16; idx++){
		uart2TxBuffer[txBufferSize+idx] = YDLIDAR_X4_Handle->serial_number[idx] + 48;
	}
	uart2TxBuffer[txBufferSize+16]='\r';
	uart2TxBuffer[txBufferSize+17]='\n';
	txBufferSize+=18;
	HAL_UART_Transmit(&huart2, uart2TxBuffer, txBufferSize, 10);
}
HAL_StatusTypeDef YDLIDAR_X4_Get_Health_Status(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle){
	YDLIDAR_header_response header;

	txBufferSize = snprintf((char *)uart2TxBuffer, UART_TX_BUFFER_SIZE, "Getting Health Status...\r\n");
	//HAL_UART_Transmit(&huart2, uart2TxBuffer, txBufferSize, 10);

	YDLIDAR_X4_Send_Cmd(YDLIDAR_X4_Handle, CMD_STOP_SCAN);
	HAL_Delay(50);

	YDLIDAR_X4_Send_Cmd(YDLIDAR_X4_Handle, CMD_GET_HEALTH_STATUS);

	HAL_UART_Abort(YDLIDAR_X4_Handle->huart); // Clean every old data in Rx Buffer

	if(HAL_UART_Receive(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, HEADER_SIZE+HEALTH_STATUS_PAYLOAD_SIZE, 5000) != HAL_OK){
		txBufferSize = snprintf((char *)uart2TxBuffer, UART_TX_BUFFER_SIZE, "Device not responding...\r\n");
		//HAL_UART_Transmit(&huart2, uart2TxBuffer, txBufferSize, 10);
		return HAL_ERROR;
	}

	// Get parameters from response
	header.start_sign[0] 	= YDLIDAR_X4_Handle->rx_buffer[0];
	header.start_sign[1] 	= YDLIDAR_X4_Handle->rx_buffer[1];
	header.content_size 	= (YDLIDAR_X4_Handle->rx_buffer[5] & 0x3F) << 24 |
			YDLIDAR_X4_Handle->rx_buffer[4] << 16 |
			YDLIDAR_X4_Handle->rx_buffer[3] << 8 |
			YDLIDAR_X4_Handle->rx_buffer[2];
	header.mode 			= YDLIDAR_X4_Handle->rx_buffer[5] >> 6;
	header.type_code 		= YDLIDAR_X4_Handle->rx_buffer[6];

	if(header.start_sign[0] = 0xA5 &&
			header.start_sign[1] == 0x5A &&
			header.content_size == 0x03 &&
			header.mode == 0x00 &&
			header.type_code == 0x06){
		YDLIDAR_X4_Handle->health_status = YDLIDAR_X4_Handle->rx_buffer[HEADER_SIZE];
		YDLIDAR_X4_Handle->health_error_code[0] = YDLIDAR_X4_Handle->rx_buffer[HEADER_SIZE+1];
		YDLIDAR_X4_Handle->health_error_code[1] = YDLIDAR_X4_Handle->rx_buffer[HEADER_SIZE+2];

	}
	else{
		txBufferSize = snprintf((char *)uart2TxBuffer, UART_TX_BUFFER_SIZE, "Wrong header response...\r\n");
		//HAL_UART_Transmit(&huart2, uart2TxBuffer, txBufferSize, 10);
		return HAL_ERROR;
	}

	txBufferSize = snprintf((char *)uart2TxBuffer, UART_TX_BUFFER_SIZE, "Health Status : Done !\r\n");
	//HAL_UART_Transmit(&huart2, uart2TxBuffer, txBufferSize, 10);

	return HAL_OK;
}
HAL_StatusTypeDef YDLIDAR_X4_Print_Health_Status(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle){
	txBufferSize = snprintf((char *)uart2TxBuffer, UART_TX_BUFFER_SIZE,
			"**********************************\r\n"
			"*      Health Status             *\r\n"
			"**********************************\r\n"
			"Status code : 0x%02x\r\n"
			"Error code : ",
			YDLIDAR_X4_Handle->health_status);

	for(int idx = 0; idx<2; idx++){
		uart2TxBuffer[txBufferSize+idx] = YDLIDAR_X4_Handle->health_error_code[idx] + 48;
	}
	uart2TxBuffer[txBufferSize+2]='\r';
	uart2TxBuffer[txBufferSize+3]='\n';
	txBufferSize+=4;
	HAL_UART_Transmit(&huart2, uart2TxBuffer, txBufferSize, 10);
}
HAL_StatusTypeDef YDLIDAR_X4_Start_Scan(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle){
	YDLIDAR_X4_Send_Cmd(YDLIDAR_X4_Handle, CMD_START_SCAN);
	YDLIDAR_X4_Handle->state = START_SYNC_CONTENT_HEADER;
	HAL_UART_Receive_IT(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, 1);
	return HAL_OK;
}
HAL_StatusTypeDef YDLIDAR_X4_Soft_Reboot(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle){
	return YDLIDAR_X4_Send_Cmd(YDLIDAR_X4_Handle, CMD_SOFT_RESTART);
}
HAL_StatusTypeDef YDLIDAR_X4_Compute_Payload(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle){
	// 50us to compute this function approx, 4000 cyles.

	float start_angle = ((float)(YDLIDAR_X4_Handle->scan_response.start_angle >> 1))/64;
	float end_angle = ((float)(YDLIDAR_X4_Handle->scan_response.end_angle >> 1))/64;
	float diff_angle = end_angle - start_angle;
	float angle, distance;
	uint16_t distance_raw;
	if(diff_angle<0){ // Check not negative (one turn)
		diff_angle = (diff_angle+360)/(YDLIDAR_X4_Handle->scan_response.sample_quantity-1);
	}
	else{
		diff_angle /= YDLIDAR_X4_Handle->scan_response.sample_quantity;
	}

	// Compute distance
	HAL_GPIO_WritePin(DEBUG_GPIO_Port, DEBUG_Pin, SET);
	for(int idx=0; idx<YDLIDAR_X4_Handle->scan_response.sample_quantity; idx++){
		distance_raw = YDLIDAR_X4_Handle->scan_response.buffer_data[2*idx];
		distance_raw |= YDLIDAR_X4_Handle->scan_response.buffer_data[2*idx+1]<<8;
		distance = ((float)distance_raw)/4;
		angle = diff_angle*idx+start_angle;
		YDLIDAR_X4_Handle->scan_response.distance[(uint32_t)angle]=distance;
	}


	int idx_angle_min_distance = -1;
	float min_distance = 10000;
	for(int idx_angle=120; idx_angle<240; idx_angle++){
		if((10 < YDLIDAR_X4_Handle->scan_response.distance[idx_angle]) &&
				(YDLIDAR_X4_Handle->scan_response.distance[idx_angle] < min_distance)){
			idx_angle_min_distance = idx_angle;
			min_distance = YDLIDAR_X4_Handle->scan_response.distance[idx_angle];
		}
	}
	if(min_distance < 200){
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, RESET);
	}
	HAL_GPIO_WritePin(DEBUG_GPIO_Port, DEBUG_Pin, RESET);
	txBufferSize = snprintf((char *)uart2TxBuffer, UART_TX_BUFFER_SIZE, "Angle %3d , Distance : %4.3f mm\r\n", idx_angle_min_distance, min_distance);
	HAL_UART_Transmit(&huart2, uart2TxBuffer, txBufferSize, 10);



	return HAL_OK;
}

HAL_StatusTypeDef YDLIDAR_X4_State_Machine(__YDLIDAR_X4_HandleTypeDef *YDLIDAR_X4_Handle){
	switch(YDLIDAR_X4_Handle->state){
	case IDLE:
		YDLIDAR_X4_Handle->state = IDLE;
		break;
	case STOP:
		YDLIDAR_X4_Handle->state = STOP;
		/************************************************************************
		 * START_WAIT_CONTENT_HEADER											*
		 * After sync, get header of content part								*
		 * PH 	2 bytes		packet header										*
		 * CT 	1 byte 		packet type (bit(0)=point cloud data packet			*
		 * LSN  1 byte		Sample quantity in hald-word, 1 point = uint16_t	*
		 * FSA 	2 bytes		Start angle											*
		 * LSA  2 bytes		End angle											*
		 ************************************************************************/
	case START_SYNC_CONTENT_HEADER:
		switch(YDLIDAR_X4_Handle->scan_response.id_data){
		case 0 :
			if(YDLIDAR_X4_Handle->rx_buffer[0] == 0xAA){
				YDLIDAR_X4_Handle->scan_response.id_data = 1;
				YDLIDAR_X4_Handle->scan_response.packet_header[0] = YDLIDAR_X4_Handle->rx_buffer[0];
				HAL_GPIO_WritePin(OSC_TRIG_GPIO_Port, OSC_TRIG_Pin, RESET);
				HAL_UART_Receive_IT(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, 1);
			}
			else{
				YDLIDAR_X4_Handle->scan_response.id_data = 0;
				HAL_GPIO_WritePin(OSC_TRIG_GPIO_Port, OSC_TRIG_Pin, RESET);
				HAL_UART_Receive_IT(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, 1);
			}
			break;
		case 1 :
			if(YDLIDAR_X4_Handle->rx_buffer[0] == 0x55){
				YDLIDAR_X4_Handle->scan_response.id_data = 2;
				YDLIDAR_X4_Handle->scan_response.packet_header[1] = YDLIDAR_X4_Handle->rx_buffer[0];
				HAL_UART_Receive_IT(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, 1);
			}
			else{
				YDLIDAR_X4_Handle->scan_response.id_data = 0;
				HAL_GPIO_WritePin(OSC_TRIG_GPIO_Port, OSC_TRIG_Pin, RESET);
				HAL_UART_Receive_IT(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, 1);
			}
			break;
		case 2 :
			if(YDLIDAR_X4_Handle->rx_buffer[0] == 0x00){
				HAL_GPIO_WritePin(OSC_TRIG_GPIO_Port, OSC_TRIG_Pin, SET);
				YDLIDAR_X4_Handle->scan_response.id_data = 3;
				YDLIDAR_X4_Handle->scan_response.package_type = YDLIDAR_X4_Handle->rx_buffer[0];
				HAL_UART_Receive_IT(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, 1);
			}
			else{
				YDLIDAR_X4_Handle->scan_response.id_data = 0;
				HAL_GPIO_WritePin(OSC_TRIG_GPIO_Port, OSC_TRIG_Pin, RESET);
				HAL_UART_Receive_IT(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, 1);
			}
			break;
		case 3 :
			if(YDLIDAR_X4_Handle->scan_response.id_data == 3){
				YDLIDAR_X4_Handle->scan_response.id_data = 4;
				YDLIDAR_X4_Handle->scan_response.sample_quantity = YDLIDAR_X4_Handle->rx_buffer[0];
				HAL_UART_Receive_IT(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, 1);
			}
			break;
		case 4 :
			YDLIDAR_X4_Handle->scan_response.id_data = 5;
			YDLIDAR_X4_Handle->scan_response.start_angle = YDLIDAR_X4_Handle->rx_buffer[0];
			HAL_UART_Receive_IT(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, 1);
			break;

		case 5 :
			YDLIDAR_X4_Handle->scan_response.id_data = 6;
			YDLIDAR_X4_Handle->scan_response.start_angle |= YDLIDAR_X4_Handle->rx_buffer[0]<<8;
			HAL_UART_Receive_IT(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, 1);
			break;

		case 6 :
			YDLIDAR_X4_Handle->scan_response.id_data = 7;
			YDLIDAR_X4_Handle->scan_response.end_angle = YDLIDAR_X4_Handle->rx_buffer[0];
			HAL_UART_Receive_IT(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, 1);
			break;

		case 7 :
			YDLIDAR_X4_Handle->scan_response.id_data = 8;
			YDLIDAR_X4_Handle->scan_response.end_angle |= YDLIDAR_X4_Handle->rx_buffer[0]<<8;
			HAL_UART_Receive_IT(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, 1);
			break;

		case 8 :
			YDLIDAR_X4_Handle->scan_response.id_data = 9;
			YDLIDAR_X4_Handle->scan_response.check_code = YDLIDAR_X4_Handle->rx_buffer[0];
			HAL_UART_Receive_IT(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, 1);
			break;

		case 9 :
			YDLIDAR_X4_Handle->scan_response.id_data = 0;
			YDLIDAR_X4_Handle->scan_response.check_code |= YDLIDAR_X4_Handle->rx_buffer[0]<<8;
			YDLIDAR_X4_Handle->state = START_WAIT_CONTENT;
			HAL_UART_Receive_IT(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->scan_response.buffer_data, YDLIDAR_X4_Handle->scan_response.sample_quantity*2);
			break;

		default :
			YDLIDAR_X4_Handle->scan_response.id_data = 0;
			HAL_GPIO_WritePin(OSC_TRIG_GPIO_Port, OSC_TRIG_Pin, RESET);
			HAL_UART_Receive_IT(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, 1);
			break;
		}

		break;

		case START_WAIT_CONTENT:
			YDLIDAR_X4_Handle->state=START_SYNC_CONTENT_HEADER;
			YDLIDAR_X4_Handle->trame_id++;
			YDLIDAR_X4_Handle->newData = 1;
			HAL_UART_Receive_IT(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, 1);
			break;

		default:
			YDLIDAR_X4_Handle->state = START_SYNC_CONTENT_HEADER;
			HAL_UART_Receive_IT(YDLIDAR_X4_Handle->huart, YDLIDAR_X4_Handle->rx_buffer, 1);
	}

	return HAL_OK;
}
