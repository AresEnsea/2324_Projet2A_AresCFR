#define DO 262
#define RE 294
#define MI 330
#define FA 349
#define SOL 392
#define LA 440
#define LAd 466
#define DO2 524

#define SIZE 25

const int buzzerPin = 2;
const int buttonPin = 4;

int frequences[SIZE] = {
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

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH){
    happyBirthday();
  }

     Serial.println(buttonState);
}


void happyBirthday(){
  for (int i = 0; i < SIZE; i++) {
    tone(buzzerPin, frequences[i]);
    delay(durations[i]);
    noTone(buzzerPin);
  }
}
  





