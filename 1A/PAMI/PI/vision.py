from picamera2 import Picamera2
from time import sleep
import cv2 as cv
from cv2 import aruco
import numpy as np
import serial 


# Initialisation de la caméra Picamera2
print("Initialisation")

picam2 = Picamera2()
camera_config = picam2.create_preview_configuration()
picam2.configure(camera_config)
picam2.start()

##démarrage de la st
#initialisation port serie
ser = serial.Serial('/dev/ttyS0', 115200)  
#envoie s pour start
ser.write(b's') 


#dictionary to specify type of the marker
marker_dict = aruco.getPredefinedDictionary(aruco.DICT_4X4_250)
#detect the marker
param_markers = aruco.DetectorParameters()

detector = aruco.ArucoDetector(marker_dict,param_markers)

#utilizes default camera/webcam driver
cap = cv.VideoCapture(0)

#iterate through multiple frames, in a live video feed
print("Début")
while True:
    frame = picam2.capture_array()    
    if frame is None:
        print("Error: Could not read frame.")
        break
    #turning the frame to grayscale-only (for efficiency)
    gray_frame = cv.cvtColor(frame,cv.COLOR_BGR2GRAY)
    marker_corners, marker_IDs, reject = detector.detectMarkers(gray_frame)
    #getting corner of markers
    if marker_corners:
        for ids, corners in zip(marker_IDs,marker_corners):
            cv.polylines(frame,[corners.astype(np.int32)],True,(0,255,255),4,cv.LINE_AA
            )
            
            corners=corners.reshape(4,2)
            corners=corners.astype(int)
            top_right=corners[0].ravel()
            top_left=corners[1].ravel()
            bottom_right=corners[2].ravel()
            bottom_left=corners[3].ravel()
            cv.putText(
                frame,
                f"id:{ids[0]}",
                top_right,
                cv.FONT_HERSHEY_PLAIN,
                1.3,
                (200,100,0),
                2,
                cv.LINE_AA,
            )
            if ids[0] == 36:
                print("pot blanc")
            elif ids[0] == 13:
                print("pot violet")
            else: 
                print("rien à signaler")