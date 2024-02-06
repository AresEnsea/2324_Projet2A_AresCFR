/**
 * @file drv8825.h
 * Ce fichier contient l'ensemble des fonctions relatives au pilotage des 
 * drivers DRV8825 pour les moteurs pas-à-pas.
 */

#include "config.h"
#include <stdlib.h>
#include "stm32f4xx_hal.h"
#include "tim.h"


typedef struct {
    /** Numéro de la broche enable. */
    uint16_t enablePin;
    /** Pointeur vers la structure GPIO associé à la broche enable. */
    GPIO_TypeDef * enableGPIO;

    /** Numéro de la broche direction. */
    uint16_t dirPin;
    /** Pointeur vers la structure GPIO associé à la broche direction. */
    GPIO_TypeDef * dirGPIO;

    /** Timer lié à la génération du signal PWM. */
    TIM_HandleTypeDef* timer;
    /** Numéro de canal utilisé du timer. */
    uint8_t channel;
} Stepper;


/** Définit les deux sens de rotation pour les moteurs. */
typedef enum {
    /** Sense de rotation trigonométrique face à l'axe du moteur. */
    POSITIVE=1, 

    /** Sense de rotation des aiguilles d'une montre. */
    NEGATIVE=0
} StepperDirection;


/** Définit deux états pour le driver. */
typedef enum {
    /** Moteur sous prise. Le driver consomme de l'énergie. */
    ACTIVE=0,

    /** Moteur en libre rotation. Le driver ne consomme plus d'énergie. */
    PASSIVE=1
} StepperState;


/**
 * Initialise la structure Stepper.
 * @param stepper Pointeur vers la structure.
 * @param enablePin Numéro de la broche enable.
 * @param enableGPIO Pointeur vers la structure GPIO associé à la broche enable.
 * @param dirPin Numéro de la broche direction.
 * @param dirGPIO Pointeur vers la structure GPIO associé à la broche direction.
 * @param timer Timer lié à la génération du signal PWM.
 * @param channel Numéro de canal utilisé du timer.
 */
void drv8825_initialize(Stepper *stepper,
                  uint16_t enablePin, GPIO_TypeDef* enableGPIO, 
                  uint16_t dirPin, GPIO_TypeDef *dirGPIO, 
                  TIM_HandleTypeDef *timer, uint8_t channel);


/**
 * Définit la direction du moteur.
 * @param stepper Pointeur vers la structure associée au moteur.
 * @param direction Sens de rotation.
 */
void drv8825_setDirection(Stepper* stepper, StepperDirection direction);


/**
 * Met le moteur sour prise.
 * @param stepper Pointeur vers la structure associée au moteur.
 */
void drv8825_enable(Stepper* stepper);


/**
 * Met le moteur hors tension.
 * @param stepper Pointeur vers la structure associée au moteur.
 */
void drv8825_disable(Stepper* stepper);


/**
 * Définit la fréquence du signal PWM de commande du moteur.
 * @param stepper Pointeur vers la structure associée au moteur.
 * @param frequency La fréquence du signal généré.
 */
void drv8825_setPWMFrequency(Stepper* stepper, uint16_t frequency);


/**
 * Definit la vitesse du moteur à partir d'un nombre de tours par minute.
 * @param stepper Pointeur vers la structure associée au moteur.
 * @param rpm Vitesse de rotation du moteur en tours par minute.
 */
void drv8825_setRotationSpeed(Stepper* stepper, float rpm);
