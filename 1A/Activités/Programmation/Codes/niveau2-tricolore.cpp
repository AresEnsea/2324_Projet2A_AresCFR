#include "mbed.h"

//Niveau 2 - Tricolore 
//Mission : Changer de manière successive l’état des 3 LEDs

DigitalOut redLed(PA_10);
DigitalOut yellowLed(PB_5);
DigitalOut greenLed(PA_8);

int main()
{
    while (true) {
        redLed = 1;
        yellowLed = 0;
        greenLed = 0;
        ThisThread::sleep_for(1000ms);

        redLed = 0;
        yellowLed = 1;
        greenLed = 0;
        ThisThread::sleep_for(1000ms);

        redLed = 0;
        yellowLed = 0;
        greenLed = 1;
        ThisThread::sleep_for(1000ms);

    }
}


//Ceci est une proposition de correction
//Donc il existe pleins d'autres façons de coder et d'arriver à une solution
//À vous de trouver celle qui vous plaira !
