# LIDAR Ares v1.4

Ce programme a televerser sur le MCU du LIDAR STM32G070 permet 
d'utiliser 16 capteurs infrarouges VL53L1X pour mesurer la distance qui separe le robot des obstacles.
Les mesures et la position du capteur correspondant sont envoyees en serie a la carte de strategie du robot,
en ayant filtre les distances trop importantes.


Caracteristiques :
- Rafraichissement maximum toutes les 50ms
- 13 ROIs (1 different a chaque tournee de mesures)
- 16 Capteurs
- Communication serie a 115200 kHz
- Distance fiable entre 10cm et 1m
- Les LEDs au dessus des capteurs deconnectes clignottent a la frequence de rafraichessement


Trame :
Header 		-> Nbre de capteurs actifs
			-> Nbre de ROIs utilises
			-> Nbre de mesures envoyees
			
Contenu		-> N°capteur*NbreROIs + N°ROI + 1
			-> Distance sur 16bits (poids forts)
			-> Distance sur 16bits (poids faibles)
			
Delimiteurs -> 0xFF, 0xFF, 0xFF (debut et fin)


Pistes d'amelioration :
- Supprimer les ROIs ou en mettre seulement 2 pour obtenir une resolution de 1/32 
avec un taux de rafraichissement encore acceptable
- Regler les distances d'offset de chaque capteur (actuellement ~+5cm)
- Ajouter la possiblite pour la carte de strategie de parametrer la distance maximale d'envoi des mesures,
ou le nombre de ROIs, ou de redemarrer le lidar,
en passant par la communication serie.


Note :
- En raison du nombre de capteurs mis en parallele il faut que les levels shifters et regulateurs 
des VL53L1X soient retire sinon au dela de 8 capteurs les capteurs n'arrivent plus a repondre au MCU.