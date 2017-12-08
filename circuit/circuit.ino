#include "pumpng.h"

PumpNg musclePump(5, 4, 3, 6);

const int killPin = 39;


void setup() {
  Serial.begin(9600); 
  Serial.println("Gravity and Grace starting");
  musclePump.init();

  //pinMode(killPin, INPUT);
}

void loop() {
    musclePump.inflate();
    delay(3000);
    musclePump.stop();
    delay(3000);
}

