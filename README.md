# 2324_Projet2A_AresCFR
## Introduction

Ce repository GitHub regroupe l'ensemble des projets & documents réalisés par l'association Ares pour la Coupe de France de Robotique 2024.

## 26/09/2023: Idées pour résoudre le problème mécanique 
### I. Partie mécanique : 

Des recherches sur internet nous on fait découvrir le Robot Trooper. 
Le site suivant permet de connaître ce robot : https://www.sick.com/fr/fr/sick-sensor-blog/trooper-le-robot-de-manutention-autonome-pour-le-distancage-en-horticulture-/w/blog-instar-robotics-success-story/

Ce deuxième site permet d'étudier la mécanique de celui-ci grâce à un concours CPGE : https://www.upsti.fr/espace-etudiants/annales-de-concours/topics/s2i-robot-trooper

Les méthodes utilisées par le robot Trooper sont:

* La récupération de pots et de cache-pots grâce à des “mains plates”. 
* Le stockage des pots grâce à un arc de cercle.

<center>

![My Remote Image](https://cdn.sick.com/media/content/hf0/h55/13160303034398.jpg)

Figure 1 - Robot Trooper
</center>

## 03/10/2023: 
### II. Utilisation de capteurs de fin de course :

Idées : Positionner un capteur sur chaque côté du robot afin que le contact avec une des parois de la table permette de réinitialiser l'odométrie du robot. Par dessus, positionner une pièce imprimée en 3D pour couvrir la surface totale de chaque côté à l'instar des robots aspirateurs.  

<center>

![aspirateur_robotique](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/114668487/2c2d610f-272f-42f1-89ed-1eb1d0f69897)

Figure 2 - Robot Asprirateur
</center>
                   
                   
### III. Utilisation de capteurs TOF [Time Of Flight] :

La différence entre un capteur classique et un capteur TOF est l'état actif et passif. Le capteur classique est passif, il se comporte "comme la rétine d'un oeil". Cependant, un capteur TOF est un composant actif car il mesure un genre "d'écho" de la lumière qu'il émet (il ne mesure donc pas la lumière ambiante).
Le principe de fonctionnement de ce capteur est de mesurer le temps que met la lumière à revenir au capteur. Cela permet notamment de déterminer sa distance par rapport aux objets environnants. 

<center>

![image](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/114668487/e778d1c0-ab90-4faa-b162-23a43392d48a)

Figure 3 - Capteur TOF : Fonctionnement 
</center>

### IV. Idées de résolution du problème mécanique :

<center>

![385482582_334418605664017_5041229388081065512_n](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/134090919/ff0db04e-0340-4904-bc05-9bb8c706db25)

Figure 4 - Schéma explicatif de la solution mécanique 
</center>

<center>

![image](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/114668487/fc00809c-a7c1-440f-b016-88b6b85ecbc1)


Figure 5 - Modélisation 3D des pots à soulever (présence d'une bordure au sommet du pot) 
</center>

<center>

![image](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/114668487/547c06f8-0fec-4816-8df1-8cad406a94d9)


Figure 6 - Modélisation 3D des plantes à soulever (ne présente pas de bordure)
</center>

1) La base du robot : en forme d'entonnoir pour guider les plantes et leurs pots jusqu'à l'endroit où se situe la première pince.
2) Un ascensceur à pots : À l'endroit où l'entonnoir a le plus petit diamètre, une première pince se charge de monter les pots dans l'esapace de stockage.
3) Un espace de stockage intégré au robot : une plateforme comporte plusieurs encoches afin d'accueillir les pots.
4) Différenciation entre les pots et les plantes fragiles et résistantes : Utilisation d'un capteur de couleur pour détecter la couleur des plantes et ainsi déterminer s'il s'agit d'une plante fragile ou non. Pour détecter si le contenant stocké est un pot ou une plante, 2 capteurs de proximité seront placées à 2 hauteurs différentes : le capteur en position haute détectera les plantes et celui du bas les pots. Nous voudrions donc utiliser un capteur RFID (RFID-RC522) en haut de l'ascenseur pour savoir si c'est un pot ou une plante qui est monté par la pince. Il faut donc récupérer en premier des pots pour les stocker puis récupérer des plantes afin de les poser directement dans les pots.
5) Descente des pots contenant les plantes : Une deuxième pince est située à l'arrière du robot, elle est composée de deux plaques qui se serrent autour du pot afin de les descendre de l'espace de stockage et de les déposer sur la table. 


