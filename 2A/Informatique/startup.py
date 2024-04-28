"""
    @file        startup.py
    @author      Mowibox (Ousmane THIONGANE)
    @brief       Simple file to check if the Raspberry boots
    @version     
    @date        
    @copyright   
    
"""

import RPi.GPIO as GPIO
import time

pin_led = 16

GPIO.setmode(GPIO.BCM)
GPIO.setup(pin_led, GPIO.OUT)

for i in range(5):
        GPIO.output(pin_led, GPIO.HIGH)
        time.sleep(0.2) 

        GPIO.output(pin_led, GPIO.LOW)
        time.sleep(0.2)  

GPIO.cleanup()
