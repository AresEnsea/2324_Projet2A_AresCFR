# Journal de Bord d'Ares 
Ce dossier constitue le journal de bord d'Ares, retraçant les réalisations hebdomadaires de l'association.
## Tutoriels
Tous les tutoriels et les méthodes de réalisations concernant la Coupe de France de Robotique 2024 sont regroupés sur le wiki de l'association : https://wiki.ares.asso-ensea.fr/index.php/Coupe_de_France_de_Robotique

## Résumés Hebdomadaires 
### Mardi 19 Septembre (J-232)
- Disscussions et réflexions autour du projet
- Répartition des tâches
- Élaboration de la présentation du projet

### Mardi 26 Septembre (J-225)
- Présentation du projet, des solutions envisagées et de la stratégie. Réflexion sur le diagramme d'architecture
- Installation de ROS2 et réalisation du tutoriel
- Inscription d'Ares à la Coupe de France de Robotique
- Rédaction de la démarche sur le wiki : https://wiki.ares.asso-ensea.fr/index.php/Introduction_%C3%A0_ROS_2
- Rédaction du tutoriel d'utilisation de GitHub pour les premières années (voir "Tutoriel GitHub.pdf" à la racine du repositary)

### Mardi 3 octobre (J-218)
- Poursuite de l'apprentissage de ROS2, assimilation des différentes notions (Nodes, topics, services, actions)
- Étude du fonctionnement de l'écran STM32F746 Discovery
- Rédaction du cahier des charges de la statégie d'évitement : Méthode des Points de Sûreté (MPDS)
- Création de l'architecture du système : fichier conçu sur l'outil drawio (fichier architecture.drawio). Réflexion concernant les composants à utiliser, comparaison entre différents paramètres
- Résolution du problème mécanique. Description de la solution dans le readme principal (2 pinces, un ascenseur, un espace de stockage)

