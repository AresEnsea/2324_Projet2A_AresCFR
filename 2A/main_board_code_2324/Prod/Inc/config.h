/**
 * @file config.h
 * Ce fichier regroupe un grand nombre de constantes utilisées à diverses 
 * endroits dans le projet. Certaines permettent de configuer le fonctionnement
 * du robot, d'autres l'activation ou non des affichages de debogage dans la 
 * console via un port USB serie.
 */
#include <math.h>

typedef int bool;
#define true 1
#define false 0


/******************************* Robot Select ********************************/
#define ISPHOBOS
//#define ISDEIMOS


/**************************** Config Farming Mars *****************************/
#define MATCH_DURATION 100


/***************************** Config propulsion *****************************/
#define DEBUG_PROPULSION(format, args...) printf(format, ##args)
//#define DEBUG_PROPULSION(format, args...) HAL_Delay(20);

#define STEPS_PER_REV       200
#define MICROSTEPS          32

#ifdef ISPHOBOS
	#define WHEEL_RADIUS    40
	#define ENTRAXE_MOTOR   146
    #define MAX_CORRECTION  80.0 	//max angular correction
	#define MAX_MOTOR_SPEED 1000		//max speed (mm/s)
	#define K_ACCEL 30				//acceleration
	#define KP_ANGLE 500			//proportional angular correction coefficient
	#define KI_ANGLE 30				//integral angular correction coefficient
	#define MAX_INTEGRAL_CORR 75	//max integral correction
	#define KD_ANGLE 0.75				//derivative angular correction coefficient
	#define KC_ANGLE 0.1			//feed forward coefficient
	#define KD_SPEED 1000			//derivative coefficient speed derating
#endif
#ifdef ISDEIMOS
	#define WHEEL_RADIUS    27.15
	#define ENTRAXE_MOTOR   112.32
	#define MAX_CORRECTION  80
	#define MAX_MOTOR_SPEED 800
#endif


/****************************** Config odometry ******************************/
//#define DEBUG_ODOMETRY(format, args...) printf(format, ##args)
#define DEBUG_ODOMETRY(format, args...) {;}

#define TICKS_PER_REV 8192

#ifdef ISPHOBOS
	#define ODOMETRY_RADIUS  26 //26.9811 28.2
	#define ENTRAXE_ODOMETRY 275.9  //286.13 305
	#define ODOMETRY_REFRESH 0.01 //10ms
#endif
#ifdef ISDEIMOS
	#define ODOMETRY_RADIUS  26.9811 //26.9811
//27.245
	#define ENTRAXE_ODOMETRY 179.68306
#endif


/*********************************** Lidar ***********************************/

#define LIDAR_THRESHOLD 500
#define LIDAR_MAX_DISTANCE 700
#define LIDAR_TIMEOUT 1000

/******************************** Timer names ********************************/
#define R_ENCODER htim1
#define L_ENCODER htim3
#define R_MOTOR_TIMER htim8
#define L_MOTOR_TIMER htim11
