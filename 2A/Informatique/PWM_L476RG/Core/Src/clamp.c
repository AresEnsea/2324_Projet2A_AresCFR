/**
  ******************************************************************************
  * @file           : clamp.c
  * @brief          : Function to control the clamp motion
  * @author         : Ousmane THIONGANE
  ******************************************************************************
*/

#include "clamp.h"

#define ANGLE TIM3->CCR1
#define MOTION_FACTOR (60/18)

extern TIM_HandleTypeDef htim3;

//Uncomment the 'while' loop to make the commande absolute

void reach_goal(int goal){
	//while(abs((int)ANGLE - goal) >= 2){
		if(ANGLE < goal){
			ANGLE += MOTION_FACTOR;
			HAL_Delay(10);
		}
		else{
			ANGLE -= MOTION_FACTOR;
			HAL_Delay(10);
		}
	//}
	return;
}