### IV. Servomoteur ou moteur :

Les servomoteurs respectent avec précision une position angulaire donnée. Ils ont une rotation souvent limitée à 180° et ne tournent pas en permanence alors qu'à l'inverse, les moteurs ont un mouvement continu. Les servomoteurs seront donc très utiles pour le déplacement d'un bras robotisé.

## 10/10/2023

### V. Décisions liées à la partie mécanique:

 - Dans les 6 zones de stockage deux caches-pots sont empilés. Puisque nous ne savons pas si le cache-pot sera en métal ou en impression 3D, nous choisisons de palier ce problème en adoptant la méthode suivante : dépose d'une plante dans les deux caches-pots empilés et placement dans les jardinières (comptera pour 1 point).
   
 - Première idée de stratégie pour ramasser les pots : Notre but est de récupérer des caches-pots et d'en avoir toujours en stock. Nous voulons ensuite mettre les plantes dans les caches-pots déjà stockés. Par ailleurs, si nous n'avons plus la possibilité de récupérer des caches-pots alors quelques emplacements auront un diamètre adapté à ceux des plantes fragiles. Lorsqu'il n'y aura plus de caches-pots à récupérer, nous utiliserons un capteur de couleur pour détecter si le robot prend une plante fragile ou une plante résitsante. Si la plantes est résistante alors la base du robot la poussera jusqu'à la zone de dépose des plantes. Si la plante est fragile alors elle sera stocké dans les emplacements adaptés situés dans le stockage avant de les déposer dans les jardinières.
   
 - Idée finale de stratégie pour ramasser les pots: Chaque cache-pot et chaque plante, de n'importe quel type, sera ramassé par la pince liée à l'ascenseur. Le système vérifiera quel type d'objet est encerclé par la pince. Pour chaque montée d'objet, un capteur détermine si c'est un cache-pot ou une plante (résistante ou fragile). Si c'est un cache-pot, alors il est dircetement déposé dans l'espace de stockage s'il reste un emplacement vide. Si c'est une plante fragile, alors elle est déposée dans un emplacement qui contient déjà un pot. Si c'est une plante résistante, alors elle est déposée dans un emplacement vide si c'est possible, sinon elle est déposée dans un emplacement contenant un pot.
   
 - Résolution de l'éclairement des panneaux solaires: Positionnement de deux crémaillères sur le côté du robot afin d'appuyer sur le côté du panneau solaire pour le faire tourner d'un quart de tour.
   
 -  Dépot des plantes avec leurs caches-pots dans les jardinières : Une pince est située à l'arrière du robot. À l'endroit où les pots peuvent sortir de l'espace de stockage, nous plaçons une plaque en bois posée sur des rails qui avance et recule selon une direction. Les dimensions de la plaque en bois sont : $75mm \times 75mm \times 6mm$. De plus, nous plaçons une pince à 75 mm de distance de l'espace de stockage. Celle-ci va pouvoir récupérer les pots grâce à la plaque de bois qui avance.

## 17/10/2023

### VI. Informations concernant les actionneurs 

#### VI.a Servomoteur Dynamixel AX-12 :

<center>

![Dimension_AX12](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/114668487/fd9a31f6-4919-4906-8de5-4d902d7033c9)
</center>

Caractéristiques:
- Tension de fonctionnement: 9 à 12V
- Couple décrochage (N.m) : 1,52 à 12V et 1,5A
- Vitesse hors-charge: 59 tours/minute
- Vitesse: 0,196 s/60° (à 10 Vcc)
- Température opérationnelle: -5°C à 70°C
- Vitesse de communication: 7343 bps à 1 Mbps
- Compatible avec AX-12+ à l'échelle 1:1
- Rapport de réduction: 254:1
- Poids : 54,6g
- Dimensions (mm) : 32 x 50,1 x 40

Détails :
- Fonctionnement en rotation continue ou de 0 à 300°.
- Le contrôleur de ce servomoteur permet un retour d'information de la position, de la température, du couple et de la tension d'alimentation.
- Les moteurs disposent de deux connecteurs 3 broches (cordon inclus) permettant de relier plusieurs moteurs en cascade et de les utiliser ensemble.
- Vérification de la mise à zéro grâce à deux encoches.
- Idée de code : CDR2022_23/2A/Project__Ax12/Core/main

#### VI.b Mirco Servomoteur MG90S :

<center>

![MG](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/114668487/1fdad03c-f377-424a-b16b-8ded5f14ea7e)
</center>

