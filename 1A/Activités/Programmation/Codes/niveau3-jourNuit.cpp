#include "mbed.h"

//Niveau 3 - Jour, Nuit, Jour...
//Mission : Commander l’allumage de la LED grâce à un bouton

DigitalOut ledPin(PA_10);
DigitalIn buttonPin(PB_5, PullDown);

//Définir une résistance de pull-down permet de maintenir l'état du bouton-poussoir à 0 lorsqu'il n'est pas pressé.
//En faisant cela, on peut se passer de la résistance que l'on a mise entre le bouton-poussoir et la masse. 

int main()
{
    while (true) {
        int buttonState = buttonPin.read();

        if (buttonState == 1){
            ledPin = 1;
        }
        else{
            ledPin = 0;
        }

    }
}


//Ceci est une proposition de correction
//Donc il existe pleins d'autres façons de coder et d'arriver à une solution
//À vous de trouver celle qui vous plaira !
