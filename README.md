# 2324_Projet2A_AresCFR
## Introduction
Ce repository GitHub regroupe l'ensemble des projets & documents réalisés par l'association Ares pour la Coupe de France de Robotique 2024.

26/09/2023: Idées pour résoudre le problème mécanique 
I. Partie mécanique: 

Des recherches sur internet nous on fait découvrir le Robot Trooper. 
Le site suivant permet de connaître ce robot : https://www.sick.com/fr/fr/sick-sensor-blog/trooper-le-robot-de-manutention-autonome-pour-le-distancage-en-horticulture-/w/blog-instar-robotics-success-story/
Ce deuxième site permet d'étudier la mécanique de celui-ci grâce à un concours post école ingénieur : https://www.upsti.fr/espace-etudiants/annales-de-concours/topics/s2i-robot-trooper

Les méthodes utilisées par le robot Trooper sont:
    * Attraper les pots et les cache pots grâce à des “mains plates”. 
    * Stocker des pots grâce à un arc de cercle.

![My Remote Image](https://cdn.sick.com/media/content/hf0/h55/13160303034398.jpg)

                     Figure 1. Robot Trooper en fonctionnement


03/10/2023: 
I. Utilisation de capteurs de fin de course:

Idée: Positionner un capteur sur chaque côté du robot. Par dessus, positionner une pièce imprimée en 3D pour couvrir la surface totale de chaque côté à l'instar des robots aspirateurs.  

![aspirateur_robotique](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/114668487/2c2d610f-272f-42f1-89ed-1eb1d0f69897)
                   
Figure 2. Robot Asprirateur
                   
II. Utilisation de capteurs TOF [Time Of Flight]

La différence entre un capteur classique et un capteur TOF est l'état actif et passif. L capteur classique est passif, il se comporte "comme la rétine d'un oeil".Un capteur ToF est un composant actif car il mesure un "genre d'écho" de la lumière qu'il émet (il ne mesure donc pas la lumière ambiante)
Le principe de fonctionnement de ce capteur est : la mesure du temps que met la lumière à revenir au capteur. Cela permet de déterminer sa distance aux objets. 


![image](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/114668487/e778d1c0-ab90-4faa-b162-23a43392d48a)

Figure 3. Cpateur TOP-Fonctionnement 

III. Idées pour résoudre le problème mécanique

![385482582_334418605664017_5041229388081065512_n](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/134090919/9884692e-69b4-44f8-ae58-f4c1bc62c0ef)

1) La base du robot : en forme d'entonnoir pour forcer les pots de pleurs et les fleurs à aller à l'endroit où on souhaite
2) Un ascensceur à pots : à l'endroit où l'entonnoir a le plus petit diamètre, une première pince  se charge de monter les pots sur la table.
3) Un espace de stockage au-dessus du robot : un disque comporte plusieurs trous afin d'accueillir les pots.
4) Différenciation entre les pots et les plantes : utilisation de détecteurs de tag RFID. Seuls les pots de fleurs contiennent des tag RFID. Nous voudrions donc utiliser un capteur RFID (RFID-RC522) en haut de l'ascenseur pour savoir si c'est un pot ou une plante qui est montée par la pince. Il faut donc récupérer en premier des pots pour les stocker puis récupérer des plantes afin de les poser directement dans les pots.
5) Descente des pots contenant des plantes : une deuxième pince est située à l'arrière du robot, elle est composée de deux plaques qui se serrent autour du pot.




