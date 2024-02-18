#include <XL320.h>

void XL320_Init(XL320* xl320, UART_HandleTypeDef* uart, uint8_t ID, uint8_t BR) {
    xl320->UART = uart;
    xl320->ID = ID;
    xl320->BaudRate = BR;
}

void XL320_ReProg(XL320* xl320, uint8_t ID, uint8_t BR) {
    // Configuration de l'ID du module
    XL320_sendTram1Byte(xl320, XL320_REG_ID, ID);

    // Réception de la réponse du module
    HAL_HalfDuplex_EnableReceiver(xl320->UART);
    uint8_t data[SIZE_PING + 1];
    if (HAL_UART_Receive(xl320->UART, data, SIZE_PING + 1, 500) == HAL_TIMEOUT) {
        data[4] = 128;
    }
    HAL_HalfDuplex_EnableTransmitter(xl320->UART);

    // Vérification que le module a bien enregistré la donnée
    if (data[5] == 0) {
        xl320->ID = ID;
    }

    // Configuration du baudrate du module
    XL320_sendTram1Byte(xl320, XL320_REG_BaudRate, BR);

    // Envoi de la requête d'écriture
    HAL_HalfDuplex_EnableReceiver(xl320->UART);
    if (HAL_UART_Receive(xl320->UART, data, SIZE_PING, 500) == HAL_TIMEOUT) {
        data[4] = 128;
    }
    HAL_HalfDuplex_EnableTransmitter(xl320->UART);

    if (data[5] == 0) {
        xl320->BaudRate = BR;
    }
}


void XL320_setAngleRange(XL320* xl320, float min, float max){
	uint16_t dataMin = min/STEP_ANGLE;
	uint16_t dataMax = max/STEP_ANGLE;
	XL320_sendTram2Byte(xl320, XL320_REG_CWAngleLimit, dataMin);
	XL320_sendTram2Byte(xl320, XL320_REG_CCWAngleLimit, dataMax);

}


void XL320_setControlMode(XL320* xl320, uint8_t mode){
	XL320_sendTram2Byte(xl320, XL320_REG_ControlMode, mode);

}

void XL320_setMaxTemperature(XL320* xl320, uint8_t temperature){
	XL320_sendTram1Byte(xl320, XL320_REG_Temperature, temperature);

}

void XL320_setVoltageRange(XL320* xl320, uint8_t minVoltage, uint8_t maxVoltage){
	minVoltage*=10;
	maxVoltage*=10;
	XL320_sendTram1Byte(xl320, XL320_REG_MinVoltage ,minVoltage);
	XL320_sendTram1Byte(xl320, XL320_REG_MaxVoltage ,maxVoltage);
}

void XL320_setMaxTorque(XL320* xl320, float maxTorque){
	uint16_t data = (uint16_t)maxTorque/TORQUE_PERCENT;
	XL320_sendTram1Byte(xl320, XL320_REG_MaxTorque, data);
}

void XL320_EnableTorque(XL320* xl320, uint8_t state){
	XL320_sendTram1Byte(xl320, XL320_REG_TorqueEnable, state);

}

uint16_t XL320_getModelNumber(XL320* xl320){
	return XL320_readTram2Byte(xl320, XL320_REG_ModelNumber);
}


uint8_t XL320_getFirmwareVersion(XL320* xl320){
	return XL320_readTram1Byte(xl320, XL320_REG_FirmwareVersion);
}

uint16_t XL320_getPosition(XL320* xl320){
	return XL320_readTram2Byte(xl320, XL320_REG_PresentPosition);
}

void XL320_EnableLED(XL320* xl320, uint8_t state){
	XL320_sendTram1Byte(xl320, XL320_REG_LED_Enable, state);
}


void XL320_setPosition(XL320* xl320, float angle){
	uint16_t data = (uint16_t)angle/STEP_ANGLE;
	XL320_sendTram2Byte(xl320, XL320_REG_GoalPosition, data);
}


void XL320_setMovingSpeed(XL320* xl320, float rpm){
	uint16_t data = (uint16_t)rpm/STEP_SPEED;
	XL320_sendTram2Byte(xl320, XL320_REG_MovingSpeed, data);
}





