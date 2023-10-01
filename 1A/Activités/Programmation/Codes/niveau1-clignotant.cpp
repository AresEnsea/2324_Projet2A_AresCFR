#include "mbed.h"

//Niveau 1 - CLignotant
//Mission : Faire clignoter la LED en changeant son état toutes les secondes

DigitalOut ledPin(PA_10);

int main()
{
    while (true) {
        ledPin = 1;
        ThisThread::sleep_for(1000ms);

        ledPin = 0;
        ThisThread::sleep_for(1000ms);

    }
}


//Ceci est une proposition de correction
//Donc il existe pleins d'autres façons de coder et d'arriver à une solution
//À vous de trouver celle qui vous plaira !