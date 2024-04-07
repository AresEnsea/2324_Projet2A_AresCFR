"""
    @file        rpi_xl320.py
    @author      Mowibox (Ousmane THIONGANE)
    @brief       Library for Dynamixel XL320 on a Raspberry Pi
    @version     1.0
    @date        2024-04-07
    
"""

import serial
import time
import RPi.GPIO as GPIO

# EEPROM
XL320_REG_MODEL_NUMBER = 0
XL320_REG_VERSION = 2
XL320_REG_XL_ID = 3
XL320_REG_BAUD_RATE = 4
XL320_REG_RETURN_DELAY_TIME = 5
XL320_REG_CW_ANGLE_LIMIT = 6
XL320_REG_CCW_ANGLE_LIMIT = 9
XL320_REG_SYSTEM_DATA2 = 10
XL320_REG_CONTROL_MODE = 11
XL320_REG_LIMIT_TEMPERATURE = 12
XL320_REG_LOWER_LIMIT_VOLTAGE = 13
XL320_REG_UPPER_LIMIT_VOLTAGE = 14
XL320_REG_MAX_TORQUE = 15
XL320_REG_RETURN_LEVEL = 17
XL320_REG_ALARM_SHUTDOWN = 18

# RAM
XL320_REG_TORQUE_ENABLE = 24
XL320_REG_LED = 25
XL320_REG_D_GAIN = 27
XL320_REG_I_GAIN = 28
XL320_REG_P_GAIN = 29
XL320_REG_GOAL_POSITION = 30
XL320_REG_GOAL_SPEED = 32
XL320_REG_GOAL_TORQUE = 35
XL320_REG_PRESENT_POSITION = 37
XL320_REG_PRESENT_SPEED = 39
XL320_REG_PRESENT_LOAD = 41
XL320_REG_PRESENT_VOLTAGE = 45
XL320_REG_PRESENT_TEMPERATURE = 46
XL320_REG_REGISTERED_INSTRUCTION = 47
XL320_REG_MOVING = 49
XL320_REG_HARDWARE_ERROR_STATUS = 50
XL320_REG_PUNCH = 51

# INSTRUCTION
XL320_INST_PING = 1
XL320_INST_READ_DATA = 2
XL320_INST_WRITE_DATA = 3
XL320_INST_REG_WRITE = 4
XL320_INST_ACTION = 5
XL320_INST_FACTORY_RESET = 6
XL320_INST_REBOOT = 8
XL320_INST_STATUS = 85
XL320_INST_SYNC_READ = 130
XL320_INST_SYNC_WRITE = 131
XL320_INST_BULK_READ = 146
XL320_INST_BULK_WRITE = 147

# HEADER
XL320_HEADER_1 = 0xFF
XL320_HEADER_2 = 0xFF
XL320_HEADER_3 = 0xFD
XL320_RSRV = 0x00

# CTRL MODE
XL320_WHEEL_MODE = 1
XL320_JOINT_MODE = 2 #Default

# LED
XL320_LED_OFF = 0
XL320_LED_RED = 1
XL320_LED_GREEN = 2
XL320_LED_YELLOW = 3
XL320_LED_BLUE = 4
XL320_LED_PURPLE = 5
XL320_LED_CYAN = 6
XL320_LED_WHITE	= 7

# UART RX TX Mode
XL320_UART_RX = GPIO.LOW
XL320_UART_TX = GPIO.HIGH
XL320_CRC_LENGTH = 2

