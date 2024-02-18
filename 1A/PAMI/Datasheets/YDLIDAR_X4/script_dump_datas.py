import serial
import time
# Ouverture du port série
ser = serial.Serial('/dev/ttyACM0', 9600)
time.sleep(1)
ser.flushInput()

counter = 0

# Ouverture du fichier en mode écriture texte
with open("data.hex", "w") as file:
    # Boucle pour lire et enregistrer les données
    while counter < 1000:  # Enregistrer sur 1000 réceptions de données
        # Lecture des données depuis le port série
        data = ser.read(1)  # Lecture d'un octet
        
        # Incrémenter le compteur
        counter += 1
        
        # Conversion des données en représentation hexadécimale
        hex_data = data.hex()
        
        # Écriture des données hexadécimales dans le fichier avec un saut de ligne
        file.write("0x" + hex_data + "\n")
