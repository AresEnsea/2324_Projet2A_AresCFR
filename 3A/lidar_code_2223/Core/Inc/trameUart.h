/*
 * trameUart.h
 *
 *  Created on: Feb 9, 2023
 *      Author: Victor Lesne
 */

#ifndef INC_TRAMEUART_H_
#define INC_TRAMEUART_H_

#include "stm32g0xx_hal.h"
#include "stdlib.h"
#include "stdio.h"
#include "main.h"

#endif /* INC_TRAMEUART_H_ */

/**
 * @brief This function sends the mesured distances to the UART after putting them into a frame
 * @param mesuredDistances:	The list of distances mesured by each captor during a cycle
 * @param Zone:				The ROI whose we want to send the mesurements (number of ROI +1 if we want to send all of them)
 * @param ToltalTime:		The time since the start of the polling
 */
void UART_Send_Mesures(uint16_t * mesuredDistances , uint8_t Zone,  uint32_t TotalTime);

/**
 * @brief This function get the mesure list into shape to send it via the UART
 * and filters out the faraway distances
 * @param LidarDistance: 	The list containing all the mesures of the captors with the differents ROIs
 * @return listOfMesures: 	The list of mesures' ID and the distance itself split in 2 bytes
 */
uint8_t * UART_makeList(uint16_t * LidarDistance);

/**
 * @brief This function get the mesure list into shape to send it via the UART
 * and filters out the faraway distances,
 * taking only into account only the specified ROI
 * @param LidarDistance: 	The list containing all the mesures of the captors with the differents ROIs
 * @param Zone: 			The ROI from whom we want the mesures
 * @return listOfMesures: 	The list of mesures' ID and the distance itself split in 2 bytes
 */
uint8_t * UART_monoROIList(uint16_t * LidarDistance, uint8_t Zone);
