# Coupe de France de Robotique 2024 : les PAMI
> A l'occasion de la Coupe de France de Robotique 2024 : "Farming Mars", nous avons décidé de créer plusieurs PAMI (Petits Automatates Motorisés indépedants) qui devront réaliser des actions simples afin de rapporter des points à l'équipe de l'ENSEA  en assistant le robot principal. Ces PAMI doivent pouvoir se déplacer sur le plateau de la Coupe et être en mesure de détécter les robots adverses pour être homologués 

# Equipe
> L'équipe PAMI est composé de 4 élèves de 1ère année :
> -Antoine Lemarignier
> -Ewan Zarha Thenault
> -Nathan Bainard
> -Mateo Gomes

# Journal de bord
>-Déroulé séance par séance

## Séance 1
>-installation machine virtuelle Ubuntu + début configuration Pi4
>-dessin du PAMI
>-verification fonctionnement lidar
>-utilisation github (push/pull/clone)

## Séance 2
>-creation organigramme
>-suite configuration machine virtuelle (configuration réseau à continuer en dehors de la séance)
>-code écran (vérification)
>-recherche modules récepteur émeteur 433mHz

## Séance 3
>-changements schématique
>-vérification moteur : fonctionnement partiel

## Séance 4
>-1ère version routage
>-vérification moteur : incomplet

## Séance 5
>-nouvelle version pcb
>-bon fonctionnement moteurs après changement de driver 
>-début écriture du code moteur

## Séance 6
>-pcb : soudage des composants

## Séance 7
>-fin soudage composants et test avec moteurs (les pcb marchent bien)

## Séance 8
>-Code final qui doit fusionner le code du Lidar des roues et de l'écran
>-Méca : Impression des deux autres modèles 3D pour

## Séance 9
Après Coupe
>-Vision : essai concluant avec tag aruco
>-Complément Githhub

## Séance 10
>-Derniers essais avant démonstration 

# Livrables
## PCB
> Présentation du schéma (grandes lignes) + PCB
![image](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/88663397/359529a3-b0eb-448c-b854-ca4c4fa7e357)
![image](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/88663397/d61f68f4-0344-420d-ba32-260c9ede2a29)

## Code
> Architecture du code
> ![image](https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/88663397/58c2daaa-fe78-4746-8fa8-1725627ea0fe)

## Getting Started Guide
> Ici le manuel d'utilisation simple et pratique !
> Le pami fonctionne de la manière suivante : après démarrage avec le switch (allume les leds rouges),
vérifier qu'une tirette (ou un pont) est bien positionnée sur les deux pins du connecteur J102,  appuyer sur le SW NRST pour initialiser l'écran, une fois fait, le BTN2 permet de changer de stratégie parmi celles définies dans "strategy.c" dans le projet STM32CubeIDE, enfin pour démarrer le pami simplement enlever la tirette (ce qui aura pour effet de démarrer le robot après un délai de 90s ou bien appuyer sur le bouton du millieu (BTN1) pour le démarrer immédiatement.

## Rendu final
>Video ici de votre projet :
> - https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/88663397/23594f17-0ef2-46ef-a65a-15afedc95028
> - https://github.com/AresEnsea/2324_Projet2A_AresCFR/assets/88663397/61659872-7cb5-43fb-a910-f1500b88333c