class XL320:
    def __init__(self):
        self.huart = None  
        self.tx_En_Pin = None  
        self.model_number = 350  
        self.firmware_version = 0  
        self.id = 1  
        self.baudrate = 3  
        self.return_delay_time = 250  
        self.CW_angle_limit = 0  
        self.CCW_angle_limit = 1023  
        self.control_mode = 2  
        self.temperature_limit = 65  
        self.min_voltage_limit = 60  
        self.max_voltage_limit = 90  
        self.max_torque = 1023  
        self.status_return_level = 2  
        self.shutdown_error_information = 3  
        self.crc = 0  
        self.tx_buffer = bytearray(64)  
        self.tx_data_length = 0  
        self.rx_buffer = bytearray(64)  
        self.rx_data_length = 0  

    def XL320_Init(self, huart, TxEnPin, id, baudrate):
        self.huart = huart
        self.tx_En_Pin = TxEnPin
        self.id = id
        self.baudrate = baudrate
        self.control_mode = 2
        self.max_torque = 1023
        # Set in RX mode
        self.XL320_Set_UART_RxTxMode(self, XL320_UART_RX)

    def XL320_Set_UART_RxTxMode(self, mode):
        GPIO.output(self.tx_En_Pin, mode)

    def XL320_Write_Data(self, Address, Value):
        # Header + reserved
        self.tx_buffer[0] = XL320_HEADER_1
        self.tx_buffer[1] = XL320_HEADER_2
        self.tx_buffer[2] = XL320_HEADER_3
        self.tx_buffer[3] = XL320_RSRV

        # ID
        self.tx_buffer[4] = self.id

        # Length (Nb param + Instru + CRC)
        self.tx_buffer[5] = 0x07  # Length (Low)
        self.tx_buffer[6] = 0x00  # Length (High)

        # Instruction : write
        self.tx_buffer[7] = XL320_INST_WRITE_DATA

        # Register Address
        self.tx_buffer[8] = Address & 0x00FF         # Addr (Low)
        self.tx_buffer[9] = (Address >> 8) & 0x00FF  # Addr (High)

        # Register Value
        self.tx_buffer[10] = Value & 0x00FF          # Addr (Low)
        self.tx_buffer[11] = (Value >> 8) & 0x00FF   # Addr (High)

        # Set Packet length (w/o crc)
        self.tx_data_length = 12

        # Update CRC
        self.XL320_Update_CRC(self)
        self.tx_buffer[12] = (self.crc) & 0x00FF
        self.tx_buffer[13] = (self.crc >> 8) & 0x00FF

        self.XL320_Set_UART_RxTxMode(XL320_UART_TX)
        self.huart.write(self.tx_buffer + (self.tx_data_length + XL320_CRC_LENGTH).to_bytes(2, byteorder='little'))
        self.XL320_Set_UART_RxTxMode(XL320_UART_RX)

    def XL320_Set_Position(self, position):
        # angle = position * 0.29°
        position = position if position < 1023 else 1023
        self.XL320_Write_Data(XL320_REG_GOAL_POSITION, position)

    def XL320_Set_Speed(self, speed):
        # rotary speed = speed * 0.111 rpm, on 10 bits,
        # in wheel mode,  11th bit = direction bit control
        if self.control_mode == XL320_JOINT_MODE:
            speed = speed if speed < 0x3FF else 0x3FF
            self.XL320_Write_Data(XL320_REG_GOAL_SPEED, speed)
        elif self.control_mode == XL320_WHEEL_MODE:
            speed = speed if speed < 0x7FF else 0x7FF
            self.XL320_Write_Data(XL320_REG_GOAL_SPEED, speed)

    def XL320_Set_Torque_Limit(self, torque_limit):
        torque_limit = torque_limit if torque_limit < 0x3FF else 0x3FF
        self.XL320_Write_Data(XL320_REG_GOAL_TORQUE, torque_limit)

    def XL320_Set_Led_Color(self, color):
        self.XL320_Write_Data(XL320_REG_LED, color)

    def XL320_Update_CRC(self):
        crc_accum = 0
        crc_table = [
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
        ]
        for j in range(self.tx_data_length):
            i = ((crc_accum >> 8) ^ self.tx_buffer[j]) & 0xFF
            crc_accum = (crc_accum << 8) ^ crc_table[i]
        self.crc = crc_accum

# Main function
if __name__ == "__main__":

    testInstr = b"*** XL320 Test ***\r\n"
    
    ser = serial.Serial('/dev/ttyS0', baudrate=57600, timeout=1)

    myServo = XL320()
    myServo.XL320_Init(ser, 10, 1, 3)

    ser.write(testInstr)

    while True:
        myServo.XL320_Set_Led_Color(XL320_LED_CYAN)
        myServo.XL320_Set_Speed(64)
        myServo.XL320_Set_Torque_Limit(256)
        myServo.XL320_Set_Position(0)

        time.sleep(5)

        myServo.XL320_Set_Led_Color(XL320_LED_PURPLE)
        myServo.XL320_Set_Speed(256)
        myServo.XL320_Set_Torque_Limit(256)
        myServo.XL320_Set_Position(1023)

        time.sleep(5)