void XL320_sendData(XL320* xl320, uint8_t size, uint8_t instruction, uint8_t numParameters, ...){

	/*******************************************
	 * Création d'une liste qui contient 	   *
	 * tous les paramètres après numParameters *
	 ******************************************/

	va_list ap;
	va_start(ap,numParameters);

	/**************************
	 * Création de la requête *
	 **************************/
	uint8_t data[size];
	data[0] = 0xFF;
	data[1] = 0xFF;
	data[2] = 0xFD;
	data[3] = 0x00;
	data[4] = xl320->ID;
	data[5] = numParameters+3;
	data[6] = 0x00;
	data[7] = instruction;


	/************************************
	 * nous implémentons les paramètres *
	 * (registre, paramètres, ...)	    *
	 ************************************/
	for(uint8_t i = 0; i < numParameters;i++){
		data[8+i] = (uint8_t)va_arg(ap,int);
	}

	uint16_t crc = update_crc(0, data+2, numParameters+3);
	data[size-1] = (crc >> 8) & 0xFF;
	data[size-2] = crc & 0xFF;



	/****************************
	 * nous détruisons la liste *
	 ****************************/
	va_end(ap);

	/************************
	 * envoi de la requête *
	 ************************/
	HAL_UART_Transmit(xl320->UART, data, sizeof(data), 500);
}

unsigned short update_crc(unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size)
{
    unsigned short i, j;
    unsigned short crc_table[256] = {
        0x0000, 0x8005, 0x800F, 0x000A, 0x801B, 0x001E, 0x0014, 0x8011,
        0x8033, 0x0036, 0x003C, 0x8039, 0x0028, 0x802D, 0x8027, 0x0022,
        0x8063, 0x0066, 0x006C, 0x8069, 0x0078, 0x807D, 0x8077, 0x0072,
        0x0050, 0x8055, 0x805F, 0x005A, 0x804B, 0x004E, 0x0044, 0x8041,
        0x80C3, 0x00C6, 0x00CC, 0x80C9, 0x00D8, 0x80DD, 0x80D7, 0x00D2,
        0x00F0, 0x80F5, 0x80FF, 0x00FA, 0x80EB, 0x00EE, 0x00E4, 0x80E1,
        0x00A0, 0x80A5, 0x80AF, 0x00AA, 0x80BB, 0x00BE, 0x00B4, 0x80B1,
        0x8093, 0x0096, 0x009C, 0x8099, 0x0088, 0x808D, 0x8087, 0x0082,
        0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D, 0x8197, 0x0192,
        0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE, 0x01A4, 0x81A1,
        0x01E0, 0x81E5, 0x81EF, 0x01EA, 0x81FB, 0x01FE, 0x01F4, 0x81F1,
        0x81D3, 0x01D6, 0x01DC, 0x81D9, 0x01C8, 0x81CD, 0x81C7, 0x01C2,
        0x0140, 0x8145, 0x814F, 0x014A, 0x815B, 0x015E, 0x0154, 0x8151,
        0x8173, 0x0176, 0x017C, 0x8179, 0x0168, 0x816D, 0x8167, 0x0162,
        0x8123, 0x0126, 0x012C, 0x8129, 0x0138, 0x813D, 0x8137, 0x0132,
        0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E, 0x0104, 0x8101,
        0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D, 0x8317, 0x0312,
        0x0330, 0x8335, 0x833F, 0x033A, 0x832B, 0x032E, 0x0324, 0x8321,
        0x0360, 0x8365, 0x836F, 0x036A, 0x837B, 0x037E, 0x0374, 0x8371,
        0x8353, 0x0356, 0x035C, 0x8359, 0x0348, 0x834D, 0x8347, 0x0342,
        0x03C0, 0x83C5, 0x83CF, 0x03CA, 0x83DB, 0x03DE, 0x03D4, 0x83D1,
        0x83F3, 0x03F6, 0x03FC, 0x83F9, 0x03E8, 0x83ED, 0x83E7, 0x03E2,
        0x83A3, 0x03A6, 0x03AC, 0x83A9, 0x03B8, 0x83BD, 0x83B7, 0x03B2,
        0x0390, 0x8395, 0x839F, 0x039A, 0x838B, 0x038E, 0x0384, 0x8381,
        0x0280, 0x8285, 0x828F, 0x028A, 0x829B, 0x029E, 0x0294, 0x8291,
        0x82B3, 0x02B6, 0x02BC, 0x82B9, 0x02A8, 0x82AD, 0x82A7, 0x02A2,
        0x82E3, 0x02E6, 0x02EC, 0x82E9, 0x02F8, 0x82FD, 0x82F7, 0x02F2,
        0x02D0, 0x82D5, 0x82DF, 0x02DA, 0x82CB, 0x02CE, 0x02C4, 0x82C1,
        0x8243, 0x0246, 0x024C, 0x8249, 0x0258, 0x825D, 0x8257, 0x0252,
        0x0270, 0x8275, 0x827F, 0x027A, 0x826B, 0x026E, 0x0264, 0x8261,
        0x0220, 0x8225, 0x822F, 0x022A, 0x823B, 0x023E, 0x0234, 0x8231,
        0x8213, 0x0216, 0x021C, 0x8219, 0x0208, 0x820D, 0x8207, 0x0202
    };

    for(j = 0; j < data_blk_size; j++)
    {
        i = ((unsigned short)(crc_accum >> 8) ^ data_blk_ptr[j]) & 0xFF;
        crc_accum = (crc_accum << 8) ^ crc_table[i];
    }

    return crc_accum;
}


