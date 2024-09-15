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

# Démarrage de la STM32
# Initialisation port série
ser = serial.Serial('/dev/ttyS0', 115200)  
# Envoi 's' pour start
ser.write(b's') 

# Dictionnaire pour spécifier le type du marqueur
marker_dict = aruco.getPredefinedDictionary(aruco.DICT_4X4_250)
# Paramètres de détection des marqueurs
param_markers = aruco.DetectorParameters()

detector = aruco.ArucoDetector(marker_dict, param_markers)

# Début de la capture vidéo
print("Début")
while True:
    frame = picam2.capture_array()    
    if frame is None:
        print("Error: Could not read frame.")
        break
    
    # Conversion du frame en niveaux de gris
    gray_frame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    marker_corners, marker_IDs, reject = detector.detectMarkers(gray_frame)
    
    # Détection des coins des marqueurs
    if marker_corners:
        for ids, corners in zip(marker_IDs, marker_corners):
            cv.polylines(frame, [corners.astype(np.int32)], True, (0,255,255), 4, cv.LINE_AA)
            
            corners = corners.reshape(4, 2)
            corners = corners.astype(int)
            top_right = corners[0].ravel()
            top_left = corners[1].ravel()
            bottom_right = corners[2].ravel()
            bottom_left = corners[3].ravel()
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
            
            # Détection de la position du tag Aruco
            marker_center_x = (top_right[0] + top_left[0] + bottom_right[0] + bottom_left[0]) // 4
            frame_center_x = frame.shape[1] // 2
            
            if ids[0] == 36:
                if marker_center_x > frame_center_x:
                    print("pot blanc gauche")
                    ser.write(b'pot blanc gauche')  # Envoi de la commande à la STM32
                else:
                    print("pot blanc droite")
                    ser.write(b'pot blanc droite')  # Envoi de la commande à la STM32
                
            elif ids[0] == 13:
                if marker_center_x > frame_center_x:
                    print("pot violet gauche")
                    ser.write(b'pot violet gauche')  # Envoi de la commande à la STM32
                else:
                    print("pot violet droite")
                    ser.write(b'pot violet droite')  # Envoi de la commande à la STM32
            else: 
                print("rien à signaler")

ser.close()