/** \file vector2.h
 * Un type `Vector2` pour représenter et manipuler des points du plan est défini 
 * dans ce fichier. Comme cette structure ne contient que deux champs, les 
 * variables de ce type sont directement passées en argument, sans indirection.
 * 
 * Néanmoins, les fonctions à effet de bord prennent naturellement un pointeur 
 * vers la struture. Cela permet de bien distinguer les arguments voués à être 
 * uniquement lus de ceux qui sont également voués à être modifiés.
 */

#ifndef _VECTOR2_
#define _VECTOR2_

#include <math.h>
#include <stdio.h>

/** Représente un vecteur du plan grâce à deux `float`. */
typedef struct {
    float x;
    float y;
} Vector2;

/**
 * Renvoit un nouveau vecteur de coordonnées \f$(x, y)\f$.
 * 
 * @param x L'abscisse du point.
 * @param y L'ordonnée du point.
 */
Vector2 vector2_new(float x, float y);

/**
 * Affiche les coordonnées du vecteur `u` via `printf`.
 * 
 * @param u Le vecteur à afficher.
 */
void vector2_display(Vector2 u);

/**
 * Renvoit la norme de `u`.
 * 
 * @param u Le vecteur dont la norme est calculée.
 */
float vector2_norm(Vector2 u);

/**
 * Rennvoit l'angle formé par le vecteur `u` avec l'horizontale.
 * 
 * @param u Le vecteur dont on calcule l'angle.
 */
float vector2_angle(Vector2 u);

/**
 * Revoit la distance entre `u` et `v` (norme de la différence). L'ordre n'a pas
 * d'importance.
 * 
 * @param u Un premier vecteur.
 * @param v Un second vecteur.
 */
float vector2_dist(Vector2 u, Vector2 v);


/**
 * Revoit la distance au carré entre `u` et `v` (norme de la différence). Cette
 * fonction est utile pour comparer deux disatnces en évitant de calculer les 
 * racines carrées. Ces dernières ne changent pas le sens des inégalités.
 * 
 * @param u Un premier vecteur.
 * @param v Un second vecteur.
 */
float vector2_dist2(Vector2 u, Vector2 v);


/**
 * Calcule la somme de deux vecteur `u` et `v`.
 * 
 * @param u Un premier vecteur.
 * @param v Un second vecteur.
 */
Vector2 vector2_sum(Vector2 u, Vector2 v);

/**
 * Calcule la différence `u - v` pour deux vecteur `u` et `v`.
 * 
 * @param u Le premier vecteur.
 * @param v Le second vecteur.
 */
Vector2 vector2_diff(Vector2 u, Vector2 v);

/**
 * Calcule le produit scalaire de deux vecteurs `u` et `v`.
 * 
 * @param u Un premier vecteur.
 * @param v Un second vecteur.
 */
float vector2_dot(Vector2 u, Vector2 v);

/**
 * Calcule le produit en croix de deux vecteurs `u` et `v`. Cela correspond à 
 * l'aire (algébrique) du paralélogramme formé à partir des points \f$0\f$, 
 * \f$u\f$, \f$u+v\f$ et \f$v\f$.
 * 
 * @param u Un premier vecteur.
 * @param v Un second vecteur.
 */
float vector2_cross(Vector2 u, Vector2 v);

/**
 * Normalise le vecteur donné en entrée. Fonction à effet de bord.
 * 
 * @param u Pointeur vers le vecteur à normaliser. 
 */
void vector2_normalize(Vector2* u);

/**
 * Multiplie le vecteur `*u` par le scalaire `k`. Fonction à effet de bord.
 * 
 * @param u Pointeur vers le vecteur dont on change la longueur.
 * @param k Scalaire.
 */
void vector2_scale(Vector2* u, float k);

/**
 * Applique une rotation de `a` radians au vecteur `*u`. Fonction à effet de 
 * bord.
 * 
 * @param u Pointeur vers le vecteur dont on change l'angle.
 * @param a Angle en radians.
 */
void vector2_rotate(Vector2* u, float a);

/**
 * Applique une rotation de 90° au vecteur `*u`. L'effet est equivalent à 
 * l'appel de `vector2_rotate` avec `a` \f$ = \pi/2\f$ mais évite de calculer 
 * \f$\cos(\pi/2)\f$ et \f$\sin(\pi/2)\f$. Fonction à effet de bord.
 * 
 * @param u Pointeur vers le vecteur dont on change l'angle.
 */
void vector2_rotate90(Vector2* u);

#endif