### Mardi 10 octobre (J-211)
- Élaboration de la machine à états de la MPDS
- Observations sur le fonctionnement du lidar TOF
- Étude du code pour le simulateur : Correction de la superposition entre la grille et l'image de la table de jeu, dont le décalage rendait les coordonnées fausses
- Elaboration plus précise de la stratégie mécanique
- Amélioration de l'architecture du système : création de la partie asservissement (ramassage et lâchage des objets)
- Création des conceptions 3D des pièces mécaniuques (les 2 pinces ainsi que l'ascenseur et la base du robot)
- Création de l'organigramme des packages ROS2, étude du Hardware pour le Robot ROS2 avec des phidgets.
- Commande des modules phidgets et découverte des librairies associés. 


### Mardi 17 octobre (J-204)
- Intégration du simulateur au site web de l'association afin de le rendre accessible à tous + correction mineure de l'exportation du code C
- Présentation de projet n°2 : Logigramme d'asservissement et diagrammes d'architecture du Robot, ROS 2 et logicielle
- Début de création de l'IHM pour la MPDS : UI réalisée avec PyQt3
- Finalisation des choix de dimensions pour les pièces mécaniques
- Recherches au sujet des capteurs de couleurs
- Ajout sur le wiki du tutoriel pour calibrer l'odométrie du robot : https://wiki.ares.asso-ensea.fr/index.php/Robot_STM32_%E2%80%93_Calibration_de_l%27odom%C3%A9trie
- Réalisation de la mécanique des roues + odométrie de Hugway. Ajout des modules phidgets, modélisation 3D des supports de codeurs et roue. 

### Mardi 24 octobre (J-197)
- Étude du code des années passées
- Installation de la nouvelle table
- Ajout de tutoriels et d'informations supplémentaires sur le wiki
- Démarrage de la rédaction du cahier des charges à donner aux premières années pour les PAMI
- Flash de la Raspberry avec docker
- Choix d'utiliser ROS2 Humble qui est supporté jusqu'en 2027 et connexion des modules phidgets aux composants de Ugway

### Mardi 7 novembre (J-183)
- Installation de ROS2 sur Ubuntu sur PC, prise en main de Gazebo, début de courbes avec phidgets desktop version...
- KiCad de la carte de puissance pour tout brancher à des batteries pour Hugway
- Correction du wiki avec l'ajout de ROS2 
- Création de la CAO de la pince avant du robot pour attraper les pots et les déposer sur la table ou dans les jardinières

### Mardi 14 novembre (J-176)
- Présentation de projet n°3 : CAO du Robot, refonte de la statégie d'évitement pour STM32, Avancement Robot Ugway (ROS2), Analyse des cartes électroniques
- Conversion de la stratégie d'évitement (Python -> C)
- Présentation de projet n°3 : CAO du Robot, refonte de la stratégie d'évitement pour STM32, Avancement Robot Ugway (ROS2), Analyse des cartes électroniques 

### Mardi 28 novembre (J-162)
- Création d'un package ROS2 pour les capteurs TOF VL53L1X
- Tentative de contact des ingénieurs d'Instar Robotics
- Essai de fonctionnement du moteur avec ROS2

### Mardi 5 décembre (J-155)
- Test de fonctionnement de la pince pour attraper les plantes
- Alimentaiton du wiki d'Ares - Comment faire fonctionner un signal PWM sur STM32 : https://wiki.ares.asso-ensea.fr/index.php/G%C3%A9n%C3%A9rer_des_signaux_PWM_avec_STM32_Cube_IDE

### Mardi 12 décembre (J-148)
- Test de fonctionnement des capteurs TOF en ROS2

### Mardi 19 décembre (J-141)
- 

### Lundi 25 décembre (J-135)
- Test de fonctionnement du capteur de couleur TCS3200

### Mardi 26 décembre (J-134)
- Calibration du capteur de couleur, finalisation du code
- Analyse du code de fonctionnement des roues motrices du robot
- Finalisation du code de la pince pour attraper les pots et les plantes

### Dimanche 31 Décembre (J-129)
- Rédaction du Dockerfile pour l'environnement ROS2
- Récupération du code de fonctionnement des capteurs TOF
- Rédaction du tutoriel (partie 1) sur l'installation de Docker sur Raspberry : https://wiki.ares.asso-ensea.fr/index.php/Introduction_%C3%A0_Docker#Mise_en_place_de_l%27environnement
- Rédaction du tutoriel (partie 2) sur les images et les conteneurs Docker : https://wiki.ares.asso-ensea.fr/index.php/Images_et_conteneurs

### Lundi 1 Janvier (J-128)
- Bonne année !
- Rédaction du tutoriel (partie 3) sur la création d'un Dockerfile : https://wiki.ares.asso-ensea.fr/index.php/Cr%C3%A9ation_d%27un_Dockerfile

### Vendredi 5 Janvier (J-124)
- Prise de contact avec l'ancien réalisateur du code du robot/simulateur
- Récupération du code de la première version du simulateur

### Vendredi 12 Janvier (J-117)
- Rendez-vous avec le réalisateur du code du robot/simulateur

### Mardi 16 Janvier (J-113)
- Présentation de projet n°4 : Récapitulatif des réalisations du semestre passé et plannification des missions pour les semaines à venir
- Étude de fonctionnement des servomoteurs Dynamixel XL-320

### Mardi 23 Janvier (J-106)
- Changement des pièces du robot pour s'addapter au xl-320
- Test du capteur de couleurs
- Réalisation du schématique de la carte mère
- Test des nouvelles pièces imprimées  

### Jeudi 25 Janvier (J-104)
- Match amical avec l'association de robotique Robotium

### Mardi 30 Janvier (J-99)
-

### Mardi 6 Février (J-92)
-

### Mardi 27 Février (J-71)
-

### Mardi 5 Mars (J-64)
-

### Mardi 12 Mars (J-57)
-

### Mardi 19 Mars (J-50)
-

### Mardi 26 Mars (J-43)
-

### Mardi 2 Avril (J-36)
-
