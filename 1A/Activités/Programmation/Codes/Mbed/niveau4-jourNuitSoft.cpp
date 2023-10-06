#include "mbed.h"

//Niveau 4 - Jour, Nuit, verison soft
//Mission : Faire varier l’intensité de la LED émise à l’aide d’un potentiomètre

AnalogIn potPin(PA_0); 
PwmOut ledPin(PB_3);  

int main() {
    while (true) {
        float potValue = potPin.read();  
        
        ledPin.write(potValue);  
        ThisThread::sleep_for(10ms); 
    }
}

//Avec ce code on voit que la LED est à son intensité maximale avant que le potentiomètre soit tourné à son maximum.
//Ça mérite une optimisation non ? Je vous laisse méditer...


//Ceci est une proposition de correction
//Donc il existe pleins d'autres façons de coder et d'arriver à une solution
//À vous de trouver celle qui vous plaira !
