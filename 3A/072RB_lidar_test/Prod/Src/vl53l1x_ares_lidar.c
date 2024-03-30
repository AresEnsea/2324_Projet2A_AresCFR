#include "vl53l1x_ares_lidar.h"

void ares_lidar_dma_irq_handler(ares_lidar_t * lidar){
	static uint8_t reading_head=0, wait_for_head_cmp=0, wait_for_fill=0;;
	uint8_t reading_head_limit=0;

	if((reading_head >= LIDAR_FRAME_SIZE) && reading_head < (LIDAR_FRAME_SIZE<<1)){	reading_head_limit = LIDAR_FRAME_SIZE<<1;				}
	else if(reading_head >= (LIDAR_FRAME_SIZE<<1)){									reading_head_limit = LIDAR_FRAME_SIZE;
																					reading_head = 0;}
	else{																			reading_head_limit = LIDAR_FRAME_SIZE;					}

	for(; reading_head < reading_head_limit; reading_head++)
	{
		switch(lidar->parsing_status)
		{
			case BEGIN 			:
				if(	lidar->rx_storage[reading_head] == 0xFF ){
					wait_for_head_cmp++;}
				else
					wait_for_head_cmp = 0;

				if(wait_for_head_cmp > 5){
					wait_for_head_cmp = 0;
					lidar->parsing_status = INFO;}
				break;

			case INFO			:
				if(	wait_for_head_cmp == 0 ){
					lidar->active_sensor = lidar->rx_storage[reading_head];
					wait_for_head_cmp++;}
				else if(wait_for_head_cmp == 1){
					lidar->ROI_number = lidar->rx_storage[reading_head];
					wait_for_head_cmp++;}
				else if(wait_for_head_cmp > 1){
					lidar->measure_number = lidar->rx_storage[reading_head];
					wait_for_head_cmp = 0;
					lidar->parsing_status = DISTANCE_MES;}
				break;

			case DISTANCE_MES	:
				if(	wait_for_fill%3 == 0 && (wait_for_head_cmp < lidar->measure_number)){
					lidar->measure[wait_for_head_cmp][0] = lidar->rx_storage[reading_head];
					wait_for_fill++;}
				else if((wait_for_fill%3 == 1) && (wait_for_head_cmp < lidar->measure_number)){
					lidar->measure[wait_for_head_cmp][1] = (uint16_t) lidar->rx_storage[reading_head];
					lidar->measure[wait_for_head_cmp][1] = lidar->measure[wait_for_head_cmp][1] <<8;
					wait_for_fill++;}
				else if((wait_for_fill%3 == 2) && (wait_for_head_cmp < lidar->measure_number)){
					lidar->measure[wait_for_head_cmp][1] = lidar->measure[wait_for_head_cmp][1] + (uint16_t) lidar->rx_storage[reading_head];
					wait_for_fill++;
					wait_for_head_cmp++;}

				if(wait_for_head_cmp >= lidar->measure_number){
					wait_for_fill = 0;
					wait_for_head_cmp = 0;
					lidar->parsing_status = BEGIN;}
				break;
		}
	}
}
