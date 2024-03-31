/** 
 * @file bezier.h
 * Un type `Bezier` pour représenter et manipuler des courbes de Bézier est 
 * défini dans ce fichier. Les strutures de ce type sont toujours passées en 
 * argument par le bias d'un pointeur.
 */
#ifndef _BEZIER_
#define _BEZIER_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vector2.h"


/**
 * Courbe de Bézier cubique. Cette courbe est représentée par quatre points.
 * La structure comprend également une LUT pour accelérer certains calculs.
 */
typedef struct {
    /** Début de la courbe. */
    Vector2 p1;

    /** Premier point de contrôle. */
    Vector2 p2;

    /** Second point de contrôle. */
    Vector2 p3;

    /** Fin de la courbe. */
    Vector2 p4;

    /** Pointeur vers la LUT. */
    Vector2* lut;

    /** Longeur de la LUT utilisée. Supérieur ou égal à deux. */
    int lutLength;
} Bezier;


/**
 * Initialise une courbe de Bézier cubique à partir des points. Initialise 
 * également une LUT dont la taille est précisée en argument.
 *
 * @param xn La coordonnée en abscisse du n-ième point.
 * @param yn La coordonnée en ordonnée du n-ième point.
 * @param lutLength La longueur de la LUT contenant les points précalculés.
 */
Bezier* bezier_new(float x1, float y1, float x2, float y2, float x3, float y3, 
                   float x4, float y4, int lutLength);


/**
 * Alloue de la mémoire pour stocker une courbe de Bézier. Elle devra être
 * initialisée via `bezier_set` avant de pouvoir être utilisable.
 */
Bezier* bezier_newEmpty();


/**
 * Modifie une courbe de Bézier cubique à partir des points. Initialise
 * également une LUT dont la taille est précisée en argument. Cette fonction
 * est utile pour modifier une courbe de Bézier sans allouer davantage de
 * mémoire.
 *
 * @param xn La coordonnée en abscisse du n-ième point.
 * @param yn La coordonnée en ordonnée du n-ième point.
 * @param lutLength La longueur de la LUT contenant les points précalculés.
 */
void bezier_set(Bezier* b, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int lutLength);


/**
 * Affiche les points qui définissent la courbe de Bézier.
 * @param b Pointeur vers une courbe de Bezier.
 */
void bezier_display(Bezier* b);


/**
 * Évalue la courbe de Bézier `b` en `t`.
 * 
 * Sur un Cortex M4, cette fonction s'exécute en 1,3 µs.
 *
 * @param b Pointeur vers une courbe de Bezier.
 * @param t Paramètre \f$t\in[0;1]\f$.
 */
Vector2 bezier_eval(Bezier* b, float t);


/**
 * Évalue la courbe de Bézier `b` en `t` approximativement grâce à la LUT (un 
 * peu plus rapide).
 * 
 * Sur un Cortex M4, cette fonction s'exécute en 0,9 µs.
 *
 * @param b Pointeur vers une courbe de Bezier.
 * @param t Paramètre \f$t\in[0;1]\f$.
 */
Vector2 bezier_evalLut(Bezier* b, float t);


/**
 * Évalue la dérivée première de la courbe de Bézier `b` en `t`. 
 * 
 * Sur un Cortex M4, cette fonction s'exécute en 1,2 µs.
 *
 * @param b Pointeur vers une courbe de Bezier.
 * @param t Paramètre \f$t\in[0;1]\f$.
 */
Vector2 bezier_deriv1(Bezier* b, float t);


/**
 * Évalue la dérivée seconde de la courbe de Bézier `b` en `t`. 
 * 
 * Sur un Cortex M4, cette fonction s'exécute en 1,0 µs.
 *
 * @param b Pointeur vers une courbe de Bezier.
 * @param t Paramètre \f$t\in[0;1]\f$.
 */
Vector2 bezier_deriv2(Bezier* b, float t);


/**
 * Évalue la courbure de la courbe de Bézier `b` en `t`, la courbure étant 
 * l'inverse du rayon de courbure. La forumle utilisée vient d'un  
 * [article wikipédia](https://en.wikipedia.org/wiki/
 * Curvature#In_terms_of_a_general_parametrization) à propos de la courbure.
 * 
 * Sur un Cortex M4, cette fonction s'exécute en 8 µs.
 * 
 * @param b Pointeur vers une courbe de Bezier.
 * @param t Paramètre \f$t\in[0;1]\f$.
 */
float bezier_curvature(Bezier* b, float t);


/**
 * Recherche le point de la courbe de Bézier `b` le plus proche du point `p` 
 * fourni en argument grâce à la LUT. Renvoit le paramètre \f$t\f$ où la 
 * distance minimum est atteinte.
 * 
 * @param b Pointeur vers une courbe de Bezier.
 * @param p Point que l'on souhaite projeter sur la courbe.
 */
float bezier_projectLut(Bezier* b, Vector2 p);


/**
 * Recherche le point de la courbe de Bézier `b` le plus proche du point `p` 
 * grâce à la LUT, puis une recherche plus fine est réalisée par dichotomie. 
 * Renvoit le paramètre \f$t\f$ où la distance minimum est atteinte.
 *
 * Pour une LUT de taille 30 et une précision de 0,01% sur le paramètre \f$t\f$,
 * cette fonction s'execute en environ 60 µs sur un Cortex M4.
 *
 * @param b Pointeur vers une courbe de Bezier.
 * @param p Point que l'on souhaite projeter sur la courbe.
 * @param precision La precision de la recherche par dichotomie. Doit être 
 * stritement positif.
 */
float bezier_project(Bezier* b, Vector2 p, float precision);

#endif
