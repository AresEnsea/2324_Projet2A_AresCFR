/**
 * @file robot.h
 * Ce fichier définit une structure Robot permettant de stocker les états
 * du robot ainsi que des structures liées au fonctionnement de certains de ses
 * systèmes.
 */
#ifndef _ROBOT_
#define _ROBOT_

#include "vector2.h"
#include "drv8825.h"


/** Définit les deux couleurs d'équipe. */
typedef enum {
    /** Jaune, gacuhe. */
    YELLOW=0,

    /** Violet, droite. */
    PURPLE=1
} Team;


/** 
 * La structure Robot permet de stocker les états du robot ainsi que des 
 * structures liées au fonctionnement de certains de ses systèmes.
 */
typedef struct {
    /** Vecteur représentant la position du robot en millimètres. */
    Vector2 position;

    /** Angle du robot en radians. */
    float angle;

    /** Stucture associée au moteur propulsif gauche. */
    Stepper* leftMotor;
    float leftSpeed;

    /** Stucture associée au moteur propulsif droit. */
    Stepper* rightMotor;
    float rightSpeed;

    /** Vitesse mesurée par les codeuses. */
    float measuredSpeed;

    /** Variables pour attendre la réalisation des actions à l'arrêt. */
    bool waitingForOnSiteAction;

    /** Variables pour attendre la réalisation des actions en mouvement. */
    bool waitingForOnMoveAction;

    /** Couleur d'équipe pour le match. */
    Team team;
} Robot;


/**
 * Variable globale représentant le robot.
 */
extern Robot robot;

#endif
