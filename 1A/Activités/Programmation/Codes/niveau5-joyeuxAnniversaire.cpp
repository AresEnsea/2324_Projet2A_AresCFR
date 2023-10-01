#include "mbed.h"

//Niveau 5 - ♪ Joyeux anniversaire ♪
//Mission : Jouer « Joyeux anniversaire » lorsque le bouton est appuyé

PwmOut buzzerPin(PB_3);  
DigitalIn buttonPin(PB_5, PullDown); 

//J'utilise des "define" pour rendre mon tableau de fréquences plus lisible

#define DO 262
#define RE 294
#define MI 330
#define FA 349
#define SOL 392
#define LA 440
#define LAd 466
#define DO2 524

#define SIZE 25

int frequencies[SIZE] = {
    DO, DO, RE, DO, FA, MI,
    DO, DO, RE, DO, SOL, FA,
    DO, DO, DO2, LA, FA, MI, RE,
    LAd, LAd, LA, FA, SOL, FA
};

int durations[SIZE] = {
    400, 200, 500, 500, 500, 900,
    400, 200, 500, 500, 500, 900,
    400, 200, 500, 500, 500, 500, 900,
    400, 200, 500, 500, 500, 900
};

void tone(int frequency) {
    buzzerPin.period(1.0 / frequency);
    buzzerPin.write(0.5);

}

int main() {
    while (true) {
        int buttonState = buttonPin.read();
        if (buttonState == 1) {
            for (int i = 0; i < SIZE; i++) {
                tone(frequencies[i]);
                ThisThread::sleep_for(durations[i]);  
                buzzerPin.write(0.0);
            }
        }
    }
}


//Ceci est une proposition de correction
//Donc il existe pleins d'autres façons de coder et d'arriver à une solution
//À vous de trouver celle qui vous plaira !
