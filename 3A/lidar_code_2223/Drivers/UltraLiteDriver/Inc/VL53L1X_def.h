
#ifndef _VL53L1X_CORE_
#define _VL53L1X_CORE_
#pragma once

#if 0
uint8_t VL51L1X_NVM_CONFIGURATION[] = {
/* Warning Part-to-Part depend registers */
/*0x00, Reg 0x00 is soft reset */
/*0x29, Reg 0x01 is I2C address*/
/*0x00, Reg 0x02 is don't touch*/
/*0x00, Reg 0x03 is don't touch*/
/*0x00, Reg 0x04 is don't touch*/
/*0x00, Reg 0x05 is don't touch*/
/*0x00, Reg 0x06 is don't touch*/
/*0x00, Reg 0x07 is don't touch*/
/*0x00, Reg 0x08 is don't touch*/
/*0x50, Reg 0x09 is don't touch*/
/*0x00, Reg 0x0A is don't touch*/
/*0x00, Reg 0x0B is don't touch*/
/*0x00, Reg 0x0C is not implemented*/
/*0x00, Reg 0x0D is refspad don't touch*/
/*0x0a, Reg 0x0E is refspad don't touch*/
/*0x00, Reg 0x0F is refspad don't touch*/
/*0x00, Reg 0x10 is refspad don't touch*/
/*0x00, Reg 0x11 is refspad don't touch*/
/*0x00, Reg 0x12 is refspad don't touch*/
/*0x00, Reg 0x13 is refspad don't touch*/
/*0x00, Reg 0x14 is refspad don't touch*/
/*0x00, Reg 0x15 is refspad don't touch*/

0x00, /* Reg 0x16 is Xtalk cal value MSB*/
0x00, /* Reg 0x17 is Xtalk cal value LSB*/
0x00, /* Reg 0x18 is Xtalk not used*/
0x00, /* Reg 0x19 is Xtalk not used*/
0x00, /* Reg 0x1a is Xtalk not used*/
0x00, /* Reg 0x1b is Xtalk not used*/
0x00, /* Reg 0x1c is refcal target rate Mcps MSB*/
0x00, /* Reg 0x1d is refcal target rate Mcps LSB*/
0x00, /* Reg 0x1e is Part to Part offset x4 MSB */
0x50, /* Reg 0x1f is Part to Part offset x4 LSB */
0x00, /* Reg 0x20 is Offset don't touch*/
0x00, /* Reg 0x21 is Offset don't touch*/
0x00, /* Reg 0x22 is Offset don't touch*/
0x00, /* Reg 0x23 is Offset don't touch*/
0x0a, /* Reg 0x24 is DSS target rate MSB Mcps*/
0x00, /* Reg 0x25 is DSS target rate LSB Mcps*/
0x00, /* Reg 0x26 is debug control don't touch*/
0x00, /* Reg 0x27 is test mode control don't touch*/
0x00, /* Reg 0x28 is don't touch*/
0x00, /* Reg 0x29 is don't touch*/
0x00, /* Reg 0x2a is don't touch*/
0x00, /* Reg 0x2b is don't touch*/
0x00, /* Reg 0x2c is don't touch*/
0x00  /* Reg 0x2d is set bit 2 and 5 at 1 for mode fast plus (1MHz I2C), else don't touch*/
};
#endif
const uint8_t VL51L1X_DEFAULT_CONFIGURATION[] = {
0x00, /* Reg 0x2e is don't touch bit 0 if I2C pulled up at 1.8V, else set bit 0 to 1 */
0x00, /* Reg 0x2f is don't touch bit 0 if GPIO pulled up at 1.8V, else set bit 0 to 1  */
0x01, /* Reg 0x30 is set bit 4 to 0 for active high interrupt and 1 for active low */
0x02, /* Reg 0x31 is bit 1 is fresh out reset information */
0x00, /* Reg 0x32 is read only don't touch */
0x02, /* Reg 0x33 is don't touch */
0x08, /* Reg 0x34 is don't touch (VCSEL pulse width offset)*/
0x00, /* Reg 0x35 is don't touch */
0x08, /* Reg 0x36 is don't touch */
0x10, /* Reg 0x37 is don't touch */
0x01, /* Reg 0x38 is don't touch */
0x01, /* Reg 0x39 is Xtalk compensation valid height don't touch */
0x00, /* Reg 0x3a is don't touch*/
0x00, /* Reg 0x3b is don't touch*/
0x00, /* Reg 0x3c is range ignore threshold MSB */
0x00, /* Reg 0x3d is range ignore threshold LSB */
0xff, /* Reg 0x3e is range ignore valid height */
0x00, /* Reg 0x3f is range min clip */
0x02, /* Reg 0x40 is consistency check don't touch*/
0x00, /* Reg 0x41 is not used */
0x00, /* Reg 0x42 is don't touch */
0x00, /* Reg 0x43 is don't touch */
0x00, /* Reg 0x44 is don't touch */
0x00, /* Reg 0x45 is don't touch */
0x20, /* Reg 0x46 is interrupt config 0->level low, 1-> level high, 2-> Out of window, 3->In window, 7-> New sample ready */
0x0b, /* Reg 0x47 is don't touch */
0x00, /* Reg 0x48 is don't touch */
0x00, /* Reg 0x49 is don't touch */
0x02, /* Reg 0x4a is don't touch */
0x0a, /* Reg 0x4b is don't touch */
0x21, /* Reg 0x4c is don't touch */
0x00, /* Reg 0x4d is don't touch */
0x00, /* Reg 0x4e is not implemented */
0x05, /* Reg 0x4f is DSS 0->Disable, 1->TargetRate, 2->Requested effective refspad, 3->Block select */
0x00, /* Reg 0x50 is don't touch */
0x00, /* Reg 0x51 is don't touch */
0x00, /* Reg 0x52 is don't touch */
0x00, /* Reg 0x53 is don't touch */
0xc8, /* Reg 0x54 is Manual spad number for DSS MSB */
0x00, /* Reg 0x55 is Manual spad number for DSS LSB */
0x00, /* Reg 0x56 is Manual block value for DSS */
0x38, /* Reg 0x57 is don't touch */
0xff, /* Reg 0x58 is Max spad limit */
0x01, /* Reg 0x59 is Min spad limit */
0x00, /* Reg 0x5a is don't touch */
0x00, /* Reg 0x5b is don't touch */
0x00, /* Reg 0x5c is don't touch */
0x00, /* Reg 0x5d is don't touch */
0x01, /* Reg 0x5e is Range A Timeout exponent */
0xdb, /* Reg 0x5f is Range A Timeout mantissa */
0x0f, /* Reg 0x60 is Range A VCSEL period */
0x01, /* Reg 0x61 is Range B Timeout exponent*/
0xf1, /* Reg 0x62 is Range B Timeout mantissa */
0x0d, /* Reg 0x63 is Range B VCSEL period */
0x00, /* Reg 0x64 is Sigma threshold MSB */
0x3c, /* Reg 0x65 is Sigma threshold LSB */
0x00, /* Reg 0x66 is Min count Rate MSB */
0x80, /* Reg 0x67 is Min count Rate LSB */
0x08, /* Reg 0x68 is phase low don't touch */
0xb8, /* Reg 0x69 is phase high don't touch */
0x00, /* Reg 0x6a is not implemented */
0x00, /* Reg 0x6b is not implemented */
0x00, /* Reg 0x6c is Intermeasurment period MSB*/
0x00, /* Reg 0x6d is Intermeasurment period */
0x0f, /* Reg 0x6e is Intermeasurment period*/
0x89, /* Reg 0x6f is Intermeasurment period LSB */
0x00, /* Reg 0x70 is fraction enable don't touch */
0x00, /* Reg 0x71 is GPH Ghost */
0x00, /* Reg 0x72 is distance threshold high MSB */
0x00, /* Reg 0x73 is distance threshold high LSB */
0x00, /* Reg 0x74 is distance threshold low MSB */
0x00, /* Reg 0x75 is distance threshold low LSB */
0x00, /* Reg 0x76 is not used */
0x01, /* Reg 0x77 is don't touch */
0x0f, /* Reg 0x78 is WOI_SD0 don't touch */
0x0d, /* Reg 0x79 is WOI_SD1 don't touch */
0x0e, /* Reg 0x7a is Initial phase SD0 don't touch */
0x0e, /* Reg 0x7b is Initial phase SD1 don't touch */
0x00, /* Reg 0x7c is GPH Ghost */
0x00, /* Reg 0x7d is don't touch */
0x02, /* Reg 0x7e is don't touch */
0xc7, /* Reg 0x7f is ROI center */
0xff, /* Reg 0x80 is XY ROI */
0x9B, /* Reg 0x81 is Sequence config, bit 7->range,bit 6->MM2, bit 5-> MM1, bit 4->DSS2, bit 3-> DSS1, bit 1->PhaseCal, bit 0->VHV */
0x00, /* Reg 0x82 is GPH */
0x00, /* Reg 0x83 is Power force don't touch */
0x00, /* Reg 0x84 is don't touch */
0x01, /* Reg 0x85 is firmware enable don't touch */
0x00, /* Reg 0x86 is interrupt clear (write one)*/
0x00 /* Reg 0x87 is Start ranging */
};


/* If you want an automatic start after the call to VL53L1X_init(),
 * put 0x40 in location 0x87
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
#define VL53L1_SYSTEM__GROUPED_PARAMETER_HOLD 						0x0082
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