void update_crc2(unsigned char *data_blk_ptr, unsigned short data_blk_size)
{
    unsigned short i, j, crc_accum = 0;
    unsigned short crc_table[256] = {
        0x0000, 0x8005, 0x800F, 0x000A, 0x801B, 0x001E, 0x0014, 0x8011,
        0x8033, 0x0036, 0x003C, 0x8039, 0x0028, 0x802D, 0x8027, 0x0022,
        0x8063, 0x0066, 0x006C, 0x8069, 0x0078, 0x807D, 0x8077, 0x0072,
        0x0050, 0x8055, 0x805F, 0x005A, 0x804B, 0x004E, 0x0044, 0x8041,
        0x80C3, 0x00C6, 0x00CC, 0x80C9, 0x00D8, 0x80DD, 0x80D7, 0x00D2,
        0x00F0, 0x80F5, 0x80FF, 0x00FA, 0x80EB, 0x00EE, 0x00E4, 0x80E1,
        0x00A0, 0x80A5, 0x80AF, 0x00AA, 0x80BB, 0x00BE, 0x00B4, 0x80B1,
        0x8093, 0x0096, 0x009C, 0x8099, 0x0088, 0x808D, 0x8087, 0x0082,
        0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D, 0x8197, 0x0192,
        0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE, 0x01A4, 0x81A1,
        0x01E0, 0x81E5, 0x81EF, 0x01EA, 0x81FB, 0x01FE, 0x01F4, 0x81F1,
        0x81D3, 0x01D6, 0x01DC, 0x81D9, 0x01C8, 0x81CD, 0x81C7, 0x01C2,
        0x0140, 0x8145, 0x814F, 0x014A, 0x815B, 0x015E, 0x0154, 0x8151,
        0x8173, 0x0176, 0x017C, 0x8179, 0x0168, 0x816D, 0x8167, 0x0162,
        0x8123, 0x0126, 0x012C, 0x8129, 0x0138, 0x813D, 0x8137, 0x0132,
        0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E, 0x0104, 0x8101,
        0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D, 0x8317, 0x0312,
        0x0330, 0x8335, 0x833F, 0x033A, 0x832B, 0x032E, 0x0324, 0x8321,
        0x0360, 0x8365, 0x836F, 0x036A, 0x837B, 0x037E, 0x0374, 0x8371,
        0x8353, 0x0356, 0x035C, 0x8359, 0x0348, 0x834D, 0x8347, 0x0342,
        0x03C0, 0x83C5, 0x83CF, 0x03CA, 0x83DB, 0x03DE, 0x03D4, 0x83D1,
        0x83F3, 0x03F6, 0x03FC, 0x83F9, 0x03E8, 0x83ED, 0x83E7, 0x03E2,
        0x83A3, 0x03A6, 0x03AC, 0x83A9, 0x03B8, 0x83BD, 0x83B7, 0x03B2,
        0x0390, 0x8395, 0x839F, 0x039A, 0x838B, 0x038E, 0x0384, 0x8381,
        0x0280, 0x8285, 0x828F, 0x028A, 0x829B, 0x029E, 0x0294, 0x8291,
        0x82B3, 0x02B6, 0x02BC, 0x82B9, 0x02A8, 0x82AD, 0x82A7, 0x02A2,
        0x82E3, 0x02E6, 0x02EC, 0x82E9, 0x02F8, 0x82FD, 0x82F7, 0x02F2,
        0x02D0, 0x82D5, 0x82DF, 0x02DA, 0x82CB, 0x02CE, 0x02C4, 0x82C1,
        0x8243, 0x0246, 0x024C, 0x8249, 0x0258, 0x825D, 0x8257, 0x0252,
        0x0270, 0x8275, 0x827F, 0x027A, 0x826B, 0x026E, 0x0264, 0x8261,
        0x0220, 0x8225, 0x822F, 0x022A, 0x823B, 0x023E, 0x0234, 0x8231,
        0x8213, 0x0216, 0x021C, 0x8219, 0x0208, 0x820D, 0x8207, 0x0202
    };

    for(j = 0; j < data_blk_size; j++)
    {
        i = ((unsigned short)(crc_accum >> 8) ^ data_blk_ptr[j]) & 0xFF;
        crc_accum = (crc_accum << 8) ^ crc_table[i];
    }

    data_blk_ptr[data_blk_size] = crc_accum & 0xFF;
    data_blk_ptr[data_blk_size+1] = crc_accum >> 8;
}


