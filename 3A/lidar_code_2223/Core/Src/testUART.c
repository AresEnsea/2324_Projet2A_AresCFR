/*
 * testUART.c
 *
 *  Created on: Feb 11, 2023
 *      Author: Victor Lesne
 */

#include "testUART.h"
extern uint16_t ActiveCaptors;

void tests(void){
	test1();
	test2();
	test3();
}

void test1(void){

	ActiveCaptors = 0xFFFF;
	uint16_t LidDist[NumOfZonesPerSensor*NumOfTOFSensors];
	LidDist[0] = 10;
	LidDist[1] = 42000;
	LidDist[2] = 0xFF12;

	UART_makeList(LidDist);
}

void test2(void){

	uint16_t LidDist[NumOfZonesPerSensor*NumOfTOFSensors];
	LidDist[0] = 10;
	LidDist[1] = 42000;
	LidDist[2] = 0xFF12;
	ActiveCaptors = 0xFFFE;
	UART_makeList(LidDist);
}

void test3(void){
	uint16_t LidDist[NumOfZonesPerSensor*NumOfTOFSensors];
	LidDist[0] = 10;
	LidDist[1] = 42000;
	LidDist[2] = 0xFF12;
	ActiveCaptors = 0x1;
	UART_Send_Mesures(LidDist, 5, 12);
}
