/*
 * trameUart.c
 *
 *  Created on: Feb 9, 2023
 *      Author: Victor Lesne
 */


#include "trameUart.h"

extern UART_HandleTypeDef SERIAL_UART;
extern uint16_t ActiveCaptors;

extern uint32_t refreshTime;

uint8_t listOfMesures[3*NumOfTOFSensors + 1]={0};

void UART_Send_Mesures(uint16_t * mesuredDistances , uint8_t Zone,  uint32_t TotalTime){
	uint8_t openCloseBuf[4] = {0xFF,0xFF, 0xFF};

	uint8_t NcaptActifs = 0;
	for(uint8_t i =0;i<16;i++){
		NcaptActifs += (ActiveCaptors & (1<<i)) ? 1 : 0;
	}





	uint8_t * mesures;
	if(Zone == NumOfZonesPerSensor + 1){
		mesures = UART_makeList(mesuredDistances);
	}
	else{
		mesures = UART_monoROIList( mesuredDistances, Zone);
	}
	uint16_t NbreMesures = listOfMesures[0];

	uint8_t batchStats[3] = {NcaptActifs, (uint8_t)NumOfZonesPerSensor, (uint8_t)NbreMesures};
		//ITM_Port32(31) = TotalTime;
			//(uint16_t) *mesures; mesures++;
	/*uint8_t A = mesures[0];
	 A = mesures[1];

	 A = mesures[2];*/

	// 0xFF		0xFF					0xFF
	HAL_UART_Transmit(&SERIAL_UART, openCloseBuf, 3, 100);
	//HAL_Delay(5);

	// Ncapteurs	Nbre de zones utilisees	Distance min
	HAL_UART_Transmit(&SERIAL_UART, batchStats, 3, 100);
	//HAL_Delay(5);

	// Capteur Zone i	Distance i (part1)	Distance i (part2)
	for(int j=0;j<NbreMesures;j++){
	HAL_UART_Transmit(&SERIAL_UART,  &listOfMesures[3*j+1], 3, 100);
	mesures+=3;
	//HAL_Delay(5);
	}

	// 0xFF		0xFF					0xFF
	HAL_UART_Transmit(&SERIAL_UART, openCloseBuf, 3, 100);
	//HAL_Delay(5);

}

uint8_t * UART_makeList(uint16_t * LidarDistance){
	uint8_t listOfMesures[3*NumOfZonesPerSensor*NumOfTOFSensors + 1];
	int ZonePosition;
	int Nmesure = 0;

	for(int CurrentSensor = 0; CurrentSensor<16; CurrentSensor++){
		if(ActiveCaptors & (1<<CurrentSensor)){

			for(int CurrentZone = 0; CurrentZone<NumOfZonesPerSensor; CurrentZone++){

				ZonePosition = NumOfZonesPerSensor*CurrentSensor + CurrentZone;

				if(LidarDistance[ZonePosition] < MaxInterestDistance){

					listOfMesures[3*Nmesure+1] 		= (uint8_t)(ZonePosition+1); //Pour que le premier element de la chaine de caracteres ne soit pas '\0'
					listOfMesures[3*Nmesure + 1+1] 	= (uint8_t)((LidarDistance[ZonePosition] & 0xFF00)>>8); 	//Bits de poids forts de la mesure
					listOfMesures[3*Nmesure + 2+1] 	= (uint8_t)(LidarDistance[ZonePosition] & 0xFF);			//Bits de poids faible de la mesure

					Nmesure++;
				}
			}
		}
	}
	listOfMesures[0] = Nmesure;

	uint8_t * exitVar =listOfMesures;

	return exitVar;
}

uint8_t * UART_monoROIList(uint16_t * LidarDistance, uint8_t Zone){

	int ZonePosition;
	int Nmesure = 0;

	for(int CurrentSensor = 0; CurrentSensor<16; CurrentSensor++){
		if(ActiveCaptors & (1<<CurrentSensor)){

			/*for(int CurrentZone = 0; CurrentZone<NumOfZonesPerSensor; CurrentZone++){*/

				ZonePosition = NumOfZonesPerSensor*CurrentSensor + Zone;

				if(LidarDistance[ZonePosition] < MaxInterestDistance){

					listOfMesures[3*Nmesure+1] 		= (uint8_t)(ZonePosition+1); //Pour que le premier element de la chaine de caracteres ne soit pas '\0'
					listOfMesures[3*Nmesure + 1+1] 	= (uint8_t)((LidarDistance[ZonePosition] & 0xFF00)>>8); 	//Bits de poids forts de la mesure
					listOfMesures[3*Nmesure + 2+1] 	= (uint8_t)(LidarDistance[ZonePosition] & 0xFF);			//Bits de poids faible de la mesure

					Nmesure++;
				}
			/*}*/
		}
	}
	listOfMesures[0] = Nmesure;

	uint8_t * exitVar;

	return exitVar;
}
