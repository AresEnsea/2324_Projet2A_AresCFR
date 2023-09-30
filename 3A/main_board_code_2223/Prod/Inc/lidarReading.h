/*
 * lidarReading.h
 *
 *  Created on: 23 avr. 2023
 *      Author: Victor Lesne
 */

#ifndef INC_LIDARREADING_H_
#define INC_LIDARREADING_H_

#include "main.h"


#define FRAME_BOUND		0xFF
#define DEFAULT_ROI 	13



extern uint8_t lidarBuf[3000];
extern uint8_t DataAcquiered;
extern uint8_t newDataset;
extern uint8_t frameStarted;
extern uint16_t bufferIndex;
extern uint16_t frameIndex;


extern uint16_t distanceList[500];
extern uint8_t captorList[300];
extern uint8_t roiList[300];

extern uint8_t NROI;
extern uint8_t maxMesure;
extern uint8_t measuresSent;


void readFrame(void);
/**
  * @brief  Reads the measures of the new frame and writes them into the memory
  */

void readHeader(uint16_t frameIndex);
/**
  * @param 	frameIndex : index of the start of the frame
  * @brief  Reads the frame's header
  */


void readValue(uint16_t usedIndex, uint16_t frameIndex);
/**
  * @param 	usedIndex  : index of the end of the frame (don't put bufferIndex because it is refreshed too often in the DMA)
  * 		frameIndex : index of the start of the frame
  * @brief  Extracts the captor, ROI and distance of every measure in the selected frame.
  * 		Will not read more measures than announced in the header
  */

void frameStatus(void);
/**
  * @brief States on the beginning and ending the latest frame and save the index when one starts
  */

uint8_t setFrameIndex(uint16_t * frameIndex);
/**
  * @param frameIndex : the index of the start of the frame primarily set in frameStatus()
  * @brief Adjust the value of the index stating the start of the frame
  * to be sure it doesn't overlap with the frame's boundaries.
  * @return the success of the adjustment, 1:success 0:failure
  */

#endif /* INC_LIDARREADING_H_ */
