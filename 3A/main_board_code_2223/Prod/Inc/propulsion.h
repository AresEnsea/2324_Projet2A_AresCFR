/** 
 * @file propulsion.h
 */
#ifndef _PROPULSION_
#define _PROPULSION_

#include "control.h"
#include "gpio.h"
#include "tim.h"
#include "robot.h"
#include "bezier.h"
#include <stdio.h>


/** Définit les sens de parcours pour le robot. */
typedef enum {
    /** Sense de rotation trigonométrique face à l'axe du moteur. */
    FORWARD=1,

    /** Sense de rotation des aiguilles d'une montre. */
    BACKWARD=-1
} Direction;


/**
 * Renvoie un angle entre -pi et pi à partir de l'angle fourni.
 */
float standardAngle(float angle);


/**
 * Initialse les deux moteurs pas-à-pas du bloc de propulsion.
 */
void propulsion_initialize();


/**
 * Met sous tension les moteurs pas-à-pas du bloc de propulsion.
 */
void propulsion_enableMotors();


/**
 * Met hors tension des moteurs pas-à-pas. Ils tournent alors librement.
 */
void propulsion_disableMotors();


/**
 * Configure la vitesse absolue et le sens des moteurs en fonction des deux
 * vitesses signées données en argument.
 * @param left Vitesse du moteur gauche.
 * @param right Vitesse du moteur droit.
 * @param k courbure, permet de ralentir dans les virages.
 */
void propulsion_setSpeeds(float left, float right, float k);


/**
 * Simule la présence de l'odometrie. La position du robot est mise à jour en
 * fonction de la vitesse des deux moteurs et d'autres paramètres du robot.
 * 
 * Cette fonction est vouée à être appelée depuis un timer. 
 * 
 * @param dt Durée passée à la vitesse actuelle (approximativement). Durée entre
 * deux appels de cette fonction. Période d'interruption.
 */
void propulsion_updatePosition(float dt);


/**
 * Définit la vitesse des moteurs de sorte que le robot suive le meilleur arc de
 * cercle approximant le point de la courbe Bézier le plus proche du robot.
 * 
 * Appelée à intervalles réguliers, cette fonction fait suivre au robot la 
 * courbe de Bézier fournie en argument.
 * 
 * Remarque : le robot doit se trouver au début de la courbe et dans la bonne
 * orientation pour que la fonction ait l'effet souhaité.
 * 
 * @param b Pointeur vers la courbe de Bézier à suivre. 
 */
float propulsion_followBezier(Bezier* b, Direction dir, float initialSpeed, float finalSpeed, bool reverse);

#endif
