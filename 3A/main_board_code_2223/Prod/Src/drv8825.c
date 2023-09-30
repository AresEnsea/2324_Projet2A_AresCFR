#include "drv8825.h"


void drv8825_initialize(Stepper *stepper, uint16_t enablePin,
                  GPIO_TypeDef* enableGPIO, uint16_t dirPin, 
                  GPIO_TypeDef *dirGPIO, TIM_HandleTypeDef *timer, 
                  uint8_t channel) {
	stepper->enablePin = enablePin;
	stepper->enableGPIO = enableGPIO;

	stepper->dirPin = dirPin;
	stepper->dirGPIO = dirGPIO;

	stepper->timer = timer;
	stepper->channel = channel;
}


void drv8825_setDirection(Stepper *stepper, StepperDirection direction) {
	HAL_GPIO_WritePin(stepper->dirGPIO, stepper->dirPin, (uint8_t) direction);
}


void drv8825_enable(Stepper *stepper) {
	HAL_GPIO_WritePin(
		stepper->enableGPIO, 
		stepper->enablePin, 
		(uint8_t) ACTIVE
	);
}


void drv8825_disable(Stepper *stepper) {
	HAL_GPIO_WritePin(
		stepper->enableGPIO, 
		stepper->enablePin,
		(uint8_t) PASSIVE
	);
}


void drv8825_setPWMFrequency(Stepper* stepper, uint16_t frequency) {
	/************************************************
	 * nous modifions ARR pour modifier la période  *
	 * pour cela nous utilisons la formule suivante *
	 *                                              *
	 * freq = (clock)/{(PSC+1)(ARR+1)})             *
	 *												*
	 * clock = 180Mhz   PSC = 179                   *
	 * ARR = la valeur que l'on souhaite appliquer  *
	 ************************************************/
	if (frequency != 0) {
		stepper->timer->Init.Prescaler = 179;
		stepper->timer->Init.Period = (uint32_t)1000000/frequency;
	} else {
		stepper->timer->Init.Prescaler = 0xFFFE;
		stepper->timer->Init.Period = 0xFFFE;
	}
	/************************************************
	 * si l'initialisation du timerc'est bien passé *
	 ************************************************/
	if (HAL_TIM_Base_Init(stepper->timer) != HAL_OK) {
		//nous affichons l'erreur qui c'est produit
		Error_Handler();
	}

	/******************************************************
	 * si l'initialisation du signal PWM c'est bien passé *
	 ******************************************************/
	if (HAL_TIM_PWM_Init(stepper->timer) != HAL_OK) {
		//nous affichons l'erreur qui c'est produit
		Error_Handler();
	}

	/**********************************
	 * nous déclanchons le signal PWM *
	 **********************************/
	HAL_TIM_PWM_Start(stepper->timer, stepper->channel);

	/****************************************
	 * nous configurons le rapport cyclique *
	 * pour qu'il soit à 50%                *
	 ****************************************/
	switch (stepper->channel) {
		case (TIM_CHANNEL_1):
			stepper->timer->Instance->CCR1 = (50*stepper->timer->Init.Period)/100;
			break;
		case (TIM_CHANNEL_2):
			stepper->timer->Instance->CCR2 = (50*stepper->timer->Init.Period)/100;
			break;
		case (TIM_CHANNEL_3):
			stepper->timer->Instance->CCR3 = (50*stepper->timer->Init.Period)/100;
			break;
		case (TIM_CHANNEL_4):
			stepper->timer->Instance->CCR4 = (50*stepper->timer->Init.Period)/100;
			break;
	}
}


void drv8825_setRotationSpeed(Stepper *stepper, float rpm) {
	uint16_t f = (rpm / 60) * STEPS_PER_REV * MICROSTEPS;
	drv8825_setPWMFrequency(stepper, f);
}