Caractéristiques :
- Tension : 4,8 V - 6,0 V
- Vitesse : 0,10 s / 60 degrés
- Couple : 1,8 kg/cm (4,8 V)
- Température : -30 à +60
- Bande passante morte : 5usec

#### I.b Servomoteur SG90 :

<center>

![servomoteursg90](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/114668487/10ae2e94-4ac3-4459-a957-0c6edcf10ca0)
![dimension_sg90](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/114668487/fc6bb665-7202-4726-9e84-5d290d8fb4c5)
</center>

– Dimensions : 22 x 11.5 x 27 mm
– Poids : 9 g
– Tension d’alimentation : 4.8V à 6V
– Vitesse : 0.12 s / 60° sous 4.8V
– Couple : 1.2 Kg / cm sous 4.8V
– Amplitude : de 0° à 180°

Correspondance des fils de la prise de type Graupner à 3 fils :
Marron -> GND
Rouge -> 5V
Orange -> Commande PWM

Détails : exemple de code ARDU*** : https://robotix.ah-oui.org/user_docs/dos10/sg90-datasheet.pdf

## Pendant les vacances de Novembre :

Nous nous sommes focalisés sur la mécanique du projet afin d'avoir une vision globale du robot et de ses composants que nous devrons par la suite commander.
La dernière grosse partie mécanique a concevoir est la pince avant du robot qui servira à attraper les pots et à les déposer sur la table ou dans les jardinières. Celle-ci a été réalisée grâce au logiciel fusion. 

#### Première version de la pince :
<center>

![Pince_v1](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/114668487/fe7242a5-99d1-424d-b7d5-a93475979640)
</center>


#### Deuxième version de la pince :

<center>

![Pince_v2](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/114668487/6610abc2-c8f3-4e79-8543-cfbe28270fe7)
</center>


## 12/11/2023 :

Première version de la CAO et de l'assemblage de l'ensemble des pièces du robot (Utilisation avec modifications de certaines pièces des années précédentes et modélisation de nouvelles pièces).

Assemblage du robot : cette première version ne prend pas en compte la pince arrière car nous souhaitons d'abord être certain d'arriver à construire complètement une pince entièrement. Nous la dupliquerons par la suite pour la mettre à l'arrière du robot. 

#### Changement de l'attache de la pince à l'ascenseur :  

![Assemblage_Pince_V2 v38](https://github.com/AresEnsea/2324_Projet2A_AresCFR/blob/main/2A/M%C3%A9canique/CAO/Photos/assemblage_23-24_v38.png)

Création de pièces et assemblage de celles-ci avec des pièces utilisées les années passées (ex: roues/batteries/équerres) pour concevoir le robot entièrement :

<center>

![8](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/114668487/0ba9a741-baf9-45e4-96c7-05244d51a081)
</center>

## 27/11/2023:

- Finalisation de la première version de toutes les pièces du robot
- Impression de toutes les pièces afin de les tester 

## Décembre 2023:

- Modification du bord de soutien des pots. Utilisation d'une imprimante avec un plus grand plateau afin que la pièce soit imprimée en une fois pour ne pas avoir besoin de la découper en plusieurs parties. Nous avons également augmenter la hauteur de ce bord afin que la plaque en bois soit bien contrainte à rester au milieu de la pièce. Conception de pylônes de soutien. 

- Les tests de ce bord de soutien nous ont incité à agrandir son ouverture afin de laisser plus de place aux pots lors de leur sortie.  

- Création de la pièce utilisée pour faire sortir les pots de l'espace de stockage. La modification à apporter est la modification de la forme de celle-ci afin qu'elle soit identique à la forme des pots pour qu'elle soit correctement ajustée à ces derniers.  
- Nous avons également ajouté les inserts et les vis dans chaque conception afin de monter le robot entièrement.  
- Les actionneurs AX12 ont été remplacés par des petits servomoteurs SG90 pour leur taille et leur facilité de commande.

### Améliorations à réaliser:  

- Les bord du stockage sont un peu haut et certaines plantes peuvent se coincer en passant sous le stockage. La modification à apporter est la hauteur des piliers de soutien.
- Décaler la position de l'ascenseur pour laisser plus de place à la rotation des pots.
- Augmenter la taille de l'ascenseur pour éviter la collision entre les pots.
- Les roues ne touchent pas le sol il faudrat donc modifier la pièce de maintien des moteurs pas à pas (correction des trous pour l'odométrie).

