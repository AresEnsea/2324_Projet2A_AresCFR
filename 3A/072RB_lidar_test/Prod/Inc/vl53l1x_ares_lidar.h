#include <stdint.h>

#define LIDAR_MODULE_NUMBER 16
#define LIDAR_FRAME_SIZE 114

typedef enum ares_lidar_parsing_status_enum
{
	BEGIN   			= 0,
	INFO   				= 1,
	DISTANCE_MES  		= 2,
} ares_lidar_parsing_status_t;

typedef struct ares_lidar_struct
{
	ares_lidar_parsing_status_t parsing_status;
	uint8_t 					active_sensor;
	uint8_t						ROI_number;
	uint8_t						measure_number;
	uint8_t 					rx_storage[LIDAR_FRAME_SIZE<<1];
	uint16_t					measure[LIDAR_MODULE_NUMBER][2];
} ares_lidar_t;

void ares_lidar_dma_irq_handler(ares_lidar_t * lidar);