void XL320_sendTram1Byte(XL320* xl320, uint8_t reg, uint8_t data){
	XL320_sendData(xl320 ,SIZE_WRITE_8, XL320_Write, 2, reg, data);
}

void XL320_sendTram2Byte(XL320* xl320, uint8_t reg, uint16_t data){
	uint8_t data1 = (uint8_t)(data>>8);
	uint8_t data2 = (uint8_t)data&0xFF;
	XL320_sendData(xl320 ,SIZE_WRITE_16, XL320_Write, 3, reg, data2, data1);
}


uint8_t XL320_readTram1Byte(XL320* xl320, uint8_t reg){
	uint8_t data[SIZE_GET_READ_8];

	/***********************************
	 * envoi de la requête de lecture *
	 ***********************************/
	XL320_sendData(xl320, SIZE_REQUEST_READ_8, XL320_Read, 2, reg, 1);

	/*************************
	 * réception des données *
	 *************************/
	HAL_HalfDuplex_EnableReceiver(xl320->UART);
	HAL_UART_Receive(xl320->UART, data, SIZE_GET_READ_8, 500);
	HAL_HalfDuplex_EnableTransmitter(xl320->UART);

	return data[5];
}

uint16_t XL320_readTram2Byte(XL320* xl320, uint8_t reg){
	uint8_t data[SIZE_GET_READ_16];

	/***********************************
	 * envoi de la requête de lecture *
	 ***********************************/
	XL320_sendData(xl320, SIZE_REQUEST_READ_16, XL320_Read, 2, reg, 2);

	/*************************
	 * réception des données *
	 *************************/
	HAL_HalfDuplex_EnableReceiver(xl320->UART);
	HAL_UART_Receive(xl320->UART, data, SIZE_GET_READ_16, 500);
	HAL_HalfDuplex_EnableTransmitter(xl320->UART);

	uint16_t dataReturn = (data[6]<<8) + data[5];
	return (dataReturn);
}

int8_t XL320_pingModule(XL320* xl320){
	uint8_t data[SIZE_PING];

	/********************************
	 * envoi de la requête de ping *
	 ********************************/
	XL320_sendData(xl320, SIZE_PING, XL320_Ping ,0);

	/*************************
	 * réception des données *
	 *************************/
	HAL_HalfDuplex_EnableReceiver(xl320->UART);
	if(HAL_UART_Receive(xl320->UART,data,SIZE_PING,150) == HAL_TIMEOUT){
		data[4] = 128;
	}
	HAL_HalfDuplex_EnableTransmitter(xl320->UART);

	/*******************************************
	 * nous renvoyons l'erreur s'il y en a une *
	 *******************************************/
	return XL320_errorControl(data[4]);
}

int8_t XL320_errorControl(uint8_t err){
	uint8_t error = 0;
	for(uint8_t i = 0; i < 8;i++){
		switch(err&(1<<i)){
		case(1): error-=1;break;
		case(2): error-=2;break;
		case(4): error-=4;break;
		case(8): error-=8;break;
		case(16): error-=16;break;
		case(32): error-=32;break;
		case(64): error-=64;break;
		case(128): error-=128;break;
		default: break;
		}
	}
	return error;
}
