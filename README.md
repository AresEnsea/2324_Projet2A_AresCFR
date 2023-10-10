# 2324_Projet2A_AresCFR
## Introduction
Ce repository GitHub regroupe l'ensemble des projets & documents réalisés par l'association Ares pour la Coupe de France de Robotique 2024.

## 26/09/2023: Idées pour résoudre le problème mécanique 
### I. Partie mécanique : 

Des recherches sur internet nous on fait découvrir le Robot Trooper. 
Le site suivant permet de connaître ce robot : https://www.sick.com/fr/fr/sick-sensor-blog/trooper-le-robot-de-manutention-autonome-pour-le-distancage-en-horticulture-/w/blog-instar-robotics-success-story/

Ce deuxième site permet d'étudier la mécanique de celui-ci grâce à un concours CPGE : https://www.upsti.fr/espace-etudiants/annales-de-concours/topics/s2i-robot-trooper

Les méthodes utilisées par le robot Trooper sont:
    * Attraper les pots et les cache-pots grâce à des “mains plates”. 
    * Stocker des pots grâce à un arc de cercle.

![My Remote Image](https://cdn.sick.com/media/content/hf0/h55/13160303034398.jpg)

Figure 1. Robot Trooper

## 03/10/2023: 
### I. Utilisation de capteurs de fin de course :

Idée: Positionner un capteur sur chaque côté du robot. Par dessus, positionner une pièce imprimée en 3D pour couvrir la surface totale de chaque côté à l'instar des robots aspirateurs.  

![aspirateur_robotique](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/114668487/2c2d610f-272f-42f1-89ed-1eb1d0f69897)
                   
Figure 2. Robot Asprirateur
                   
### II. Utilisation de capteurs TOF [Time Of Flight] :

La différence entre un capteur classique et un capteur TOF est l'état actif et passif. Le capteur classique est passif, il se comporte "comme la rétine d'un oeil". Cependant, un capteur TOF est un composant actif car il mesure un "genre d'écho" de la lumière qu'il émet (il ne mesure donc pas la lumière ambiante).
Le principe de fonctionnement de ce capteur est : la mesure du temps que met la lumière à revenir au capteur. Cela permet de déterminer sa distance aux objets. 

![image](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/114668487/e778d1c0-ab90-4faa-b162-23a43392d48a)

Figure 3. Cpateur TOF-Fonctionnement 

### III. Idées pour résoudre le problème mécanique :
![385482582_334418605664017_5041229388081065512_n](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/134090919/ff0db04e-0340-4904-bc05-9bb8c706db25)

 Figure 4. Schéma explicatif de la solution mécanique 


 ![image](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/114668487/fc00809c-a7c1-440f-b016-88b6b85ecbc1)


Figure 5. Modélisation 3D des pots à soulever [présence d'une bordure]


![image](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/114668487/547c06f8-0fec-4816-8df1-8cad406a94d9)


Figure 6. Modélisation 3D des plantes à soulever [ne présente pas de bordure]
 
1) La base du robot : en forme d'entonnoir pour forcer les pots de plantes et les plantes à aller à l'endroit où se situe la première pince.
2) Un ascensceur à pots : à l'endroit où l'entonnoir a le plus petit diamètre, une première pince  se charge de monter les pots dans l'esapace de stockage.
3) Un espace de stockage au-dessus du robot : une plateforme comporte plusieurs trous afin d'accueillir les pots.
4) Différenciation entre les pots et les plantes : utilisation de détecteurs de tag RFID. Seuls les pots de fleurs contiennent des tag RFID. Nous voudrions donc utiliser un capteur RFID (RFID-RC522) en haut de l'ascenseur pour savoir si c'est un pot ou une plante qui est monté par la pince. Il faut donc récupérer en premier des pots pour les stocker puis récupérer des plantes afin de les poser directement dans les pots.
5) Descente des pots contenant des plantes : une deuxième pince est située à l'arrière du robot, elle est composée de deux plaques qui se serrent autour du pot afin de les descendre de l'espace de stockage et de les poser sur la table. 


### IV. Servomoteur ou moteur :

Les servomoteurs respectent avec précision la position angulaire. Ils ont une rotation souvent limitée à 180° et ne tournent pas en permanence alors qu'à l'inverse, les moteurs ont un mouvement continu. Les servomoteurs seront donc très utiles pour le déplacement d'un bras robotisé.

10/10/2023

I. Décisions liées à la partie mécanique:
 - Dans les 6 zones de stockage deux caches-pots sont empilés. Puisque nous ne savons pas si le cache-pot sera en métal ou en impression 3D, nous choisisons de palier ce problème en adoptant la méthode suivante : pose d'une plante dans les deux caches-pots empilés et placement dans les jardinières (comptera pour 1 point).
 - Première idée de stratégie pour ramasser les pots : Notre but est de récupérer des caches-pots et d'en avoir toujours en stock. Nous voulons mettre les plantes dans les caches-pots déjà stockés. Par ailleurs, si nous n'avons plus la possibilité de récupérer des caches-pots alors quelques emplacements auront un diamètre adapté à ceux des plantes fragiles. Lorsqu'il n'y aura plus de caches-pots à récupérer, nous utiliserons un capteur de couleur pour détecter si le robot prend une plante fragile ou une plante résitsante. Si la plantes est résistante alors la base du robot la poussera jusqu'à la zone de dépose des plantes. Si la plante est fragile alors elle sera stocké dans les emplacements adaptés situés dans le stockage avant de les déposer dans les jardinières.
 - Idée finale de stratégie pour ramasser les pots:
 - Résolution de l'éclairement des panneaux solaires: positionnement de deux crémaillères sur le côté du robot afin d'appuyer sur le côté du panneau solaire afin de le faire tourner d'un quart de tour.
 -  Dépot des plantes avec leurs caches-pots dans les jardinières:


