#ifndef XL320_H_
#define XL320_H_

#include "stm32f3xx_hal.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>

#define TRUE 1
#define FALSE 0

#define STEP_ANGLE 0.293255132
#define TORQUE_PERCENT 0.09775171065
#define STEP_SPEED 0.1114369501

#define SIZE_WRITE_8 8
#define SIZE_WRITE_16 9
#define SIZE_REQUEST_READ_8 8
#define SIZE_REQUEST_READ_16 8
#define SIZE_GET_READ_8 7
#define SIZE_GET_READ_16 8
#define SIZE_REQUEST_PING 6
#define SIZE_PING 11

#define BR_9600 0
#define BR_57600 1
#define BR_115200 2
#define BR_1M 3

#define WHEEL_MODE 1
#define JOINT_MODE 2

#define OFF 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define VIOLET 5
#define CYAN 6
#define WHITE 7


enum XL320Instruction {
    XL320_Ping = 1,
    XL320_Read,
    XL320_Write,
    XL320_RegWrite,
    XL320_Action,
    XL320_Reset,
    XL320_Reboot = 8,
	XL320_Clear = 10,
    XL320_ControlTableBackup = 20

};

enum XL320EEPROMRegister {
    XL320_REG_ModelNumber = 0,
    XL320_REG_FirmwareVersion = 2,
    XL320_REG_ID,
    XL320_REG_BaudRate,
    XL320_REG_DelayTime,
    XL320_REG_CWAngleLimit,
    XL320_REG_CCWAngleLimit = 8,
	XL320_REG_ControlMode = 11,
    XL320_REG_Temperature = 12,
    XL320_REG_MinVoltage,
    XL320_REG_MaxVoltage,
    XL320_REG_MaxTorque,
    XL320_REG_Status = 17,
    XL320_REG_Shutdown
};

enum XL320RAMRegister {
    XL320_REG_TorqueEnable = 24,
    XL320_REG_LED_Enable,
	XL320_REG_D_Gain = 27,
	XL320_REG_I_Gain,
	XL320_REG_P_Gain,
	XL320_REG_GoalPosition,
	XL320_REG_MovingSpeed = 32,
    XL320_REG_TorqueLimit = 35,
    XL320_REG_PresentPosition = 37,
    XL320_REG_PresentSpeed = 39,
    XL320_REG_PresentLoad = 41,
    XL320_REG_PresentVoltage = 45,
    XL320_REG_PresentTemperature,
    XL320_REG_Registered = 47,
    XL320_REG_Moving = 49,
    XL320_REG_ErrorStatus,
    XL320_REG_Punch
};

/**
 * @brief XL320 : Structure contenant l'adresse et le baudrate du module
 */

typedef struct XL320{
    UART_HandleTypeDef* UART;
    uint8_t ID;
    uint8_t BaudRate;
} XL320;

/**
 * @brief Initialisation du module
 * @param uart : Liaison série utilisée pour communiquer avec le module
 * @param ID : Adresse du module
 * @param BR : Vitesse de communication du module
 * @return Adresse de la structure
 */
void XL320_Init(XL320* xl320, UART_HandleTypeDef* uart, uint8_t ID, uint8_t BaudRate);

/**
 * @brief Attribution d'une nouvelle adresse et baudrate au module
 * @param xl320 : Structure XL320
 * @param ID : Nouvel ID du module
 * @param BR : Nouvelle vitesse de communication
 */
void XL320_ReProg(XL320* xl320, uint8_t ID, uint8_t BaudRate);

/**
 * @brief Définition de l'échelle d'angle que peut atteindre le module
 * @param xl320 : Structure XL320
 * @param min : Angle minimal 0° min
 * @param man : Angle maximal 300° max
 */
void XL320_setAngleRange(XL320* xl320, float minAngle, float maxAngle);

/**
 * @brief Permet de choisir le mode de contrôle
 * @param xl320 : Structure XL320
 * @param mode : WHEEL_MODE ou JOINT_MODE
 */
void XL320_setControlMode(XL320* xl320, uint8_t mode);

/**
 * @brief Définition de la température maximale
 * @param xl320 : Structure XL320
 * @param temp : Température maximale
 */
void XL320_setMaxTemperature(XL320* xl320, uint8_t temperature);

/**
 * @brief Définition de l'échelle de tension
 * @param xl320 : Structure XL320
 * @param min : Tension minimale en V limité 6V
 * @param man : Tension maximale en V limité 8.4V
 */
void XL320_setVoltageRange(XL320* xl320, uint8_t minVoltage, uint8_t maxVoltage);

/**
 * @brief Définition du couple maximal du module
 * @param xl320 : Structure XL320
 * @param max : Couple maximal en pourcentage
 */
void XL320_setMaxTorque(XL320* xl320, float maxTorque);

/**
 * @brief Activation du couple ou non
 * @param xl320 : Structure XL320
 * @param state : TRUE : activation du couple
 * 				  FALSE : désactivation du couple
 */
void XL320_EnableTorque(XL320* xl320, uint8_t state);

/**
 * @brief Activation de la LED
 * @param xl320 : Structure XL320
 * @param state : 000 : OFF
 *				  001 : Rouge
 *				  010 :	Vert
 *				  100 : Bleu
 *				  011 : Jaune
 *				  110 : Cyan
 *				  101 : Violet
 *				  111 : Blanc
 */
void XL320_EnableLED(XL320* xl320, uint8_t state);

/**
 * @brief Récupération le numéro de série du module
 * @param xl320 : Structure XL320
 * @return Numéro de série
 */
uint16_t XL320_getModelNumber(XL320* xl320);

/**
 * @brief Récupération de la version du Firmware du module
 * @param xl320 : structure XL320
 * @return Version du Firmware
 */
uint8_t XL320_getFirmwareVersion(XL320* xl320);

/**
 * @biref Récupération de la posistion actuelle du servo
 * @param xl320 : Structure XL320
 * @return Position du servo
 */
uint16_t XL320_getPosition(XL320* xl320);

/**
 * @brief Définition d'une position objectif au robot
 * @param xl320 : Structure XL320
 * @param angle : Angle que l'on souhaite attribuer au servo
 */
void XL320_setPosition(XL320* xl320, float angle);

/**
 * @brief Définition de la vitesse de déplacement
 * @param xl320 : Structure XL320
 * @param rpm : Révolution par minute (compris entre 1-114 tr/min)
 */
void XL320_setMovingSpeed(XL320* xl320, float rpm);





/**
 * @brief Envoie une trame qui contient 1 octet
 * @param xl320 : structure XL320
 * @param data : la donnée que l'on souhaite envoyer
 */
void XL320_sendTram1Byte(XL320* xl320, uint8_t reg, uint8_t data);

/**
 * @brief Envoie une trame qui contient 2 octets
 * @param xl320 : structure XL320
 * @param data : la donnée que l'on souhaite envoyer
 */
void XL320_sendTram2Byte(XL320* xl320, uint8_t reg, uint16_t data);

/**
 * @brief Permet de lire un registre
 * @param xl320 : structure XL320
 * @param reg : registre que l'on souhaite lire
 * @return retourne l'octet lu
 */
uint8_t XL320_readTram1Byte(XL320* xl320, uint8_t reg);

/**
 * @brief permet de lire un registre
 * @param xl320 : structure XL320
 * @param reg : registre que l'on souhaite lire
 * @return retourne les 2 octets lus
 */
uint16_t XL320_readTram2Byte(XL320* xl320, uint8_t reg);

/**
 * @brief permet d'envoyer 1 octet
 * @param xl320 : structure XL320
 * @param data : la donnée que l'on souhaite envoyer
 */
void XL320_sendData(XL320* xl320, uint8_t size, uint8_t instruction, uint8_t numParameters, ...);

/**
 * @brief permet de calculer le checksum
 * @param id : Identifiant du capteur
 * @param length : la taille de la trame
 * @param instruction : instruction que l'on souhaite utiliser
 * @param reg : registre que l'on souhaite utilisé
 * @param param1 : donnée
 * @param param2 : donnée égale à 0 si 1 octet attendu par la commande
 * @return le checksum
 */
uint8_t XL320_calculateChecksum(uint8_t id, uint8_t length, uint8_t instruction, uint8_t reg, uint8_t param1, uint8_t param2);

/**
 * @brief Permet de vérifier si le module est bien connecté
 * @param xl320 : structure XL320
 * @return TRUE : module connecté | FALSE : module non connecté
 */
int8_t XL320_pingModule(XL320* xl320);

/**
 * @brief permet de contrôler s'il y a une erreur
 * @param data : la valeur retourné par la fonction readData
 * @return un octet qui qui décrit l'ensemble des erreurs
 *
 *			bit 7 : pas de module connecté
 * 			bit 6 : Erreur d'instruction
 * 			bit 5 : Charge trop importante
 * 			bit 4 : Mauvais calcul du checksum
 * 			bit 3 : Instruction inconnue
 * 			bit 2 : Température maximale atteinte
 * 		    bit 1 : Angle souhaité n'est pas compris dans l'intervalle
 * 			bit 0 : La tension n'est pas comprise dans l'intervalle
 */
int8_t XL320_errorControl(uint8_t data);

unsigned short update_crc(unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size);

#endif /* XL320_H_ */
