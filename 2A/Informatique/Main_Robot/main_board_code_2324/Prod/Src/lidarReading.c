/*
 * lidarReading.c
 *
 *  Created on: 23 avr. 2023
 *      Author: Victor Lesne
 *
 *  Bibliotheque permettant la lecture du buffer du port serie avec le LIDAR (v1.3 et plus)
 */

#include "lidarReading.h"


// Indexes lidar
uint8_t newDataset = 0;
uint8_t frameStarted = 0;
uint16_t frameIndex = 0;


// Memoire
uint16_t distanceList[500] = {0};
uint8_t captorList[300] = {0};
uint8_t roiList[300] 	= {0};

// Informations sur les mesures
uint8_t NROI;			//Nbre de ROIs utilises
uint8_t maxMesure = 0; 	//Nbre de mesures stockees
uint8_t measuresSent; 		//Nbre de mesures annoncees


void readFrame(void){
	if(newDataset){
		/* On sauvegarde les index de debut et fin de trame car
		 * l'extraction des mesures peut prendre plus de temps que la reception de nouvelles*/
		uint16_t usedIndex = bufferIndex;
		uint16_t usedStart = frameIndex;

		// On ne lit pas les donnees si le debut de la trame n'est pas conforme
		if(setFrameIndex(&usedStart)){
			readHeader(usedStart);
			readValue(usedIndex, usedStart);
		}
		newDataset = 0;

		/*Pour eviter de remplir le buffer en entier.
		 * Situe ici pour eviter de perdre la position de fin de trame lors de l'etape de lecture des mesures*/
		if(bufferIndex >2000){
			bufferIndex = 0;
		}
	}
}

void readHeader(uint16_t frameIndex){
	uint8_t value[20];

	// 1
	uint8_t ncaptActifs = lidarBuf[frameIndex];

	// 2
	//Pour eviter les erreurs de lecture de trame ne lisant pas l'en-tete (255 ROIs fausse toutes
	if((ncaptActifs <= 0 || ncaptActifs >16) || (lidarBuf[frameIndex+1]>14)){
		NROI = DEFAULT_ROI;
	}
	else{
		//NROI = buffer[frameIndex+1];
		NROI = DEFAULT_ROI; // Not the right value for debug purposes
	}

	// 3
	measuresSent = lidarBuf[frameIndex+2];
}

void readValue(uint16_t usedIndex, uint16_t frameIndex){

	// Variables
	int i = frameIndex + 3;// Debut des mesures apres l'en-tete

	uint8_t value[30];
	uint8_t nbreMes = 0;
	uint8_t Ncapteur; uint8_t indiceROI; uint16_t distance;

	/* Double verification pour eviter la lecture des 0x0 de la memoire par defaut en cas d'index defaillant.
	 * Peut etre enleve si on ajuste aussi usedIndex dans setFrameIndex()
	 * */
	while(i < (usedIndex - 3) && nbreMes < measuresSent){
		//Selon le code du systeme de detection : "Pour que le premier element de la chaine de caracteres ne soit pas '\0'"
		// Donc il faut enlever l'offset sur buffer[i]
		indiceROI = (lidarBuf[i]-1)%NROI;
		Ncapteur  = (lidarBuf[i]-1 -indiceROI)/NROI;
		distance  = (lidarBuf[i+1]<<8) + lidarBuf[i+2];

		// Ecriture memoire
		captorList[nbreMes]=Ncapteur; roiList[nbreMes]=indiceROI; distanceList[nbreMes]=distance;

		i += 3;
		nbreMes++;
	}
	maxMesure = nbreMes;
}

void frameStatus(void){
	//End of Frame
	if(frameStarted && (bufferIndex >= 3) && DataAcquiered){
		if((lidarBuf[bufferIndex - 3] == FRAME_BOUND) && (lidarBuf[bufferIndex - 2] == FRAME_BOUND) && (lidarBuf[bufferIndex - 1] == FRAME_BOUND)){
			frameStarted = 0;

			newDataset = 1;
		}
	}
	//Start of Frame
	else if(!frameStarted && (bufferIndex >= 3) && DataAcquiered){
		if((lidarBuf[bufferIndex - 3] == FRAME_BOUND) && (lidarBuf[bufferIndex - 2] == FRAME_BOUND) && (lidarBuf[bufferIndex - 1] == FRAME_BOUND)){
			frameStarted = 1;
			frameIndex = bufferIndex;
			//frameIndex = 0;

		}
	}
	DataAcquiered = 0;
}

uint8_t setFrameIndex(uint16_t * frameIndex){
	uint16_t bound = *frameIndex;
	while(bound<3000){
		if((lidarBuf[bound - 3] == FRAME_BOUND)	//0xFF
		&& (lidarBuf[bound - 2] == FRAME_BOUND)	//0xFF
		&& (lidarBuf[bound - 1] == FRAME_BOUND)	//0xFF
		&& (lidarBuf[bound - 0] != FRAME_BOUND)){	//NcaptActifs

			*frameIndex = bound;
			return 1;
		}
		else{
			bound++;
		}
	}
	return 0;

}
