
#ifndef _VL53L1X_CORE_
#define _VL53L1X_CORE_
#pragma once

	/* Default configuration: Autonomous Low Power
	 * TimingBudgetInMs = 90
	 * Distance Mode = 3
	 * InterMeasurementInMs = 90
	 */

uint8_t VL51L1X_DEFAULT_CONFIGURATION[] = {
	/* First 21 bytes are Part-to-part depend,
	 * please use factory calibration and not over-write these bytes */
	0x00, 0x00, 0x00,	// 24
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	//32
	0x36, 0x00, 0x36, 0x0A, 0x00, 0x00, 0x00, 0x00,	//40
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,	//48
	0x02, 0x00, 0x02, 0x08, 0x00, 0x08, 0x10, 0x01,	//56
	0x01, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x02,	//64
	0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x0B, 0x00,	//72
	0x00, 0x02, 0x0A, 0x21, 0x00, 0x00, 0x05, 0x00,	//80
	0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x38, 0xFF,	//88
	0x01, 0x00, 0x00, 0x00, 0x00, 0x81, 0xDA, 0x0F,	//96
	0x00, 0x94, 0x0D, 0x00, 0x3C, 0x00, 0x80, 0x08,	//104
	0xB8, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x74, 0x00,	//112
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0F,	//120
	0x0D, 0x0E, 0x0E, 0x01, 0x00, 0x02, 0xC7, 0xFF,	//128
	0x9B, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00	//135
};

/* If you want an automatic start after the call to VL53L1X_init(),
 * put 0x40 in location 135
 */

#define SOFT_RESET													0x0000
#define VL53L1_I2C_SLAVE__DEVICE_ADDRESS							0x0001
#define VL53L1_VHV_CONFIG__TIMEOUT_MACROP_LOOP_BOUND                0x0008
#define ALGO__CROSSTALK_COMPENSATION_PLANE_OFFSET_KCPS 				0x0016
#define ALGO__CROSSTALK_COMPENSATION_X_PLANE_GRADIENT_KCPS 			0x0018
#define ALGO__CROSSTALK_COMPENSATION_Y_PLANE_GRADIENT_KCPS 			0x001A
#define ALGO__PART_TO_PART_RANGE_OFFSET_MM							0x001E
#define MM_CONFIG__INNER_OFFSET_MM									0x0020
#define MM_CONFIG__OUTER_OFFSET_MM 									0x0022
#define GPIO_HV_MUX__CTRL											0x0030
#define GPIO__TIO_HV_STATUS       									0x0031
#define SYSTEM__INTERRUPT_CONFIG_GPIO 								0x0046
#define PHASECAL_CONFIG__TIMEOUT_MACROP     						0x004B
#define MM_CONFIG__TIMEOUT_MACROP_A_LO      						0x005B
#define MM_CONFIG__TIMEOUT_MACROP_B_HI      						0x005C
#define RANGE_CONFIG__TIMEOUT_MACROP_A_HI   						0x005E
#define RANGE_CONFIG__VCSEL_PERIOD_A        						0x0060
#define RANGE_CONFIG__VCSEL_PERIOD_B								0x0063
#define RANGE_CONFIG__TIMEOUT_MACROP_B_HI  					 		0x0061
#define RANGE_CONFIG__TIMEOUT_MACROP_B_LO  					 		0x0062
#define RANGE_CONFIG__SIGMA_THRESH 									0x0064
#define RANGE_CONFIG__MIN_COUNT_RATE_RTN_LIMIT_MCPS 				0x0066
#define RANGE_CONFIG__VALID_PHASE_HIGH      						0x0069
#define VL53L1_SYSTEM__INTERMEASUREMENT_PERIOD						0x006C
#define SYSTEM__THRESH_HIGH 										0x0072
#define SYSTEM__THRESH_LOW 											0x0074
#define SD_CONFIG__WOI_SD0                  						0x0078
#define SD_CONFIG__INITIAL_PHASE_SD0        						0x007A
#define ROI_CONFIG__USER_ROI_CENTRE_SPAD							0x007F
#define ROI_CONFIG__USER_ROI_REQUESTED_GLOBAL_XY_SIZE				0x0080
#define SYSTEM__SEQUENCE_CONFIG										0x0081
#define SYSTEM__INTERRUPT_CLEAR       						  		0x0086
#define SYSTEM__MODE_START                 					  		0x0087
#define VL53L1_RESULT__RANGE_STATUS									0x0089
#define VL53L1_RESULT__DSS_ACTUAL_EFFECTIVE_SPADS_SD0				0x008C
#define RESULT__AMBIENT_COUNT_RATE_MCPS_SD							0x0090
#define VL53L1_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0 		0x0096
#define VL53L1_RESULT__PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0 	0x0098
#define VL53L1_RESULT__OSC_CALIBRATE_VAL							0x00DE
#define VL53L1_FIRMWARE__SYSTEM_STATUS                              0x00E5
#define VL53L1_IDENTIFICATION__MODEL_ID                             0x010F
#define VL53L1_ROI_CONFIG__MODE_ROI_CENTRE_SPAD						0x013E

#endif
